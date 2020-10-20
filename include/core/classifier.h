#pragma once

#include <core/read_data.h>

#include <cmath>
#include <map>
#include <vector>

class Classifier {
 public:
  Classifier(const std::map<size_t, double> &prior_probabilities,
             const std::map<size_t, std::vector<std::vector<double>>>
                 &feature_probabilities);

 private:

  std::map<size_t, std::vector<Image>> testing_data_;
  std::map<size_t, double> prior_probabilities_;
  std::map<size_t, std::vector<std::vector<double>>> feature_probabilities_;
  std::map<size_t, double> likelihoods_;

  const std::string kLabelsPath = "data/testlabels";
  const std::string kImagesPath = "data/testimages";
  const char kGreyPixel = '+';
  const char kBlackPixel = '#';
};