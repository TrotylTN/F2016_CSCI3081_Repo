/*******************************************************************************
 * Name            : t_eraser.cc
 * Project         : BrushWork
 * Module          : Tool
 * Description     : Implementation of eraser tool class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/t_eraser.h"
#include <string>
#include "include/m_constant.h"
#include "include/color_data.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
TEraser::TEraser(void) { mask(new MConstant(10.0, 1.0)); }

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
// Eraser does not blend colors with the toolColor.  Here we are overriding the
// superclass's colorBlendMath to set the canvasColor to the backgroundColor.
ColorData TEraser::color_blend_math(
    float mask_pixel_amount,
    const ColorData& tool_color,
    const ColorData& current_color,
    const ColorData& background_color) {
  return background_color*mask_pixel_amount +
      current_color*(1-mask_pixel_amount);
}

}  /* namespace image_tools */
