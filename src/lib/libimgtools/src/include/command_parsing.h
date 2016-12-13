/*******************************************************************************
 * Name            : mia_cmd.h
 * Project         : MIA
 * Module          : App
 * Description     : Header file for CommandParsing class
 * Copyright       : 2016 CSCI3081W Group A01. all rights reserved.
 * Creation Date   : 12/06/2016
 * Original Author : CSCI3081W Group A01
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_COMMAND_PARSING_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_COMMAND_PARSING_H_

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
class CommandParsing {
 public:
  CommandParsing(void);
  CommandParsing(int argc, char** argv);
  enum RETURNCODE{
    SUCCESSFUL_PARSE = 0,
    COMPARE_IMG = 1,
    HELP_MESSAGE = 2,
    FILE_ERROR = 3,
    CMD_ERROR = 4,
    INVALID_FILTER = 5,
    ARGUMENTS_ERROR = 6
  };

  std::vector <std::pair<std::string, std::string> >
    FileName(void) { return filename_; }

  int ParseResult(void) { return parseresult_;}

  void GenFileNamePair(std::string infilename,
                       std::string outfilename,
                       int rest_sign);

  bool Sharpen(void) { return sharpen_; }
  float SharpenAmount(void) { return sharpen_amount_; }

  bool Edge(void) { return edge_; }

  bool Threshold(void) { return threshold_; }
  float ThresholdAmount(void) { return threshold_amount_; }

  bool Quantize(void) { return quantize_; }
  int QuantizeBin(void) { return quantize_bin_; }

  bool Blur(void) { return blur_; }
  float BlurAmount(void) { return blur_amount_; }

  bool Saturate(void) { return saturate_; }
  float SaturateAmount(void) { return saturate_amount_; }

  bool Channel(void) { return channel_; }
  float ChannelRed(void) { return channel_red_; }
  float ChannelBlue(void) { return channel_blue_; }
  float ChannelGreen(void) { return channel_green_; }

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

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_COMMAND_PARSING_H_
