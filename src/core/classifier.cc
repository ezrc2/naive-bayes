#include "core/classifier.h"

Classifier::Classifier() {
  FileParser file_parser;
  testing_data_ = file_parser.GetLabelImagePairs(kLabelsPath, kImagesPath);
}

double Classifier::ValidateModel(
    const std::map<size_t, double>& prior_probabilities,
    const std::map<size_t, FeatureData>&
        feature_probabilities) {
  double correct = 0;
  double total = 0;

  for (const auto& label_image : testing_data_) {
    size_t class_value = label_image.first;
    for (Image image : label_image.second) {
      size_t prediction = ClassifyImage(image.GetPixels(), prior_probabilities,
                                        feature_probabilities);
      prediction == class_value ? correct++ : correct;
      total++;
    }
  }
  accuracy_ = correct / total;
  std::cout << "accuracy: " << accuracy_ << std::endl;
  return accuracy_;
}

size_t Classifier::ClassifyImage(
    const std::vector<std::vector<char>>& pixels,
    const std::map<size_t, double>& prior_probabilities,
    const std::map<size_t, FeatureData>&
        feature_probabilities) {
  likelihoods_.clear();

  for (std::pair<size_t, FeatureData> data : feature_probabilities) {

    std::vector<std::vector<double>> features = data.second.features_;
    double score = prior_probabilities.at(data.first);

    for (size_t row = 0; row < features.size(); row++) {
      for (size_t col = 0; col < features[row].size(); col++) {
        char pixel = pixels[row][col];
        // Use log to avoid arithmetic underflow
        if (pixel == kGreyPixel || pixel == kBlackPixel) {
          score += log(features[row][col]);
        } else {
          score += log(1 - features[row][col]);
        }
      }
    }

    likelihoods_.insert(std::make_pair(data.first, score));
  }
  return FindHighestProbability(likelihoods_);
}

size_t Classifier::FindHighestProbability(
    const std::map<size_t, double>& likelihoods) {
  size_t highest_class = likelihoods.begin()->first;
  double max = likelihoods.begin()->second;

  for (const auto& probability : likelihoods) {
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

double Classifier::GetModelAccuracy() {
  return accuracy_;
}
