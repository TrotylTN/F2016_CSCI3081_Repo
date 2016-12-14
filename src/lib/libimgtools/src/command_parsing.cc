/*******************************************************************************
 * Name            : mia_cmd.cc
 * Project         : MIA
 * Module          : App
 * Description     : Implementation of CommandParsing
 * Copyright       : 2016 CSCI3081W Group A01. all rights reserved.
 * Creation Date   : 12/06/2016
 * Original Author : CSCI3081W Group A01
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/command_parsing.h"
#include <sys/stat.h>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <stdexcept>
#include "include/image_handler.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
CommandParsing::CommandParsing(void) : filename_({}),
                       parseresult_(0),
                       sharpen_(false),
                       sharpen_amount_(0),
                       edge_(false),
                       threshold_(false),
                       threshold_amount_(0),
                       quantize_(false),
                       quantize_bin_(2),
                       blur_(false),
                       blur_amount_(0),
                       saturate_(false),
                       saturate_amount_(0),
                       channel_(false),
                       channel_red_(0),
                       channel_green_(0),
                       channel_blue_(0) {}

CommandParsing::CommandParsing(int argc, char** argv) : filename_({}),
                                        parseresult_(0),
                                        sharpen_(false),
                                        sharpen_amount_(0),
                                        edge_(false),
                                        threshold_(false),
                                        threshold_amount_(0),
                                        quantize_(false),
                                        quantize_bin_(2),
                                        blur_(false),
                                        blur_amount_(0),
                                        saturate_(false),
                                        saturate_amount_(0),
                                        channel_(false),
                                        channel_red_(0),
                                        channel_green_(0),
                                        channel_blue_(0) {
  std::vector <std::string> argstr;
  argstr.clear();
  for (int i = 1; i < argc; i++)
    argstr.push_back(std::string(argv[i]));
  for (std::size_t i = 0; i < argstr.size(); i++) {
    if (argstr[i] == "-h") {
      this->parseresult_ = HELP_MESSAGE;
      return;
    }
  }

  if (argstr.size() < 2) {
    this->parseresult_ = CMD_ERROR;
    return;
  }
  if (argstr[0][0] == '-' || argstr[argstr.size() - 1][0] == '-') {
    this->parseresult_ = CMD_ERROR;
    return;
  }
  std::size_t numofinsign, numofoutsign;
  numofinsign = std::count(argstr[0].begin(), argstr[0].end(), '#');
  numofoutsign = std::count(argstr[argstr.size() - 1].begin(),
                            argstr[argstr.size() - 1].end(),
                            '#');
  if (numofinsign != numofoutsign) {
    this->parseresult_ = FILE_ERROR;
    return;
  }
  GenFileNamePair(argstr[0], argstr[argstr.size() - 1], numofinsign);
  if (this->filename_.size() == 0) {
    this->parseresult_ = FILE_ERROR;
    return;
  }

  if (argstr[1] == "-compare") {
    if (argstr.size() == 3) {
      this->parseresult_ = COMPARE_IMG;
      for (std::size_t i = 0; i < this->filename_.size();) {
        std::ifstream filetest(this->filename_[i].second.c_str());
        if (filetest.good()) {
          struct stat stat_outfile;
          stat(this->filename_[i].second.c_str(), &stat_outfile);
          if (S_ISREG(stat_outfile.st_mode)) {
            if (ImageHandler::image_type(this->filename_[i].second) !=
                ImageHandler::UNKNOWN_IMAGE) {
              i++;
            } else {
              this->filename_.erase(this->filename_.begin() + i);
            }
          } else {
            this->filename_.erase(this->filename_.begin() + i);
          }
        } else {
          this->filename_.erase(this->filename_.begin() + i);
        }
      }
      if (this->filename_.size() == 0) {
        this->parseresult_ = FILE_ERROR;
      }
      return;
    } else {
      this->parseresult_ = CMD_ERROR;
      return;
    }
  }

  for (std::size_t i = 1; i < argstr.size() - 1; i++) {
    if (argstr[i] == "-sharpen") {
      sharpen_ = true;
      i++;
      if (i >= argstr.size() - 1) {
        this->parseresult_ = ARGUMENTS_ERROR;
        return;
      } else {
        if (!IsValidNum(argstr[i])) {
          this->parseresult_ = ARGUMENTS_ERROR;
          return;
        }
        try {
          sharpen_amount_ = stof(argstr[i]);
        }
        catch (const std::invalid_argument& ia) {
          this->parseresult_ = ARGUMENTS_ERROR;
          return;
        }
      }
      if (sharpen_amount_ < 1.0 || sharpen_amount_ > 100.0) {
        this->parseresult_ = ARGUMENTS_ERROR;
        return;
      }
    } else if (argstr[i] == "-edge") {
      edge_ = true;
    } else if (argstr[i] == "-threshold") {
      threshold_ = true;
      i++;
      if (i >= argstr.size() - 1) {
        this->parseresult_ = ARGUMENTS_ERROR;
        return;
      } else {
        if (!IsValidNum(argstr[i])) {
          this->parseresult_ = ARGUMENTS_ERROR;
          return;
        }
        try {
          threshold_amount_ = stof(argstr[i]);
        }
        catch (const std::invalid_argument& ia) {
          this->parseresult_ = ARGUMENTS_ERROR;
          return;
        }
      }
      if (threshold_amount_ < 0.0 || threshold_amount_ > 1.0) {
        this->parseresult_ = ARGUMENTS_ERROR;
        return;
      }
    } else if (argstr[i] == "-quantize") {
      quantize_ = true;
      double bin_temp;
      i++;
      if (i >= argstr.size() - 1) {
        this->parseresult_ = ARGUMENTS_ERROR;
        return;
      } else {
        if (!IsValidNum(argstr[i])) {
          this->parseresult_ = ARGUMENTS_ERROR;
          return;
        }
        try {
          bin_temp = stof(argstr[i]);
        }
        catch (const std::invalid_argument& ia) {
          this->parseresult_ = ARGUMENTS_ERROR;
          return;
        }
      }
      quantize_bin_ = static_cast<int>(bin_temp);
      if (argstr[i].find('.') != std::string::npos) {
        this->parseresult_ = ARGUMENTS_ERROR;
        return;
      }
      if (quantize_bin_ < 2 || quantize_bin_ > 256) {
        this->parseresult_ = ARGUMENTS_ERROR;
        return;
      }
    } else if (argstr[i] == "-blur") {
      blur_ = true;
      i++;
      if (i >= argstr.size() - 1) {
        this->parseresult_ = ARGUMENTS_ERROR;
        return;
      } else {
        if (!IsValidNum(argstr[i])) {
          this->parseresult_ = ARGUMENTS_ERROR;
          return;
        }
        try {
          blur_amount_ = stof(argstr[i]);
        }
        catch (const std::invalid_argument& ia) {
          this->parseresult_ = ARGUMENTS_ERROR;
          return;
        }
      }
      if (blur_amount_ < 0.0 || blur_amount_ > 20.0) {
        this->parseresult_ = ARGUMENTS_ERROR;
        return;
      }
    } else if (argstr[i] == "-saturate") {
      saturate_ = true;
      i++;
      if (i >= argstr.size() - 1) {
        this->parseresult_ = ARGUMENTS_ERROR;
        return;
      } else {
        if (!IsValidNum(argstr[i])) {
          this->parseresult_ = ARGUMENTS_ERROR;
          return;
        }
        try {
          saturate_amount_ = stof(argstr[i]);
        }
        catch (const std::invalid_argument& ia) {
          this->parseresult_ = ARGUMENTS_ERROR;
          return;
        }
      }
      if (saturate_amount_ < -10.0 || saturate_amount_ > 10.0) {
        this->parseresult_ = ARGUMENTS_ERROR;
        return;
      }
    } else if (argstr[i] == "-channel") {
      channel_ = true;
      i++;
      if (i >= argstr.size() - 1) {
        this->parseresult_ = ARGUMENTS_ERROR;
        return;
      } else {
        if (!IsValidNum(argstr[i])) {
          this->parseresult_ = ARGUMENTS_ERROR;
          return;
        }
        try {
          channel_red_ = stof(argstr[i]);
        }
        catch (const std::invalid_argument& ia) {
          this->parseresult_ = ARGUMENTS_ERROR;
          return;
        }
      }
      i++;
      if (i >= argstr.size() - 1) {
        this->parseresult_ = ARGUMENTS_ERROR;
        return;
      } else {
        if (!IsValidNum(argstr[i])) {
          this->parseresult_ = ARGUMENTS_ERROR;
          return;
        }
        try {
          channel_green_ = stof(argstr[i]);
        }
        catch (const std::invalid_argument& ia) {
          this->parseresult_ = ARGUMENTS_ERROR;
          return;
        }
      }
      i++;
      if (i >= argstr.size() - 1) {
        this->parseresult_ = ARGUMENTS_ERROR;
        return;
      } else {
        if (!IsValidNum(argstr[i])) {
          this->parseresult_ = ARGUMENTS_ERROR;
          return;
        }
        try {
          channel_blue_ = stof(argstr[i]);
        }
        catch (const std::invalid_argument& ia) {
          this->parseresult_ = ARGUMENTS_ERROR;
          return;
        }
      }
      if (channel_red_ < 0.0 || channel_red_ > 10.0) {
        this->parseresult_ = ARGUMENTS_ERROR;
        return;
      }
      if (channel_green_ < 0.0 || channel_green_ > 10.0) {
        this->parseresult_ = ARGUMENTS_ERROR;
        return;
      }
      if (channel_blue_ < 0.0 || channel_blue_ > 10.0) {
        this->parseresult_ = ARGUMENTS_ERROR;
        return;
      }
    } else {
      this->parseresult_ = INVALID_FILTER;
      return;
    }
  }
  this->parseresult_ = SUCCESSFUL_PARSE;
  return;
}
/*******************************************************************************
 * Member Functions
 ******************************************************************************/

bool CommandParsing::IsValidNum(std::string num) {
  int num_of_dot = 0;
  if (num.size() == 0)
    return false;
  for (std::size_t i = 0; i < num.size(); i++) {
    if (num[i] == '-' && i == 0) {
      // this is fine
    } else if (num[i] == '.') {
      if (num_of_dot > 0)
        return false;
      num_of_dot++;
    } else if (num[i] < '0' || num[i] > '9') {
      return false;
    }
  }
  return true;
}

void CommandParsing::GenFileNamePair(std::string infilename,
                             std::string outfilename,
                             int rest_sign) {
  if (rest_sign == 0) {
    std::ifstream filetest(infilename.c_str());
    if (filetest.good()) {
      struct stat stat_infile;
      stat(infilename.c_str(), &stat_infile);
      if (S_ISREG(stat_infile.st_mode)) {
        if (ImageHandler::image_type(infilename) !=
            ImageHandler::UNKNOWN_IMAGE) {
          if (ImageHandler::image_type(outfilename) !=
              ImageHandler::UNKNOWN_IMAGE) {
                this->filename_.push_back(make_pair(infilename, outfilename));
              }
        }
      }
    }
    return;
  }
  std::size_t pos_sig_in = infilename.find('#');
  std::size_t pos_sig_out = outfilename.find('#');
  for (char dig = '0'; dig <= '9'; dig++) {
    infilename[pos_sig_in] = dig;
    outfilename[pos_sig_out] = dig;
    GenFileNamePair(infilename, outfilename, rest_sign - 1);
  }
}

}  /* namespace image_tools */
