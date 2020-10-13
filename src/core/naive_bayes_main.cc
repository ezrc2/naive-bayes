#include <core/naive_bayes_main.h>

namespace naivebayes {

void Main::TrainModel() {
  std::multimap<size_t, Image> pairs = parser_.getImageLabelPairs();
  size_t image_size = parser_.GetImageSize();

  Classifier classifier(pairs, image_size);

  classifier.CalculateClassProbabilities();
  classifier.CalculateFeatureProbabilities();

  std::vector<double> class_probabilities = classifier.GetClassProbabilities();
  std::vector<std::vector<std::vector<double>>> features =
      classifier.GetFeatureProbabilities();

  for (size_t class_value = 0; class_value < features.size(); class_value++) {
    for (size_t row = 0; row < image_size; row++) {
      for (size_t col = 0; col < image_size; col++) {
        std::cout << features[class_value][row][col] << " ";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }

}

void Main::WriteToFile() {
}

}  // namespace naivebayes