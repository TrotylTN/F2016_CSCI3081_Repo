/*******************************************************************************
 * Name            : Tool.cc
 * Project         : BrushWork
 * Module          : utils
 * Description     : Implementation tools
 * Copyright       : 2016 CSCI3081W GroupA01. All rights reserved.
 * Creation Date   : 10/12/16
 * Original Author : GroupA01
 *
 ******************************************************************************/



/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/tool.h"
#include <cstring>
#include <algorithm>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors
 ******************************************************************************/
Tool::Tool(void) {
    memset(mask_, 0, sizeof mask_);
    mask_radius_ = 0;
    mask_len_ = 41;
    color_ = ColorData();
}
/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void Tool::draw_mask(PixelBuffer *frame, int x, int y) {
    ColorData temp_color;
    for (int i = 0; i < mask_len_; i++)
        for (int j = 0; j < mask_len_; j++) {
            int temp_x = i + x - CENTER;
            int temp_y = j + y - CENTER;
            if (!(temp_x < 0 ||
                  temp_x >= frame->width() ||
                  temp_y < 0 ||
                  temp_y >= frame->height()))
            {
                temp_color = (color_ * mask_[i][j]) +
                             (frame->get_pixel(temp_x, temp_y) *
                              (1 - mask_[i][j])
                             );
                frame->set_pixel(temp_x, temp_y, temp_color);
            }
        }
}

void Tool::set_color (ColorData cur_color, ColorData background_color) {
    color_ = cur_color;
}


/**
 *@brief to refill gaps, depend on different tools
   */
float Tool::mask_radius(void) {
    return std::max(mask_radius_ / 3.0, 1.0);
}
} //namespace image_tools
