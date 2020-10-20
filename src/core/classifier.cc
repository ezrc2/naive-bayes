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
      prediction == class_value ? correct++ : correct;
      total++;
    }
  }
  return correct / total;
}

size_t Classifier::ClassifyImage(const std::vector<std::vector<char>> &pixels) {
  likelihoods_.clear();

  for (const auto &iterator : feature_probabilities_) {
    std::vector<std::vector<double>> features = iterator.second;
    double score = 0;

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

    likelihoods_.insert(std::make_pair(iterator.first, score));
  }

  for (const auto &prior : prior_probabilities_) {
    // Use log to avoid arithmetic underflow
    likelihoods_[prior.first] += log(prior.second);
  }

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
