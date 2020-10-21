#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/**
 * Stores a 2D vector of feature probabilities and has overloaded operators to
 * load in a model and write the model to a file
 */
class FeatureData {
 public:
  /**
   * Initializes a FeatureData object
   *
   * @param class_value The class that these feature probabilities belong to
   * @param features The 2D vector of feature probabilities
   */
  FeatureData(size_t class_value,
              const std::vector<std::vector<double>>& features);

  /**
   * Overloads the >> operator to load in a previously saved model
   *
   * @param istream The input stream
   * @param data The FeatureData object
   * @return The input stream
   */
  friend std::istream& operator>>(std::istream& istream, FeatureData& data);

  /**
   * Overloads the << operator to write the feature probabilities to a file
   *
   * @param ostream The output stream
   * @param data The FeatureData object
   * @return The output stream
   */
  friend std::ostream& operator<<(std::ostream& ostream, FeatureData& data);

  std::vector<std::vector<double>> features_;

 private:
  size_t class_value_;
};