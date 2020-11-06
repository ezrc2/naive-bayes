#pragma once

#include <iostream>
#include <iterator>
#include <ostream>
#include <sstream>
#include <string>

#include "classifier.h"
#include "feature_data.h"
#include "file_parser.h"
#include "model.h"

namespace naivebayes {

/**
 * Trains, saves, loads, and validates a model
 */

class Driver {
 public:
  /**
   * Takes in the file paths of the training labels and images, calls the
   * methods in Model class to train the model, and saves the model to a file
   *
   * @param labels_path The file path of the labels
   * @param images_path The file path of the images
   * @param saved_path The file path to save the model
   * @param validate_model Validate the model or not
   */
  void TrainModel(const std::string& labels_path,
                  const std::string& images_path, const std::string& saved_path,
                  bool validate_model);

  /**
   * Loads in a trained model
   *
   * @param saved_path The file path of the model
   * @param validate_model Validate the model or not
   */
  void LoadModel(const std::string& saved_path, bool validate_model);

  /**
   * Calls on the classifier methods to verify the model
   */
  void VerifyModel();

  /**
   * Classifies a single image (used in the sketchpad)
   *
   * @param pixels The 2D char vector of the image
   * @return The predicted class of the image
   */
  size_t ClassifySingleImage(const std::vector<std::vector<char>>& pixels);

  /**
   * @return The model's accuracy
   */
  double GetModelAccuracy();

  /**
   * @return The priors of the model
   */
  std::map<size_t, double> GetPriors();

  /**
   * @return The likelihoods from the classifier
   */
  std::map<size_t, double> GetLikelihoods();

 private:
  /**
   * Writes the class and feature probabilities to the specified file path if
   * the file is empty
   *
   * @param path The path of the file
   * @param prior_probabilities The vector of class probabilities
   * @param feature_probabilities The 3D vector of feature probabilities
   */
  void SaveModel(const std::string& saved_path,
                 const std::map<size_t, double>& prior_probabilities,
                 const std::map<size_t, FeatureData>& feature_probabilities);

  /**
   * Splits a string by space
   *
   * @param string The input string
   * @return A vector of string tokens
   */
  std::vector<std::string> SplitString(const std::string& to_split);

  std::map<size_t, double> prior_probabilities_;
  std::map<size_t, FeatureData> feature_probabilities_;
  Classifier classifier_;

  const char kSpace = ' ';
};

}  // namespace naivebayes
