/*******************************************************************************
 * Name            : f_quan_filter.h
 * Project         : FlashPhoto
 * Module          : filter_manager
 * Description     : Header for QuanFilter class
 * Copyright       : 2016 CSCI3081W Group A01. All rights reserved.
 * Creation Date   : Thu Nov 10 19:17:42 2016
 * Original Author : Tiannan Zhou
 *
 ******************************************************************************/

#ifndef SRC_INCLUDE_QUAN_FILTER_H_
#define SRC_INCLUDE_QUAN_FILTER_H_

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
class QuanFilter : public FilterMatrix{
 public:
  QuanFilter() : FilterMatrix::FilterMatrix(), quantize_bins_(1) {}
  ~QuanFilter() {}
  /**
   * @brief apply the filter on the buffer then return the cached buffer
   *
   * @param[in] original_buffer the display_buffer of GUI
   */
  void Resize(float incoming_size, float bins);

  PixelBuffer* ApplyMatrix(PixelBuffer* original_buffer);
 private:
  int quantize_bins_;
};
}

#endif  // SRC_INCLUDE_QUAN_FILTER_H_
