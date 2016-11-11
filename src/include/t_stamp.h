/*******************************************************************************
 * Name            : t_stamp.h
 * Project         : image_tools
 * Module          : Tool
 * Description     : Header file for Stamp class
 * Copyright       : 2016 Group A1. All rights reserved.
 * Creation Date   : 11/09/16
 * Original Author : 2016 Group A1
 *
 ******************************************************************************/

#ifndef SRC_INCLUDE_T_STAMP_H_
#define SRC_INCLUDE_T_STAMP_H_

/*******************************************************************************
 * Include Definitions
 ******************************************************************************/
#include <string>
#include "include/tool.h"
#include "include/pixel_buffer.h"

/*******************************************************************************
 * Namespace Definitions
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This tool simulates the usage of a Stamp.
 * It has a oval mask with a radius of 7.0 (diameter of 15), an opacity of 0.4
 * (semi-transparent), an angle of 90 degrees counter-clockwise from the x-axis,
 * and an elongation ratio of 0.3
 */
class TStamp : public Tool {
 public:
  TStamp(void);

  /**
   * @brief
   *
   *
   * @return The new ColorData for the pixel
   */
   // not implemented yet
  ColorData color_blend_math(
      float mask_pixel_amount,
      const ColorData& tool_color,
      const ColorData& current_color,
      const ColorData& background_color);

  // implemented wrongly
  virtual void ApplyToBuffer(
      int tool_x,
      int tool_y,
      ColorData tool_color,
      PixelBuffer* buffer);

  std::string name(void) { return "Stamp"; }

  void stamp_mask(PixelBuffer *stamp) { stamp_mask_ = stamp; }

private:
  PixelBuffer *stamp_mask_;
};

}  /* namespace image_tools */

#endif  /* SRC_INCLUDE_T_STAMP_H_ */
