#include <core/classifier.h>

Classifier::Classifier(const std::map<size_t, double> &prior_probabilities,
                       const std::map<size_t, std::vector<std::vector<double>>>
                           &feature_probabilities) {
  FileParser file_parser;
  testing_data_ = file_parser.GetLabelImagePairs(kLabelsPath, kImagesPath);
  prior_probabilities_ = prior_probabilities;
  feature_probabilities_ = feature_probabilities;
}

