/*******************************************************************************
 * Name            : calligraphy_pen.cc
 * Project         : BrushWork
 * Module          : Utils
 * Description     : Implementation of CalligraphyPen on top of tools
 * Copyright       : 2016 CSCI3081W GroupA01. All rights reserved.
 * Creation Date   : 10/12/16
 * Original Author : GroupA01
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "include/calligraphy_pen.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/

namespace image_tools {
/*******************************************************************************
 * Constructors
 ******************************************************************************/
CalligraphyPen::CalligraphyPen(void) {
    memset(mask_, 0, sizeof mask_);
    mask_radius_ = 0;
    mask_len_ = 41;
    color_ = ColorData();
    mask_radius_ = 2.5;
    for (int x = -2; x <= 2; x++)
        for (int y = -7; y <= 7; y++)
            this->mask_[CENTER + x][CENTER + y] = 1;
}
}//namespace image_tools
