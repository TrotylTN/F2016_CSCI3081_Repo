/*******************************************************************************
 * Name            : mia_cmd.cc
 * Project         : MIA
 * Module          : App
 * Description     : Implementation of MIACmd
 * Copyright       : 2016 CSCI3081W Group A01. all rights reserved.
 * Creation Date   : 12/06/2016
 * Original Author : CSCI3081W Group A01
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/mia_cmd.h"
#include <stdexcept>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
MIACmd::MIACmd(void) : filename_({}),
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

}

MIACmd::MIACmd(int argc, char *argv[]) {
  MIACmd::MIACmd();
  try {
    // bitset constructor throws an invalid_argument if initialized
  }
  catch (const std::invalid_argument& ia) {

  }
}
/*******************************************************************************
 * Member Functions
 ******************************************************************************/


}  /* namespace image_tools */
