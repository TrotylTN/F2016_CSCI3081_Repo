/*******************************************************************************
 * Name            : f_saturation_filter.h
 * Project         : FlashPhoto
 * Module          : filter_manager
 * Description     : Header for SaturationFilter class
 * Copyright       : 2016 CSCI3081W Group A01. All rights reserved.
 * Creation Date   : Wed Nov 9 17:1:52 2016
 * Original Author : Tiannan Zhou
 *
 ******************************************************************************/

#ifndef SRC_INCLUDE_SATURATION_FILTER_H_
#define SRC_INCLUDE_SATURATION_FILTER_H_

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
class SaturationFilter : public FilterMatrix{
 public:
  SaturationFilter() : FilterMatrix::FilterMatrix(), saturation_amount_(1) {}
  ~SaturationFilter() {}
  /**
   * @brief apply the filter on the buffer then return the cached buffer
   *
   * @param[in] original_buffer the display_buffer of GUI
   */
  void Resize(float incoming_size, float saturation_amount);

  PixelBuffer* ApplyMatrix(PixelBuffer* original_buffer);
 private:
  float saturation_amount_;
};
}

#endif  // SRC_INCLUDE_SATURATION_FILTER_H_
