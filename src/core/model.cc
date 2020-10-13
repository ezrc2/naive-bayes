#include <core/model.h>

Classifier::Classifier(std::multimap<size_t, Image> &pairs, size_t image_size) {
  // set all to 0
  for (size_t i = 0; i < kNumberOfClasses; i++) {
    images_per_class_.push_back(0);
  }
  // Count number of images for each class
  for (auto it = pairs.begin(); it != pairs.end(); it++) {
    images_per_class_[it->first]++;
  }

  //set all to 0
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

void Classifier::CalculateClassProbabilities() {
  double sum = 0;
  for (size_t num_images : images_per_class_) {
    sum += num_images;
  }

  // Laplace smoothing
  for (size_t i = 0; i < images_per_class_.size(); i++) {
    class_probabilities_.push_back(
        (kLapLaceSmoothing + images_per_class_[i]) /
        (kNumberOfClasses * kLapLaceSmoothing + sum));
  }
}

void Classifier::CalculateFeatureProbabilities() {

}

std::vector<double> Classifier::GetClassProbabilities() {
  return class_probabilities_;
}
