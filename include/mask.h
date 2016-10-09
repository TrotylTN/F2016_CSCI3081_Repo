#ifndef INCLUDE_MASK_H_
#define INCLUDE_MASK_H_

#define MASK_LEN 41
#define CENTER 20
#define R_PEN 1.5
#define R_CAN 20.5
#define R_ERASER 10.5
namespace image_tools {

class Mask{
  public:
    Mask(void);
    Mask(int tool_number);

    float matrix_[41][41];

    void switch_mask(int tool_number);
    void print_mask(void);

  private:
    int cur_tool_;

};
}

#endif
