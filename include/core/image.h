#pragma once

#include <vector>
#include <iostream>
#include <string>

class Image {

  std::vector<std::vector<char>> pixels;

 public:

  friend std::istream &operator>>(std::istream &input, Image &image);

};