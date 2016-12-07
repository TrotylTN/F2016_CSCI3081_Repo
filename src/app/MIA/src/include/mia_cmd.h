/*******************************************************************************
 * Name            : mia_cmd.h
 * Project         : MIA
 * Module          : App
 * Description     : Header file for MIACmd class
 * Copyright       : 2016 CSCI3081W Group A01. all rights reserved.
 * Creation Date   : 12/06/2016
 * Original Author : CSCI3081W Group A01
 *
 ******************************************************************************/

#ifndef SRC_APP_MIA_SRC_INCLUDE_MIA_CMD_H_
#define SRC_APP_MIA_SRC_INCLUDE_MIA_CMD_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
class MIACmd {
 public:
  MIACmd(void);
  MIACmd(int argc, char *argv[]);
  enum {
    HELP_MESSAGE,
    ERROR_INPUT,
    SUCCESSFUL_PARSE,
    NO_CMD_LINES
  };
 private:
}

}  /* namespace image_tools */

#endif  // SRC_APP_MIA_SRC_INCLUDE_MIA_CMD_H_
