/*******************************************************************************
 * Name            : f_threshold_filter.cc
 * Project         : FlashPhoto
 * Module          : filter_manager
 * Description     : Implementation for ThresholdFilter class
 * Copyright       : 2016 CSCI3081W Group A01. All rights reserved.
 * Creation Date   : Mon Nov 7 20:27:51 2016
 * Original Author : Tiannan Zhou
 *
 ******************************************************************************/

/*******************************************************************************
* Includes
******************************************************************************/
#include "include/f_threshold_filter.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
* Member Functions
******************************************************************************/

void ThresholdFilter::Resize(float incoming_size, float threshold_amount) {
  this->threshold_amount_ = threshold_amount;
  int new_matrix_size = int(incoming_size);
  std::vector <std::vector<float> > new_matrix;
  new_matrix.resize(new_matrix_size, std::vector<float>(new_matrix_size));
  new_matrix[0][0] = 1;
  FilterMatrix::MatrixSize(new_matrix_size);
  FilterMatrix::Matrix(new_matrix);
}

PixelBuffer* ThresholdFilter::ApplyMatrix(PixelBuffer* original_buffer) {
  PixelBuffer* result_buffer;
  ColorData temp_color;
  result_buffer = new PixelBuffer(original_buffer->width(),
                                  original_buffer->height(),
                                  original_buffer->background_color());
  for (int x = 0; x < result_buffer->width(); x++)
    for (int y = 0; y < result_buffer->height(); y++) {
      temp_color = original_buffer->get_pixel(x, y);
      if (temp_color.red() > this->threshold_amount_)
        temp_color.red(1);
      else
        temp_color.red(0);
      if (temp_color.green() > this->threshold_amount_)
        temp_color.green(1);
      else
        temp_color.green(0);
      if (temp_color.blue() > this->threshold_amount_)
        temp_color.blue(1);
      else
        temp_color.blue(0);
      result_buffer->set_pixel(x, y, temp_color);
    }
  return result_buffer;
}
} /* namespace image_tools */
