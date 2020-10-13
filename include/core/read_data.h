#pragma once

#include <fstream>
#include <iostream>
#include <istream>
#include <map>
#include <string>
#include <vector>

#include "image.h"

class Parser {

 public:

  std::multimap<size_t, Image> getImageLabelPairs();
  size_t GetImageSize();

 private:

  std::vector<size_t> GetLabelsFromFile();
  std::vector<Image> GetImagesFromFile();

  size_t kImageSize;

};
