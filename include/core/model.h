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
   * Initializes class probability and feature probability vectors with zeroes
   * @param pairs The multimap with label-image pairs
   * @param image_size The size of each image
   */
  Model(const std::map<size_t, std::vector<Image>> &training_data, size_t image_size);

  /**
   * Calculates the class probabilities
   */
  void CalculateClassProbabilities();

  /**
   * Calculates the probability of each coordinate being shaded
   */
  void CalculateFeatureProbabilities();

  /**
   * @return The vector of class probabilities
   */
  std::vector<double> GetClassProbabilities();

  /**
   * @return The vector containing feature probabilities for each class
   */
  std::vector<std::vector<std::vector<double>>> GetFeatureProbabilities();

 private:
  /**
   * Applies laplace smoothing to the feature probabilities
   */
  void ApplyLaplaceSmoothing();

  std::map<size_t, std::vector<Image>> training_data_;
  std::vector<size_t> images_per_class_;
  std::vector<double> class_probabilities_;
  std::vector<std::vector<std::vector<double>>> feature_probabilities_;

  size_t image_size_;
  size_t sum_images_;
  const size_t kLapLaceSmoothing = 1;
  const size_t kNumberOfClasses = 10;
  const char kGreyPixel = '+';
  const char kBlackPixel = '#';
};
