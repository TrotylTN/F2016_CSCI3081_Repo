/*******************************************************************************
 * Name            : t_stamp.cc
 * Project         : image_tools
 * Module          : Tool
 * Description     : Header file for Stamp class
 * Copyright       : 2016 CSCI3081W Group A01. All rights reserved.
 * Creation Date   : 11/09/16
 * Original Author : Group-A01
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/t_stamp.h"
#include <string>
#include "include/color_data.h"
#include "include/pixel_buffer.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
TStamp::TStamp(void) : stamp_mask_(nullptr) {
  drag_status(false);
}

TStamp::~TStamp(void) {
  if (this->stamp_mask_ != nullptr) {
    delete this->stamp_mask_;
  }
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
ColorData TStamp::color_blend_math(
    float mask_pixel_amount,
    const ColorData& tool_color,
    const ColorData& current_color,
    const ColorData& background_color) {
  return ColorData();
}

void TStamp::stamp_mask(PixelBuffer *stamp) {
  if (this->stamp_mask_ != nullptr) {
    delete this->stamp_mask_;
  }
  this->stamp_mask_ = stamp;
}

void TStamp::ApplyToBuffer(
    int tool_x,
    int tool_y,
    ColorData tool_color,
    PixelBuffer* buffer) {
  if (stamp_mask_ == nullptr) {
    printf("Stamp not initialized.\n");
    return;
  }

  int left_bound = std::max(tool_x-stamp_mask_->width()/2, 0);
  int right_bound = std::min(tool_x+stamp_mask_->width()/2,
                             buffer->width()-1);
  int lower_bound = std::max(tool_y-stamp_mask_->height()/2, 0);
  int upper_bound = std::min(tool_y+stamp_mask_->height()/2,
                             buffer->height()-1);

  #pragma omp for
  for (int y = lower_bound; y < upper_bound; y++) {
    for (int x = left_bound; x < right_bound; x++) {
      int mask_x = x - (tool_x - stamp_mask_->width()/2);
      int mask_y = y - (tool_y - stamp_mask_->height()/2);
      ColorData c = stamp_mask_->get_pixel(mask_x, mask_y);
      if (c.alpha() > 0.0)
        buffer->set_pixel(x, y, c);
    }
  }
}

}  /* namespace image_tools */
