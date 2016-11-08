/*******************************************************************************
 * Name            : threshold_filter.cc
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
#include "include/threshold_filter.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
* Member Functions
******************************************************************************/
PixelBuffer* ThresholdFilter::ApplyFilter(PixelBuffer* original_buffer) {
  PixelBuffer* result_buffer;
  ColorData temp_color;
  result_buffer = new PixelBuffer(original_buffer->width(),
                                  original_buffer->height(),
                                  original_buffer->background_color());
  for (int x = 0; x < result_buffer->width(); x++)
    for (int y = 0; y < result_buffer->height(); y++) {
      temp_color = original_buffer->get_pixel(x, y);
      if (temp_color.red() > FilterArg())
        temp_color.red(1);
      else
        temp_color.red(0);
      if (temp_color.green() > FilterArg())
        temp_color.green(1);
      else
        temp_color.green(0);
      if (temp_color.blue() > FilterArg())
        temp_color.blue(1);
      else
        temp_color.blue(0);
      result_buffer->set_pixel(x, y, temp_color);
    }
  return result_buffer;
}
} /* namespace image_tools */
