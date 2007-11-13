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
/* Declaration of the Grid and its access functions data structure      */
/* ******************************************************************** */
/* Author        : Charles Tong (LLNL) and Raymond Tuminaro (SNL)       */
/* Date          : March, 1999                                          */
/* ******************************************************************** */

#ifndef __MLGRIDFUNC__
#define __MLGRIDFUNC__

#include "ml_common.h"
#include "ml_defs.h"
#include "ml_memory.h"

typedef struct ML_GridFunc_Struct ML_GridFunc;

/* ******************************************************************** */
/* definition of the data structure for Grid and its access functions   */
/* -------------------------------------------------------------------- */

struct ML_GridFunc_Struct
{
   int  ML_id;
   int  ML_MaxElmntVert;

   int  (*USR_grid_get_dimension)( void * );
   int  (*USR_grid_get_nvertices)( void * );
   int  (*USR_grid_get_nelements)( void * );
   ml_big_int  (*USR_grid_get_element_global_num)( void *, int );
   int  (*USR_grid_get_element_nvertices)( void *, int );
   int  (*USR_grid_get_element_vlist)( void *, int, int * );
   int  (*USR_grid_get_vertex_global_num)( void *, int );
   int  (*USR_grid_get_vertex_coordinate)( void *, int, double *);

   int  (*USR_compute_basis_coefficients)(void*,int,double*,int,double*,int*);

   int  (*USR_grid_get_element_volumes)(void*,int,int*,double*);
   int  (*USR_grid_get_element_matrix)(void*,int,double**);
   int  (*USR_grid_get_element_nullspace)(void*,int,double*);

};

/* ******************************************************************** */
/* definition of the functions                                          */
/* -------------------------------------------------------------------- */

#ifndef ML_CPP
#ifdef __cplusplus
extern "C"
{
#endif
#endif

extern int ML_GridFunc_Create( ML_GridFunc ** );
extern int ML_GridFunc_Destroy( ML_GridFunc ** );
extern int ML_GridFunc_Check( ML_GridFunc * );
extern int ML_GridFunc_Set_MaxVertPerElmnt(ML_GridFunc *, int);
#ifdef NOTSTRICT_PROTO
extern int ML_GridFunc_Set_Function(ML_GridFunc *, int, int (*func)());
#endif
extern int ML_GridFunc_Set_GetDimension(ML_GridFunc *, int (*func)(void *));
extern int ML_GridFunc_Set_GetNVert(ML_GridFunc *, int (*func)(void *));
extern int ML_GridFunc_Set_GetNElmnts(ML_GridFunc *, int (*func)(void *));
extern int ML_GridFunc_Set_GetElmntGlobalNum(ML_GridFunc*,ml_big_int(*func)(void *, int));
extern int ML_GridFunc_Set_GetElmntNVert(ML_GridFunc*,int(*func)(void *, int));
extern int ML_GridFunc_Set_GetElmntVertList(ML_GridFunc *, int (*func)(void *, int, int *));
extern int ML_GridFunc_Set_GetVertGlobalNum(ML_GridFunc*,int (*func)(void *, int));
extern int ML_GridFunc_Set_GetVertCoordinate(ML_GridFunc*,int (*func)(void *, int, double *));
extern int ML_GridFunc_Set_ComputeBasisCoef(ML_GridFunc *, int (*func)(void*,int,double*,int,double*,int*));
extern int ML_GridFunc_Set_GetElmntVolumes(ML_GridFunc *, int (*func)(void*,int,int*,double*));
extern int ML_GridFunc_Set_GetElmntMatrix(ML_GridFunc *, int (*func)(void*,int,double**));
extern int ML_GridFunc_Set_GetElmntNullSpace(ML_GridFunc*,int (*func)(void*,int,double*));



int ML_compute_basis_coefficients3D(void *grid, double *coord,
				    int ncoord, double *coefs, int *coef_ptr);
int ML_compute_basis_coefficients2D(void *grid, double *coord,
				    int ncoord, double *coefs, int *coef_ptr);

#ifndef ML_CPP
#ifdef __cplusplus
}
#endif
#endif

#endif

