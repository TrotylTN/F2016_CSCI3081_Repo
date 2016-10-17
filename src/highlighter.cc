/*******************************************************************************
 * Name            : highlighter.cc
 * Project         : BrushWork
 * Module          : Utils
 * Description     : Implementation of Highlighter on top of Tool
 * Copyright       : 2016 CSCI3081W GroupA01. All rights reserved.
 * Creation Date   : 10/12/16
 * Original Author : GroupA01
 *
 ******************************************************************************/
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/highlighter.h"
#include <iostream>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/

namespace image_tools {
/*******************************************************************************
 * Constructors
 ******************************************************************************/

Highlighter::Highlighter(void) {
    memset(mask_, 0, sizeof mask_);
    mask_radius_ = 0;
    mask_len_ = 41;
    color_ = ColorData();
    mask_radius_ = 2.5;
    for (int x = -2; x <= 2; x++)
        for (int y = -7; y <= 7; y++)
            this->mask_[CENTER + x][CENTER + y] = 0.4;
}
/**
 * @brief draw according the intensity of each pixel on the canvas.
 */
void Highlighter::draw_mask(PixelBuffer *frame, int x, int y) {
    ColorData temp_color;
    float intensity;
    for (int i = 0; i < mask_len_; i++)
        for (int j = 0; j < mask_len_; j++) {
            int temp_x = i + x - CENTER;
            int temp_y = j + y - CENTER;
            if (!(temp_x < 0 ||
                  temp_x >= frame->width() ||
                  temp_y < 0 ||
                  temp_y >= frame->height())) {
                intensity = mask_[i][j] *
                            frame->get_pixel(temp_x, temp_y).luminance();
                temp_color = (color_ * intensity) +
                             (frame->get_pixel(temp_x, temp_y) *
                              (1.0 - intensity));
                frame->set_pixel(temp_x, temp_y, temp_color);
            }
        }
}
}  // namespace image_tools
