#pragma once

#include <core/model.h>

#include <iostream>
#include <ostream>
#include <string>

#include "read_data.h"

namespace naivebayes {

/**
 * The main method the model is trained and the probabilities are written into a
 * file
 */

class Driver {
 public:
  /**
   * Takes in the file paths of the training labels and images and calls the
   * methods in Model class to train the model
   */
  void TrainModel();

 private:
  /**
   * Writes the class and feature probabilities to the specified file path if
   * the file is empty
   *
   * @param path The path of the file
   * @param class_probabilities The vector of class probabilities
   * @param feature_probabilities The 3D vector of feature probabilities
   */
  void WriteToFile(std::string &path,
                   const std::vector<double> &class_probabilities,
                   const std::vector<std::vector<std::vector<double>>>
                       &feature_probabilities);
};

}  // namespace naivebayes
