/*******************************************************************************
 * Name            : fp_filter_manager.h
 * Project         : FlashPhoto
 * Module          : filter_manager
 * Description     : Header for FPFilterManager class
 * Copyright       : Group A01. All rights reserved.
 * Creation Date   : Sat Dec 03 22:29:33 2016
 * Original Author : Yu Xian Ang
 *
 ******************************************************************************/

#ifndef SRC_APP_FLASHPHOTO_SRC_INCLUDE_FP_FILTER_MANAGER_H_
#define SRC_APP_FLASHPHOTO_SRC_INCLUDE_FP_FILTER_MANAGER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/filter_manager.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

 /*******************************************************************************
  * Class Definitions
  ******************************************************************************/
 /**
  * @brief Manager for all aspects of filters in FlashPhoto, including
  * initialization of GLUI control elements for filters, filter creation,
  * application, deletion.
  */
class FPFilterManager : public FilterManager {
 public:
  FPFilterManager();

  GLUI_Panel* InitGlui(const GLUI *const glui,
                       void (*s_gluicallback)(int));
};

}  /* namespace image_tools */

#endif  /* SRC_APP_FLASHPHOTO_SRC_INCLUDE_FP_FILTER_MANAGER_H_ */
