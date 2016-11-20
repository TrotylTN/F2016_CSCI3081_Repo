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

    default:
      filter = nullptr;
      break;
  }

  return filter;
}

}  /* namespace image_tools */
