/*******************************************************************************
 * Name            : t_blur.h
 * Project         : image_tools
 * Module          : Tool
 * Description     : Header file for Blur class
 * Copyright       : 2016 CSCI3081W Group A01. All rights reserved.
 * Creation Date   : 11/15/16
 * Original Author : Yu Xian Ang
 *
 ******************************************************************************/

#ifndef SRC_INCLUDE_T_BLUR_H_
#define SRC_INCLUDE_T_BLUR_H_

/*******************************************************************************
 * Include Definitions
 ******************************************************************************/
#include <string>
#include "include/tool.h"
#include "include/m_linear.h"
#include "include/pixel_buffer.h"

/*******************************************************************************
 * Namespace Definitions
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This tool simulates the usage of blur filter.
 * It has an linear mask with a radius of 50.0 (diameter of 61), an opacity of
 * 1 (opaque). It is able to drag.
 */
class TBlur : public Tool {
 public:
  TBlur(void) : max_blur_size_(2) {
    mask(new MLinear(30, 1.0));
    drag_status(true);
  }

  virtual void ApplyToBuffer(
      int tool_x,
      int tool_y,
      ColorData tool_color,
      PixelBuffer* buffer);

  std::string name(void) { return "Blur"; }

 private:
/**
  * @brief Make the pixel with (tool_x, tool_y) blur.
  */
  ColorData ApplyBlur(PixelBuffer *buffer, int x,
                               int y, int mask_value);

  int max_blur_size_;
};

}  /* namespace image_tools */

#endif  /* SRC_INCLUDE_T_BLUR_H_ */
