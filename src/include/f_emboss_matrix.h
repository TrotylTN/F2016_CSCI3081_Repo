/*******************************************************************************
 * Name            : f_emboss_matrix.h
 * Project         : FlashPhoto
 * Module          : filter_manager
 * Description     : Header for EmbossMatrix class
 * Copyright       : 2016 CSCI3081W Group A01. All rights reserved.
 * Creation Date   : Thu Nov 10 20:19:47 2016
 * Original Author : Group-A01 
 *
 ******************************************************************************/

#ifndef SRC_INCLUDE_F_EMBOSS_MATRIX_H_
#define SRC_INCLUDE_F_EMBOSS_MATRIX_H_

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
class EmbossMatrix : public FilterMatrix {
 public:
  EmbossMatrix() : FilterMatrix::FilterMatrix() {
     FilterMatrix::MatrixSize(3);;
     FilterMatrix::Matrix({{-1, -1, 0}, {-1, 0, 1}, {0, 1, 1}});
  }
  ~EmbossMatrix() {}
  /**
   * @brief apply a new size for a filter matrix
   *
   * @param[in] incoming_size the new size of this matrix
   */
};
}  // namespace image_tools

#endif  // SRC_INCLUDE_F_EMBOSS_MATRIX_H_
