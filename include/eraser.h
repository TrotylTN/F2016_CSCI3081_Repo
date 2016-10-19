/*******************************************************************************
 * Name            : eraser.h
 * Project         : BrushWork
 * Module          : utils
 * Description     : Header file for Eraser tools.
 * Copyright       : 2016 CSCI3081W GroupA01. All rights reserved.
 * Creation Date   : 10/12/2016
 * Original Author : Group A01
 *
 *******************************************************************************/
#ifndef INCLUDE_ERASER_H_
#define INCLUDE_ERASER_H_

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "include/tool.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/

namespace image_tools {
/*******************************************************************************
 * Class Definitions
******************************************************************************/
/**
 * @brief This is a subclass of the tool class
 * we implement the Eraser tool on top of the Tool class
 */

class Eraser : public Tool{
 public:
  Eraser(void);
  void set_color(ColorData cur_color, ColorData background_color);
};
}  // namespace image_tools
#endif  // INCLUDE_ERASER_H_
