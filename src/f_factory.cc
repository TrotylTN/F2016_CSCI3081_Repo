/*******************************************************************************
 * Name            : f_factory.cc
 * Project         : FlashPhoto
 * Module          : filter_manager
 * Description     : Implementation of factory design pattern for filters
 * Copyright       : 2016 CSCI3081W Group A01. All rights reserved.
 * Creation Date   : 11/19/16
 * Original Author : Group-A01
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/filter_factory.h"
#include "include/filter_manager.h"
#include "include/f_blur_matrix.h"
#include "include/f_edge_matrix.h"
#include "include/f_threshold_filter.h"
#include "include/f_saturation_filter.h"
#include "include/f_rgb_filter.h"
#include "include/f_quan_filter.h"
#include "include/f_emboss_matrix.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
FilterMatrix* FilterFactory::CreateFilter(int filter_id) {
  FilterMatrix* filter = nullptr;
  switch (filter_id) {
    case F_BLUR:
      filter = new BlurMatrix();
      break;
    case F_MOTION:
      filter = new BlurMatrix();
      break;
    case F_SHARPEN:
      filter = new EdgeMatrix();
      break;
    case F_EDGE:
      filter = new EdgeMatrix();
      break;
    case F_THRESHOLD:
      filter = new ThresholdFilter();
      break;
    case F_SATURATION:
      filter = new SaturationFilter();
      break;
    case F_CHANNEL:
      filter = new RGBFilter();
      break;
    case F_QUANTIZE:
      filter = new QuanFilter();
      break;
    case F_EMBOSS:
      filter = new EmbossMatrix();
      break;
    default:
      filter = nullptr;
      break;
  }

  return filter;
}

}  /* namespace image_tools */
