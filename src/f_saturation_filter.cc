/*******************************************************************************
 * Name            : f_saturation_filter.cc
 * Project         : FlashPhoto
 * Module          : filter_manager
 * Description     : Implementation for SaturationFilter class
 * Copyright       : 2016 CSCI3081W Group A01. All rights reserved.
 * Creation Date   : Wed Nov 9 17:20:16 2016
 * Original Author : Tiannan Zhou
 *
 ******************************************************************************/

/*******************************************************************************
* Includes
******************************************************************************/
#include "include/f_saturation_filter.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
* Member Functions
******************************************************************************/

void SaturationFilter::Resize(float incoming_size, float saturation_amount) {
  this->saturation_amount_ = saturation_amount;
  int new_matrix_size = int(incoming_size);
  std::vector <std::vector<float> > new_matrix;
  new_matrix.resize(new_matrix_size, std::vector<float>(new_matrix_size));
  new_matrix[0][0] = 1;
  FilterMatrix::MatrixSize(new_matrix_size);
  FilterMatrix::Matrix(new_matrix);
}

PixelBuffer* SaturationFilter::ApplyMatrix(PixelBuffer* original_buffer) {
  PixelBuffer* result_buffer;
  ColorData temp_color;
  float lum, result_lum;
  result_buffer = new PixelBuffer(original_buffer->width(),
                                  original_buffer->height(),
                                  original_buffer->background_color());
  for (int x = 0; x < result_buffer->width(); x++)
    for (int y = 0; y < result_buffer->height(); y++) {
      temp_color = original_buffer->get_pixel(x, y);
      lum = temp_color.luminance();
      result_lum = lum + (temp_color.red() - lum) * this->saturation_amount_;
      temp_color.red(result_lum);
      result_lum = lum + (temp_color.green() - lum) * this->saturation_amount_;
      temp_color.green(result_lum);
      result_lum = lum + (temp_color.blue() - lum) * this->saturation_amount_;
      temp_color.blue(result_lum);
      result_buffer->set_pixel(x, y, temp_color);
    }
  result_buffer->ValidPixel();
  return result_buffer;
}
} /* namespace image_tools */
