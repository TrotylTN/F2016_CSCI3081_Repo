/*******************************************************************************
 * Name            : Mask.cc
 * Project         : image_tools
 * Module          : Mask
 * Description     : Implementation of Mask class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/mask.h"
#include <cmath>
#include <iostream>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Mask::Mask(void) : radius_(0.0),
               opacity_(0.0),
               height_(0),
               width_(0),
               mask_array_(nullptr) {}

Mask::Mask(float radius, float opacity)
    : radius_(radius),
      opacity_(opacity),
      height_(ceil(radius)*2+1),
      width_(ceil(radius)*2+1),
      mask_array_(new float[width_*height_]) {
    std::fill(mask_array_, mask_array_+width_*height_, 1.f);
}

Mask::~Mask(void) {
  delete [] mask_array_;
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

float Mask::value(int x, int y) const {
  if (mask_array_ == nullptr || x < 0 || x > width_ || y < 0 || y > width_) {
    return 0.f;
  } else {
    return mask_array_[y*width_ + x];
  }
}

void Mask::value(int x, int y, float v) {
  if (mask_array_ == nullptr || x < 0 || x > width_ || y < 0 || y > width_) {
    return;
  } else {
    mask_array_[y*width_ + x] = v;
  }
}

void Mask::GenerateMask(void) {
  for (int j = 0; j < height(); j++) {
    for (int i = 0; i < width(); i++) {
      int x = i-width()/2;
      int y = j-height()/2;
      float intensity = opacity_*get_intensity(x, y, radius_);
      value(i, j, intensity);
    }
  }
}

}  /* namespace image_tools */
