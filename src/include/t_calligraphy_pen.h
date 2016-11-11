/*******************************************************************************
 * Name            : t_calligraphy_pen.h
 * Project         : image_tools
 * Module          : Tool
 * Description     : Header file for Calligraphy pen class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef SRC_INCLUDE_T_CALLIGRAPHY_PEN_H_
#define SRC_INCLUDE_T_CALLIGRAPHY_PEN_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "include/tool.h"
#include "include/m_oval.h"

/*******************************************************************************
 * Namespace Definitions
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This tool simulates the usage of a Calligraphy Pen.
 * It has a oval mask with a radius of 7.0 (diameter of 15), an opacity of 1.0
 * (completely opaque), an angle of 70 degrees counter-clockwise from the
 * x-axis, and an elongation ratio of 0.333
 */
class TCalligraphyPen : public Tool {
 public:
  TCalligraphyPen(void) {
    mask(new MOval(7.0, 1.0, 70.0, 0.333));
    drag_status(true);
  }

    std::string name(void) { return "Caligraphy Pen"; }
};

}  /* namespace image_tools */

#endif  /* SRC_INCLUDE_T_CALLIGRAPHY_PEN_H_ */
