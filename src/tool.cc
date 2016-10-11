#include "include/tool.h"
#include <cstring>

namespace image_tools {
Tool::Tool(void) {
    memset(mask, 0, sizeof mask);
    mask_radius_ = 0;
    mask_len = 41;
    color_ = ColorData();
}

void Tool::Tool::draw_mask(PixelBuffer *frame, int x, int y) {
    ColorData temp_color;
    for (int i = 0; i < mask_len; i++)
        for (int j = 0; j < mask_len; j++) {
            int temp_x = i + x - CENTER;
            int temp_y = j + y - CENTER;
            if (!(temp_x < 0 ||
                  temp_x >= frame->width() ||
                  temp_y < 0 ||
                  temp_y >= frame->height()))
            {
                temp_color = (color_ * mask[i][j]) +
                             (frame->get_pixel(temp_x, temp_y) *
                              (1 - mask[i][j])
                             );
                frame->set_pixel(temp_x, temp_y, temp_color);
            }
        }
}

void Tool::set_color (ColorData cur_color, ColorData background_color) {
    color_ = cur_color;
}

float Tool::mask_radius(void) {
    return mask_radius_;
}
}
