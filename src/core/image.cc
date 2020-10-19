#include "core/image.h"

std::istream& operator>>(std::istream& input, Image& image) {
  std::string line;
  std::getline(input, line);
  size_t image_size = line.length();

  for (size_t row = 0; row < image_size - 1; row++) {
    if (line.length() == image_size) {
      std::vector<char> row_pixels;
      for (char c : line) {
        row_pixels.push_back(c);
      }
      image.pixels_.push_back(row_pixels);
    }
    else {
      break;
    }

    std::getline(input, line);
  }
  return input;
}

std::vector<std::vector<char>> Image::GetPixels() {
  return pixels_;
}
