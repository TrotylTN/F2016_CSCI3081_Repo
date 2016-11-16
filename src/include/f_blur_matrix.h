/*******************************************************************************
 * Name            : f_blur_matrix.h
 * Project         : FlashPhoto
 * Module          : filter_manager
 * Description     : Header for BlurMatrix class
 * Copyright       : 2016 CSCI3081W Group A01. All rights reserved.
 * Creation Date   : Sat Nov 5 16:24:11 2016
 * Original Author : Tiannan Zhou
 *
 ******************************************************************************/

#ifndef SRC_INCLUDE_F_BLUR_MATRIX_H_
#define SRC_INCLUDE_F_BLUR_MATRIX_H_

/*******************************************************************************
* Includes
******************************************************************************/
#include "include/filter_matrix.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This class is the matrix tool which would be used by FilterManager
 */
class BlurMatrix : public FilterMatrix {
 public:
  BlurMatrix() : FilterMatrix::FilterMatrix(), blur_type_(-1) {}
  ~BlurMatrix() {}
  /**
   * @brief apply a new size for a filter matrix
   *
   * @param[in] incoming_size the new size of this matrix
   */
  void Resize(float incoming_size, float blur_type);

  PixelBuffer* ApplyMatrix(PixelBuffer* original_buffer);

 private:
  int blur_type_;
};
}  // namespace image_tools

#endif  // SRC_INCLUDE_F_BLUR_MATRIX_H_
