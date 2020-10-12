#pragma once

#include <vector>
#include <iostream>
#include <string>

class Image {

  std::vector<std::vector<char>> pixels;
  const size_t kImageSize = 28;

 public:

  friend std::istream &operator>>(std::istream &input, Image &image);
  
};