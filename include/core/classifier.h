#pragma once

#include <core/feature_data.h>
#include <core/file_parser.h>

#include <cmath>
#include <map>
#include <vector>

/**
 * Classifies images using a saved model
 */
class Classifier {
 public:
  /**
   * Loads in testing labels and images to validate the accuracy of the model
   */
  Classifier();

  /**
   * Validates the model based on the testing labels and images
   *
   * @param prior_probabilities The model's priors
   * @param feature_probabilities The model's feature probabilities
   * @return The accuracy of the model
   */
  double ValidateModel(
      const std::map<size_t, double>& prior_probabilities,
      const std::map<size_t, FeatureData>& feature_probabilities);

  /**
   * Classifies an image
   *
   * @param pixels The 2D char vector of the image
   * @param prior_probabilities The model's priors
   * @param feature_probabilities The model's feature probabilities
   * @return The predicted class of the image
   */
  size_t ClassifyImage(
      const std::vector<std::vector<char>>& pixels,
      const std::map<size_t, double>& prior_probabilities,
      const std::map<size_t, FeatureData>& feature_probabilities);

  /**
   * @return The likelihoods of the image
   */
  std::map<size_t, double> GetLikelihoods();

 private:
  /**
   * Finds the highest probability in the likelihoods
   *
   * @param likelihoods The likelihoods of the image
   * @return The class value of the highest probability
   */
  size_t FindHighestProbability(const std::map<size_t, double>& likelihoods);

  std::map<size_t, std::vector<Image>> testing_data_;
  std::map<size_t, double> likelihoods_;

  const std::string kLabelsPath = "data/testlabels";
  const std::string kImagesPath = "data/testimages";
  const char kGreyPixel = '+';
  const char kBlackPixel = '#';
};