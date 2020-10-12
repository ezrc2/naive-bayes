#include <core/read_data.h>


std::vector<size_t> Parser::GetLabelsFromFile() {
  std::string path;
  std::cout << "Enter file path of training labels" << std::endl;
  std::getline(std::cin, path);

  std::ifstream file_reader(path);
  // Check if file doesn't exist
  while (!file_reader) {
    std::cout << "File doesn't exist." << std::endl;
    std::cout << "Enter file path of training labels" << std::endl;
    std::getline(std::cin, path);
    file_reader.open(path);
  }
  std::string line;

  std::vector<size_t> training_labels;
  while (std::getline(file_reader, line)) {
    training_labels.push_back(std::stoi(line)); // convert to int
  }

  return training_labels;
}


