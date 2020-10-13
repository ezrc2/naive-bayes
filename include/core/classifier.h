#pragma once

#include <map>
#include <vector>

#include "image.h"

class Classifier {

 public:

  Classifier(std::multimap<size_t, std::vector<Image>> pairs);

  void CalculateClassProbabilities();
  void CalculateFeatureProbabilities();

  std::vector<double> GetClassProbabilities();

 private:

  std::multimap<size_t, std::vector<Image>> kImageLabelPairs;
  std::vector<size_t> images_per_class_;
  std::vector<double> class_probabilities_;
  std::vector<std::vector<std::vector<double>>> feature_probabilities;

  const size_t kLapLaceSmoothing = 1;
  const size_t kNumberOfClasses = 10;
  const char kWhitePixel = ' ';
  const char kGreyPixel = '+';
  const char kBlackPixel = '#';

};
