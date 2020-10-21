#pragma once

#include <iostream>
#include <string>
#include <vector>

/**
 * Contains a 2D vector of pixels and a friend function to overload the >>
 * operator
 */
class Image {
 public:
  /**
   * Overloads the >> operator to read the whole image
   *
   * @param istream The input stream
   * @param image The Image object
   * @return The input stream
   */
  friend std::istream& operator>>(std::istream& istream, Image& image);

  /**
   * @return The 2D vector of Pixels
   */
  std::vector<std::vector<char>> GetPixels();

 private:
  std::vector<std::vector<char>> pixels_;
};