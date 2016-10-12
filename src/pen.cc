/*******************************************************************************
 * Name            : pen.cc
 * Project         : BrushWork
 * Module          : utils
 * Description     : Implementation of Pen on top of tools
 * Copyright       : 2016 CSCI3081W GroupA01. All rights reserved.
 * Creation Date   : 10/12/16
 * Original Author : GroupA01
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/pen.h"
/*******************************************************************************
 * Constructors
 ******************************************************************************/

namespace image_tools {
/*******************************************************************************
 * Constructors
 ******************************************************************************/

Pen::Pen(void) {
    memset(mask, 0, sizeof mask);
    mask_radius_ = 0;
    mask_len = 41;
    color_ = ColorData();
    mask_radius_ = 1.5;
    for (int i = 0; i < mask_len; i++)
        for (int j = 0; j < mask_len; j++) {
            int x = i - CENTER;
            int y = j - CENTER;
            if (x * x + y * y <= mask_radius_ * mask_radius_)
                this->mask[i][j] = 1;
        }
}
}//namespace image_tools
