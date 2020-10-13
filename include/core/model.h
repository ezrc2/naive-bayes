#pragma once

#include <map>
#include <vector>

#include "image.h"

class Classifier {
 public:

  Classifier(std::multimap<size_t, Image> &pairs, size_t image_size);

  void CalculateClassProbabilities();
  void CalculateFeatureProbabilities();

  std::vector<double> GetClassProbabilities();
  std::vector<std::vector<std::vector<double>>> GetFeatureProbabilities();

 private:

  void ApplyLaplaceSmoothing();

  std::multimap<size_t, Image> image_label_pairs_;
  std::vector<size_t> images_per_class_;
  std::vector<double> class_probabilities_;
  std::vector<std::vector<std::vector<double>>>
      feature_probabilities_;  // shaded pixels

  size_t image_size_;
  size_t total_training_images_;
  const size_t kLapLaceSmoothing = 1;
  const size_t kNumberOfClasses = 10;
  const char kWhitePixel = ' ';
  const char kGreyPixel = '+';
  const char kBlackPixel = '#';
};
