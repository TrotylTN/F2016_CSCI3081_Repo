/*******************************************************************************
 * Name            : main.cc
 * Project         : FlashPhoto
 * Module          : App
 * Description     : Do ALL THE THINGS!
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include "include/flashphoto_app.h"
#include "include/color_data.h"
#include "include/command_parsing.h"

/*******************************************************************************
 * Functions
 ******************************************************************************/
int main(int argc, char* argv[]) {
  if (argc == 1) {
    // normal mode
    image_tools::FlashPhotoApp *app = new image_tools::FlashPhotoApp(800, 800);
    app->Init(argc, argv, 50, 50,
              image_tools::ColorData(1, 1, static_cast<float>(0.95)));

    // runMainLoop returns when the user closes the graphics window.
    app->RunMainLoop();
    delete app;
    exit(0);
  } else {
    // command line mode
    image_tools::CommandParsing *cmd_parsing;
    cmd_parsing = new image_tools::CommandParsing(argc, argv);
    int parsing_state = cmd_parsing->ParseResult();

    std::string brief_help, full_help, s_space;
    s_space = "                              ";
    brief_help = "usage: FlashPhoto source_file -compare destination_file\n";
    brief_help += "       FlashPhoto source_file ";
    brief_help += "[-sharpen sharpen_amount(1.0~100.0)]\n";
    brief_help += s_space + "[-edge]\n";
    brief_help += s_space + "[-threshold threshold_amount(0.0~1.0)]\n";
    brief_help += s_space + "[-quantize quantize_bin_number(2~256 integer)]\n";
    brief_help += s_space + "[-blur blur_amount(0.0~20.0)]\n";
    brief_help += s_space + "[-saturate saturate_amount(-10.0~10.0)]\n";
    brief_help += s_space + "[-channel red_amount(0.0~10.0)";
    brief_help += " green_amount(0.0~10.0) blue_amount(0.0~10.0)]\n";
    brief_help += s_space + "filename_to_be_save\n";
    brief_help += "please enter \"FlashPhoto -h\" for more information.\n";

    full_help = "Overview: FlashPhoto application\n\n";
    full_help += "Usage: FlashPhoto source_file -compare destination_file\n";
    full_help += "       FlashPhoto source_file [options] filename_to_be_save";
    full_help += "\n\nNotes:\n";
    full_help += "  source_file should be a valid image file\n";
    full_help += "  filename_to_be_save should be a filename ";
    full_help += "which extension is .png, .jpg or .jpeg\n\n";
    full_help += "Options:\n";
    full_help += "  -sharpen sharpen_amount\n";
    full_help += "      sharpen_amount should be a float and ";
    full_help += "in the range of [1.0, 100.0]\n";
    full_help += "  -edge\n";
    full_help += "      Create a representation of ";
    full_help += "the rate-of-change in the image\n";
    full_help += "  -threshold threshold_amount\n";
    full_help += "      threshold_amount should be a float and ";
    full_help += "in the range of [0.0, 1.0]\n";
    full_help += "  -quantize quantize_bin_number\n";
    full_help += "      quantize_bin_number should be an integer and ";
    full_help += "in the range of [2, 256]\n";
    full_help += "  -blur blur_amount\n";
    full_help += "      blur_amount should be a float and ";
    full_help += "in the range of [0.0, 20.0]\n";
    full_help += "  -saturate saturate_amount\n";
    full_help += "      saturate_amount should be a float and ";
    full_help += "in the range of [-10.0, 10.0]\n";
    full_help += "  -channel red_amount green_amount blue_amount\n";
    full_help += "      the three color arguments for channel filter should ";
    full_help += "all be floats and in the range of [0.0, 10.0]\n";

    if (parsing_state == image_tools::CommandParsing::FILE_ERROR) {
      std::cout << "Error: invalid filename or file not existent,"
      << " please check your input" << '\n';
      std::cout << brief_help << std::endl;
      return 1;
    }
    if (parsing_state == image_tools::CommandParsing::CMD_ERROR) {
      std::cout << "Error: input cannot be recognized" << '\n';
      std::cout << brief_help << std::endl;
      return 1;
    }
    if (parsing_state == image_tools::CommandParsing::INVALID_FILTER) {
      std::cout << "Error: input contained invalid filter" << '\n';
      std::cout << brief_help << std::endl;
      return 1;
    }
    if (parsing_state == image_tools::CommandParsing::ARGUMENTS_ERROR) {
      std::cout << "Error: filters contained invalid argument(s) or "
      << "didn't have appropriate argument(s)" << '\n';
      std::cout << brief_help << std::endl;
      return 1;
    }
    if (parsing_state == image_tools::CommandParsing::HELP_MESSAGE) {
      std::cout << full_help << '\n';
      return 0;
    }

    image_tools::FlashPhotoApp *app = new image_tools::FlashPhotoApp(800, 800);
    int app_result = app->CommandLineMode(cmd_parsing);
    delete app;
    if (app_result != 0) {
      std::cout << "Error: invalid filename or output directory"
      << " not existent, please check your input" << '\n';
      std::cout << brief_help << std::endl;
      return 1;
    }
  }
  return 0;
}
