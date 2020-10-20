#pragma once

#include <map>
#include <vector>

#include "image.h"

/**
 * Calculates the class and feature probabilities given the training labels and
 * images
 */
class Model {
 public:
  /**
   * Initializes prior probability and feature probability maps with zeroes
   * @param pairs The training data map with label-vector<image> pairs
   * @param image_size The size of each image
   */
  Model(const std::map<size_t, std::vector<Image>> &training_data,
        size_t image_size);

  /**
   * Calculates the prior probabilities
   */
  void CalculatePriorProbabilities();

  /**
   * Calculates the probability of each coordinate being shaded
   */
  void CalculateFeatureProbabilities();

  /**
   * @return The map of prior probabilities
   */
  std::map<size_t, double> GetPriorProbabilities();

  /**
   * @return The map containing feature probabilities for each class
   */
  std::map<size_t, std::vector<std::vector<double>>> GetFeatureProbabilities();

 private:

  std::map<size_t, std::vector<Image>> training_data_;
  std::map<size_t, size_t> images_per_class_;
  std::map<size_t, double> prior_probabilities_;
  std::map<size_t, std::vector<std::vector<double>>> feature_probabilities_;

  size_t sum_images_;
  const double kLapLaceSmoothing = 1;
  const size_t kNumberOfClasses = 10;
  const char kGreyPixel = '+';
  const char kBlackPixel = '#';
};
