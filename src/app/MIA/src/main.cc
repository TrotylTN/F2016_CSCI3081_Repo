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
    if (parsing_state == image_tools::MIACmd::FILE_ERROR) {
      return 1;
    }
    if (parsing_state == image_tools::MIACmd::CMD_ERROR) {
      return 1;
    }
    if (parsing_state == image_tools::MIACmd::INVALID_FILTER) {
      return 1;
    }
    if (parsing_state == image_tools::MIACmd::ARGUMENTS_ERROR) {
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
