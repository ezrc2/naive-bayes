#include <core/read_data.h>

Parser::Parser() {
  std::cout << "Enter file path to training images" << std::endl;
  std::getline(std::cin, path_images_);

  std::cout << "Enter file path to training labels" << std::endl;
  std::getline(std::cin, path_labels_);

  line_number_ = 0;
}

std::istream &operator>>(std::istream &input, Parser &parser) {
  std::vector<std::vector<char>> pixels;
  std::vector<char> row;
  for (size_t row = 0; row < parser.kImageSize; row++) {
    std::string line;
    std::getline(input, line);
    for (size_t col = 0; col < parser.kImageSize; col++) {
      parser.pairs_.
    }
  }
}

