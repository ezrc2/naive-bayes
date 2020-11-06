#include "core/driver.h"

namespace naivebayes {

void Driver::TrainModel(const std::string& labels_path,
                        const std::string& images_path,
                        const std::string& saved_path, bool validate_model) {
  FileParser file_parser;
  std::map<size_t, std::vector<Image>> training_data =
      file_parser.GetLabelImagePairs(labels_path, images_path);
  size_t image_size = file_parser.GetImageSize();

  Model model(training_data, image_size);
  std::ifstream input_stream(saved_path);

  model.CalculatePriorProbabilities();
  model.CalculateFeatureProbabilities();

  prior_probabilities_ = model.GetPriorProbabilities();
  feature_probabilities_ = model.GetFeatureProbabilities();

  SaveModel(saved_path, prior_probabilities_, feature_probabilities_);

  input_stream.close();

  if (validate_model) {
    VerifyModel();
  }
}

void Driver::LoadModel(const std::string& saved_path, bool validate_model) {
  std::ifstream input_stream(saved_path);
  std::string line;
  std::getline(input_stream, line);

  // Read priors first since they're in a different format
  while (!line.empty()) {
    std::vector<std::string> tokens = SplitString(line);
    prior_probabilities_.insert(
        std::make_pair(std::stoi(tokens[0]), std::stoi(tokens[1])));
    std::getline(input_stream, line);
  }

  // Overloaded operator to read in feature probabilities
  size_t i = 0;
  while (i++ < prior_probabilities_.size()) {
    std::getline(input_stream, line);
    size_t class_value = std::stoi(line);
    std::vector<std::vector<double>> features;

    FeatureData data(class_value, features);
    input_stream >> data;

    feature_probabilities_.insert(std::make_pair(class_value, data));
  }

  input_stream.close();
  if (validate_model) {
    VerifyModel();
  }
}

void Driver::VerifyModel() {
  classifier_.ValidateModel(prior_probabilities_, feature_probabilities_);
}

size_t Driver::ClassifySingleImage(
    const std::vector<std::vector<char>>& pixels) {
  return classifier_.ClassifyImage(pixels, prior_probabilities_,
                                   feature_probabilities_);
}

void Driver::SaveModel(
    const std::string& saved_path,
    const std::map<size_t, double>& prior_probabilities,
    const std::map<size_t, FeatureData>& feature_probabilities) {
  std::ofstream output_stream(saved_path);

  for (const auto& label : prior_probabilities) {
    output_stream << label.first << kSpace
                  << prior_probabilities.at(label.first) << std::endl;
  }
  output_stream << std::endl;

  // Overloaded operator to write the feature probabilities
  for (const auto& training_data : feature_probabilities) {
    FeatureData data(training_data.second);
    output_stream << data;
  }

  output_stream.close();
}

std::vector<std::string> Driver::SplitString(const std::string& to_split) {
  std::vector<std::string> tokens;

  std::stringstream stream(to_split);
  std::string temp;
  while (stream >> temp) {
    tokens.push_back(temp);
  }

  return tokens;
}

double Driver::GetModelAccuracy() {
  return classifier_.GetModelAccuracy();
}

std::map<size_t, double> Driver::GetPriors() {
  return prior_probabilities_;
}

std::map<size_t, double> Driver::GetLikelihoods() {
  return classifier_.GetLikelihoods();
}

}  // namespace naivebayes
