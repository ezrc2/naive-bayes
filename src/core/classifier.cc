#include <core/classifier.h>

Classifier::Classifier(std::multimap<size_t, std::vector<Image>> pairs) {
  for (size_t i = 0; i < kNumberOfClasses; i++) {
    images_per_class_.push_back(0);
  }
  // Count number of images for each class
  for (auto it = pairs.begin(); it != pairs.end(); it++) {
    images_per_class_[it->first]++;
  }
  kImageLabelPairs = pairs;
}

void Classifier::CalculateClassProbabilities() {
  double sum = 0;
  for (size_t num_images : images_per_class_) {
    sum += num_images;
  }

  // Laplace smoothing
  for (size_t i = 0; i < images_per_class_.size(); i++) {
    class_probabilities_.push_back((kLapLaceSmoothing + images_per_class_[i]) /
                              (kNumberOfClasses * kLapLaceSmoothing + sum));
  }
}

void Classifier::CalculateFeatureProbabilities() {

}


std::vector<double> Classifier::GetClassProbabilities() {
  return class_probabilities_;
}
