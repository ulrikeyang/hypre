#include "spmv.h"
#include <cuda_runtime.h>
#include "cusparse.h"

#if DOUBLEPRECISION
texture<int2, 1> texRef;
#else
texture<REAL, 1> texRef;
#endif


__global__
void csr_v_k(int n, int *d_ia, int *d_ja, REAL *d_a, REAL *d_y) {
/*------------------------------------------------------------*
 *               CSR spmv-vector kernel
 *  shared memory reduction, texture memory fetching
 *          FULL-Warp (32 threads) per row
 *------------------------------------------------------------*/
  // num of full-warps
  int nw = gridDim.x*BLOCKDIM/WARP;
  // full warp id
  int wid = (blockIdx.x*BLOCKDIM+threadIdx.x)/WARP;
  // thread lane in each full warp
  int lane = threadIdx.x & (WARP-1);
  // full warp lane in each block
  int wlane = threadIdx.x/WARP;
  // shared memory for patial result
  volatile __shared__ REAL r[BLOCKDIM+16];
  volatile __shared__ int startend[BLOCKDIM/WARP][2];
  for (int row = wid; row < n; row += nw) {
    // row start and end point
    if (lane < 2)
      startend[wlane][lane] = d_ia[row+lane];
    int p = startend[wlane][0];
    int q = startend[wlane][1];
    REAL sum = 0.0;
    for (int i=p+lane; i<q; i+=WARP) {

      int2 t = tex1Dfetch(texRef, d_ja[i]);
      sum += d_a[i] * __hiloint2double(t.y, t.x);

    }
    // parallel reduction
    r[threadIdx.x] = sum;
    r[threadIdx.x] = sum = sum + r[threadIdx.x+16];
    r[threadIdx.x] = sum = sum + r[threadIdx.x+8];
    r[threadIdx.x] = sum = sum + r[threadIdx.x+4];
    r[threadIdx.x] = sum = sum + r[threadIdx.x+2];
    r[threadIdx.x] = sum = sum + r[threadIdx.x+1];
    if (lane == 0)
      d_y[row] = r[threadIdx.x];
  }
}

/*-------------------------------------------------------*/
void spmv_csr_vector(struct csr_t *csr, REAL *x, REAL *y) {
  int *d_ia, *d_ja, i;
  REAL *d_a, *d_x, *d_y;
  int n = csr->nrows;
  int nnz = csr->ia[n];
  double t1,t2;
/*---------- Device Memory */
  cudaMalloc((void **)&d_ia, (n+1)*sizeof(int));
  cudaMalloc((void **)&d_ja, nnz*sizeof(int));
  cudaMalloc((void **)&d_a, nnz*sizeof(REAL));
  cudaMalloc((void **)&d_x, n*sizeof(REAL));
  cudaMalloc((void **)&d_y, n*sizeof(REAL));
/*---------- Memcpy */
  cudaMemcpy(d_ia, csr->ia, (n+1)*sizeof(int),
  cudaMemcpyHostToDevice);
  cudaMemcpy(d_ja, csr->ja, nnz*sizeof(int),
  cudaMemcpyHostToDevice);
  cudaMemcpy(d_a, csr->a, nnz*sizeof(REAL),
  cudaMemcpyHostToDevice);
  cudaMemcpy(d_x, x, n*sizeof(REAL),
  cudaMemcpyHostToDevice);
/*--------- texture binding */
  size_t offset;
#if DOUBLEPRECISION
  cudaBindTexture(&offset, texRef, d_x, n*sizeof(int2));
#else
  cudaBindTexture(&offset, texRef, d_x, n*sizeof(float));
#endif
  assert(offset == 0);
/*-------- set spmv kernel */
/*-------- num of half-warps per block */
  int hwb = BLOCKDIM/HALFWARP;
  int gDim = min(MAXTHREADS/BLOCKDIM, (n+hwb-1)/hwb);
  int bDim = BLOCKDIM;
  //printf("CSR<<<%4d, %3d>>>  ",gDim,bDim);
/*-------- start timing */
  t1 = wall_timer();
  for (i=0; i<REPEAT; i++) {
    //cudaMemset((void *)d_y, 0, n*sizeof(REAL));
    csr_v_k<<<gDim, bDim>>>(n, d_ia, d_ja, d_a, d_y);
  }
/*-------- Barrier for GPU calls */
  cudaThreadSynchronize();
/*-------- stop timing */
  t2 = wall_timer()-t1;
/*--------------------------------------------------*/
  printf("\n=== [GPU] CSR-vector Kernel ===\n");
  printf("  Number of Threads <%d*%d>\n",gDim,bDim);
  printf("  %.2f ms, %.2f GFLOPS, ",
  t2*1e3,2*nnz/t2/1e9*REPEAT);
/*-------- copy y to host mem */
  cudaMemcpy(y, d_y, n*sizeof(REAL),
  cudaMemcpyDeviceToHost);
/*--------- unbind texture */
  cudaUnbindTexture(texRef);
/*---------- CUDA free */
  cudaFree(d_ia);
  cudaFree(d_ja);
  cudaFree(d_a);
  cudaFree(d_x);
  cudaFree(d_y);
}

/*-----------------------------------------------*/
void cuda_init(int argc, char **argv) {
  int deviceCount, dev;
  cudaGetDeviceCount(&deviceCount);
  printf("=========================================\n");
  if (deviceCount == 0)
    printf("There is no device supporting CUDA\n");

  for (dev = 0; dev < deviceCount; ++dev) {
    cudaDeviceProp deviceProp;
    cudaGetDeviceProperties(&deviceProp, dev);
    if (dev == 0) {
      if (deviceProp.major == 9999 && deviceProp.minor == 9999)
        printf("There is no device supporting CUDA.\n");
      else if (deviceCount == 1)
        printf("There is 1 device supporting CUDA\n");
      else
        printf("There are %d devices supporting CUDA\n", deviceCount);
    }
    printf("\nDevice %d: \"%s\"\n", dev, deviceProp.name);
    printf("  Major revision number:          %d\n",
           deviceProp.major);
    printf("  Minor revision number:          %d\n",
           deviceProp.minor);
    printf("  Total amount of global memory:  %.2f GB\n",
           deviceProp.totalGlobalMem/1e9);
  }
  dev = 0;
  cudaSetDevice(dev);
  cudaDeviceProp deviceProp;
  cudaGetDeviceProperties(&deviceProp, dev);
  printf("\nRunning on Device %d: \"%s\"\n", dev, deviceProp.name);
  printf("=========================================\n");
}

/*---------------------------------------------------*/
void cuda_check_err() {
  cudaError_t cudaerr = cudaGetLastError() ;
  if (cudaerr != cudaSuccess)
    printf("error: %s\n",cudaGetErrorString(cudaerr));
}

void spmv_cusparse_csr(struct csr_t *csr, REAL *x, REAL *y) {
  int n = csr->nrows;
  int nnz = csr->ia[n];
  int *d_ia, *d_ja, i;
  REAL *d_a, *d_x, *d_y;
  double t1, t2;
  REAL done = 1.0, dzero = 0.0;
/*------------------- allocate Device Memory */
  cudaMalloc((void **)&d_ia, (n+1)*sizeof(int));
  cudaMalloc((void **)&d_ja, nnz*sizeof(int));
  cudaMalloc((void **)&d_a, nnz*sizeof(REAL));
  cudaMalloc((void **)&d_x, n*sizeof(REAL));
  cudaMalloc((void **)&d_y, n*sizeof(REAL));
/*------------------- Memcpy */
  cudaMemcpy(d_ia, csr->ia, (n+1)*sizeof(int),
  cudaMemcpyHostToDevice);
  cudaMemcpy(d_ja, csr->ja, nnz*sizeof(int),
  cudaMemcpyHostToDevice);
  cudaMemcpy(d_a, csr->a, nnz*sizeof(REAL),
  cudaMemcpyHostToDevice);
  cudaMemcpy(d_x, x, n*sizeof(REAL),
  cudaMemcpyHostToDevice);

  cusparseStatus_t status;
  cusparseHandle_t handle=0;
  cusparseMatDescr_t descr=0;

  /* initialize cusparse library */
  status= cusparseCreate(&handle);
  if (status != CUSPARSE_STATUS_SUCCESS) {
     printf("CUSPARSE Library initialization failed\n");
     exit(1);
  }

  /* create and setup matrix descriptor */
  status= cusparseCreateMatDescr(&descr);
  if (status != CUSPARSE_STATUS_SUCCESS) {
     printf("Matrix descriptor initialization failed\n");
     exit(1);
  }
  cusparseSetMatType(descr,CUSPARSE_MATRIX_TYPE_GENERAL);
  cusparseSetMatIndexBase(descr,CUSPARSE_INDEX_BASE_ZERO);

/*-------- start timing */
  t1 = wall_timer();
  for (i=0; i<REPEAT; i++) {
#if DOUBLEPRECISION
    status= cusparseDcsrmv(handle, CUSPARSE_OPERATION_NON_TRANSPOSE, n, n, nnz,
                           &done, descr, d_a, d_ia, d_ja,
                           d_x, &dzero, d_y);
#else
    status= cusparseScsrmv(handle, CUSPARSE_OPERATION_NON_TRANSPOSE, n, n, nnz,
                           &done, descr, d_a, d_ia, d_ja,
                           d_x, &dzero, d_y);
#endif
    if (status != CUSPARSE_STATUS_SUCCESS) {
      printf("Matrix-vector multiplication failed\n");
      exit(1);
    }
  }
/*-------- barrier for GPU calls */
  cudaThreadSynchronize();
/*-------- stop timing */
  t2 = wall_timer()-t1;
/*--------------------------------------------------*/
  printf("\n=== [GPU] CUSPARSE CSR Kernel ===\n");
  printf("  %.2f ms, %.2f GFLOPS, ",
  t2*1e3,2*nnz/t2/1e9*REPEAT);
/*-------- copy y to host mem */
  cudaMemcpy(y, d_y, n*sizeof(REAL),
  cudaMemcpyDeviceToHost);
/*--------- CUDA free */
  cudaFree(d_ia);
  cudaFree(d_ja);
  cudaFree(d_a);
  cudaFree(d_x);
  cudaFree(d_y);

  /* destroy matrix descriptor */
  status = cusparseDestroyMatDescr(descr);
  descr = 0;
  if (status != CUSPARSE_STATUS_SUCCESS) {
     printf("Matrix descriptor destruction failed\n");
     exit(1);
  }

  /* destroy handle */
  status = cusparseDestroy(handle);
  handle = 0;
  if (status != CUSPARSE_STATUS_SUCCESS) {
     printf("CUSPARSE Library release of resources failed\n");
     exit(1);
  }
}
