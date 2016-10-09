#ifndef INCLUDE_MASK_H_
#define INCLUDE_MASK_H_

#define MASK_LEN 41
#define CENTER 20
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
