#include <core/read_data.h>

std::multimap<size_t, Image> Parser::getImageLabelPairs() {
  std::vector<size_t> labels = GetLabelsFromFile();
  std::vector<Image> images = GetImagesFromFile();

  std::multimap<size_t, Image> pairs;
  for (size_t i = 0; i < labels.size(); i++) {
    pairs.insert(std::pair<size_t, Image> (labels[i], images[i]));
  }

  return std::multimap<size_t, Image>();
}

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

std::vector<Image> Parser::GetImagesFromFile() {
  std::string path;
  std::cout << "Enter file path of training images" << std::endl;
  std::getline(std::cin, path);

  std::ifstream file_reader(path);
  //check if file doesn't exist;
  while (!file_reader) {
    std::cout << "File doesn't exist." << std::endl;
    std::cout << "Enter file path of training images" << std::endl;
    std::getline(std::cin, path);
    file_reader.open(path);
  }

  std::vector<Image> training_images;
  while (!file_reader.eof()) {
    Image image;
    file_reader >> image;
    training_images.push_back(image);
  }

  return std::vector<Image>();
}