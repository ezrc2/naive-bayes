#pragma once

#include <iostream>
#include <string>
#include <vector>

/**
 * Contains a 2D vector of pixels and a friend function to overload the >>
 * operator
 */
class Image {

  std::vector<std::vector<char>> pixels;

 public:

  /**
   * Overloads the >> operator to read the whole image
   *
   * @param input The input stream
   * @param image The Image object
   * @return The input stream
   */
  friend std::istream &operator>>(std::istream &input, Image &image);

  /**
   * @return The 2D vector of Pixels
   */
  std::vector<std::vector<char>> GetPixels();

};