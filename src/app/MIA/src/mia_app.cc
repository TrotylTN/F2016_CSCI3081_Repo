/*******************************************************************************
 * Name            : mia_app.cc
 * Project         : MIA
 * Module          : App
 * Description     : Implementation of MIA
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 5/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/mia_app.h"
#include <cmath>
#include <string>
#include <iostream>
#include "include/image_handler.h"
#include "include/t_stamp.h"
#include "include/tool_factory.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
MIAApp::MIAApp(int width, int height,
               const std::string& marker_fname) : BaseGfxApp(width, height),
                                                  filter_manager_(),
                                                  io_manager_(),
                                                  state_manager_(),
                                                  display_buffer_(nullptr),
                                                  marker_fname_(marker_fname),
                                                  cur_tool_(0),
                                                  tools_(nullptr),
                                                  mouse_last_x_(0),
                                                  mouse_last_y_(0){}
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void MIAApp::Init(
    int argc,
    char* argv[],
    int x,
    int y,
    ColorData background_color) {
  BaseGfxApp::Init(argc, argv,
                   x, y,
                   GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH,
                   true,
                   width()+51,
                   50);

  // Set the name of the window
  set_caption("MIA");

  // Initialize Interface
  InitializeBuffers(background_color, width(), height());

  // since we only have two tools in this application then
  // we only need to make 2 length long array of tools
  tools_ = new Tool* [2];
  tools_[0] = ToolFactory::CreateTool(0);
  tools_[1] = ToolFactory::CreateTool(5);

  InitGlui();
  InitGraphics();
}

void MIAApp::Display(void) {
  DrawPixels(0, 0, width(), height(), display_buffer_->data());
}

MIAApp::~MIAApp(void) {
  if (display_buffer_) {
    delete display_buffer_;
  }
  // Delete each of the tools befoe deleting the list of tools pointers
  if (tools_) {
    delete tools_[0];
    delete tools_[1];
  }

  delete [] tools_;

}

void MIAApp::MouseMoved(int x, int y) {}

void MIAApp::MouseDragged(int x, int y) {

  if (tools_[cur_tool_]->should_smear()) {
    int max_steps = tools_[cur_tool_]->max_smear();

    // We implimented a smoothing feature by interpolating between
    // mouse events. This is at the expense of processing, though,
    // because we just "stamp" the tool many times between the two
    // even locations. you can reduce max_steps until it runs
    // smoothly on your machine.

    // Get the differences between the events
    // in each direction
    int delta_x = x-mouse_last_x_;
    int delta_y = y-mouse_last_y_;

    // Calculate the min number of steps necesary to fill
    // completely between the two event locations.
    float pixels_between = fmax(abs(delta_x), abs(delta_y));
    int step_size = 1;

    // Optimize by maxing out at the max_steps,
    // and fill evenly between
    if (pixels_between > max_steps) {
      step_size = pixels_between/max_steps;
    }

    // Iterate between the event locations
    for (int i = 0; i < pixels_between; i+=step_size) {
      int curr_x = mouse_last_x_+(i*delta_x/pixels_between);
      int curr_y = mouse_last_y_+(i*delta_y/pixels_between);

      tools_[cur_tool_]->ApplyToBuffer(curr_x, height()-curr_y,
                                       ColorData(cur_color_red_,
                                                 cur_color_green_,
                                                 cur_color_blue_),
                                       display_buffer_);
    }
  }

  // let the previous point catch up with the current.
  mouse_last_x_ = x;
  mouse_last_y_ = y;

}

void MIAApp::LeftMouseDown(int x, int y) {
  std::cout << "mousePressed " << x << " " << y << std::endl;

  display_buffer_ = state_manager_.CommitState(display_buffer_);

  tools_[cur_tool_]->ApplyToBuffer(x, height()-y, ColorData(cur_color_red_,
                                                            cur_color_green_,
                                                            cur_color_blue_),
                                   display_buffer_);

  mouse_last_x_ = x;
  mouse_last_y_ = y;

}

void MIAApp::LeftMouseUp(int x, int y) {
  std::cout << "mouseReleased " << x << " " << y << std::endl;
}

void MIAApp::InitializeBuffers(ColorData background_color,
                               int width, int height) {
  display_buffer_ = new PixelBuffer(width, height, background_color);
}

void MIAApp::InitGlui(void) {
  // Select first tool (this activates the first radio button in glui)
  cur_tool_ = 0;

  new GLUI_Column(glui(), false);
  GLUI_Panel *tool_panel = new GLUI_Panel(glui(), "Tool Type");
  {
    GLUI_RadioGroup *radio = new GLUI_RadioGroup(tool_panel, &cur_tool_,
                                                 UICtrl::UI_TOOLTYPE,
                                                 s_gluicallback);
    // Create interface buttons for different tools:
    new GLUI_RadioButton(radio, "Pen");
    new GLUI_RadioButton(radio, "Marker");
  }

  /* Initialize state management (undo, redo, quit) */
  state_manager_.InitGlui(glui(), s_gluicallback);
/*
  new GLUI_Button(const_cast<GLUI*>(glui()),
                  "Quit", UICtrl::UI_QUIT,
                  static_cast<GLUI_Update_CB>(exit));
*/
  /* Initialize Filtering */
  filter_manager_.InitGlui(glui(), s_gluicallback);

  /* Initialize image I/O */
  io_manager_.InitGlui(glui(), s_gluicallback);
  return;
}

void MIAApp::GluiControl(int control_id) {
  switch (control_id) {
    case UICtrl::UI_APPLY_SHARP:
      filter_manager_.ApplySharpen(&display_buffer_);
      break;
    case UICtrl::UI_APPLY_MOTION_BLUR:
      filter_manager_.ApplyMotionBlur(&display_buffer_);
      break;
    case UICtrl::UI_APPLY_EDGE:
      filter_manager_.ApplyEdgeDetect(&display_buffer_);
      break;
    case UICtrl::UI_APPLY_THRESHOLD:
      filter_manager_.ApplyThreshold(&display_buffer_);
      break;
    case UICtrl::UI_APPLY_SATURATE:
      filter_manager_.ApplySaturate(&display_buffer_);
      break;
    case UICtrl::UI_APPLY_CHANNEL:
      filter_manager_.ApplyChannel(&display_buffer_);
      break;
    case UICtrl::UI_APPLY_QUANTIZE:
      filter_manager_.ApplyQuantize(&display_buffer_);
      break;
    case UICtrl::UI_APPLY_BLUR:
      filter_manager_.ApplyBlur(&display_buffer_);
      break;
    case UICtrl::UI_FILE_BROWSER:
      io_manager_.set_image_file(io_manager_.file_browser()->get_file());
      break;
    case UICtrl::UI_LOAD_CANVAS_BUTTON:
      io_manager_.LoadImageToCanvas(&display_buffer_);
      SetWindowDimensions(display_buffer_->width(),
                        display_buffer_->height());
      break;
    case UICtrl::UI_LOAD_STAMP_BUTTON:
    /*
      PixelBuffer * loadedStamp;
      io_manager_.LoadImageToStamp(&loadedStamp);
      static_cast<TStamp*>(
          tools_[ToolFactory::TOOL_STAMP])->set_stamp_buffer(loadedStamp);
    */
      break;
    case UICtrl::UI_SAVE_CANVAS_BUTTON:
      // Reload the current directory:
      io_manager_.file_browser()->fbreaddir(".");
      io_manager_.SaveCanvasToFile(*display_buffer_);
      break;
    case UICtrl::UI_NEXT_IMAGE_BUTTON:
      io_manager_.LoadNextImage();
      break;
    case UICtrl::UI_PREV_IMAGE_BUTTON:
      io_manager_.LoadPreviousImage();
      break;
    case UICtrl::UI_FILE_NAME:
      io_manager_.set_image_file(io_manager_.file_name());
      break;
    case UICtrl::UI_UNDO:
      state_manager_.UndoOperation(&display_buffer_);
      SetWindowDimensions(display_buffer_->width(),
                          display_buffer_->height());
      break;
    case UICtrl::UI_REDO:
      state_manager_.RedoOperation(&display_buffer_);
      SetWindowDimensions(display_buffer_->width(),
                          display_buffer_->height());
      Display();
      break;
    default:
      break;
  }

  // Forces canvas to update changes made in this function
  glui()->post_update_main_gfx();
}

void MIAApp::InitGraphics(void) {
  // Initialize OpenGL for 2D graphics as used in the BrushWork app
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluOrtho2D(0, width(), 0, height());
  glViewport(0, 0, width(), height());
}


}  /* namespace image_tools */
