#include <core/model.h>

Model::Model(std::multimap<size_t, Image> &pairs, size_t image_size) {
  // set all to 0
  for (size_t i = 0; i < kNumberOfClasses; i++) {
    images_per_class_.push_back(0);
  }
  // Count number of images for each class
  for (auto it = pairs.begin(); it != pairs.end(); it++) {
    images_per_class_[it->first]++;
  }

  // set all to 0
  for (size_t class_value = 0; class_value < image_size; class_value++) {
    std::vector<std::vector<double>> features;
    for (size_t row = 0; row < image_size; row++) {
      std::vector<double> rows;
      for (size_t col = 0; col < image_size; col++) {
        rows.push_back(0.0);
      }
      features.push_back(rows);
    }
    feature_probabilities_.push_back(features);
  }

  image_size_ = image_size;
  image_label_pairs_ = pairs;
}

void Model::CalculateClassProbabilities() {
  total_training_images_ = 0;
  for (size_t num_images : images_per_class_) {
    total_training_images_ += num_images;
  }

  // Laplace smoothing
  for (size_t i = 0; i < images_per_class_.size(); i++) {
    class_probabilities_.push_back(
        (kLapLaceSmoothing + images_per_class_[i]) /
        (kNumberOfClasses * kLapLaceSmoothing + total_training_images_));
  }
}

void Model::CalculateFeatureProbabilities() {
  for (auto &pair : image_label_pairs_) {
    int class_value = pair.first;
    std::vector<std::vector<char>> pixels = pair.second.GetPixels();

    for (size_t row = 0; row < image_size_; row++) {
      for (size_t col = 0; col < image_size_; col++) {
        char pixel = pixels[row][col];
        // increment count at (row, col) for this class if pixel is shaded
        if (pixel == kGreyPixel || pixel == kBlackPixel) {
          feature_probabilities_[class_value][row][col]++;
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
            (kLapLaceSmoothing + images_per_class_[class_value] + 0.0) /
            (kNumberOfClasses * kLapLaceSmoothing + total_training_images_);
      }
    }
  }
}

std::vector<double> Model::GetClassProbabilities() {
  return class_probabilities_;
}

std::vector<std::vector<std::vector<double>>>
Model::GetFeatureProbabilities() {
  return feature_probabilities_;
}