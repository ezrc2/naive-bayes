#pragma once

#include <fstream>
#include <iostream>
#include <istream>
#include <map>
#include <string>
#include <vector>

#include "image.h"

/**
 * Reads in the files for training labels and images and stores the label-image
 * pairs
 */
class Parser {
 public:
  /**
   * Places the label-image pairs into a multimap
   * @return
   */
  std::map<size_t, std::vector<Image>> GetLabelImagePairs();
  size_t GetImageSize();

 private:
  /**
   * Reads in the training labels and stores them in a vector
   */
  void GetLabelsFromFile();
  /**
   * Reads in the training images and stores them in a vector
   */
  void GetImagesFromFile();

  size_t image_size_;
  std::vector<size_t> training_labels_;
  std::vector<Image> training_images_;
};
