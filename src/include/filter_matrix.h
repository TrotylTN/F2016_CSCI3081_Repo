/*******************************************************************************
 * Name            : filter_matrix.h
 * Project         : FlashPhoto
 * Module          : filter_manager
 * Description     : Header for FilterMatrix class
 * Copyright       : 2016 CSCI3081W Group A01. All rights reserved.
 * Creation Date   : Sat Nov 5 14:47:31 2016
 * Original Author : Tiannan Zhou
 *
 ******************************************************************************/

#ifndef SRC_INCLUDE_FILTER_MATRIX_H_
#define SRC_INCLUDE_FILTER_MATRIX_H_

/*******************************************************************************
* Includes
******************************************************************************/
#include <vector>
#include <cmath>
#include "include/color_data.h"
#include "include/pixel_buffer.h"

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
class FilterMatrix {
 public:
  FilterMatrix();
  virtual ~FilterMatrix() {}
  /**
   * @brief apply a new size for a filter matrix
   *
   * @param[in] incoming_size the new size of this matrix
   */
  virtual void Resize(float incoming_size);

  /**
   * @brief apply the matrix on the buffer then return the cached buffer
   *
   * @param[in] original_buffer the display_buffer of GUI
   */
  PixelBuffer* ApplyMatrix(PixelBuffer* original_buffer);

  void SetMatrixSize(int new_matrix_size);

  void SetMatrix(std::vector <std::vector<int> > new_matrix);

 private:
   int  matrix_size_;
   std::vector <std::vector<int> > matrix_;
};
}

#endif  // SRC_INCLUDE_FILTER_MATRIX_H_
