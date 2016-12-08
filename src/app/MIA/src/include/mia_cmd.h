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
#include <vector>
#include <utility>

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
  enum RETURNCODE{
    NO_CMD_LINES = 0,
    SUCCESSFUL_PARSE = 1,
    COMPARE_IMG = 2,
    HELP_MESSAGE = 3,
    FILE_ERROR = 4,
    CMD_ERROR = 5,
    ARGUMENTS_ERROR = 6
  };

  std::vector <std::pair<std::string, std::string> >
    FileName(void) { return filename_; }

  int ParseResult(void) { return parseresult_;}

  void GenFileNamePair(std::string infilename,
                       std::string outfilename,
                       int rest_sign);
 private:
  std::vector <std::pair<std::string, std::string> > filename_;
  int parseresult_;

  bool sharpen_;
  float sharpen_amount_;

  bool edge_;

  bool threshold_;
  float threshold_amount_;

  bool quantize_;
  int quantize_bin_;

  bool blur_;
  float blur_amount_;

  bool saturate_;
  float saturate_amount_;

  bool channel_;
  float channel_red_;
  float channel_green_;
  float channel_blue_;

};

}  /* namespace image_tools */

#endif  // SRC_APP_MIA_SRC_INCLUDE_MIA_CMD_H_
