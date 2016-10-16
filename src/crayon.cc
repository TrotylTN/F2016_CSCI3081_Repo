/*******************************************************************************
 * Name            : Crayon.cc
 * Project         : BrushWork
 * Module          : Utils
 * Description     : Implementation of Crayon on top of tools
 * Copyright       : 2016 CSCI3081W GroupA01. All rights reserved.
 * Creation Date   : 10/12/16
 * Original Author : GroupA01
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "include/crayon.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {
/*******************************************************************************
 * Constructors
 ******************************************************************************/

Crayon::Crayon(void) {
    memset(mask_, 0, sizeof mask_);
    mask_radius_ = 0;
    mask_len_ = 41;
    color_ = ColorData();
    mask_radius_ = 10.5;
    int tmp;
    for (int i = 0; i < mask_len_; i++)
        for (int j = 0; j < mask_len_; j++) {
            int x = i - CENTER;
            int y = j - CENTER;
            if ((tmp = x * x + y * y) <= mask_radius_ * mask_radius_) {
                if (sqrt(tmp) < 0.7 * mask_radius_) {
                    if (rand() % 10 > 3)
                        this->mask_[i][j] = 1;
                    else
                        this->mask_[i][j] = 0;
                }
                else {
                    if (rand() % 10 > 7)
                        this->mask_[i][j] = 1;
                    else
                        this->mask_[i][j] = 0;
                }
            }
        }
}
}//namespace image_tools
