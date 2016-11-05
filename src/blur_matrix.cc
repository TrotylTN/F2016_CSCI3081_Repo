/*******************************************************************************
 * Name            : blur_matrix.cc
 * Project         : FlashPhoto
 * Module          : filter_manager
 * Description     : Implementation for BlurMatrix class
 * Copyright       : 2016 CSCI3081W Group A01. All rights reserved.
 * Creation Date   : Sat Nov 5 16:26:01 2016
 * Original Author : Tiannan Zhou
 *
 ******************************************************************************/

/*******************************************************************************
* Includes
******************************************************************************/
#include "include/blur_matrix.h"
#include <cstdio>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
* Member Functions
******************************************************************************/
void BlurMatrix::Resize(float incoming_size) {
  int n = (int) incoming_size;
  int new_matrix_size = n * 2 + 1;
  std::vector <std::vector<int> > new_matrix;
  new_matrix.resize(new_matrix_size, std::vector<int>(new_matrix_size));
  float tot_cell = 2 * n * n + 2 * n + 1;
  float value_in_cell = 1.0 / tot_cell;
  for (int i = 0; i < new_matrix_size; i++)
  {
    printf("\n");
    for (int j = 0; j < new_matrix_size; j++)
    {
      int dis = std::abs(i - n) + std::abs(j - n);
      if (dis <= n)
        new_matrix[i][j] = value_in_cell;
      else
        new_matrix[i][j] = 0;
      printf("%d \n", new_matrix[i][j]);
    }
  }
  FilterMatrix::SetMatrixSize(new_matrix_size);
  FilterMatrix::SetMatrix(new_matrix);
}

} /* namespace image_tools */
