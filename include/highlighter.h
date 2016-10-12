#ifndef INCLUDE_HIGHLIGHTER_H_
#define INCLUDE_HIGHLIGHTER_H_

#include "include/tool.h"

namespace image_tools {

class Highlighter : public Tool{
    public:
        Highlighter(void);
        void draw_mask(PixelBuffer *frame, int x, int y);
};
}

#endif
