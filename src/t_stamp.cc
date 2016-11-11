/*******************************************************************************
 * Name            : t_highlighter.cc
 * Project         : BrushWork
 * Module          : Tool
 * Description     : Implementation of highlighter tool class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
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
TStamp::TStamp(void) {
    stamp_mask(NULL);
    drag_status(false);
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
ColorData TStamp::color_blend_math(
    float mask_pixel_amount,
    const ColorData& tool_color,
    const ColorData& current_color,
    const ColorData& background_color) {
  // TBC
}

/* Implemented wrongly */
void TStamp::ApplyToBuffer(
    int tool_x,
    int tool_y,
    ColorData tool_color,
    PixelBuffer* buffer) {
  if (stamp_mask_ == NULL) {
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
/*      float mask_value = mask_->value(mask_x, mask_y);
      ColorData current = buffer->get_pixel(x, y);

      // Because we interpolate the pixels, colors overlap
      // and increase intensity quickly. We found that cubing
      // the mask intensity compensated for this.
      float slimmed_mask_value = powf(mask_value, 3);
      ColorData c = color_blend_math(
          slimmed_mask_value,
          tool_color,
          current,
          buffer->background_color());
*/
      ColorData c = stamp_mask_->get_pixel(mask_x, mask_y);
      if (!(c == buffer->background_color() ||
            c == stamp_mask_->background_color()))
        buffer->set_pixel(x, y, c);
    }
  }
}

}  /* namespace image_tools */
