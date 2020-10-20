#include <core/classifier.h>

Classifier::Classifier(const std::map<size_t, double> &prior_probabilities,
                       const std::map<size_t, std::vector<std::vector<double>>>
                           &feature_probabilities) {
  FileParser file_parser;
  testing_data_ = file_parser.GetLabelImagePairs(kLabelsPath, kImagesPath);
  prior_probabilities_ = prior_probabilities;
  feature_probabilities_ = feature_probabilities;
}

double Classifier::ValidateModel() {
  double correct = 0;
  double total = 0;
  for (const auto &label_image : testing_data_) {
    size_t class_value = label_image.first;
    for (Image image : label_image.second) {
      size_t prediction = ClassifyImage(image.GetPixels());
      if (prediction == class_value) {
        correct++;
      }
      total++;
    }
  }
  return correct / total;
}

size_t Classifier::ClassifyImage(const std::vector<std::vector<char>> &pixels) {

  return FindHighestProbability(likelihoods_);
}

size_t Classifier::FindHighestProbability(
    const std::map<size_t, double> &likelihoods) {
  size_t highest_class = likelihoods.begin()->first;
  double max = likelihoods.begin()->second;

  for (const auto &probability : likelihoods) {
    if (probability.second > max) {
      max = probability.second;
      highest_class = probability.first;
    }
  }

  return highest_class;
}


std::map<size_t, double> Classifier::GetLikelihoods() {
  return likelihoods_;
}
