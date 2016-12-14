/*******************************************************************************
 * Name            : fp_io_manager.cc
 * Project         : FlashPhoto
 * Module          : io_manager
 * Description     : Implementation of FPIOManager class
 * Copyright       : Group A01. All rights reserved.
 * Creation Date   : Sat Dec 3 9:41:00 2016
 * Original Author : Yu Xian Ang
 *
 ******************************************************************************/

 /*******************************************************************************
  * Includes
  ******************************************************************************/
#include "include/fp_io_manager.h"
#include <assert.h>
#include <iostream>
#include <sstream>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
FPIOManager::FPIOManager(void) :
  IOManager() {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
GLUI_Panel* FPIOManager::InitGlui(const GLUI *const glui,
                         void (*s_gluicallback)(int)) {
  new GLUI_Column(const_cast<GLUI*>(glui), true);
  GLUI_Panel *image_panel = new GLUI_Panel(const_cast<GLUI*>(glui),
                                           "Image I/O");
  AddFileBrowserToGLUI(image_panel, s_gluicallback);
  AddLoadStampToGLUI(image_panel, s_gluicallback);
  new GLUI_Separator(image_panel);
  AddSaveCanvasToGLUI(image_panel, s_gluicallback);
  return image_panel;
}

} /* namespace image_tools */
