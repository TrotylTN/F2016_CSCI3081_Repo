/*******************************************************************************
 * Name            : main.cc
 * Project         : MIA
 * Module          : main
 * Description     : Entry point for MIA application
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 1/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/mia_app.h"
#include "include/color_data.h"
#include "include/mia_cmd.h"
#include <iostream>

/*******************************************************************************
 * Non-Member Functions
 ******************************************************************************/
int main(int argc, char** argv) {
  if (argc == 1) {
    image_tools::MIAApp *app = new image_tools::MIAApp(
        400,
        400,
        "resources/marker.png");
    app->Init(argc, argv, 50, 50,
              image_tools::ColorData(1, 1, static_cast<float>(0.95)));
    app->RunMainLoop();
    delete app;
  } else {
    image_tools::MIACmd *cmd_parsing;
    cmd_parsing = new image_tools::MIACmd(argc, argv);
    int parsing_state = cmd_parsing->ParseResult();
    std::string brief_help, full_help;
    brief_help = "usage: MIA source_file -compare destination_file\n";
    brief_help += "       MIA source_file ";
    brief_help += "[-sharpen sharpen_amount(1.0~100.0)]\n";
    brief_help += "                       [-edge]\n";
    brief_help += "                       [-threshold threshold_amount(0.0~1.0)]\n";
    brief_help += "                       [-quantize quantize_bin_number(2~256 integer)]\n";
    brief_help += "                       [-blur blur_amount(0.0~20.0)]\n";
    brief_help += "                       [-saturate saturate_amount(-10.0~10.0)]\n";
    brief_help += "                       [-channel red_amount(0.0~10.0)";
    brief_help += " green_amount(0.0~10.0) blue_amount(0.0~10.0)]\n";
    brief_help += "                       filename_to_be_save\n";
    brief_help += "please enter \"MIA -h\" for more information.\n";
    if (parsing_state == image_tools::MIACmd::FILE_ERROR) {
      std::cout << "Error: invalid filename or file not existent,"
                << " please check your input" << '\n';
      std::cout << brief_help << std::endl;
      return 1;
    }
    if (parsing_state == image_tools::MIACmd::CMD_ERROR) {
      std::cout << "Error: input cannot be recognized" << '\n';
      std::cout << brief_help << std::endl;
      return 1;
    }
    if (parsing_state == image_tools::MIACmd::INVALID_FILTER) {
      std::cout << "Error: input contained invalid filter" << '\n';
      std::cout << brief_help << std::endl;
      return 1;
    }
    if (parsing_state == image_tools::MIACmd::ARGUMENTS_ERROR) {
      std::cout << "Error: filters contained invalid argument(s) or "
                << "didn't have appropriate argument(s)" << '\n';
      std::cout << brief_help << std::endl;
      return 1;
    }
    if (parsing_state == image_tools::MIACmd::HELP_MESSAGE) {
      return 0;
    }


    // if (cmd_parsing)
    // std::cout<<cmd_parsing->FileName().size() << std::endl;
    // for (int i = 0 ; i < cmd_parsing->FileName().size(); i++) {
    //   std::cout<< cmd_parsing->FileName()[i].first << ", " << cmd_parsing->FileName()[i].second << std::endl;
  }
  return 0;
} /* main() */
