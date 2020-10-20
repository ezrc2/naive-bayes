#include "core/driver.h"

namespace naivebayes {

void Driver::TrainModel(const std::string& labels_path,
                        const std::string& images_path,
                        const std::string& saved_path, bool test) {
  FileParser file_parser;
  std::map<size_t, std::vector<Image>> training_data =
      file_parser.GetLabelImagePairs(labels_path, images_path);
  size_t image_size = file_parser.GetImageSize();

  Model model(training_data, image_size);
  std::ifstream file_reader(saved_path);

  model.CalculatePriorProbabilities();
  model.CalculateFeatureProbabilities();

  prior_probabilities_ = model.GetPriorProbabilities();
  feature_probabilities_ = model.GetFeatureProbabilities();

  WriteToFile(saved_path, prior_probabilities_, feature_probabilities_);

  file_reader.close();

  if (test) {
    VerifyClassifier();
  }
}

void Driver::LoadModel(const std::string& saved_path, bool validate_model) {
  std::ifstream file_reader(saved_path);

  std::string line;
  std::getline(file_reader, line);

  while (!line.empty()) {
    std::vector<std::string> tokens = SplitString(line);
    prior_probabilities_.insert(
        std::make_pair(std::stoi(tokens[0]), std::stoi(tokens[1])));
    std::getline(file_reader, line);
  }

  while (std::getline(file_reader, line)) {
    size_t class_value = std::stoi(line);
    std::vector<std::vector<double>> features;

    while (!line.empty()) {
      std::getline(file_reader, line);
      std::vector<std::string> tokens = SplitString(line);

      std::vector<double> row;
      for (size_t i = 0; i < tokens.size(); i++) {
        row.push_back(std::stod(tokens[i]));
      }

      features.push_back(row);
    }
    FeatureData data(class_value, features);
    feature_probabilities_.insert(std::make_pair(class_value, data));
  }

  file_reader.close();
  if (validate_model) {
    VerifyClassifier();
  }
}

void Driver::VerifyClassifier() {
  Classifier classifier;
  classifier.ValidateModel(prior_probabilities_, feature_probabilities_);
}

size_t Driver::ClassifySingleImage(
    const std::vector<std::vector<char>>& pixels) {
  Classifier classifier;
  return classifier.ClassifyImage(pixels, prior_probabilities_,
                                  feature_probabilities_);
}

void Driver::WriteToFile(
    const std::string& saved_path,
    const std::map<size_t, double>& prior_probabilities,
    const std::map<size_t, FeatureData>& feature_probabilities) {

  std::ofstream file_writer(saved_path);

  for (const auto& label : prior_probabilities) {
    file_writer << label.first << kSpace << prior_probabilities.at(label.first)
                << std::endl;
  }
  file_writer << std::endl;

  // Overloaded operator
  for (const auto& training_data : feature_probabilities) {
    FeatureData data(training_data.second);
    file_writer << data;
  }

  file_writer.close();
}

std::vector<std::string> Driver::SplitString(const std::string& to_split) {
  std::vector<std::string> tokens;

  std::stringstream stream(to_split);
  std::string temp;
  while (stream >> temp)
    tokens.push_back(temp);

  return tokens;
}

}  // namespace naivebayes