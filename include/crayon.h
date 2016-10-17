/*******************************************************************************
 * Name            : crayon.h
 * Project         : BrushWork
 * Module          : utils
 * Description     : Header file for special tool -- Crayon.
 * Copyright       : 2016 CSCI3081W GroupA01. All rights reserved.
 * Creation Date   : 10/12/2016
 * Original Author : Group A01
 *
 *******************************************************************************/
#ifndef INCLUDE_CRAYON_H_
#define INCLUDE_CRAYON_H_

/*******************************************************************************
 * Includes
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
 * We create a Crayon tool as our special tool and implement on top of the Tool Class
 */

class Crayon : public Tool{
    public:
        Crayon(void);
};
} // namespace image_tools

#endif //INCLUDE_PIXEL_BUFFER_H_
