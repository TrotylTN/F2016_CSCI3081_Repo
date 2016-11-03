/*******************************************************************************
 * Name            : brushwork_app.h
 * Project         : BrushWork
 * Module          : App
 * Description     : Header file for BrushWork application.
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef SRC_INCLUDE_BRUSHWORK_APP_H_
#define SRC_INCLUDE_BRUSHWORK_APP_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include "include/base_gfx_app.h"
#include "include/color_data.h"
#include "include/pixel_buffer.h"
#include "include/tool.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for BrushWork.
 * It is a graphics app that derives from BaseGfxApp. It creates two graphics
 * windows, one for 2D painting and one for the buttons and other UI widgets to
 * control the brushes.
 **/
class BrushWorkApp : public BaseGfxApp {
 public:
  BrushWorkApp(
      int width,
      int height);

  virtual ~BrushWorkApp(void);

  void MouseDragged(int x, int y);
  void MouseMoved(int x, int y);
  void LeftMouseDown(int x, int y);
  void LeftMouseUp(int x, int y);
  void Display(void);
  void GluiControl(int control_id);

  virtual void Init(
      int argc,
      char* argv[],
      int x,
      int y,
      ColorData background_color);

 private:
  void InitGlui(void);
  void InitGraphics(void);

  /**
   * @brief Initialize the buffers for the main window
   */
  void InitializeBuffers(ColorData initial_color,
                         int width, int height);

  /** Pointer to pixel data for the screen */
  PixelBuffer *display_buffer_;

  int cur_tool_; /**< Currently selected tool from UI  */
  std::vector<Tool*> tools_;

  // Previous mouse coordinates for interpreting mouse moves
  int mouse_last_x_;
  int mouse_last_y_;
  float cur_color_red_;
  float cur_color_green_;
  float cur_color_blue_;

  GLUI_Spinner *spinner_r_; /**< Hook for accessing the UI red amount  */
  GLUI_Spinner *spinner_g_; /**< Hook for accessing the UI green amount  */
  GLUI_Spinner *spinner_b_; /**< Hook for accessing the UI blue amount  */

  /* Copy/move assignment/construction disallowed */
  BrushWorkApp(const BrushWorkApp &rhs) = delete;
  BrushWorkApp& operator=(const BrushWorkApp &rhs) = delete;
};

}  /* namespace image_tools */

#endif  // SRC_INCLUDE_BRUSHWORK_APP_H_
