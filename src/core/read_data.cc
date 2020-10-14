#include <core/read_data.h>

void Parser::GetLabelsFromFile() {
  training_labels_.clear();

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
  while (std::getline(file_reader, line)) {
    training_labels_.push_back(std::stoi(line));  // convert to int
  }

  file_reader.close();
}

void Parser::GetImagesFromFile() {
  training_images_.clear();

  std::string path;
  std::cout << "Enter file path of training images" << std::endl;
  std::getline(std::cin, path);

  std::ifstream file_reader(path);

  // check if file doesn't exist;
  while (!file_reader) {
    std::cout << "File doesn't exist." << std::endl;
    std::cout << "Enter file path of training images" << std::endl;
    std::getline(std::cin, path);
    file_reader.open(path);
  }

  while (!file_reader.eof()) {
    Image image;
    file_reader >> image;
    training_images_.push_back(image);
  }

  file_reader.close();
  file_reader.clear();

  // Re-open file to read length of first line and get the size of the image
  file_reader.open(path);
  std::string line;
  std::getline(file_reader, line);
  image_size_ = line.length();

  file_reader.close();
}

std::multimap<size_t, Image> Parser::GetLabelImagePairs() {
  GetLabelsFromFile();
  GetImagesFromFile();

  std::multimap<size_t, Image> pairs;
  // Insert label-image pairs into multimap
  for (size_t i = 0; i < training_images_.size(); i++) {
    pairs.insert(std::make_pair(training_labels_[i], training_images_[i]));
  }

  return pairs;
}

size_t Parser::GetImageSize() {
  return image_size_;
}