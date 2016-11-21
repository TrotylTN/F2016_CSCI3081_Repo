/*******************************************************************************
 * Name            : t_blur.cc
 * Project         : image_tools
 * Module          : Tool
 * Description     : Header file for Blur class
 * Copyright       : 2016 CSCI3081W Group A01. All rights reserved.
 * Creation Date   : 11/15/16
 * Original Author : Yu Xian Ang
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <assert.h>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include "include/t_blur.h"
#include "include/color_data.h"
#include "include/pixel_buffer.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
ColorData TBlur::ApplyBlur(PixelBuffer *buffer, int x, int y, int matrix_size) {
  int shift_length = matrix_size / 2;
  float tot_cell = 2 * shift_length * shift_length + 2 * shift_length + 1;
  float value_in_cell = 1.0 / tot_cell;
  ColorData temp_color(0, 0, 0, 0);
  for (int i = 0; i < matrix_size; i++) {
    for (int j = 0; j < matrix_size; j++) {
      int dis = std::abs(i - shift_length) + std::abs(j - shift_length);
      if (dis > shift_length) {
        continue;
      }
      int s_x = x + i - shift_length;
      int s_y = y + j - shift_length;
      if (s_x >= 0 && s_y >= 0 &&
          s_x < buffer->width() &&
          s_y < buffer->height()) {
        temp_color = buffer->get_pixel(s_x, s_y) *
                       value_in_cell + temp_color;
      } else {
        temp_color = buffer->get_pixel(x, y) * value_in_cell + temp_color;
      }
    }
  }
  return temp_color;
}

void TBlur::ApplyToBuffer(
    int tool_x,
    int tool_y,
    ColorData tool_color,
    PixelBuffer* buffer) {
  Mask* blur_mask = mask();
  assert(blur_mask);

  int left_bound = std::max(tool_x-blur_mask->width()/2, 0);
  int right_bound = std::min(tool_x+blur_mask->width()/2,
                             buffer->width()-1);
  int lower_bound = std::max(tool_y-blur_mask->height()/2, 0);
  int upper_bound = std::min(tool_y+blur_mask->height()/2,
                             buffer->height()-1);

  #pragma omp for
  for (int y = lower_bound; y <= upper_bound; y++) {
    for (int x = left_bound; x <= right_bound; x++) {
      int mask_x = x - (tool_x-blur_mask->width()/2);
      int mask_y = y - (tool_y-blur_mask->height()/2);
      float mask_value = blur_mask->value(mask_x, mask_y);
      int matrix_size = (static_cast<int>(mask_value * max_blur_size_)) * 2 + 1;
      if (matrix_size <= 0.0) {
        continue;
      }
      buffer->set_pixel(x, y, ApplyBlur(buffer, x, y, matrix_size));
    }
  }
}

}  /* namespace image_tools */
