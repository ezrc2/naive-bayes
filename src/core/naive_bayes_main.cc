#include <core/naive_bayes_main.h>

namespace naivebayes {

void Main::TrainModel() {
  std::multimap<size_t, Image> pairs = parser_.getImageLabelPairs();
  size_t image_size = parser_.GetImageSize();

  Model model(pairs, image_size);

  model.CalculateClassProbabilities();
  model.CalculateFeatureProbabilities();

  std::vector<double> class_probabilities(model.GetClassProbabilities());
  std::vector<std::vector<std::vector<double>>> features(model.GetFeatureProbabilities());

  //testing
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

void Main::WriteToFile(std::vector<std::vector<std::vector<double>>> features) {
  std::string path;
  std::cout << "Enter file path of file to save trained model" << std::endl;
  std::getline(std::cin, path);

  std::ifstream file_reader(path);
  //check if file doesn't exist;
  while (!file_reader) {
    std::cout << "File doesn't exist." << std::endl;
    std::cout << "Enter file path of file to save trained model" << std::endl;
    std::getline(std::cin, path);
    file_reader.open(path);
  }

  // save data if file is empty
  // https://stackoverflow.com/questions/2390912/checking-for-an-empty-file-in-c
  if (file_reader.peek() == std::ifstream::traits_type::eof()) {
    std::ofstream file_writer(path);
    for (size_t class_value = 0; class_value < features.size(); class_value++) {
      for (size_t row = 0; row < features[class_value].size(); row++) {
        for (size_t col = 0; col < features[class_value].size(); col++) {
          file_writer << features[class_value][row][col] << " ";
        }
        file_writer << std::endl;
      }
      file_writer << std::endl;
    }
    file_writer.close();
  }

  file_reader.close();
}

}  // namespace naivebayes