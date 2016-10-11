#include "include/highlighter.h"

namespace image_tools {
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
}
