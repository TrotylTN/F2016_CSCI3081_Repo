/*******************************************************************************
 * Name            : fp_filter_manager.cc
 * Project         : FlashPhoto
 * Module          : filter_manager
 * Description     : Implementation of FPFilterManager class
 * Copyright       : Group A01. All rights reserved.
 * Creation Date   : Sat Dec 03 22:29:33 2016
 * Original Author : Yu Xian Ang
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/fp_filter_manager.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
FPFilterManager::FPFilterManager(void) :
    FilterManager() {}

GLUI_Panel* FPFilterManager::InitGlui(const GLUI *const glui,
                             void (*s_gluicallback)(int)) {
  new GLUI_Column(const_cast<GLUI*>(glui), true);
  GLUI_Panel *filter_panel = new GLUI_Panel(const_cast<GLUI*>(glui), "Filters");
  {
    AddBlurToGLUI(filter_panel, s_gluicallback);
    AddMotionBlurToGLUI(filter_panel, s_gluicallback);
    AddSharpenToGLUI(filter_panel, s_gluicallback);
    AddEdgeDetectToGLUI(filter_panel, s_gluicallback);
    AddThresholdToGLUI(filter_panel, s_gluicallback);

    new GLUI_Column(filter_panel, true);
    AddSaturationToGLUI(filter_panel, s_gluicallback);
    AddChannelToGLUI(filter_panel, s_gluicallback);
    AddQuantizationToGLUI(filter_panel, s_gluicallback);
  }

  return filter_panel;
} /* FPFilterManager::InitGlui() */

}  /* namespace image_tools */
