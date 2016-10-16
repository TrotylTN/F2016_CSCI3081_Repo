/*******************************************************************************
 * Name            : Eraser.cc
 * Project         : BrushWork
 * Module          : Utils
 * Description     : Implementation of Eraser on top of tools
 * Copyright       : 2016 CSCI3081W GroupA01. All rights reserved.
 * Creation Date   : 10/12/16
 * Original Author : GroupA01
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/eraser.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/

namespace image_tools {
/*******************************************************************************
 * Constructors
 ******************************************************************************/
Eraser::Eraser(void) {
    memset(mask_, 0, sizeof mask_);
    mask_radius_ = 0;
    mask_len_ = 41;
    color_ = ColorData();
    mask_radius_ = 10.5;
    for (int i = 0; i < mask_len_; i++)
        for (int j = 0; j < mask_len_; j++) {
            int x = i - CENTER;
            int y = j - CENTER;
            if (x * x + y * y <= mask_radius_ * mask_radius_)
                this->mask_[i][j] = 1;
        }
}

void Eraser::set_color(ColorData cur_color, ColorData background_color) {
    color_ = background_color;
}
} //namespace image_tools
