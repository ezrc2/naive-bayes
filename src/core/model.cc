#include <core/model.h>

Model::Model(const std::map<size_t, std::vector<Image>> &training_data,
             size_t image_size) {
  for (const auto &label_image : training_data) {
    images_per_class_.push_back(label_image.second.size());

    // Set starting counts at all coordinates to 0.0
    std::vector<std::vector<double>> features;
    for (size_t row = 0; row < image_size; row++) {
      std::vector<double> rows(image_size, 0.0);
      features.push_back(rows);
    }
    feature_probabilities_.insert(std::make_pair(label_image.first, features));
  }

  training_data_ = training_data;
}

void Model::CalculatePriorProbabilities() {
  sum_images_ = 0;
  for (size_t num_images : images_per_class_) {
    sum_images_ += num_images;
  }

  // Laplace smoothing for class probabilities
  for (size_t image_count : images_per_class_) {
    prior_probabilities_.push_back(
        (kLapLaceSmoothing + image_count) /
        (kNumberOfClasses * kLapLaceSmoothing + sum_images_));
  }
}

void Model::CalculateFeatureProbabilities() {
  for (auto &label_image : training_data_) {
    size_t class_value = label_image.first;
    for (Image image : label_image.second) {
      std::vector<std::vector<char>> pixels = image.GetPixels();
      for (size_t row = 0; row < pixels.size(); row++) {
        for (size_t col = 0; col < pixels[row].size(); col++) {
          char pixel = pixels[row][col];
          // Increment count at pixel (row, col) if pixel is shaded
          if (pixel == kGreyPixel || pixel == kBlackPixel) {
            feature_probabilities_.find(class_value)->second[row][col]++;
          }
        }
      }
    }
    ApplyLaplaceSmoothing(class_value);
  }
}

void Model::ApplyLaplaceSmoothing(size_t class_value) {
  for (size_t row = 0; row < feature_probabilities_[class_value].size();
       row++) {
    for (size_t col = 0;
         col < feature_probabilities_[class_value][row].size(); col++) {
      feature_probabilities_.find(class_value)->second[row][col] =
          (kLapLaceSmoothing +
              feature_probabilities_.find(class_value)->second[row][col]) /
              (2 * kLapLaceSmoothing + images_per_class_[class_value]);
    }
  }
}

std::vector<double> Model::GetPriorProbabilities() {
  return prior_probabilities_;
}

std::map<size_t, std::vector<std::vector<double>>>
Model::GetFeatureProbabilities() {
  return feature_probabilities_;
}