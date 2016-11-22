/*******************************************************************************
 * Name            : filter_factory.h
 * Project         : image_tools
 * Module          : filter_manager
 * Copyright       : 2016 CSCI3081W Group A01. All rights reserved.
 * Description     : Header file for FilterFactory
 * Creation Data   : 11/19/16
 * Original Author : Group-A01
 *
 ******************************************************************************/

#ifndef SRC_INCLUDE_FILTER_FACTORY_H_
#define SRC_INCLUDE_FILTER_FACTORY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include "include/filter_matrix.h"

/*******************************************************************************
 * Namespace Definitions
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Implementation of factory pattern to handle filters creation
 * This enables easy extension/addition of new filters.
 */
class FilterFactory {
 public:
  /**
   * @brief The list of filters that can be created by the factory and used by
   * the application
   */
  enum FILTERS {
    F_BLUR = 0,
    F_MOTION = 1,
    F_SHARPEN = 2,
    F_EDGE = 3,
    F_THRESHOLD = 4,
    F_SATURATION = 5,
    F_CHANNEL = 6,
    F_QUANTIZE = 7,
    F_EMBOSS = 8,
    NUMFILTERS = 9
  };

  /**
   * @brief Return the total # of tools in the application
   */
  static int num_filters(void) { return NUMFILTERS; }

  /**
   * @brief Create a filter from the list of defined filters
   * @return The initialized filter, or nullptr if an invalid index was passed
   */
  static FilterMatrix* CreateFilter(int filter_id);
};

}  /* namespace image_tools */

#endif  /* SRC_INCLUDE_FILTER_FACTORY_H_ */
