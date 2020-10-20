#pragma once

#include <iostream>
#include <vector>

class FeatureData {

 public:

  FeatureData(size_t class_value, const std::vector<std::vector<double>>& features);

  friend std::istream &operator>>(std::istream& input, FeatureData &data);

  friend std::ostream &operator<<(std::ostream &output, FeatureData &data);

 private:

  size_t class_value_;
  std::vector<std::vector<double>> features_;
};