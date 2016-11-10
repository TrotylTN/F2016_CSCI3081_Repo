/*******************************************************************************
 * Name            : f_rgb_filter.cc
 * Project         : FlashPhoto
 * Module          : filter_manager
 * Description     : Implementation for RGBFilter class
 * Copyright       : 2016 CSCI3081W Group A01. All rights reserved.
 * Creation Date   : Thu Nov 10 14:11:26 2016
 * Original Author : Tiannan Zhou
 *
 ******************************************************************************/

/*******************************************************************************
* Includes
******************************************************************************/
#include "include/f_rgb_filter.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
* Member Functions
******************************************************************************/

void RGBFilter::Resize(float incoming_size,
                       float r_amount,
                       float g_amount,
                       float b_amount) {
  this->channel_color_red_ = r_amount;
  this->channel_color_green_ = g_amount;
  this->channel_color_blue_ = b_amount;
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
  result_buffer = new PixelBuffer(original_buffer->width(),
                                  original_buffer->height(),
                                  original_buffer->background_color());
  for (int x = 0; x < result_buffer->width(); x++)
    for (int y = 0; y < result_buffer->height(); y++) {
      temp_color = original_buffer->get_pixel(x, y);
      temp_color.red(temp_color.red() * this->channel_color_red_);
      temp_color.green(temp_color.green() * this->channel_color_green_);
      temp_color.blue(temp_color.blue() * this->channel_color_blue_);
      result_buffer->set_pixel(x, y, temp_color);
    }
  return result_buffer;
}
} /* namespace image_tools */
