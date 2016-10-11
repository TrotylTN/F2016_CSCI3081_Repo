#ifndef INCLUDE_ERASER_H_
#define INCLUDE_ERASER_H_

#include "include/tool.h"

namespace image_tools {

class Eraser : public Tool{
    public:
        Eraser(void);
        void set_color(ColorData cur_color, ColorData background_color);
};
}

#endif
