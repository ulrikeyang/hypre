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




/* Copyright (2004) Sandia Corportation. Under the terms of Contract
 * DE-AC04-94AL85000, there is a non-exclusive license for use of this
 * work by or on behalf of the U.S. Government.  Export of this program
 * may require a license from the United States Government. */ 

 /* NOTICE:  The United States Government is granted for itself and others 
 * acting on its behalf a paid-up, nonexclusive, irrevocable worldwide 
 * license in ths data to reproduce, prepare derivative works, and 
 * perform publicly and display publicly.  Beginning five (5) years from 
 * July 25, 2001, the United States Government is granted for itself and 
 * others acting on its behalf a paid-up, nonexclusive, irrevocable 
 * worldwide license in this data to reproduce, prepare derivative works, 
 * distribute copies to the public, perform publicly and display 
 * publicly, and to permit others to do so.  
 * 
 * NEITHER THE UNITED STATES GOVERNMENT, NOR THE UNITED STATES DEPARTMENT 
 * OF ENERGY, NOR SANDIA CORPORATION, NOR ANY OF THEIR EMPLOYEES, MAKES 
 * ANY WARRANTY, EXPRESS OR IMPLIED, OR ASSUMES ANY LEGAL LIABILITY OR 
 * RESPONSIBILITY FOR THE ACCURACY, COMPLETENESS, OR USEFULNESS OF ANY 
 * INFORMATION, APPARATUS, PRODUCT, OR PROCESS DISCLOSED, OR REPRESENTS 
 * THAT ITS USE WOULD NOT INFRINGE PRIVATELY OWNED RIGHTS. */ 

#ifndef ML_SELF_WRAP
#define ML_SELF_WRAP

#include "ml_include.h"
#if defined(HAVE_ML_EPETRA) && defined(HAVE_ML_TEUCHOS) && defined(HAVE_ML_IFPACK)

#ifndef ML_CPP
#ifdef __cplusplus
extern "C" {
#endif
#endif

namespace Teuchos {
  class ParameterList;
}
class Epetra_Comm;

int ML_Smoother_Self(ML_Smoother *sm,int inlen,double x[],int outlen,
                     double rhs[]);

void ML_Smoother_Clean_Self(void * Self_Handle);

#ifndef ML_CPP
#ifdef __cplusplus
}
#endif
#endif

int ML_Gen_Smoother_Self(ML *ml, int Overlap, int nl, int pre_or_post, 
                         Teuchos::ParameterList& List,
                         const Epetra_Comm& Comm);

#endif
#endif
