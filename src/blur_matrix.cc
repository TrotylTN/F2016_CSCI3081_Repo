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
  this->blur_type_ = blur_type;
  int n = (int) incoming_size / 2;
  int new_matrix_size = n * 2 + 1;
  std::vector <std::vector<float> > new_matrix;
  new_matrix.resize(new_matrix_size, std::vector<float>(new_matrix_size));
  if (blur_type == -1) {
    float tot_cell = 2 * n * n + 2 * n + 1;
    float value_in_cell = 1.0 / tot_cell;
    printf("$$$%f\n", value_in_cell);
    for (int i = 0; i < new_matrix_size; i++) {
      for (int j = 0; j < new_matrix_size; j++) {
        int dis = fabs(i - n) + fabs(j - n);
        if (dis <= n)
        new_matrix[i][j] = value_in_cell;
        else
        new_matrix[i][j] = 0;
      }
    }
  }
  else {
    new_matrix.clear();
  }
  FilterMatrix::SetMatrixSize(new_matrix_size);
  FilterMatrix::SetMatrix(new_matrix);
}

PixelBuffer* BlurMatrix::ApplyMatrix(PixelBuffer* original_buffer) {
  if (this->blur_type_ == -1) {
    FilterMatrix::ApplyMatrix(original_buffer);
  }
  else {
    int n = matrix_size() / 2;
    PixelBuffer* result_buffer;
    ColorData temp_color;
    float tot_cell = matrix_size();
    float value_in_cell = 1.0 / tot_cell;
    printf("$$$%f\n", value_in_cell);
    int init_x, init_y;
    int delta_x, delta_y;
    if (this->blur_type_ == 0) {
      init_x = n;
      init_y = 0;
      delta_x = 0;
      delta_y = 1;
    }
    else if (this->blur_type_ == 1) {
      init_x = 0;
      init_y = n;
      delta_x = 1;
      delta_y = 0;
    }
    else if (this->blur_type_ == 2) {
      init_x = 0;
      init_y = 0;
      delta_x = 1;
      delta_y = 1;
    }
    else if (this->blur_type_ == 3) {
      init_x = 0;
      init_y = matrix_size() - 1;
      delta_x = 1;
      delta_y = -1;
    }

    result_buffer = new PixelBuffer(original_buffer->width(),
                                    original_buffer->height(),
                                    original_buffer->background_color());

    for (int x = 0; x < original_buffer->width(); x++)
      for (int y = 0; y < original_buffer->height(); y++) {
        temp_color = ColorData(0, 0, 0);
        for (int i = 0, d_x = init_x, d_y = init_y;
             i < matrix_size();
             d_x += delta_x, d_y += delta_y, i++) {
          int s_x = x + d_x - n;
          int s_y = y + d_y - n;
          if (s_x >= 0 && s_y >= 0 &&
              s_x < original_buffer->width() &&
              s_y < original_buffer->height()) {
            temp_color = original_buffer->get_pixel(s_x, s_y) *
                         value_in_cell +
                         temp_color;
          }
          else {
            temp_color = ColorData() * value_in_cell + temp_color;
          }
        }
        if (temp_color.green() < 0)
          temp_color.green(0);
        if (temp_color.blue() < 0)
          temp_color.blue(0);
        if (temp_color.red() < 0)
          temp_color.red(0);
        if (temp_color.green() > 1)
          temp_color.green(1);
        if (temp_color.blue() > 1)
          temp_color.blue(1);
        if (temp_color.red() > 1)
          temp_color.red(1);
        result_buffer->set_pixel(x, y, temp_color);
      }
      return result_buffer;
  }
}

} /* namespace image_tools */
