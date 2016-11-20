/*******************************************************************************
 * Name            : Mask.h
 * Project         : image_tools
 * Module          : Mask
 * Description     : Header file for Mask base class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef REPO_GROUP_A01_SRC_INCLUDE_MASK_H_
#define REPO_GROUP_A01_SRC_INCLUDE_MASK_H_

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Base class for representing the shape of a tool.
 * Mask is a wrapper for the array of floats representing the shape of a
 * tool. It does not have a shape; shapes are defined implicitly with
 * get_intensity().
 */
class Mask {
 public:
  Mask(float radius, float opacity);
  Mask(void);
  virtual ~Mask(void);

  /**
   * @brief Get a handle on the underlying array of float values representing
   * the shape of the tool
   * @return The float array
   */
  float const *float_array(void) const { return mask_array_; }

  /**
   * @brief Get the width of the tool shape (radius)
   * @return The width
   */
  int width(void) const { return width_;}

  /**
   * @brief Get the height of the tool shape (radius)
   * @return The height
   */
  int height(void) const {return height_;}

  /**
   * @brief Get the value of the mask at (x,y) with the radius of the tool shape
   * @return The value
   */
  float value(int x, int y) const;

 protected:
  /**
   * @brief Set the value of the mask at (x,y) with the radius of the tool shape
   */
  void value(int x, int y, float v);

  /**
   * @brief Generate the intensity value array that defines the shape and effect
   * of the tool.
   * Relies on the derived class implementation of get_intensity to do so.
   */
  void GenerateMask(void);

  /**
   * @brief Define the shape of the mask.
   * @param x The X coordinate of the tool/mouse location
   * @param y The Y coordinate of the tool/mouse location
   * @param radius Distance from (x,y) tool/mouse location to compute intensity
   * at
   */
  virtual float get_intensity(int x, int y, float radius) = 0;

 private:
  /* Copy/move assignment/construction are disallowed */
  Mask(const Mask& rhs) = delete;
  Mask& operator=(const Mask& rhs) = delete;

  float radius_; /**< max distance in pixels the mask reaches from center  */
  float opacity_;
  int height_; /**< number of pixel rows available in the mask  */
  int width_; /**< number pixel columns available in the mask  */
  float *mask_array_;
};

}  /* namespace image_tools */

#endif  /* REPO_GROUP_A01_SRC_INCLUDE_MASK_H_ */
