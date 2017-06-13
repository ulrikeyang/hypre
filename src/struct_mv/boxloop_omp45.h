/*BHEADER**********************************************************************
 * Copyright (c) 2008,  Lawrence Livermore National Security, LLC.
 * Produced at the Lawrence Livermore National Laboratory.
 * This file is part of HYPRE.  See file COPYRIGHT for details.
 *
 * HYPRE is free software; you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License (as published by the Free
 * Software Foundation) version 2.1 dated February 1999.
 *
 * $Revision$
 ***********************************************************************EHEADER*/

/******************************************************************************
 *
 * Header info for the BoxLoop
 *
 *****************************************************************************/

/*--------------------------------------------------------------------------
 * BoxLoop macros:
 *--------------------------------------------------------------------------*/

#ifndef HYPRE_NEWBOXLOOP_HEADER
#define HYPRE_NEWBOXLOOP_HEADER

#include "omp.h"

/* stringification:
 * _Pragma(string-literal), so we need to cast argument to a string
 * The three dots as last argument of the macro tells compiler that this is a variadic macro. 
 * I.e. this is a macro that receives variable number of arguments. 
 */
#define HYPRE_STR(s...) #s
#define HYPRE_XSTR(s...) HYPRE_STR(s)
/* concatenation:
 */
#define HYPRE_CONCAT2(x, y) x ## _ ## y
#define HYPRE_XCONCAT2(x, y) HYPRE_CONCAT2(x, y)

#define HYPRE_CONCAT3(x, y, z) x ## _ ## y ## _ ## z
#define HYPRE_XCONCAT3(x, y, z) HYPRE_CONCAT3(x, y, z)

/* if use OMP 4.5 default team size and number of teams */
#define AUTO_OMP_TEAM 

#ifndef AUTO_OMP_TEAM
/* omp team size (aka. gpu block size) */
#define hypre_gpu_block_size 512
/* the max number of omp teams */
#define hypre_max_num_blocks 1000000
#endif

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   BOX LOOPS [TEAM DISTRIBUTE VERSION]
   !!! NOTE: THIS CODE ONLY WORKS FOR DIM <= 3 !!!
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
#define hypre_BoxLoop0For() 
#define hypre_BoxLoop1For(i1) 
#define hypre_BoxLoop2For(i1, i2) 
#define hypre_BoxLoop3For(i1, i2, i3) 
#define hypre_BoxLoop4For(i1, i2, i3, i4) 

#define hypre_BoxLoopGetIndex    zypre_BoxLoopGetIndex  
#define hypre_BoxLoopSetOneBlock() ; 
#define hypre_BoxLoopBlock()       0

#define hypre_BoxLoop0Begin  zypre_omp4_dist_BoxLoop0Begin
#define hypre_BoxLoop0End    zypre_omp4_dist_BoxLoop0End
#define hypre_BoxLoop1Begin  zypre_omp4_dist_BoxLoop1Begin
#define hypre_BoxLoop1End    zypre_omp4_dist_BoxLoop1End
#define hypre_BoxBoundaryCopyBegin  zypre_omp4_dist_BoxLoop1_v2_Begin
#define hypre_BoxBoundaryCopyEnd    zypre_omp4_dist_BoxLoop1_v2_End
#define hypre_BoxDataExchangeBegin  zypre_omp4_dist_BoxLoop2_v2_Begin
#define hypre_BoxDataExchangeEnd    zypre_omp4_dist_BoxLoop2_v2_End
#define hypre_BoxLoop2Begin  zypre_omp4_dist_BoxLoop2Begin
#define hypre_BoxLoop2End    zypre_omp4_dist_BoxLoop2End
#define hypre_BoxLoop3Begin  zypre_omp4_dist_BoxLoop3Begin
#define hypre_BoxLoop3_SAME_STRIDE_Begin  zypre_omp4_dist_BoxLoop3_SAME_STRIDE_Begin
#define hypre_BoxLoop3End    zypre_omp4_dist_BoxLoop3End
#define hypre_BoxLoop4Begin  zypre_omp4_dist_BoxLoop4Begin
#define hypre_BoxLoop4End    zypre_omp4_dist_BoxLoop4End
/* reductions */
#define hypre_newBoxLoop1ReductionBegin   zypre_omp4_dist_Red_BoxLoop1Begin
#define hypre_newBoxLoop1ReductionEnd    zypre_omp4_dist_Red_BoxLoop1End
#define hypre_newBoxLoop2ReductionBegin   zypre_omp4_dist_Red_BoxLoop2Begin
#define hypre_newBoxLoop2ReductionEnd     zypre_omp4_dist_Red_BoxLoop2End

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * host code: declare variables used in the box loop
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
#define zypre_omp4_BoxLoopDeclareInit_0(ndim, loop_size) \
HYPRE_Int hypre__ndim = ndim, hypre__tot = 1, hypre__thread; \
/* loop size */ \
HYPRE_Int hypre__loop_size_0, hypre__loop_size_1, hypre__loop_size_2; \
if (hypre__ndim > 0) { hypre__loop_size_0 = loop_size[0];  hypre__tot *= hypre__loop_size_0; } \
if (hypre__ndim > 1) { hypre__loop_size_1 = loop_size[1];  hypre__tot *= hypre__loop_size_1; } \
if (hypre__ndim > 2) { hypre__loop_size_2 = loop_size[2];  hypre__tot *= hypre__loop_size_2; }

#ifdef AUTO_OMP_TEAM
#define TEAM_CLAUSE
#define zypre_omp4_BoxLoopDeclareInit(ndim, loop_size) zypre_omp4_BoxLoopDeclareInit_0(ndim, loop_size)
#else
#define TEAM_CLAUSE num_teams(num_blocks) thread_limit(block_size)
#define zypre_omp4_BoxLoopDeclareInit(ndim, loop_size) zypre_omp4_BoxLoopDeclareInit_0(ndim, loop_size) \
/* GPU block numbers and dimensions */ \
HYPRE_Int block_size = hypre_gpu_block_size; \
HYPRE_Int num_blocks = hypre_min(hypre_max_num_blocks, (hypre__tot + hypre_gpu_block_size - 1) / hypre_gpu_block_size);
#endif


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * host code: declare and initialize variables for box k
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
#define zypre_omp4_BoxKDeclareInitBody(j, k, startk, dboxk, stridek) \
   HYPRE_XCONCAT3(hypre__stride,j,k) = stridek[j]; \
/* precompute some entities used in the parallel for loop */ \
   HYPRE_XCONCAT3(hypre__box_start_imin,j,k) = startk[j] - dboxk->imin[j]; \
   HYPRE_XCONCAT3(hypre__box_imax_imin,j,k) = dboxk->imax[j] - dboxk->imin[j] + 1;


#define zypre_omp4_BoxKDeclareInit(k, startk, dboxk, stridek)\
/* start - imin */ \
HYPRE_Int HYPRE_XCONCAT3(hypre__box_start_imin,0,k), HYPRE_XCONCAT3(hypre__box_start_imin,1,k), HYPRE_XCONCAT3(hypre__box_start_imin,2,k); \
/* imax - imin + 1 */ \
HYPRE_Int HYPRE_XCONCAT3(hypre__box_imax_imin,0,k), HYPRE_XCONCAT3(hypre__box_imax_imin,1,k), HYPRE_XCONCAT3(hypre__box_imax_imin,2,k); \
/* stride */ \
HYPRE_Int HYPRE_XCONCAT3(hypre__stride,0,k), HYPRE_XCONCAT3(hypre__stride,1,k), HYPRE_XCONCAT3(hypre__stride,2,k); \
/*if (hypre__ndim > 0)*/ { zypre_omp4_BoxKDeclareInitBody(0, k, startk, dboxk, stridek) } \
  if (hypre__ndim > 1)   { zypre_omp4_BoxKDeclareInitBody(1, k, startk, dboxk, stridek) } \
  if (hypre__ndim > 2)   { zypre_omp4_BoxKDeclareInitBody(2, k, startk, dboxk, stridek) } \

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * map clause
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
#define MAP_CLAUSE1 
#define MAP_CLAUSE2 
#define MAP_CLAUSE3 
#define MAP_CLAUSE4 

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * if clause
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
#define IF_CLAUSE if (hypre__global_offload)


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * device code for BoxLoop 1, set i1
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
#define zypre_omp4_BoxLoopSet1Body(j, i1) \
/* */ \
hypre__i = hypre__J % HYPRE_XCONCAT2(hypre__loop_size,j); \
/* once */ \
hypre__i_1 = hypre__i * HYPRE_XCONCAT3(hypre__stride,j,1) + HYPRE_XCONCAT3(hypre__box_start_imin,j,1);\
/* once */ \
i1 += hypre__i_1 * hypre__I_1; \
/* once */ \
hypre__I_1 *= HYPRE_XCONCAT3(hypre__box_imax_imin,j,1); \
/* */ \
hypre__J /= HYPRE_XCONCAT2(hypre__loop_size,j);


#define zypre_omp4_BoxLoopSet1(i1) \
HYPRE_Int hypre__I_1, hypre__i, hypre__i_1, hypre__J, i1; \
hypre__I_1 = 1;  hypre__J = hypre__thread;  i1 = 0; \
/*if (hypre__ndim > 0)*/ { zypre_omp4_BoxLoopSet1Body(0, i1) } \
  if (hypre__ndim > 1)   { zypre_omp4_BoxLoopSet1Body(1, i1) } \
  if (hypre__ndim > 2)   { zypre_omp4_BoxLoopSet1Body(2, i1) }


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * device code for BoxLoop 2, set i1, i2
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
#define zypre_omp4_BoxLoopSet2Body(j, i1, i2) \
/* */ \
hypre__i = hypre__J % HYPRE_XCONCAT2(hypre__loop_size,j); \
/* twice */ \
hypre__i_1 = hypre__i * HYPRE_XCONCAT3(hypre__stride,j,1) + HYPRE_XCONCAT3(hypre__box_start_imin,j,1);\
hypre__i_2 = hypre__i * HYPRE_XCONCAT3(hypre__stride,j,2) + HYPRE_XCONCAT3(hypre__box_start_imin,j,2);\
/* twice */ \
i1 += hypre__i_1 * hypre__I_1; \
i2 += hypre__i_2 * hypre__I_2; \
/* twice */ \
hypre__I_1 *= HYPRE_XCONCAT3(hypre__box_imax_imin,j,1); \
hypre__I_2 *= HYPRE_XCONCAT3(hypre__box_imax_imin,j,2); \
/* */ \
hypre__J /= HYPRE_XCONCAT2(hypre__loop_size,j);


#define zypre_omp4_BoxLoopSet2(i1, i2) \
HYPRE_Int hypre__I_1, hypre__I_2, hypre__i, hypre__i_1, hypre__i_2, hypre__J, i1, i2; \
hypre__I_1 = hypre__I_2 = 1;  hypre__J = hypre__thread;  i1 = i2 = 0; \
/*if (hypre__ndim > 0)*/ { zypre_omp4_BoxLoopSet2Body(0, i1, i2) } \
  if (hypre__ndim > 1)   { zypre_omp4_BoxLoopSet2Body(1, i1, i2) } \
  if (hypre__ndim > 2)   { zypre_omp4_BoxLoopSet2Body(2, i1, i2) }


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * device code for BoxLoop 3, set i1, i2, i3
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
#define zypre_omp4_BoxLoopSet3Body(j, i1, i2, i3) \
/* */ \
hypre__i = hypre__J % HYPRE_XCONCAT2(hypre__loop_size,j); \
/* 3 times */ \
hypre__i_1 = hypre__i * HYPRE_XCONCAT3(hypre__stride,j,1) + HYPRE_XCONCAT3(hypre__box_start_imin,j,1);\
hypre__i_2 = hypre__i * HYPRE_XCONCAT3(hypre__stride,j,2) + HYPRE_XCONCAT3(hypre__box_start_imin,j,2);\
hypre__i_3 = hypre__i * HYPRE_XCONCAT3(hypre__stride,j,3) + HYPRE_XCONCAT3(hypre__box_start_imin,j,3);\
/* 3 times */ \
i1 += hypre__i_1 * hypre__I_1; \
i2 += hypre__i_2 * hypre__I_2; \
i3 += hypre__i_3 * hypre__I_3; \
/* 3 times */ \
hypre__I_1 *= HYPRE_XCONCAT3(hypre__box_imax_imin,j,1); \
hypre__I_2 *= HYPRE_XCONCAT3(hypre__box_imax_imin,j,2); \
hypre__I_3 *= HYPRE_XCONCAT3(hypre__box_imax_imin,j,3); \
/* */ \
hypre__J /= HYPRE_XCONCAT2(hypre__loop_size,j);


#define zypre_omp4_BoxLoopSet3(i1, i2, i3) \
HYPRE_Int hypre__I_1, hypre__I_2, hypre__I_3, hypre__i, hypre__i_1, hypre__i_2, hypre__i_3, hypre__J, i1, i2, i3; \
hypre__I_1 = hypre__I_2 = hypre__I_3 = 1;  hypre__J = hypre__thread;  i1 = i2 = i3 = 0; \
/*if (hypre__ndim > 0)*/ { zypre_omp4_BoxLoopSet3Body(0, i1, i2, i3) } \
  if (hypre__ndim > 1)   { zypre_omp4_BoxLoopSet3Body(1, i1, i2, i3) } \
  if (hypre__ndim > 2)   { zypre_omp4_BoxLoopSet3Body(2, i1, i2, i3) }

/* - - - - - special Box 3: XXX */
#define zypre_omp4_BoxLoopSet3_SAME_STRIDE_Body(j, i1, i2, i3) \
/* */ \
hypre__i = (hypre__J % HYPRE_XCONCAT2(hypre__loop_size,j)) * HYPRE_XCONCAT3(hypre__stride,j,1); \
/* 3 times */ \
hypre__i_1 = hypre__i + HYPRE_XCONCAT3(hypre__box_start_imin,j,1);\
hypre__i_2 = hypre__i + HYPRE_XCONCAT3(hypre__box_start_imin,j,2);\
hypre__i_3 = hypre__i + HYPRE_XCONCAT3(hypre__box_start_imin,j,3);\
/* 3 times */ \
i1 += hypre__i_1 * hypre__I_1; \
i2 += hypre__i_2 * hypre__I_2; \
i3 += hypre__i_3 * hypre__I_3; \
/* 3 times */ \
hypre__I_1 *= HYPRE_XCONCAT3(hypre__box_imax_imin,j,1); \
hypre__I_2 *= HYPRE_XCONCAT3(hypre__box_imax_imin,j,2); \
hypre__I_3 *= HYPRE_XCONCAT3(hypre__box_imax_imin,j,3); \
/* */ \
hypre__J /= HYPRE_XCONCAT2(hypre__loop_size,j);


#define zypre_omp4_BoxLoopSet3_SAME_STRIDE(i1, i2, o2, i3) \
HYPRE_Int hypre__I_1, hypre__I_2, hypre__I_3, hypre__i, hypre__i_1, hypre__i_2, hypre__i_3, hypre__J; \
hypre__I_1 = hypre__I_2 = hypre__I_3 = 1;  hypre__J = hypre__thread;  i1 = i3 = 0; i2 = o2;\
/*if (hypre__ndim > 0)*/ { zypre_omp4_BoxLoopSet3_SAME_STRIDE_Body(0, i1, i2, i3) } \
  if (hypre__ndim > 1)   { zypre_omp4_BoxLoopSet3_SAME_STRIDE_Body(1, i1, i2, i3) } \
  if (hypre__ndim > 2)   { zypre_omp4_BoxLoopSet3_SAME_STRIDE_Body(2, i1, i2, i3) }


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * device code for BoxLoop 4, set i1, i2, i3, i4
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
#define zypre_omp4_BoxLoopSet4Body(j, i1, i2, i3, i4) \
/* */ \
hypre__i = hypre__J % HYPRE_XCONCAT2(hypre__loop_size,j); \
/* 4 times */ \
hypre__i_1 = hypre__i * HYPRE_XCONCAT3(hypre__stride,j,1) + HYPRE_XCONCAT3(hypre__box_start_imin,j,1);\
hypre__i_2 = hypre__i * HYPRE_XCONCAT3(hypre__stride,j,2) + HYPRE_XCONCAT3(hypre__box_start_imin,j,2);\
hypre__i_3 = hypre__i * HYPRE_XCONCAT3(hypre__stride,j,3) + HYPRE_XCONCAT3(hypre__box_start_imin,j,3);\
hypre__i_4 = hypre__i * HYPRE_XCONCAT3(hypre__stride,j,4) + HYPRE_XCONCAT3(hypre__box_start_imin,j,4);\
/* 4 times */ \
i1 += hypre__i_1 * hypre__I_1; \
i2 += hypre__i_2 * hypre__I_2; \
i3 += hypre__i_3 * hypre__I_3; \
i4 += hypre__i_4 * hypre__I_4; \
/* 4 times */ \
hypre__I_1 *= HYPRE_XCONCAT3(hypre__box_imax_imin,j,1); \
hypre__I_2 *= HYPRE_XCONCAT3(hypre__box_imax_imin,j,2); \
hypre__I_3 *= HYPRE_XCONCAT3(hypre__box_imax_imin,j,3); \
hypre__I_4 *= HYPRE_XCONCAT3(hypre__box_imax_imin,j,4); \
/* */ \
hypre__J /= HYPRE_XCONCAT2(hypre__loop_size,j);


#define zypre_omp4_BoxLoopSet4(i1, i2, i3, i4) \
HYPRE_Int hypre__I_1, hypre__I_2, hypre__I_3, hypre__I_4, hypre__i, hypre__i_1, hypre__i_2, hypre__i_3, hypre__i_4, hypre__J, i1, i2, i3, i4; \
hypre__I_1 = hypre__I_2 = hypre__I_3 = hypre__I_4 = 1;  hypre__J = hypre__thread;  i1 = i2 = i3 = i4 = 0; \
/*if (hypre__ndim > 0)*/ { zypre_omp4_BoxLoopSet4Body(0, i1, i2, i3, i4) } \
  if (hypre__ndim > 1)   { zypre_omp4_BoxLoopSet4Body(1, i1, i2, i3, i4) } \
  if (hypre__ndim > 2)   { zypre_omp4_BoxLoopSet4Body(2, i1, i2, i3, i4) }



/* - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * BoxLoop 0
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
#define zypre_omp4_dist_BoxLoop0Begin(ndim, loop_size) \
{\
   /* host code: */ \
   zypre_omp4_BoxLoopDeclareInit(ndim, loop_size) \
   /* device code: */ \
   _Pragma (HYPRE_XSTR(omp target teams distribute parallel for IF_CLAUSE MAP_CLAUSE1 TEAM_CLAUSE)) \
   for (hypre__thread=0; hypre__thread<hypre__tot; hypre__thread++) \
   {\



#define zypre_omp4_dist_BoxLoop0End(...) \
   }\
}


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * BoxLoop 1
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

#define zypre_omp4_dist_BoxLoop1Begin(ndim, loop_size, dbox1, start1, stride1, i1) \
{\
   /* host code: */ \
   zypre_omp4_BoxLoopDeclareInit(ndim, loop_size) \
   zypre_omp4_BoxKDeclareInit(1, start1, dbox1, stride1) \
   /* device code: */ \
   _Pragma (HYPRE_XSTR(omp target teams distribute parallel for IF_CLAUSE MAP_CLAUSE1 TEAM_CLAUSE)) \
   for (hypre__thread=0; hypre__thread<hypre__tot; hypre__thread++) \
   {\
      zypre_omp4_BoxLoopSet1(i1)



#define zypre_omp4_dist_BoxLoop1End(...)\
   }\
}


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * BoxLoop 2
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

#define zypre_omp4_dist_BoxLoop2Begin(ndim, loop_size, dbox1, start1, stride1, i1, dbox2, start2, stride2, i2) \
{\
   /* host code: */ \
   zypre_omp4_BoxLoopDeclareInit(ndim, loop_size) \
   zypre_omp4_BoxKDeclareInit(1, start1, dbox1, stride1) \
   zypre_omp4_BoxKDeclareInit(2, start2, dbox2, stride2) \
   /* device code: */ \
   _Pragma (HYPRE_XSTR(omp target teams distribute parallel for IF_CLAUSE MAP_CLAUSE2 TEAM_CLAUSE)) \
   for (hypre__thread=0; hypre__thread<hypre__tot; hypre__thread++) \
   {\
      zypre_omp4_BoxLoopSet2(i1, i2)



#define zypre_omp4_dist_BoxLoop2End(...)\
   }\
}


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * BoxLoop 3
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
#define zypre_omp4_dist_BoxLoop3Begin(ndim, loop_size, \
      dbox1, start1, stride1, i1, \
      dbox2, start2, stride2, i2, \
      dbox3, start3, stride3, i3) \
{\
   /* host code: */ \
   zypre_omp4_BoxLoopDeclareInit(ndim, loop_size) \
   zypre_omp4_BoxKDeclareInit(1, start1, dbox1, stride1) \
   zypre_omp4_BoxKDeclareInit(2, start2, dbox2, stride2) \
   zypre_omp4_BoxKDeclareInit(3, start3, dbox3, stride3) \
   /* device code: */ \
   _Pragma (HYPRE_XSTR(omp target teams distribute parallel for IF_CLAUSE MAP_CLAUSE3 TEAM_CLAUSE)) \
   for (hypre__thread=0; hypre__thread<hypre__tot; hypre__thread++) \
   {\
      zypre_omp4_BoxLoopSet3(i1, i2, i3)
      

#define zypre_omp4_dist_BoxLoop3End(...)\
   }\
}

#define zypre_omp4_dist_BoxLoop3_SAME_STRIDE_Begin(ndim, loop_size, \
      dbox1, start1, stride1, i1, \
      dbox2, start2, stride2, i2, o2, \
      dbox3, start3, stride3, i3) \
{\
   /* host code: */ \
   zypre_omp4_BoxLoopDeclareInit(ndim, loop_size) \
   zypre_omp4_BoxKDeclareInit(1, start1, dbox1, stride1) \
   zypre_omp4_BoxKDeclareInit(2, start2, dbox2, stride2) \
   zypre_omp4_BoxKDeclareInit(3, start3, dbox3, stride3) \
   /* device code: */ \
   _Pragma (HYPRE_XSTR(omp target teams distribute parallel for IF_CLAUSE MAP_CLAUSE3 TEAM_CLAUSE)) \
   for (hypre__thread=0; hypre__thread<hypre__tot; hypre__thread++) \
   {\
      zypre_omp4_BoxLoopSet3_SAME_STRIDE(i1, i2, o2, i3)
 
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * BoxLoop 4
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
#define zypre_omp4_dist_BoxLoop4Begin(ndim, loop_size, \
      dbox1, start1, stride1, i1, \
      dbox2, start2, stride2, i2, \
      dbox3, start3, stride3, i3, \
      dbox4, start4, stride4, i4) \
{\
   /* host code: */ \
   zypre_omp4_BoxLoopDeclareInit(ndim, loop_size) \
   zypre_omp4_BoxKDeclareInit(1, start1, dbox1, stride1) \
   zypre_omp4_BoxKDeclareInit(2, start2, dbox2, stride2) \
   zypre_omp4_BoxKDeclareInit(3, start3, dbox3, stride3) \
   zypre_omp4_BoxKDeclareInit(4, start4, dbox4, stride4) \
   /* device code: */ \
   _Pragma (HYPRE_XSTR(omp target teams distribute parallel for IF_CLAUSE MAP_CLAUSE4 TEAM_CLAUSE)) \
   for (hypre__thread=0; hypre__thread<hypre__tot; hypre__thread++) \
   {\
      zypre_omp4_BoxLoopSet4(i1, i2, i3, i4)


#define zypre_omp4_dist_BoxLoop4End(...)\
   }\
}


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * BoxLoop 1 reduction
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

#define zypre_omp4_dist_Red_BoxLoop1Begin(ndim, loop_size,\
      dbox1, start1, stride1, i1, xsum) \
{\
   /* host code: */ \
   zypre_omp4_BoxLoopDeclareInit(ndim, loop_size) \
   zypre_omp4_BoxKDeclareInit(1, start1, dbox1, stride1) \
   /* xsum = 0.0; */ \
   /* device code: */ \
   _Pragma (HYPRE_XSTR(omp target teams distribute parallel for IF_CLAUSE MAP_CLAUSE1 map(tofrom: xsum) reduction(+:xsum) TEAM_CLAUSE)) \
   for (hypre__thread=0; hypre__thread<hypre__tot; hypre__thread++) \
   {\
      zypre_omp4_BoxLoopSet1(i1)



#define zypre_omp4_dist_Red_BoxLoop1End(...) \
   }\
}


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * BoxLoop 2 reduction
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

#define zypre_omp4_dist_Red_BoxLoop2Begin(ndim, loop_size,\
      dbox1, start1, stride1, i1,\
      dbox2, start2, stride2, i2, xsum) \
{\
   /* host code: */ \
   zypre_omp4_BoxLoopDeclareInit(ndim, loop_size) \
   zypre_omp4_BoxKDeclareInit(1, start1, dbox1, stride1) \
   zypre_omp4_BoxKDeclareInit(2, start2, dbox2, stride2) \
   /* xsum = 0.0; */ \
   /* device code: */ \
   _Pragma (HYPRE_XSTR(omp target teams distribute parallel for IF_CLAUSE MAP_CLAUSE2 map(tofrom: xsum) reduction(+:xsum) TEAM_CLAUSE)) \
   for (hypre__thread=0; hypre__thread<hypre__tot; hypre__thread++) \
   {\
      zypre_omp4_BoxLoopSet2(i1, i2)



#define zypre_omp4_dist_Red_BoxLoop2End(...)\
   }\
}




/* - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 *                     v2
 * host code: declare and initialize variables for box k
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
#define zypre_omp4_BoxKDeclareInit_v2(k, stridek)\
/* stridek[0,1,2] */ \
HYPRE_Int HYPRE_XCONCAT3(hypre__stride,0,k), HYPRE_XCONCAT3(hypre__stride,1,k), HYPRE_XCONCAT3(hypre__stride,2,k); \
/*if (hypre__ndim > 0)*/ { HYPRE_XCONCAT3(hypre__stride,0,k) = stridek[0]; } \
  if (hypre__ndim > 1)   { HYPRE_XCONCAT3(hypre__stride,1,k) = stridek[1]; } \
  if (hypre__ndim > 2)   { HYPRE_XCONCAT3(hypre__stride,2,k) = stridek[2]; } \

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 *                     v2
 * device code for BoxLoop 1, set i1
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
#define zypre_omp4_BoxLoopSet1Body_v2(j, i1) \
i1 += ( hypre__J % HYPRE_XCONCAT2(hypre__loop_size,j) ) * HYPRE_XCONCAT3(hypre__stride,j,1);\
hypre__J /= HYPRE_XCONCAT2(hypre__loop_size,j);


#define zypre_omp4_BoxLoopSet1_v2(i1, idx) \
HYPRE_Int hypre__J, i1, idx; \
idx = hypre__J = hypre__thread; i1 = 0; \
/*if (hypre__ndim > 0)*/ { zypre_omp4_BoxLoopSet1Body_v2(0, i1) } \
  if (hypre__ndim > 1)   { zypre_omp4_BoxLoopSet1Body_v2(1, i1) } \
  if (hypre__ndim > 2)   { zypre_omp4_BoxLoopSet1Body_v2(2, i1) }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 *                      v2: Basic
 * BoxLoop 1
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
#define zypre_omp4_dist_BoxLoop1_v2_Begin(ndim, loop_size, stride1, i1, idx) \
{\
   /* host code: */ \
   zypre_omp4_BoxLoopDeclareInit(ndim, loop_size) \
   zypre_omp4_BoxKDeclareInit_v2(1, stride1) \
   /* device code: */ \
   _Pragma (HYPRE_XSTR(omp target teams distribute parallel for IF_CLAUSE MAP_CLAUSE1 TEAM_CLAUSE)) \
   for (hypre__thread=0; hypre__thread<hypre__tot; hypre__thread++) \
   {\
      zypre_omp4_BoxLoopSet1_v2(i1, idx)



#define zypre_omp4_dist_BoxLoop1_v2_End(...)\
   }\
}


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 *                     v2
 * device code for BoxLoop 2, set i1, i2
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
#define zypre_omp4_BoxLoopSet2Body_v2(j, i1, i2) \
hypre__i = hypre__J % HYPRE_XCONCAT2(hypre__loop_size,j); \
/* twice */ \
i1 += hypre__i * HYPRE_XCONCAT3(hypre__stride,j,1); \
i2 += hypre__i * HYPRE_XCONCAT3(hypre__stride,j,2); \
hypre__J /= HYPRE_XCONCAT2(hypre__loop_size,j);


#define zypre_omp4_BoxLoopSet2_v2(i1, i2) \
HYPRE_Int hypre__i, hypre__J, i1, i2; \
hypre__J = hypre__thread;  i1 = i2 = 0; \
/*if (hypre__ndim > 0)*/ { zypre_omp4_BoxLoopSet2Body_v2(0, i1, i2) } \
  if (hypre__ndim > 1)   { zypre_omp4_BoxLoopSet2Body_v2(1, i1, i2) } \
  if (hypre__ndim > 2)   { zypre_omp4_BoxLoopSet2Body_v2(2, i1, i2) }


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 *                      v2: Basic
 * BoxLoop 2
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

#define zypre_omp4_dist_BoxLoop2_v2_Begin(ndim, loop_size, stride1, i1, stride2, i2) \
{\
   /* host code: */ \
   zypre_omp4_BoxLoopDeclareInit(ndim, loop_size) \
   zypre_omp4_BoxKDeclareInit_v2(1, stride1) \
   zypre_omp4_BoxKDeclareInit_v2(2, stride2) \
   /* device code: */ \
   _Pragma (HYPRE_XSTR(omp target teams distribute parallel for IF_CLAUSE MAP_CLAUSE2 TEAM_CLAUSE)) \
   for (hypre__thread=0; hypre__thread<hypre__tot; hypre__thread++) \
   {\
      zypre_omp4_BoxLoopSet2_v2(i1, i2)



#define zypre_omp4_dist_BoxLoop2_v2_End(...)\
   }\
}

#endif
