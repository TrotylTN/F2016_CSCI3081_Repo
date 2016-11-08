/*******************************************************************************
 * Name            : single_filter.h
 * Project         : FlashPhoto
 * Module          : filter_manager
 * Description     : Header for SingleFilter class
 * Copyright       : 2016 CSCI3081W Group A01. All rights reserved.
 * Creation Date   : Mon Nov 7 20:13:37 2016
 * Original Author : Tiannan Zhou
 *
 ******************************************************************************/

#ifndef SRC_INCLUDE_SINGLE_FILTER_H_
#define SRC_INCLUDE_SINGLE_FILTER_H_

/*******************************************************************************
* Includes
******************************************************************************/
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
 * @brief This class is the filter tool which would be used by FilterManager
 */
class SingleFilter {
 public:
  SingleFilter() : filter_arg_(0) {}
  virtual ~SingleFilter() {}

  float FilterArg(void) { return filter_arg_; }
  void FilterArg(float arg) { filter_arg_ = arg; }
  /**
   * @brief apply the filter on the buffer then return the cached buffer
   *
   * @param[in] original_buffer the display_buffer of GUI
   */
  virtual PixelBuffer* ApplyFilter(PixelBuffer* original_buffer) = 0;
 private:
  float filter_arg_;
};
}

#endif  // SRC_INCLUDE_SINGLE_FILTER_H_
