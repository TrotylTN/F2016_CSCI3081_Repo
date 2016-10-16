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

#ifndef INCLUDE_CALLIGRAPHY_PEN_H_
#define INCLUDE_CALLIGRAPHY_PEN_H_

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
 * we implement the CallographyPen tool on top of the Tool class
 */
class CalligraphyPen : public Tool{
    public:
        CalligraphyPen(void);
};
} // namespace image_tools
#endif //INCLUDE_PIXEL_BUFFER_H_