/*******************************************************************************
 * Name            : f_quan_filter.cc
 * Project         : FlashPhoto
 * Module          : filter_manager
 * Description     : Implementation for QuanFilter class
 * Copyright       : 2016 CSCI3081W Group A01. All rights reserved.
 * Creation Date   : Thu Nov 10 19:41:36 2016
 * Original Author : Tiannan Zhou
 *
 ******************************************************************************/

/*******************************************************************************
* Includes
******************************************************************************/
#include "include/f_quan_filter.h"
#include <cmath>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/

namespace image_tools {

/*******************************************************************************
* Member Functions
******************************************************************************/

void QuanFilter::Resize(float incoming_size, float bins) {
  this->quantize_bins_ = static_cast<int>(bins);
  int new_matrix_size = static_cast<int>(incoming_size);
  std::vector <std::vector<float> > new_matrix;
  new_matrix.resize(new_matrix_size, std::vector<float>(new_matrix_size));
  new_matrix[0][0] = 1;
  FilterMatrix::MatrixSize(new_matrix_size);
  FilterMatrix::Matrix(new_matrix);
}

PixelBuffer* QuanFilter::ApplyMatrix(PixelBuffer* original_buffer) {
  PixelBuffer* result_buffer;
  ColorData temp_color;
  float detail_gap = 1.0 / (this->quantize_bins_ - 1);
  int multi_of_gap;
  result_buffer = new PixelBuffer(original_buffer->width(),
                                  original_buffer->height(),
                                  original_buffer->background_color());
  for (int x = 0; x < result_buffer->width(); x++)
    for (int y = 0; y < result_buffer->height(); y++) {
      temp_color = original_buffer->get_pixel(x, y);
      multi_of_gap = round(temp_color.red() / detail_gap);
      temp_color.red(multi_of_gap * detail_gap);
      multi_of_gap = round(temp_color.green() / detail_gap);
      temp_color.green(multi_of_gap * detail_gap);
      multi_of_gap = round(temp_color.blue() / detail_gap);
      temp_color.blue(multi_of_gap * detail_gap);
      result_buffer->set_pixel(x, y, temp_color);
    }
  result_buffer->ValidPixel();
  return result_buffer;
}
} /* namespace image_tools */
