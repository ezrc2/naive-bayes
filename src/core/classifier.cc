#include <core/classifier.h>

Classifier::Classifier() {
  for (size_t i = 0; i < kNumberOfClasses; i++) {
    class_probabilities_.push_back(0);
  }
}

void Classifier::CalculateClassProbabilities(
    std::multimap<size_t, std::vector<std::vector<char>>> pairs) {

  // Count number of images for each class
  for (auto it = pairs.begin(); it != pairs.end(); it++) {
    class_probabilities_[it->first]++;
  }

  size_t sum = 0;
  for (size_t images_in_class : class_probabilities_) {
    sum += images_in_class;
  }

  // Laplace smoothing
  for (size_t i = 0; i < class_probabilities_.size(); i++) {
    class_probabilities_[i] = (kLapLaceSmoothing + class_probabilities_[i]) /
                              (kNumberOfClasses * kLapLaceSmoothing + sum);
  }
}
std::vector<double> Classifier::getClassProbabilities() {
  return class_probabilities_;
}
