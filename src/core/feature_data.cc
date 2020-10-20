#include "core/feature_data.h"

FeatureData::FeatureData(size_t class_value, const std::vector<std::vector<double>> &features) {
  class_value_ = class_value;
  features_ = features;
}

std::istream& operator>>(std::istream& input, FeatureData& data) {
  return input;
}

std::ostream& operator<<(std::ostream& output, FeatureData& data) {
  std::vector<std::vector<double>> features = data.features_;
  output << data.class_value_ << std::endl;
  for (size_t row = 0; row < features.size(); row++) {
    for (size_t col = 0; col < features[row].size(); col++) {
      output << features[row][col] << " ";
    }
    output << std::endl;
  }
  output << std::endl;

  return output;
}
