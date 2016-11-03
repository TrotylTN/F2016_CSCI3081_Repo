/*******************************************************************************
 * Name            : brushwork_app.cc
 * Project         : BrushWork
 * Module          : App
 * Description     : Implementation of BrushWrok
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/brushwork_app.h"
#include <assert.h>
#include <cmath>
#include <iostream>
#include "include/color_data.h"
#include "include/pixel_buffer.h"
#include "include/ui_ctrl.h"
#include "include/tool_factory.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
BrushWorkApp::BrushWorkApp(int width,
                           int height)
    : BaseGfxApp(width,
                 height),
      display_buffer_(nullptr),
      cur_tool_(0),
      tools_(),
      mouse_last_x_(0),
      mouse_last_y_(0),
      cur_color_red_(0.0),
      cur_color_green_(0.0),
      cur_color_blue_(0.0),
      spinner_r_(nullptr),
      spinner_g_(nullptr),
      spinner_b_(nullptr) {}

BrushWorkApp::~BrushWorkApp(void) {
  if (display_buffer_) {
    delete display_buffer_;
  }
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void BrushWorkApp::Init(
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
  set_caption("BrushWork");

  // Initialize Interface
  InitializeBuffers(background_color, width(), height());

  // Create array of tools and populate
  for (int i = 0; i < ToolFactory::num_tools(); i++) {
    Tool* t = ToolFactory::CreateTool(i);
    assert(t);
    tools_.push_back(t);
  }
  InitGlui();
  InitGraphics();
}

void BrushWorkApp::Display(void) {
  DrawPixels(0, 0, width(), height(), display_buffer_->data());
}


void BrushWorkApp::MouseMoved(int x, int y) {}

void BrushWorkApp::MouseDragged(int x, int y) {
  int max_steps = 30;

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

  // let the previous point catch up with the current.
  mouse_last_x_ = x;
  mouse_last_y_ = y;
}
void BrushWorkApp::LeftMouseDown(int x, int y) {
  tools_[cur_tool_]->ApplyToBuffer(x, height()-y,
                                   ColorData(cur_color_red_,
                                             cur_color_green_,
                                             cur_color_blue_),
                                   display_buffer_);
  mouse_last_x_ = x;
  mouse_last_y_ = y;
}

void BrushWorkApp::LeftMouseUp(int x, int y) {
  std::cout << "mouseReleased " << x << " " << y << std::endl;
}

void BrushWorkApp::InitializeBuffers(
    ColorData background_color,
    int width,
    int height) {
  display_buffer_ = new PixelBuffer(width, height, background_color);
}

void BrushWorkApp::InitGlui(void) {
  // Select first tool (this activates the first radio button in glui)
  cur_tool_ = 0;

  GLUI_Panel *tool_panel = new GLUI_Panel(glui(), "Tool Type");
  GLUI_RadioGroup *radio = new GLUI_RadioGroup(tool_panel,
                                               &cur_tool_,
                                               UICtrl::UI_TOOLTYPE,
                                               s_gluicallback);

  // Create interface buttons for different tools:
  for (int i = 0; i < ToolFactory::num_tools(); ++i) {
    new GLUI_RadioButton(radio, tools_[i]->name().c_str());
  }

  GLUI_Panel *color_panel = new GLUI_Panel(glui(), "Tool Color");

  cur_color_red_ = 0;
  spinner_r_  = new GLUI_Spinner(color_panel, "Red:", &cur_color_red_,
                                 UICtrl::UI_COLOR_R, s_gluicallback);
  spinner_r_->set_float_limits(0, 1.0);

  cur_color_green_ = 0;
  spinner_g_ = new GLUI_Spinner(color_panel, "Green:", &cur_color_green_,
                                UICtrl::UI_COLOR_G, s_gluicallback);
  spinner_g_->set_float_limits(0, 1.0);

  cur_color_blue_ = 0;
  spinner_b_  = new GLUI_Spinner(color_panel, "Blue:", &cur_color_blue_,
                                 UICtrl::UI_COLOR_B, s_gluicallback);
  spinner_b_->set_float_limits(0, 1.0);
  new GLUI_Button(color_panel,
                  "Red", UICtrl::UI_PRESET_RED,
                  s_gluicallback);
  new GLUI_Button(color_panel,
                  "Orange", UICtrl::UI_PRESET_ORANGE,
                  s_gluicallback);
  new GLUI_Button(color_panel,
                  "Yellow", UICtrl::UI_PRESET_YELLOW,
                  s_gluicallback);
  new GLUI_Button(color_panel,
                  "Green", UICtrl::UI_PRESET_GREEN,
                  s_gluicallback);
  new GLUI_Button(color_panel,
                  "Blue", UICtrl::UI_PRESET_BLUE,
                  s_gluicallback);
  new GLUI_Button(color_panel,
                  "Purple", UICtrl::UI_PRESET_PURPLE,
                  s_gluicallback);
  new GLUI_Button(color_panel,
                  "White", UICtrl::UI_PRESET_WHITE,
                  s_gluicallback);
  new GLUI_Button(color_panel,
                  "Black", UICtrl::UI_PRESET_BLACK,
                  s_gluicallback);

  new GLUI_Button(glui(),
                  "Quit", UICtrl::UI_QUIT,
                  static_cast<GLUI_Update_CB>(exit));
}


void BrushWorkApp::InitGraphics(void) {
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

void BrushWorkApp::GluiControl(int control_id) {
  switch (control_id) {
    case UICtrl::UI_PRESET_RED:
      cur_color_red_ = 1;
      cur_color_green_ = 0;
      cur_color_blue_ = 0;
      break;
    case UICtrl::UI_PRESET_ORANGE:
      cur_color_red_ = 1;
      cur_color_green_ = 0.5;
      cur_color_blue_ = 0;
      break;
    case UICtrl::UI_PRESET_YELLOW:
      cur_color_red_ = 1;
      cur_color_green_ = 1;
      cur_color_blue_ = 0;
      break;
    case UICtrl::UI_PRESET_GREEN:
      cur_color_red_ = 0;
      cur_color_green_ = 1;
      cur_color_blue_ = 0;
      break;
    case UICtrl::UI_PRESET_BLUE:
      cur_color_red_ = 0;
      cur_color_green_ = 0;
      cur_color_blue_ = 1;
      break;
    case UICtrl::UI_PRESET_PURPLE:
      cur_color_red_ = 0.5;
      cur_color_green_ = 0;
      cur_color_blue_ = 1;
      break;
    case UICtrl::UI_PRESET_WHITE:
      cur_color_red_ = 1;
      cur_color_green_ = 1;
      cur_color_blue_ = 1;
      break;
    case UICtrl::UI_PRESET_BLACK:
      cur_color_red_ = 0;
      cur_color_green_ = 0;
      cur_color_blue_ = 0;
      break;
    default:
      break;
  }

  spinner_b_->set_float_val(cur_color_blue_);
  spinner_g_->set_float_val(cur_color_green_);
  spinner_r_->set_float_val(cur_color_red_);
}

}  /* namespace image_tools */
