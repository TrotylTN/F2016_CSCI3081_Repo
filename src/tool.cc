#include "include/tool.h"
#include <cstring>

namespace image_tools {
Tool::Tool(void) {
    memset(mask, 0, sizeof mask);
    mask_radius_ = 0;
    mask_len = 41;
    color_ = ColorData();
}

void Tool::Tool::draw_mask(BrushWorkApp *frame, int x, int y) {
    ColorData temp_color;
    for (int i = 0; i < mask_len; i++)
        for (int j = 0; j < mask_len; j++) {
            int temp_x = i + x - CENTER;
            int temp_y = j + y - CENTER;
            if (!(temp_x < 0 ||
                  temp_x >= frame->display_buffer()->width() ||
                  temp_y < 0 ||
                  temp_y >= frame->display_buffer()->height()))
            {
                temp_color = (color_ * mask[i][j]) +
                             (frame->display_buffer()->get_pixel(temp_x, temp_y) *
                              (1 - mask[i][j])
                             );
                frame->display_buffer()->set_pixel(temp_x, temp_y, temp_color);
            }
        }
}

void Tool::set_color (float r, float g, float b) {
    color_ = ColorData(r, g, b);
}

float Tool::mask_radius(void) {
    return mask_radius_;
}
}
