#include "core/image.h"

std::istream& operator>>(std::istream& input, Image& image) {
  for (size_t row = 0; row < image.kImageSize; row++) {
    std::string line;
    std::getline(input, line);
    std::vector<char> row_pixels;
    row_pixels.reserve(image.kImageSize);
    for (size_t col = 0; col < image.kImageSize; col++) {
      row_pixels.push_back(line[col]);
    }
    image.pixels.push_back(row_pixels);
  }
  return input;
}
