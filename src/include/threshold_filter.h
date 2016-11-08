/*******************************************************************************
 * Name            : threshold_filter.h
 * Project         : FlashPhoto
 * Module          : filter_manager
 * Description     : Header for ThresholdFilter class
 * Copyright       : 2016 CSCI3081W Group A01. All rights reserved.
 * Creation Date   : Mon Nov 7 20:14:39 2016
 * Original Author : Tiannan Zhou
 *
 ******************************************************************************/

#ifndef SRC_INCLUDE_THRESHOLD_FILTER_H_
#define SRC_INCLUDE_THRESHOLD_FILTER_H_

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
 * @brief This class is threshold filter which would be used by FilterManager
 */
class ThresholdFilter : public FilterMatrix{
 public:
  ThresholdFilter() : FilterMatrix::FilterMatrix() {}
  ~ThresholdFilter() {}
  /**
   * @brief apply the filter on the buffer then return the cached buffer
   *
   * @param[in] original_buffer the display_buffer of GUI
   */
  void Resize(float incoming_size, float threshold_amount);

  PixelBuffer* ApplyMatrix(PixelBuffer* original_buffer);
 private:
  float threshold_amount_;
};
}

#endif  // SRC_INCLUDE_THRESHOLD_MATRIX_H_
