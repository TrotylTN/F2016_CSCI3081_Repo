/*******************************************************************************
 * Name            : filter_matrix.cc
 * Project         : FlashPhoto
 * Module          : filter_manager
 * Description     : Implementation for FilterMatrix class
 * Copyright       : 2016 CSCI3081W Group A01. All rights reserved.
 * Creation Date   : Sat Nov 5 15:26:31 2016
 * Original Author : Tiannan Zhou
 *
 ******************************************************************************/

/*******************************************************************************
* Includes
******************************************************************************/
#include "include/filter_matrix.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {
/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
FilterMatrix::FilterMatrix() : matrix_size_(0), matrix_() {}
/*******************************************************************************
* Member Functions
******************************************************************************/
PixelBuffer* FilterMatrix::ApplyMatrix(PixelBuffer* original_buffer) {
  PixelBuffer* result_buffer;
  ColorData temp_color;
  result_buffer = new PixelBuffer(original_buffer->width(),
                                  original_buffer->height(),
                                  original_buffer->background_color());
  for (int x = 0; x < original_buffer->width(); x++)
    for (int y = 0; y < original_buffer->height(); y++)
    {
      temp_color = ColorData(0, 0, 0);
      int shift_length = matrix_size_ / 2;
      for (int i = 0; i < matrix_size_; i++)
        for (int j = 0; j < matrix_size_; j++)
        {
          if (matrix_[i][j] == 0)
            continue;
          int s_x = x + i - shift_length;
          int s_y = y + j - shift_length;
          if (s_x >= 0 && s_y >= 0 &&
              s_x < original_buffer->width() &&
              s_y < original_buffer->height()) {
            temp_color = original_buffer->get_pixel(s_x, s_y) *
                         matrix_[i][j] +
                         temp_color;
          }
          else {
            temp_color = ColorData() *
                         matrix_[i][j] +
                         temp_color;
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

// void Resize(float incoming_size) {}
// void Resize(float incoming_size, int args_for_resize) {}

void FilterMatrix::SetMatrixSize(int new_matrix_size) {
  this->matrix_size_ = new_matrix_size;
}

void FilterMatrix::SetMatrix(std::vector <std::vector<float> > new_matrix) {
  this->matrix_ = new_matrix;
}

} /* namespace image_tools */
