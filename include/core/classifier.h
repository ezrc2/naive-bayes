#pragma once

#include <core/feature_data.h>
#include <core/file_handler.h>

#include <cmath>
#include <map>
#include <vector>

/**
 *
 */
class Classifier {
 public:
  /**
   * Loads in testing labels and images to validate the accuracy of the model
   */
  Classifier();

  /**
   * Validates the model
   *
   * @param prior_probabilities
   * @param feature_probabilities
   * @return
   */
  double ValidateModel(
      const std::map<size_t, double>& prior_probabilities,
      const std::map<size_t, FeatureData>& feature_probabilities);

  /**
   *
   * @param pixels
   * @param prior_probabilities
   * @param feature_probabilities
   * @return
   */
  size_t ClassifyImage(
      const std::vector<std::vector<char>>& pixels,
      const std::map<size_t, double>& prior_probabilities,
      const std::map<size_t, FeatureData>& feature_probabilities);

  /**
   *
   * @return
   */
  std::map<size_t, double> GetLikelihoods();

 private:
  /**
   *
   * @param vector
   * @return
   */
  size_t FindHighestProbability(const std::map<size_t, double>& vector);

  std::map<size_t, std::vector<Image>> testing_data_;
  std::map<size_t, double> likelihoods_;

  const std::string kLabelsPath = "data/testlabels";
  const std::string kImagesPath = "data/testimages";
  const char kGreyPixel = '+';
  const char kBlackPixel = '#';
};