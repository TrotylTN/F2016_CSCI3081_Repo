/*******************************************************************************
 * Name            : spray.cc
 * Project         : BrushWork
 * Module          : utils
 * Description     : Implementation of spray on top of tools
 * Copyright       : 2016 CSCI3081W GroupA01. All rights reserved.
 * Creation Date   : 10/12/16
 * Original Author : GroupA01
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/spray_can.h"
#include <cmath>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/

namespace image_tools {
/*******************************************************************************
 * Constructors
 ******************************************************************************/

SprayCan::SprayCan(void) {
    memset(mask_, 0, sizeof mask_);
    mask_radius_ = 0;
    mask_len_ = 41;
    color_ = ColorData();
    mask_radius_ = 20.5;
    for (int i = 0; i < mask_len_; i++)
        for (int j = 0; j < mask_len_; j++) {
            int x = i - CENTER;
            int y = j - CENTER;
            if (x * x + y * y <= mask_radius_ * mask_radius_)
                this->mask_[i][j] = 0.2 - sqrt(x * x + y * y) * 0.01;
        }
}
}//namespace image_tools
