/*******************************************************************************
 * Name            : io_manager.cc
 * Project         : FlashPhoto
 * Module          : io_manager
 * Description     : Implementation of IOManager class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : Wed Sep 21 20:47:05 2016
 * Original Author : jharwell
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/io_manager.h"
#include <iostream>
#include "include/ui_ctrl.h"
#include "png.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
IOManager::IOManager(void) :
    file_browser_(nullptr),
    load_canvas_btn_(nullptr),
    load_stamp_btn_(nullptr),
    save_canvas_btn_(nullptr),
    current_file_label_(nullptr),
    file_name_box_(nullptr),
    save_file_label_(nullptr),
    file_name_() {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void IOManager::InitGlui(const GLUI *const glui,
                         void (*s_gluicallback)(int)) {
  new GLUI_Column(const_cast<GLUI*>(glui), true);
  GLUI_Panel *image_panel = new GLUI_Panel(const_cast<GLUI*>(glui),
                                           "Image I/O");
  file_browser_ = new GLUI_FileBrowser(image_panel,
                                      "Choose Image",
                                      false,
                                      UICtrl::UI_FILE_BROWSER,
                                      s_gluicallback);

  file_browser_->set_h(400);

  file_name_box_ = new GLUI_EditText(image_panel ,
                                    "Image:",
                                    file_name_,
                                    UICtrl::UI_FILE_NAME,
                                    s_gluicallback);
  file_name_box_->set_w(200);

  new GLUI_Separator(image_panel);

  current_file_label_ = new GLUI_StaticText(image_panel,
                                           "Will load image: none");
  load_canvas_btn_ = new GLUI_Button(image_panel,
                                    "Load Canvas",
                                    UICtrl::UI_LOAD_CANVAS_BUTTON,
                                    s_gluicallback);
  load_stamp_btn_ = new GLUI_Button(image_panel,
                                   "Load Stamp",
                                   UICtrl::UI_LOAD_STAMP_BUTTON,
                                   s_gluicallback);

  new GLUI_Separator(image_panel);

  save_file_label_ = new GLUI_StaticText(image_panel,
                                        "Will save image: none");

  save_canvas_btn_ = new GLUI_Button(image_panel,
                                    "Save Canvas",
                                    UICtrl::UI_SAVE_CANVAS_BUTTON,
                                    s_gluicallback);

  load_canvas_toggle(false);
  load_stamp_toggle(false);
  save_canvas_toggle(false);
}


bool IOManager::is_valid_image_file(const std::string & name) {
  FILE *f;
  bool is_valid = false;
  if (is_valid_image_file_name(name)) {
    if ((f = fopen(name.c_str(), "r"))) {
      is_valid = true;
      fclose(f);
    }
  }
  return is_valid;
}

void IOManager::set_image_file(const std::string & file_name) {
  // If a directory was selected
  // instead of a file, use the
  // latest file typed or selected.
  std::string image_file = file_name;
  if (!is_valid_image_file_name(image_file)) {
    image_file = file_name_;
  }

  // TOGGLE SAVE FEATURE
  // If no file is selected or typed,
  // don't allow file to be saved. If
  // there is a file name, then allow
  // file to be saved to that name.

  if (!is_valid_image_file_name(image_file)) {
    save_file_label_->set_text("Will save image: none");
    save_canvas_toggle(false);
  } else {
    save_file_label_->set_text((std::string("Will save image: ") +
                                image_file).c_str());
    save_canvas_toggle(true);
  }

  // TOGGLE LOAD FEATURE

  // If the file specified cannot be opened,
  // then disable stamp and canvas loading.
  if (is_valid_image_file(image_file)) {
    load_stamp_toggle(true);
    load_canvas_toggle(true);

    current_file_label_->set_text((std::string("Will load: ") +
                                   image_file).c_str());
    file_name_box_->set_text(image_file);
  } else {
    load_stamp_toggle(false);
    load_canvas_toggle(false);
    current_file_label_->set_text("Will load: none");
  }
}

void IOManager::LoadImageToCanvas(void) {
  std::cout << "Load Canvas has been clicked for file " <<
      file_name_ << std::endl;
}

void IOManager::LoadImageToStamp(void) {
  std::cout << "Load Stamp has been clicked for file " <<
      file_name_ << std::endl;
}

void IOManager::SaveCanvasToFile(void) {
  std::cout << "Save Canvas been clicked for file " <<
      file_name_ << std::endl;
  
  FILE *fp;
  int row;
  png_structp png_ptr;
  png_infop info_ptr;
  png_colorp palsette;
  
  /*Open the file if*/
  fp = fopen(file_name().c_str(),"wb");
  if (fp == NULL )
    std::cout << "in the save Canvas function the varibale fb is null"
        << std::endl;
    return;
  
  /* Create and Initialize the png_struct with the desired error handler
   * functions.
   */

  png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING,
     NULL,NULL,NULL);

  if (png_ptr == NULL) {
    fclose(fp);
    std::cout << "in the save Canvas to file  png_ptr is null"<<
        std::endl;
    return;
  }

 
  /* Allocate/initialize the image information date
   */
  info_ptr = png_create_info_struct(png_ptr);

  if (info_ptr == NULL) {
    fclose(fp);
    png_destroy_write_struct(&png_ptr, &info_ptr);
    std::cout << "Error in info_pter, then destory write struct" << std::endl;
    return;
  }
  
  /* set error handleing */
  if (setjmp(png_jmpbuf(png_ptr))) {
    fclose(fp);
    png_destroy_write_struct(&png_ptr, &info_ptr);
    std::cout << "Error in the setjmp" << std::endl;
    return;
  }
  
  int width = png_get_image_width(png_ptr,info_ptr);
  int height = png_get_image_height(png_ptr,info_ptr);
  int PNG_COLOR_TYPE = png_get_color_type(png_ptr,info_ptr);
  
  /*set up the image information here. such like the width and high 
   * and the bit_depth which we choose the 8 bit, since we have RGBA 
   */
  png_set_IHDR(png_ptr, info_ptr, width,
               height, 8,PNG_COLOR_TYPE_RGB
               ,PNG_INTERLACE_NONE,       
               PNG_COMPRESSION_TYPE_BASE,
               PNG_FILTER_TYPE_BASE);
  
  png_write_info(png_ptr, info_ptr);

  /*start to write the image*/
  png_bytep row_pointers[height]; 
  
  for (row = 0;row < height; row++) {
    row_pointers[row] = NULL;
    
  }
  free(row_pointers);


  png_write_end(png_ptr, info_ptr);
  // png_free(png_ptr,palette);
  png_destroy_write_struct(&png_ptr, &info_ptr);
  fclose(fp);
} 



























}  /* namespace image_tools */
