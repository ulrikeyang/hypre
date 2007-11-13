/*BHEADER**********************************************************************
 * Copyright (c) 2007, Lawrence Livermore National Security, LLC.
 * Produced at the Lawrence Livermore National Laboratory.
 * Written by the HYPRE team. UCRL-CODE-222953.
 * All rights reserved.
 *
 * This file is part of HYPRE (see http://www.llnl.gov/CASC/hypre/).
 * Please see the COPYRIGHT_and_LICENSE file for the copyright notice, 
 * disclaimer, contact information and the GNU Lesser General Public License.
 *
 * HYPRE is free software; you can redistribute it and/or modify it under the 
 * terms of the GNU General Public License (as published by the Free Software
 * Foundation) version 2.1 dated February 1999.
 *
 * HYPRE is distributed in the hope that it will be useful, but WITHOUT ANY 
 * WARRANTY; without even the IMPLIED WARRANTY OF MERCHANTABILITY or FITNESS 
 * FOR A PARTICULAR PURPOSE.  See the terms and conditions of the GNU General
 * Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * $Revision$
 ***********************************************************************EHEADER*/




/* ******************************************************************** */
/* See the file COPYRIGHT for a complete copyright notice, contact      */
/* person and disclaimer.                                               */        
/* ******************************************************************** */

/* ******************************************************************** */
/* Declaration of the ML RAP data structure                             */
/* ******************************************************************** */
/* Author        : Raymond Tuminaro (SNL)                               */
/* Date          : February, 1999                                       */
/* ******************************************************************** */

#ifndef _MLRAP_
#define _MLRAP_

#include "ml_common.h"
#include "ml_defs.h"
#include "ml_struct.h"
#include "ml_comminfoagx.h"

/* ******************************************************************** */
/* external function proto-types                                        */
/* -------------------------------------------------------------------- */

#ifndef ML_CPP
#ifdef __cplusplus
extern "C" {
#endif
#endif

extern void ML_convert_data_org(ML_Operator *mat, int d_org[], int *rcv,
                                int *remap, int leng, int add_or_not);

extern void ML_add_appended_rows(ML_CommInfoOP *comm_info, 
                                 ML_Operator *matrix, int orig_rows, 
                                 int total_rcvd, int appended_nzs);

extern void ML_back_to_local(ML_Operator *imatrix, ML_Operator *omatrix, 
                             int max_per_proc);

extern void ML_back_to_csrlocal(ML_Operator *imatrix, ML_Operator *omatrix,
        int max_per_proccomm);

extern int  ML_back_to_epetraCrs(ML_Operator *Mat1Mat2,  ML_Operator *Result, 
				 ML_Operator *Mat1,  ML_Operator *Mat2); 
                                  /* code is in ml_epetra_utils.h. Put the  */
                                 /* proto-type here to avoid c++ compiler on ml_rap.c */


extern void ML_exchange_rows(ML_Operator *orig, ML_Operator **appended, 
                             ML_CommInfoOP *comm_info);

extern void ML_expand_accum(int accum_size, int **accum_col, 
                            double **accum_val, int Ncols);

extern void ML_get_matrix_row(ML_Operator *input_matrix,int N_requested_rows,
                              int requested_rows[], int *allocated_space, 
                              int **columns, double **values, 
                              int row_lengths[], int index);

extern void ML_globalcsr2localcsr(ML_Operator *imatrix, int max_per_proc);

extern void ML_matmat_mult(ML_Operator *Amat, ML_Operator *Bmat, 
                           ML_Operator **Cmat);
extern void ML_2matmult(ML_Operator *Mat1, ML_Operator *Mat2,
			ML_Operator *Result, int matrix_type);

extern void ML_oldmatmat_mult(ML_Operator *Amatrix, ML_Operator *Bmatrix,
			      ML_Operator **Cmatrix);
extern void ML_get_matrow_CSR(ML_Operator *input_matrix, int N_requested_rows,
        int requested_rows[], int *allocated_space, int **columns,
        double **values, int row_lengths[], int index);
extern void ML_get_row_CSR_norow_map(ML_Operator *input_matrix, 
        int N_requested_rows, int requested_rows[], int *allocated_space, 
        int **columns, double **values, int row_lengths[], int index);

extern void ML_getrow_matvec(ML_Operator *matrix, double *vec, 
                             int Nvec, double *ovec, int *Novec);

extern void ML_rap(ML_Operator *R2mat, ML_Operator *A2mat, 
                   ML_Operator *P2mat, ML_Operator *Result,
		   int matrix_type);

extern void ML_rap_check(ML *ml, ML_Operator *RAP, ML_Operator *R,
                         ML_Operator *A, ML_Operator *P, int iNvec,
                         int oNvec);

extern void ML_CommInfoOP_GenUsingGIDExternals(int N_external, int external[], 
                                int max_per_proc, ML_Operator *omatrix);

extern void ML_sum_duplicates(int accum_col[],double accum_val[],int *Ncols);

extern int ML_determine_Brows(int start, int *end, ML_Operator *Amatrix,
		       int *rows[], int *rows_length, int *NBrows,
		       int *rows_that_fit, 
		       void   (*Agetrow)(ML_Operator *,int,int *,int *,int **,
					 double **,int *,int));



#ifndef ML_CPP
#ifdef __cplusplus
}
#endif
#endif

#define ML_matrix_type         0
#define ML_N_internal          1
#define ML_N_border            2
#define ML_N_external          3
#define ML_N_int_blk           4
#define ML_N_bord_blk          5
#define ML_N_ext_blk           6
#define ML_N_neigh             7
#define ML_total_send          8
#define ML_name                9
#define ML_internal_use        10
#define ML_N_rows              11
#define ML_neighbors           12
#define ML_rec_length          (12 +   ML_MAX_NEIGHBORS)
#define ML_send_length         (12 + 2*ML_MAX_NEIGHBORS)
#define ML_send_list           (12 + 3*ML_MAX_NEIGHBORS)
#define ML_FALSE               0
#define ML_TRUE                1

#endif
