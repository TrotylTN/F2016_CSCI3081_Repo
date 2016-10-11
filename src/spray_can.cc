#include "include/spray_can.h"
#include <cmath>

namespace image_tools {
SprayCan::SprayCan(void) {
    memset(mask, 0, sizeof mask);
    mask_radius_ = 0;
    mask_len = 41;
    color_ = ColorData();
    mask_radius_ = 20.5;
    for (int i = 0; i < mask_len; i++)
        for (int j = 0; j < mask_len; j++) {
            int x = i - CENTER;
            int y = j - CENTER;
            if (x * x + y * y <= mask_radius_ * mask_radius_)
                this->mask[i][j] = 0.2 - sqrt(x * x + y * y) * 0.01;
        }
}
}
