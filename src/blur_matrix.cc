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

using namespace std;
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
* Member Functions
******************************************************************************/
void BlurMatrix::Resize(float incoming_size, int blur_type) {
  int n = (int) incoming_size;
  int new_matrix_size = n * 2 + 1;
  std::vector <std::vector<float> > new_matrix;
  new_matrix.resize(new_matrix_size, std::vector<float>(new_matrix_size));
  if (blur_type == -1) {
    float tot_cell = 2 * n * n + 2 * n + 1;
    float value_in_cell = 1.0 / tot_cell;
    printf("$$$%f\n", value_in_cell);
    for (int i = 0; i < new_matrix_size; i++) {
      printf("\n");
      for (int j = 0; j < new_matrix_size; j++) {
        int dis = fabs(i - n) + fabs(j - n);
        if (dis <= n)
        new_matrix[i][j] = value_in_cell;
        else
        new_matrix[i][j] = 0;
        printf("%f ", new_matrix[i][j]);
      }
    }
  }
  else
  {
    float tot_cell = new_matrix_size;
    float value_in_cell = 1.0 / tot_cell;
    printf("$$$%f\n", value_in_cell);
    int init_x, init_y;
    int delta_x, delta_y;
    if (blur_type == 0) {
      init_x = n;
      init_y = 0;
      delta_x = 0;
      delta_y = 1;
    }
    else if (blur_type == 1) {
      init_x = 0;
      init_y = n;
      delta_x = 1;
      delta_y = 0;
    }
    else if (blur_type == 2) {
      init_x = 0;
      init_y = 0;
      delta_x = 1;
      delta_y = 1;
    }
    else if (blur_type == 3) {
      init_x = 0;
      init_y = new_matrix_size - 1;
      delta_x = 1;
      delta_y = -1;
    }
    for (int i = 0, x = init_x, y = init_y;
         i < new_matrix_size;
         x += delta_x, y += delta_y, i++) {
      printf("x:%d y:%d \n", x, y);
      new_matrix[x][y] = value_in_cell;
    }
  }
  FilterMatrix::SetMatrixSize(new_matrix_size);
  FilterMatrix::SetMatrix(new_matrix);
}

} /* namespace image_tools */
