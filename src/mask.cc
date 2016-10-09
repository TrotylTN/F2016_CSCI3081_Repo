#include "include/mask.h"
#include <cstring>
#include <iostream>

namespace image_tools {
  Mask::Mask(void) {
    memset(this->matrix_, 0, sizeof this->matrix_);
    this->cur_tool_ = -1; //-1 means no tool is active.
  }

  Mask::Mask(int tool_number) {
    memset(this->matrix_, 0, sizeof this->matrix_);
    Mask::switch_mask(tool_number);
  }

  void Mask::switch_mask(int tool_number) {
    if (tool_number == this->cur_tool_)
      return;
    memset(this->matrix_, 0, sizeof this->matrix_);
    switch (tool_number) {
      case 0:
      //Pen
        for (int r = 0; r <= 1; r++)
          for (int x = 0; x <= r; x++) {
            int y = r - x;
            this->matrix_[CENTER + x][CENTER + y] = 1;
            this->matrix_[CENTER + x][CENTER - y] = 1;
            this->matrix_[CENTER - x][CENTER + y] = 1;
            this->matrix_[CENTER - x][CENTER - y] = 1;
          }
      break;

      case 1:
      //Calligraphy Pen
        for (int x = -2; x <= 2; x++)
          for (int y = -7; y <= 7; y++)
            this->matrix_[CENTER + x][CENTER + y] = 1;
      break;

      case 2:
      //Highlighter
        for (int x = -2; x <= 2; x++)
          for (int y = -7; y <= 7; y++)
            this->matrix_[CENTER + x][CENTER + y] = 0.4;
      break;

      case 3:
      //Spray Can radius:20
        for (int r = 0; r <= 20; r++)
          for (int x = 0; x <= r; x++) {
            int y = r - x;
            this->matrix_[CENTER + x][CENTER + y] = 0.2 - (r * 0.01);
            this->matrix_[CENTER + x][CENTER - y] = 0.2 - (r * 0.01);
            this->matrix_[CENTER - x][CENTER + y] = 0.2 - (r * 0.01);
            this->matrix_[CENTER - x][CENTER - y] = 0.2 - (r * 0.01);
          }
      break;

      case 4:
      //Eraser radius:10
        for (int r = 0; r <= 10; r++)
          for (int x = 0; x <= r; x++) {
            int y = r - x;
            this->matrix_[CENTER + x][CENTER + y] = 1;
            this->matrix_[CENTER + x][CENTER - y] = 1;
            this->matrix_[CENTER - x][CENTER + y] = 1;
            this->matrix_[CENTER - x][CENTER - y] = 1;
          }
      break;

      default:
        std::cout << "The tool does not exist." << std::endl;
    }
    this->cur_tool_ = tool_number;
  }

  void Mask::print_mask(void) {
    std::cout << "This is Tool no." << this->cur_tool_ <<std::endl;
    for (int i = 0; i < MASK_LEN; i++) {
      for (int j = 0; j < MASK_LEN; j++)
        std::cout << this->matrix_[i][j] << " ";
      std::cout << std::endl;
    }
  }
}
