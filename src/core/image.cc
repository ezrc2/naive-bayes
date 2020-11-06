#include "core/image.h"

std::istream& operator>>(std::istream& input, Image& image) {
  for (size_t row = 0; row < image.image_size_; row++) {
    std::string line;
    std::getline(input, line);

    if (line.length() == image.image_size_) {
      image.pixels_.push_back(line);
    }
    else {
      break;
    }

  }
  return input;
}

void Image::SetImageSize(size_t size) {
  image_size_ = size;
}

std::vector<std::string> Image::GetPixels() {
  return pixels_;
}
