/*******************************************************************************
 * Name            : f_edge_matrix.cc
 * Project         : FlashPhoto
 * Module          : filter_manager
 * Description     : Implementation for EdgeMatrix class
 * Copyright       : 2016 CSCI3081W Group A01. All rights reserved.
 * Creation Date   : Sun Nov 5 20:42:51 2016
 * Original Author : Tiannan Zhou
 *
 ******************************************************************************/

/*******************************************************************************
* Includes
******************************************************************************/
#include "include/f_edge_matrix.h"
#include <cstdio>

using namespace std;
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
* Member Functions
******************************************************************************/
void EdgeMatrix::Resize(float incoming_size, float detect_type) {
  this->detect_type_ = (int)detect_type;
  int n = (int) incoming_size / 2;
  int new_matrix_size = n * 2 + 1;
  float value_in_cell;
  std::vector <std::vector<float> > new_matrix;
  new_matrix.resize(new_matrix_size, std::vector<float>(new_matrix_size));
  if (detect_type == -1) {
    for (int i = 0; i < new_matrix_size; i++) {
      new_matrix[0][i] = -1;
      new_matrix[i][0] = -1;
      new_matrix[new_matrix_size - 1][i] = -1;
      new_matrix[i][new_matrix_size - 1] = -1;
    }
    new_matrix[n][n] = 8;
  }
  else {
    value_in_cell = detect_type / 5.0;
    for (int i = 0; i < new_matrix_size; i++) {
      new_matrix[0][i] = -value_in_cell;
      new_matrix[i][0] = -value_in_cell;
      new_matrix[new_matrix_size - 1][i] = -value_in_cell;
      new_matrix[i][new_matrix_size - 1] = -value_in_cell;
    }
    new_matrix[n][n] = 1 + 8 * value_in_cell;
  }
  for (int i = 0; i < new_matrix_size; i++) {
    for (int j = 0; j < new_matrix_size; j++)
      printf("%f ", new_matrix[i][j]);
    printf("\n");
  }

  FilterMatrix::MatrixSize(new_matrix_size);
  FilterMatrix::Matrix(new_matrix);
}

} /* namespace image_tools */
