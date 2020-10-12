#pragma once

#include <vector>
#include <map>
#include <iostream>
#include <istream>
#include <ostream>
#include <string>

class Parser {
 public:

  Parser();

  friend std::istream &operator>>(std::istream &input, std::string &file);

  const size_t kImageSize = 28;
  std::multimap<int, std::vector<std::vector<char>>> pairs_;

 private:
  size_t line_number_;
  std::string path_images_;
  std::string path_labels_;


};
