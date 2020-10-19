#pragma once

#include <core/model.h>
#include <core/classifier.h>

#include <iostream>
#include <ostream>
#include <string>
#include <sstream>
#include <iterator>

#include "read_data.h"

namespace naivebayes {

/**
 * The main method the model is trained and the probabilities are written into a
 * file
 */

class Driver {
 public:
  /**
   * Takes in the file paths of the training labels and images, calls the
   * methods in Model class to train the model, and saves the model to a file
   *
   * @param labels_path
   * @param images_path
   * @param saved_path
   */
  void TrainModel(const std::string &labels_path, const std::string &images_path, const std::string &saved_path, bool test);

  /**
   * Loads in a trained model
   * @param saved_path The file path of the model
   */
  void LoadModel(const std::string &saved_path);

  void Classify();

 private:
  /**
   * Writes the class and feature probabilities to the specified file path if
   * the file is empty
   *
   * @param path The path of the file
   * @param class_probabilities The vector of class probabilities
   * @param feature_probabilities The 3D vector of feature probabilities
   */
  void WriteToFile(const std::string &saved_path,
                   const std::map<size_t, double> &prior_probabilities,
                   const std::map<size_t, std::vector<std::vector<double>>>
                       &feature_probabilities);

  /**
   * Splits a string by a delimiter
   *
   * @param string The input string
   * @param delimiter The delimiter
   * @return A vector of string tokens
   */
  std::vector<std::string> SplitString(std::string string, char delimiter);

  std::map<size_t, double> prior_probabilities_;
  std::map<size_t, std::vector<std::vector<double>>> feature_probabilities_;

  const char kSpace = ' ';

};

}  // namespace naivebayes
