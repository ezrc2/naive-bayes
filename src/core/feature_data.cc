#include "core/feature_data.h"

FeatureData::FeatureData(size_t class_value,
                         const std::vector<std::vector<double>>& features) {
  class_value_ = class_value;
  features_ = features;
}

std::istream& operator>>(std::istream& istream, FeatureData& data) {
  std::string line;
  std::getline(istream, line);
  while (!line.empty()) {
    std::cout << line << std::endl;
    std::vector<std::string> tokens;

    std::stringstream stream(line);
    std::string temp;
    while (stream >> temp) {
      tokens.push_back(temp);
    }

    std::vector<double> row;
    row.reserve(tokens.size());
    for (const std::string& token : tokens) {
      row.push_back(std::stod(token));
      std::cout << token << " ";
    }
    std::cout << std::endl;

    data.features_.push_back(row);
    std::getline(istream, line);
  }
  return istream;
}

std::ostream& operator<<(std::ostream& ostream, FeatureData& data) {
  std::vector<std::vector<double>> features = data.features_;
  ostream << data.class_value_ << std::endl;
  for (const std::vector<double>& feature : features) {
    for (double col : feature) {
      ostream << col << " ";
    }
    ostream << std::endl;
  }
  ostream << std::endl;

  return ostream;
}