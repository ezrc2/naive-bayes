#include <core/naive_bayes_main.h>

namespace naivebayes {

void Main::TrainModel() {
  Parser parser;
  std::multimap<size_t, Image> pairs(parser.GetLabelImagePairs());
  size_t image_size = parser.GetImageSize();

  Model model(pairs, image_size);

  std::string path;
  std::cout << "Enter file path of file to save trained model: " << std::endl;
  std::getline(std::cin, path);

  std::ifstream file_reader(path);
  // Check if file doesn't exist;
  while (!file_reader) {
    std::cout << "File doesn't exist." << std::endl;
    std::cout << "Enter file path of file to save trained model:" << std::endl;
    std::getline(std::cin, path);
    file_reader.open(path);
  }

  // Save data if file is empty
  // https://stackoverflow.com/questions/2390912/checking-for-an-empty-file-in-c
  if (file_reader.peek() == std::ifstream::traits_type::eof()) {
    model.CalculateClassProbabilities();
    model.CalculateFeatureProbabilities();

    WriteToFile(path, model.GetClassProbabilities(),
                model.GetFeatureProbabilities());
  } else {
    std::cout << "File already contains model data." << std::endl;
  }

  file_reader.close();
}

void Main::WriteToFile(std::string &path,
                       const std::vector<double> &class_probabilities,
                       const std::vector<std::vector<std::vector<double>>>
                           &feature_probabilities) {
  std::ofstream file_writer(path);

  // Write the class probabilities first
  for (double probability : class_probabilities) {
    file_writer << probability << std::endl;
  }
  file_writer << std::endl;

  // A row of 2D double vectors for each class
  for (size_t class_value = 0; class_value < feature_probabilities.size();
       class_value++) {
    for (size_t row = 0; row < feature_probabilities[class_value].size();
         row++) {
      for (size_t col = 0; col < feature_probabilities[class_value].size();
           col++) {
        file_writer << feature_probabilities[class_value][row][col] << " ";
      }
      file_writer << std::endl;
    }
    file_writer << std::endl;
  }
  file_writer.close();
}

}  // namespace naivebayes