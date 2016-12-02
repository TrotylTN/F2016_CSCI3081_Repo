/*******************************************************************************
 * Name            : tool_factory.cc
 * Project         : image_tools
 * Module          : Tool
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Description     : Implementation of ToolFactory
 * Creation Data   : 2/6/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/tool_factory.h"
#include "include/tool.h"
#include "include/t_pen.h"
#include "include/t_eraser.h"
#include "include/t_calligraphy_pen.h"
#include "include/t_highlighter.h"
#include "include/t_spray_can.h"
#include "include/t_chalk.h"
#include "include/t_blur.h"
#include "include/t_stamp.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
Tool* ToolFactory::CreateTool(int toolID) {
  Tool* tool = NULL;

  switch (toolID) {
    case TOOL_PEN:
      tool = new TPen();
      break;
    case TOOL_ERASER:
      tool = new TEraser();
      break;
    case TOOL_SPRAYCAN:
      tool = new TSprayCan();
      break;
    case TOOL_CALLIGRAPHYPEN:
      tool = new TCalligraphyPen();
      break;
    case TOOL_HIGHLIGHTER:
      tool = new THighlighter();
      break;
    case TOOL_CHALK:
      tool = new TChalk();
      break;
    case TOOL_STAMP:
      tool = new TStamp();
      break;
    case TOOL_BLUR:
      tool = new TBlur();
      break;
    default:
      tool = NULL;
      break;
  }

  return tool;
}

} /* namespace image_tools */
