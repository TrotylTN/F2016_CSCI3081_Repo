/*******************************************************************************
 * Name            : edge_matrix.h
 * Project         : FlashPhoto
 * Module          : filter_manager
 * Description     : Header for EdgeMatrix class
 * Copyright       : 2016 CSCI3081W Group A01. All rights reserved.
 * Creation Date   : Sun Nov 6 20:40:17 2016
 * Original Author : Tiannan Zhou
 *
 ******************************************************************************/

#ifndef SRC_INCLUDE_EDGE_MATRIX_H_
#define SRC_INCLUDE_EDGE_MATRIX_H_

/*******************************************************************************
* Includes
******************************************************************************/
#include "include/filter_matrix.h"
#include <string>

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
class EdgeMatrix : public FilterMatrix {
 public:
   EdgeMatrix() : FilterMatrix::FilterMatrix(), detect_type_(0) {}
   ~EdgeMatrix() {}
  /**
   * @brief apply a new size for a filter matrix
   *
   * @param[in] incoming_size the new size of this matrix
   */
  void Resize(float incoming_size, float detect_type);

 private:
  int detect_type_;
};
}

#endif  // SRC_INCLUDE_BLUR_MATRIX_H_
