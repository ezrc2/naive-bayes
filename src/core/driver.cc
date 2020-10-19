#include <core/driver.h>

namespace naivebayes {

void Driver::TrainModel(const std::string &labels_path,
                        const std::string &images_path,
                        const std::string &saved_path, bool test) {
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
    Classify();
  }
}

void Driver::LoadModel(const std::string &saved_path) {
  std::ifstream file_reader(saved_path);

  prior_probabilities_.clear();
  feature_probabilities_.clear();

  std::string line;
  std::getline(file_reader, line);

  while (!line.empty()) {
    std::vector<std::string> tokens = SplitString(line, kSpace);
    prior_probabilities_.insert(
        std::make_pair(std::stoi(tokens[0]), std::stod(tokens[1])));
  }

  int j = 0;
  while (!file_reader.eof()) {
    std::getline(file_reader, line);
    size_t class_value = std::stoi(line);
    std::vector<std::vector<double>> features;
    while (!line.empty()) {
      std::vector<std::string> tokens = SplitString(line, kSpace);
      std::vector<double> row;
      for (size_t i = 0; i < tokens.size(); i++) {
        row.push_back(std::stod(tokens[i]));
      }
      features.push_back(row);
    }
    feature_probabilities_.insert(std::make_pair(class_value, features));
    std::cout << j++ << std::endl;
  }

  file_reader.close();
}

void Driver::Classify() {
  Classifier classifier(prior_probabilities_, feature_probabilities_);
  classifier.ValidateModel();
}

void Driver::WriteToFile(
    const std::string &saved_path,
    const std::map<size_t, double> &prior_probabilities,
    const std::map<size_t, std::vector<std::vector<double>>>
        &feature_probabilities) {
  std::ofstream file_writer(saved_path);

  // Write the priors first
  for (const auto &label_image : prior_probabilities) {
    file_writer << label_image.first << kSpace
                << prior_probabilities.at(label_image.first) << std::endl;
  }
  file_writer << std::endl;

  for (const auto &label_image : feature_probabilities) {
    file_writer << label_image.first << std::endl;
    for (size_t row = 0; row < label_image.second.size(); row++) {
      for (size_t col = 0; col < label_image.second[row].size(); col++) {
        file_writer << feature_probabilities.at(label_image.first)[row][col]
                    << kSpace;
      }
      file_writer << std::endl;
    }
    file_writer << std::endl;
  }

  file_writer.close();
}

std::vector<std::string> Driver::SplitString(std::string string,
                                             char delimiter) {
  size_t position = 0;
  std::vector<std::string> token;
  while ((position = string.find(delimiter)) != std::string::npos) {
    token.push_back(string.substr(0, position));
    string.erase(0, position + 1);
  }
  return token;
}

}  // namespace naivebayes