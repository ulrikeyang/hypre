/*BHEADER**********************************************************************
 * (c) 1997   The Regents of the University of California
 *
 * See the file COPYRIGHT_and_DISCLAIMER for a complete copyright
 * notice, contact person, and disclaimer.
 *
 * $Revision$
 *********************************************************************EHEADER*/
/******************************************************************************
 *
 * Constructors and destructors for stencil structure.
 *
 *****************************************************************************/

#include "headers.h"

/*--------------------------------------------------------------------------
 * hypre_NewStructStencil
 *--------------------------------------------------------------------------*/

hypre_StructStencil *
hypre_NewStructStencil( int         dim,
                      int         size,
                      hypre_Index  *shape )
{
   hypre_StructStencil   *stencil;

   stencil = hypre_TAlloc(hypre_StructStencil, 1);

   hypre_StructStencilShape(stencil) = shape;
   hypre_StructStencilSize(stencil)  = size;
   hypre_StructStencilDim(stencil)   = dim;

   return stencil;
}

/*--------------------------------------------------------------------------
 * hypre_FreeStructStencil
 *--------------------------------------------------------------------------*/

void 
hypre_FreeStructStencil( hypre_StructStencil *stencil )
{
   if (stencil)
   {
      hypre_TFree(hypre_StructStencilShape(stencil));
      hypre_TFree(stencil);
   }
}

/*--------------------------------------------------------------------------
 * hypre_StructStencilElementRank
 *    Returns the rank of the `stencil_element' in `stencil'.
 *    If the element is not found, a -1 is returned.
 *--------------------------------------------------------------------------*/

int
hypre_StructStencilElementRank( hypre_StructStencil *stencil,
                              hypre_Index          stencil_element )
{
   hypre_Index  *stencil_shape;
   int         rank;
   int         i;

   rank = -1;
   stencil_shape = hypre_StructStencilShape(stencil);
   for (i = 0; i < hypre_StructStencilSize(stencil); i++)
   {
      if ((hypre_IndexX(stencil_shape[i]) == hypre_IndexX(stencil_element)) &&
          (hypre_IndexY(stencil_shape[i]) == hypre_IndexY(stencil_element)) &&
          (hypre_IndexZ(stencil_shape[i]) == hypre_IndexZ(stencil_element))   )
      {
         rank = i;
         break;
      }
   }

   return rank;
}

/*--------------------------------------------------------------------------
 * hypre_SymmetrizeStructStencil:
 *    Computes a new "symmetrized" stencil.
 *
 *    An integer array called `symm_elements' is also set up.  A non-negative
 *    value of `symm_elements[i]' indicates that the `i'th stencil element
 *    is a "symmetric element".  That is, this stencil element is the
 *    transpose element of an element that is not a "symmetric element".
 *--------------------------------------------------------------------------*/

int
hypre_SymmetrizeStructStencil( hypre_StructStencil  *stencil,
                             hypre_StructStencil **symm_stencil_ptr,
                             int               **symm_elements_ptr )
{
   hypre_Index          *stencil_shape = hypre_StructStencilShape(stencil);
   int                 stencil_size  = hypre_StructStencilSize(stencil); 

   hypre_StructStencil  *symm_stencil;
   hypre_Index          *symm_stencil_shape;
   int                 symm_stencil_size;
   int                *symm_elements;

   int                 no_symmetric_stencil_element;
   int                 i, j, d;

   int                 ierr = 0;

   /*------------------------------------------------------
    * Copy stencil elements into `symm_stencil_shape'
    *------------------------------------------------------*/

   symm_stencil_shape = hypre_CTAlloc(hypre_Index, 2*stencil_size);
   for (i = 0; i < stencil_size; i++)
   {
      hypre_CopyIndex(stencil_shape[i], symm_stencil_shape[i]);
   }

   /*------------------------------------------------------
    * Create symmetric stencil elements and `symm_elements'
    *------------------------------------------------------*/

   symm_elements = hypre_CTAlloc(int, 2*stencil_size);
   for (i = 0; i < 2*stencil_size; i++)
      symm_elements[i] = -1;

   symm_stencil_size = stencil_size;
   for (i = 0; i < stencil_size; i++)
   {
      if (symm_elements[i] < 0)
      {
         /* note: start at i to handle "center" element correctly */
         no_symmetric_stencil_element = 1;
         for (j = i; j < stencil_size; j++)
         {
            if ( (hypre_IndexX(symm_stencil_shape[j]) ==
                  -hypre_IndexX(symm_stencil_shape[i])  ) &&
                 (hypre_IndexY(symm_stencil_shape[j]) ==
                  -hypre_IndexY(symm_stencil_shape[i])  ) &&
                 (hypre_IndexZ(symm_stencil_shape[j]) ==
                  -hypre_IndexZ(symm_stencil_shape[i])  )   )
            {
               /* only "off-center" elements have symmetric entries */
               if (i != j)
                  symm_elements[j] = i;
               no_symmetric_stencil_element = 0;
            }
         }

         if (no_symmetric_stencil_element)
         {
            /* add symmetric stencil element to `symm_stencil' */
            for (d = 0; d < 3; d++)
            {
               hypre_IndexD(symm_stencil_shape[symm_stencil_size], d) =
                  -hypre_IndexD(symm_stencil_shape[i], d);
            }
	       
            symm_elements[symm_stencil_size] = i;
            symm_stencil_size++;
         }
      }
   }

   symm_stencil = hypre_NewStructStencil(hypre_StructStencilDim(stencil),
                                       symm_stencil_size, symm_stencil_shape);

   *symm_stencil_ptr  = symm_stencil;
   *symm_elements_ptr = symm_elements;

   return ierr;
}

