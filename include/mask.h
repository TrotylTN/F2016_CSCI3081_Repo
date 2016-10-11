/*******************************************************************************
 * name            : mask.cc
 * project         : brushwork
 * module          : app
 * description     : implementation of mask for graph tools the all
 *                   mask would be install in a 2d matirx
 * copyright       : 2016 csci3081w GroupA-01. all rights reserved.
 * creation Date   : 10/09/16
 * Original Author : GroupA-01 All member
 *
 ******************************************************************************/

#ifndef INCLUDE_MASK_H_
#define INCLUDE_MASK_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#define MASK_LEN 41
#define CENTER 20
#define R_PEN 1.5
#define R_CAN 20.5
#define R_ERASER 10.5
#define R_REC 2.5

namespace image_tools {

class Mask{
  public:
    Mask(void);

    float matrix_[41][41];

    void switch_mask(int tool_number);
    void print_mask(void);
    float mask_radius(void);
  private:
    int cur_tool_;
    float mask_radius_;

};
}

#endif
