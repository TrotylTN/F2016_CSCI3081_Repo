#include "include/crayon.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

namespace image_tools {
Crayon::Crayon(void) {
    memset(mask, 0, sizeof mask);
    mask_radius_ = 0;
    mask_len = 41;
    color_ = ColorData();
    mask_radius_ = 10.5;
    int tmp;
    for (int i = 0; i < mask_len; i++)
        for (int j = 0; j < mask_len; j++) {
            int x = i - CENTER;
            int y = j - CENTER;
            if ((tmp = x * x + y * y) <= mask_radius_ * mask_radius_) {
                if (sqrt(tmp) < 0.75 * mask_radius_) {
                    if (rand() % 10 > 4)
                        this->mask[i][j] = 1;
                    else
                        this->mask[i][j] = 0;
                }
                else {
                    if (rand() % 10 > 6)
                        this->mask[i][j] = 1;
                    else
                        this->mask[i][j] = 0;
                }
            }
        }
}
}
