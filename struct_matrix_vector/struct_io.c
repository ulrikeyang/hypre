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
 * Functions for scanning and printing "box-dimensioned" data.
 *
 *****************************************************************************/

#include "headers.h"

/*--------------------------------------------------------------------------
 * hypre_PrintBoxArrayData
 *--------------------------------------------------------------------------*/

void
hypre_PrintBoxArrayData( FILE             *file,
                       hypre_BoxArray     *box_array,
                       hypre_BoxArray     *data_space,
                       int               num_values,
                       double           *data       )
{
   hypre_Box         *box;
   hypre_Box         *data_box;

   int              data_box_volume;
   int              datai;

   hypre_Index        loop_size;
   hypre_IndexRef     start;
   hypre_Index        stride;

   int              i, j;
   int              loopi, loopj, loopk;

   /*----------------------------------------
    * Print data
    *----------------------------------------*/

   hypre_SetIndex(stride, 1, 1, 1);

   hypre_ForBoxI(i, box_array)
   {
      box      = hypre_BoxArrayBox(box_array, i);
      data_box = hypre_BoxArrayBox(data_space, i);

      start = hypre_BoxIMin(box);
      data_box_volume = hypre_BoxVolume(data_box);

      hypre_GetBoxSize(box, loop_size);
      hypre_BoxLoop1(loopi, loopj, loopk, loop_size,
                   data_box, start, stride, datai,
                   {
                      for (j = 0; j < num_values; j++)
                      {
                         fprintf(file, "%d: (%d, %d, %d; %d) %e\n", i,
                                 hypre_IndexX(start) + loopi,
                                 hypre_IndexY(start) + loopj,
                                 hypre_IndexZ(start) + loopk,
                                 j, data[datai + j*data_box_volume]);
                      }
                   });

      data += num_values*data_box_volume;
   }
}

/*--------------------------------------------------------------------------
 * hypre_ReadBoxArrayData
 *--------------------------------------------------------------------------*/

void
hypre_ReadBoxArrayData( FILE             *file,
                      hypre_BoxArray     *box_array,
                      hypre_BoxArray     *data_space,
                      int               num_values,
                      double           *data       )
{
   hypre_Box         *box;
   hypre_Box         *data_box;

   int              data_box_volume;
   int              datai;

   hypre_Index        loop_size;
   hypre_IndexRef     start;
   hypre_Index        stride;

   int              i, j, idummy;
   int              loopi, loopj, loopk;

   /*----------------------------------------
    * Read data
    *----------------------------------------*/

   hypre_SetIndex(stride, 1, 1, 1);

   hypre_ForBoxI(i, box_array)
   {
      box      = hypre_BoxArrayBox(box_array, i);
      data_box = hypre_BoxArrayBox(data_space, i);

      start = hypre_BoxIMin(box);
      data_box_volume = hypre_BoxVolume(data_box);

      hypre_GetBoxSize(box, loop_size);
      hypre_BoxLoop1(loopi, loopj, loopk, loop_size,
                   data_box, start, stride, datai,
                   {
                      for (j = 0; j < num_values; j++)
                      {
                         fscanf(file, "%d: (%d, %d, %d; %d) %le\n", &idummy,
                                &idummy,
                                &idummy,
                                &idummy,
                                &idummy, &data[datai + j*data_box_volume]);
                      }
                   });

      data += num_values*data_box_volume;
   }
}
