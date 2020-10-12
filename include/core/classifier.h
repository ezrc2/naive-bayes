#pragma once

#include <vector>
#include <map>

class Classifier {

 public:

  Classifier();

  void CalculateClassProbabilities(std::multimap<size_t, std::vector<std::vector<char>>>);

  std::vector<double> getClassProbabilities();

 private:

  const size_t kLapLaceSmoothing = 1;
  const size_t kNumberOfClasses = 10;
  const char kWhitePixel = ' ';
  const char kGreyPixel = '+';
  const char kBlackPixel = '#';
  std::vector<double> class_probabilities_;

};
