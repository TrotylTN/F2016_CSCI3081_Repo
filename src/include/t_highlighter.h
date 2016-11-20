/*******************************************************************************
 * Name            : t_highlighter.h
 * Project         : image_tools
 * Module          : Tool
 * Description     : Header file for Highlighter class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef REPO_GROUP_A01_SRC_INCLUDE_T_HIGHLIGHTER_H_
#define REPO_GROUP_A01_SRC_INCLUDE_T_HIGHLIGHTER_H_

/*******************************************************************************
 * Include Definitions
 ******************************************************************************/
#include <string>
#include "include/tool.h"

/*******************************************************************************
 * Namespace Definitions
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This tool simulates the usage of a Highlighter.
 * It has a oval mask with a radius of 7.0 (diameter of 15), an opacity of 0.4
 * (semi-transparent), an angle of 90 degrees counter-clockwise from the x-axis,
 * and an elongation ratio of 0.3. It is able to drag.
 */
class THighlighter : public Tool {
 public:
  THighlighter(void);

  /**
   * @brief Overrides the super's function to include the luminance of the
   * canvas_color in the calculation of the tool's intensity
   *
   * @return The new ColorData for the pixel
   */
  ColorData color_blend_math(
      float mask_pixel_amount,
      const ColorData& tool_color,
      const ColorData& current_color,
      const ColorData& background_color);

  std::string name(void) { return "Highlighter"; }
};

}  /* namespace image_tools */

#endif  /* REPO_GROUP_A01_SRC_INCLUDE_T_HIGHLIGHTER_H_ */
