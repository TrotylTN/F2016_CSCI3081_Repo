/*******************************************************************************
 * Name            : CalligraphyPen.h
 * Project         : BrushWork
 * Module          : utils
 * Description     : Header file for CalligraphyPen tools.
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

#include "include/color_data.h"
#include "include/pixel_buffer.h"
#include <cstring>

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
class Tool{
  public:
    Tool(void);

    /**
     *@brief Initialize the
     * draw mask on screen;
     */
    virtual void draw_mask(PixelBuffer *frame, int x, int y);

    /**
     * @brief used for fill the gap between the current position
     * and previous position
     */
    float mask_radius(void);

    /**
     * @brief set up the background color and current tools color.
     * getting ready when the tool color been changed.
     */
    virtual void set_color(ColorData cur_color, ColorData background_color);

  protected:
    float mask_radius_;
    float mask[41][41];
    int mask_len;
    ColorData color_;
};
} //namespace image_tools

#endif //INCLUDE_COLOR_DATA_H_
