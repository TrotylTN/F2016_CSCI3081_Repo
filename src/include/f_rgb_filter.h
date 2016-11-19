/*******************************************************************************
 * Name            : f_rgb_filter.h
 * Project         : FlashPhoto
 * Module          : filter_manager
 * Description     : Header for RGBFilter class
 * Copyright       : 2016 CSCI3081W Group A01. All rights reserved.
 * Creation Date   : Thu Nov 10 14:01:18 2016
 * Original Author : Group-A01
 *
 ******************************************************************************/

#ifndef REPO_GROUP_A01_SRC_INCLUDE_F_RGB_FILTER_H_
#define REPO_GROUP_A01_SRC_INCLUDE_F_RGB_FILTER_H_

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
class RGBFilter : public FilterMatrix{
 public:
  RGBFilter() : FilterMatrix::FilterMatrix(),
                channel_color_red_(1),
                channel_color_green_(1),
                channel_color_blue_(1) {}
  ~RGBFilter() {}
  /**
   * @brief apply the filter on the buffer then return the cached buffer
   *
   * @param[in] original_buffer the display_buffer of GUI
   */
  void Resize(float incoming_size,
              float r_amount,
              float g_amount,
              float b_amount);

  PixelBuffer* ApplyMatrix(PixelBuffer* original_buffer);

 private:
  float channel_color_red_;
  float channel_color_green_;
  float channel_color_blue_;
};
}  // namespace image_tools

#endif  // REPO_GROUP_A01_SRC_INCLUDE_F_RGB_FILTER_H_
