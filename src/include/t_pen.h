/*******************************************************************************
 * Name            : t_pen.h
 * Project         : image_tools
 * Module          : Tool
 * Description     : Header file for Pen tool class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef SRC_INCLUDE_T_PEN_H_
#define SRC_INCLUDE_T_PEN_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "include/tool.h"
#include "include/m_constant.h"

/*******************************************************************************
 * Namespace Definitions
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This tool simulates the usage of a Pen.
 * It has a constant mask with a radius of 1.0 (diameter of 3) and an opacity
 * of 1.0
 */
class TPen : public Tool {
 public:
  TPen(void) {
    mask(new MConstant(1.0, 1.0));
    drag_status(true);
  }

  std::string name(void) { return "Pen"; }
};

}  /* namespace image_tools */

#endif  /* SRC_INCLUDE_T_PEN_H_ */
