/*******************************************************************************
 * Name            : pen.h
 * Project         : BrushWork
 * Module          : utils
 * Description     : Header file for Pen tools.
 * Copyright       : 2016 CSCI3081W GroupA01. All rights reserved.
 * Creation Date   : 10/12/2016
 * Original Author : Group A01
 *
 *******************************************************************************/
#ifndef INCLUDE_PEN_H_
#define INCLUDE_PEN_H_

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
 * we implement the Pen tool on top of the Tool class
 */

class Pen : public Tool{
    public:
        Pen(void);
};
} //namespace image_tools

#endif //INCLUDE_PIXEL_BUFFER_H_
