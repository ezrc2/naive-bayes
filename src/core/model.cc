#include <core/model.h>

Model::Model(const std::map<size_t, std::vector<Image>> &training_data,
             size_t image_size) {
  // Count number of images for each class
  for (const auto &data_pair : training_data) {
    images_per_class_.push_back(data_pair.second.size());
  }

  // Set starting counts at all coordinates to 0.0
  for (size_t class_value = 0; class_value < kNumberOfClasses; class_value++) {
    std::vector<std::vector<double>> features;
    for (size_t row = 0; row < image_size; row++) {
      std::vector<double> rows;
      rows.reserve(image_size);

      for (size_t col = 0; col < image_size; col++) {
        rows.push_back(0.0);
      }

      features.push_back(rows);
    }
    feature_probabilities_.push_back(features);
  }

  image_size_ = image_size;
  training_data_ = training_data;
}

void Model::CalculateClassProbabilities() {
  sum_images_ = 0;
  for (size_t num_images : images_per_class_) {
    sum_images_ += num_images;
  }

  // Laplace smoothing for class probabilities
  for (size_t image_count : images_per_class_) {
    class_probabilities_.push_back(
        (kLapLaceSmoothing + image_count + 0.0) /  // Convert to float
        (kNumberOfClasses * kLapLaceSmoothing + sum_images_));
  }
}

void Model::CalculateFeatureProbabilities() {
  for (auto &data_pair : training_data_) {
    for (Image image : data_pair.second) {
      std::vector<std::string> pixels = image.GetPixels();
      for (size_t row = 0; row < pixels.size(); row++) {
        for (size_t col = 0; col < pixels.size(); col++) {
          char pixel = pixels[row][col];
          // Increment count at pixel (row, col) for this class if pixel is shaded
          if (pixel == kGreyPixel || pixel == kBlackPixel) {
            feature_probabilities_[data_pair.first][row][col]++;
          }
        }
      }
    }
  }
  ApplyLaplaceSmoothing();
}

void Model::ApplyLaplaceSmoothing() {
  for (size_t class_value = 0; class_value < kNumberOfClasses; class_value++) {
    for (size_t row = 0; row < image_size_; row++) {
      for (size_t col = 0; col < image_size_; col++) {
        feature_probabilities_[class_value][row][col] =
            (kLapLaceSmoothing +
             feature_probabilities_[class_value][row][col]) /
            (2 * kLapLaceSmoothing + images_per_class_[class_value] + 0.0);
      }
    }
  }
}

std::vector<double> Model::GetClassProbabilities() {
  return class_probabilities_;
}

std::vector<std::vector<std::vector<double>>> Model::GetFeatureProbabilities() {
  return feature_probabilities_;
}