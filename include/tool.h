/*******************************************************************************
 * Name            : tool.h
 * Project         : BrushWork
 * Module          : utils
 * Description     : Header file for Tool class.
 * Copyright       : 2016 CSCI3081W GroupA01. All rights reserved.
 * Creation Date   : 10/12/2016
 * Original Author : Group A01
 *
 *******************************************************************************/
#ifndef INCLUDE_TOOL_H_
#define INCLUDE_TOOL_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <cstring>
#include "include/color_data.h"
#include "include/pixel_buffer.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/

#define CENTER 20

namespace image_tools {
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This is a base class for each tool class.
 */
class Tool {
 public:
  Tool(void);

    /**
     *@brief draw on canvas using each tool's mask
     */
  virtual void draw_mask(PixelBuffer *frame, int x, int y);

    /**
     * @brief used to fill the gap between the current
     * and previous position
     */
  float mask_radius(void);

    /**
     * @brief set color used to draw on canvas
     */
  virtual void set_color(ColorData cur_color, ColorData background_color);

 protected:
  float mask_radius_;
  float mask_[41][41];
  int mask_len_;
  ColorData color_;
};
}  // namespace image_tools

#endif  // INCLUDE_TOOL_H_
