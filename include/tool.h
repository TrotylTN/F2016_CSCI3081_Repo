#ifndef INCLUDE_TOOL_H_
#define INCLUDE_TOOL_H_

#include "include/color_data.h"
#include "include/pixel_buffer.h"
#include <cstring>

#define CENTER 20

namespace image_tools {

class Tool{
    public:
        Tool(void);

        void draw_mask(PixelBuffer *frame, int x, int y);
        float mask_radius(void);
        virtual void set_color(ColorData cur_color, ColorData background_color);

    protected:
        float mask_radius_;
        float mask[41][41];
        int mask_len;
        ColorData color_;
};
}

#endif
