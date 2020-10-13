#include "core/image.h"

std::istream& operator>>(std::istream& input, Image& image) {
  std::string line;
  std::getline(input, line);
  size_t image_size = line.length();

  for (size_t row = 0; row < image_size; row++) {
    std::string line;
    std::getline(input, line);
    std::vector<char> row_pixels;
    row_pixels.reserve(image_size);
    for (size_t col = 0; col < image_size; col++) {
      row_pixels.push_back(line[col]);
    }
    image.pixels.push_back(row_pixels);
  }
  return input;
}
