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

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/mask.h"
#include <cstring>
#include <iostream>
#include <cmath>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {
/*******************************************************************************
 * Constructors
 ******************************************************************************/
    Mask::Mask(void) {
        memset(this->matrix_, 0, sizeof this->matrix_);
        this->cur_tool_ = -1; //-1 means no tool is active.
    }

    Mask::Mask(int tool_number) {
        memset(this->matrix_, 0, sizeof this->matrix_);
        Mask::switch_mask(tool_number);
    }

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
    // Set up the Matirx as a mast
    // to reprensent each of tool style
    void Mask::switch_mask(int tool_number) {
        if (tool_number == this->cur_tool_)
            return;
        memset(this->matrix_, 0, sizeof this->matrix_);
        switch (tool_number) {
            case 0:
            //Pen
            for (int i = 0; i < MASK_LEN; i++)
                for (int j = 0; j < MASK_LEN; j++) {
                    int x = i - CENTER;
                    int y = j - CENTER;
                    if (x * x + y * y <= R_PEN * R_PEN)
                    this->matrix_[i][j] = 1;
                }
            break;

            case 1:
            //Eraser radius:10
            for (int i = 0; i < MASK_LEN; i++)
                for (int j = 0; j < MASK_LEN; j++) {
                    int x = i - CENTER;
                    int y = j - CENTER;
                    if (x * x + y * y <= R_ERASER * R_ERASER)
                    this->matrix_[i][j] = 1;
                }
            break;

            case 2:
            //Spray Can radius:20
            for (int i = 0; i < MASK_LEN; i++)
                for (int j = 0; j < MASK_LEN; j++) {
                    int x = i - CENTER;
                    int y = j - CENTER;
                    if (x * x + y * y <= R_CAN * R_CAN)
                    this->matrix_[i][j] = 0.2 - sqrt(x * x + y * y) * 0.01;
                }
            break;

            case 3:
            //Calligraphy Pen
            for (int x = -2; x <= 2; x++)
                for (int y = -7; y <= 7; y++)
                    this->matrix_[CENTER + x][CENTER + y] = 1;
            break;

            case 4:
            //Highlighter
            for (int x = -2; x <= 2; x++)
                for (int y = -7; y <= 7; y++)
                    this->matrix_[CENTER + x][CENTER + y] = 0.4;
            break;

            default:
            std::cout << "The tool does not exist." << std::endl;
        }
        this->cur_tool_ = tool_number;
    }
    // Print each value been sotred in Matirx
    void Mask::print_mask(void) {
        std::cout << "This is Tool no." << this->cur_tool_ <<std::endl;
        for (int i = 0; i < MASK_LEN; i++) {
            for (int j = 0; j < MASK_LEN; j++)
                std::cout << this->matrix_[i][j] << " ";
                std::cout << std::endl;
        }
    }
} //namespace image_tools

