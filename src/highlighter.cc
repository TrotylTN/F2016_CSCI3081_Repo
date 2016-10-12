/*******************************************************************************
 * Name            : brushwork_app.cc
 * Project         : BrushWork
 * Module          : Utils
 * Description     : Implementation of Highlighter on top of tools
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
    memset(mask, 0, sizeof mask);
    mask_radius_ = 0;
    mask_len = 41;
    color_ = ColorData();
    mask_radius_ = 2.5;
    for (int x = -2; x <= 2; x++)
        for (int y = -7; y <= 7; y++)
            this->mask[CENTER + x][CENTER + y] = 0.4;
}
/**
 * @brief since we do not want to highlighter to covered the color
 * was been painted on the board, we have to override draw_mask
 * make the highlighter more real.
 */
void Highlighter::draw_mask(PixelBuffer *frame, int x, int y) {
    ColorData temp_color;
    float intensity;
    for (int i = 0; i < mask_len; i++)
        for (int j = 0; j < mask_len; j++) {
            int temp_x = i + x - CENTER;
            int temp_y = j + y - CENTER;
            if (!(temp_x < 0 ||
                  temp_x >= frame->width() ||
                  temp_y < 0 ||
                  temp_y >= frame->height()))
            {
                intensity = mask[i][j] * frame->get_pixel(temp_x, temp_y).luminance();
                temp_color = (color_ * intensity) +
                             (frame->get_pixel(temp_x, temp_y) *
                              (1.0 - intensity));
                frame->set_pixel(temp_x, temp_y, temp_color);
            }
        }
}
} //namespace image_tools
