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
#include "include/filter_factory.h"
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
                                                  cur_color_red_(1.0),
                                                  cur_color_green_(0.0),
                                                  cur_color_blue_(0.0),
                                                  mouse_last_x_(0),
                                                  mouse_last_y_(0) {}
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void MIAApp::CommandLineMode(MIACmd *parsed_res) {
  for (unsigned long i = 0; i < parsed_res->FileName().size(); i++) {
    std::string filename_in, filename_out;
    filename_in = parsed_res->FileName()[i].first;
    filename_out = parsed_res->FileName()[i].second;
    if (parsed_res->ParseResult() == MIACmd::COMPARE_IMG) {
      PixelBuffer *infile, *outfile;
      infile = ImageHandler::LoadImage(filename_in);
      outfile = ImageHandler::LoadImage(filename_out);
      if (*infile == *outfile)
        std::cout << "1" << '\n';
      else
        std::cout << "0" << '\n';
      if (infile)
        delete infile;
      if (outfile)
        delete outfile;
    }
    else {
      PixelBuffer *cmd_pixelbuffer;
      cmd_pixelbuffer = ImageHandler::LoadImage(filename_in);

      if (parsed_res->Sharpen()) {
        Filter * f_sharpen = FilterFactory::CreateFilter(
                               FilterFactory::FILTER_SHARPEN,
                               1, parsed_res->SharpenAmount());
        FilterFactory::ApplyFilter(*f_sharpen, &cmd_pixelbuffer);
        delete f_sharpen;
      }
      if (parsed_res->Edge()) {
        Filter * f_edge = FilterFactory::CreateFilter(
                            FilterFactory::FILTER_EDGE_DETECT,
                            0);
        FilterFactory::ApplyFilter(*f_edge, &cmd_pixelbuffer);
        delete f_edge;
      }
      if (parsed_res->Threshold()) {
        Filter * f_threshold = FilterFactory::CreateFilter(
                                 FilterFactory::FILTER_THRESHOLD,
                                 1, parsed_res->ThresholdAmount());
        FilterFactory::ApplyFilter(*f_threshold, &cmd_pixelbuffer);
        delete f_threshold;
      }
      if (parsed_res->Quantize()) {
        Filter * f_quantize = FilterFactory::CreateFilter(
                                FilterFactory::FILTER_QUANTIZE,
                                1, parsed_res->QuantizeBin());
        FilterFactory::ApplyFilter(*f_quantize, &cmd_pixelbuffer);
        delete f_quantize;
      }
      if (parsed_res->Blur()) {
        Filter * f_blur = FilterFactory::CreateFilter(
                            FilterFactory::FILTER_BLUR,
                            1, parsed_res->BlurAmount());
        FilterFactory::ApplyFilter(*f_blur, &cmd_pixelbuffer);
        delete f_blur;
      }
      if (parsed_res->Saturate()) {
        Filter * f_saturate = FilterFactory::CreateFilter(
                                FilterFactory::FILTER_SATURATION,
                                1, parsed_res->SaturateAmount());
        FilterFactory::ApplyFilter(*f_saturate, &cmd_pixelbuffer);
        delete f_saturate;
      }
      if (parsed_res->Channel()) {
        Filter * f_channel = FilterFactory::CreateFilter(
                               FilterFactory::FILTER_CHANNELS,
                               3,
                               parsed_res->ChannelRed(),
                               parsed_res->ChannelGreen(),
                               parsed_res->ChannelBlue());
        FilterFactory::ApplyFilter(*f_channel, &cmd_pixelbuffer);
        delete f_channel;
      }

      bool save_res = ImageHandler::SaveImage(filename_out, cmd_pixelbuffer);
      if (save_res) {
        std::cout << '\"' << filename_out << '\"'
                  << " successfully saved." << '\n';
      } else {
        std::cout << '\"' << filename_out << '\"'
                  << " failed to save, please enter a valid image filename."
                  << '\n';
      }
      if (cmd_pixelbuffer)
        delete cmd_pixelbuffer;
    }
  }
}

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
  // we only need to create an array containing two tools
  tools_ = new Tool* [2];
  tools_[0] = ToolFactory::CreateTool(ToolFactory::TOOL_PEN);
  tools_[1] = ToolFactory::CreateTool(ToolFactory::TOOL_STAMP);
  // Load marker image (assumed the current directory is set to root directory)
  static_cast<TStamp*>(tools_[1])
                      ->set_stamp_buffer(
                        ImageHandler::LoadImage(marker_fname_));
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

  /* Initialize Filtering */
  filter_manager_.InitGlui(glui(), s_gluicallback);

  /* Initialize image I/O */
  io_manager_.InitGlui(glui(), s_gluicallback);
  return;
}

void MIAApp::GluiControl(int control_id) {
  switch (control_id) {
    case UICtrl::UI_APPLY_SHARP:
      display_buffer_ = state_manager_.CommitState(display_buffer_);
      filter_manager_.ApplySharpen(&display_buffer_);
      break;
    case UICtrl::UI_APPLY_EDGE:
      display_buffer_ = state_manager_.CommitState(display_buffer_);
      filter_manager_.ApplyEdgeDetect(&display_buffer_);
      break;
    case UICtrl::UI_APPLY_THRESHOLD:
      display_buffer_ = state_manager_.CommitState(display_buffer_);
      filter_manager_.ApplyThreshold(&display_buffer_);
      break;
    case UICtrl::UI_APPLY_SATURATE:
      display_buffer_ = state_manager_.CommitState(display_buffer_);
      filter_manager_.ApplySaturate(&display_buffer_);
      break;
    case UICtrl::UI_APPLY_CHANNEL:
      display_buffer_ = state_manager_.CommitState(display_buffer_);
      filter_manager_.ApplyChannel(&display_buffer_);
      break;
    case UICtrl::UI_APPLY_QUANTIZE:
      display_buffer_ = state_manager_.CommitState(display_buffer_);
      filter_manager_.ApplyQuantize(&display_buffer_);
      break;
    case UICtrl::UI_APPLY_BLUR:
      display_buffer_ = state_manager_.CommitState(display_buffer_);
      filter_manager_.ApplyBlur(&display_buffer_);
      break;
    case UICtrl::UI_FILE_BROWSER:
      io_manager_.set_image_file(io_manager_.file_browser()->get_file());
      break;
    case UICtrl::UI_LOAD_CANVAS_BUTTON:
      display_buffer_ = state_manager_.CommitState(display_buffer_);
      io_manager_.LoadImageToCanvas(&display_buffer_);
      SetWindowDimensions(display_buffer_->width(),
                        display_buffer_->height());
      io_manager_.next_prev_image_toggle();
      break;
    case UICtrl::UI_SAVE_CANVAS_BUTTON:
      // Reload the current directory:
      io_manager_.file_browser()->fbreaddir(".");
      io_manager_.SaveCanvasToFile(*display_buffer_);
      break;
    case UICtrl::UI_NEXT_IMAGE_BUTTON:
      display_buffer_ = state_manager_.CommitState(display_buffer_);
      io_manager_.LoadNextImage();
      io_manager_.LoadImageToCanvas(&display_buffer_);
      SetWindowDimensions(display_buffer_->width(),
                        display_buffer_->height());
      break;
    case UICtrl::UI_PREV_IMAGE_BUTTON:
      display_buffer_ = state_manager_.CommitState(display_buffer_);
      io_manager_.LoadPreviousImage();
      io_manager_.LoadImageToCanvas(&display_buffer_);
      SetWindowDimensions(display_buffer_->width(),
                        display_buffer_->height());
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
