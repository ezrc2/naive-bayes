#include "core/model.h"

Model::Model(const std::map<size_t, std::vector<Image>>& training_data,
             size_t image_size) {
  for (const auto& label_image : training_data) {
    images_per_class_.insert(
        std::make_pair(label_image.first, label_image.second.size()));

    std::vector<std::vector<double>> features(
        image_size, std::vector<double>(image_size, 0));
    FeatureData data(label_image.first, features);

    feature_probabilities_.insert(std::make_pair(label_image.first, data));
  }

  training_data_ = training_data;
}

void Model::CalculatePriorProbabilities() {
  sum_images_ = 0;
  for (const auto& class_value : images_per_class_) {
    sum_images_ += class_value.second;
  }

  // Laplace smoothing for priors
  std::vector<double> probabilities;
  for (const auto& class_value : images_per_class_) {
    probabilities.push_back(
        (kLapLaceSmoothing + class_value.second) /
        (kNumberOfClasses * kLapLaceSmoothing + sum_images_));
  }

  size_t index = 0;
  for (const auto& label_image : training_data_) {
    prior_probabilities_.insert(
        std::make_pair(label_image.first, probabilities[index++]));
  }
}

void Model::CalculateFeatureProbabilities() {
  for (const auto& label_image : training_data_) {
    size_t class_value = label_image.first;
    size_t image_size =
        training_data_.at(class_value)[class_value].GetPixels().size();

    FeatureData feature_data = feature_probabilities_.at(class_value);

    for (size_t row = 0; row < image_size; row++) {
      for (size_t col = 0; col < image_size; col++) {
        for (Image image : label_image.second) {
          char pixel = image.GetPixels()[row][col];
          // Increment count at pixel (row, col) if pixel is shaded
          if (pixel == kGreyPixel || pixel == kBlackPixel) {
            feature_probabilities_.at(class_value).features_[row][col]++;
          }
        }
        // Laplace smoothing
        double temp =
            (kLapLaceSmoothing +
             feature_probabilities_.at(class_value).features_[row][col]) /
            (2 * kLapLaceSmoothing + images_per_class_.at(class_value));
        feature_probabilities_.at(class_value).features_[row][col] = temp;
      }
    }
  }
}

std::map<size_t, double> Model::GetPriorProbabilities() {
  return prior_probabilities_;
}

std::map<size_t, FeatureData> Model::GetFeatureProbabilities() {
  return feature_probabilities_;
}