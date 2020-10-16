#include <core/read_data.h>

void Parser::GetLabelsFromFile() {
  std::string path;
  std::cout << "Enter file path of training labels:" << std::endl;
  std::getline(std::cin, path);
  std::ifstream file_reader(path);

  // Check if file doesn't exist
  while (!file_reader) {
    std::cout << "File doesn't exist." << std::endl;
    std::cout << "Enter file path of training labels:" << std::endl;
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
  std::string path;
  std::cout << "Enter file path of training images:" << std::endl;
  std::getline(std::cin, path);

  std::ifstream file_reader(path);

  // check if file doesn't exist;
  while (!file_reader) {
    std::cout << "File doesn't exist." << std::endl;
    std::cout << "Enter file path of training images:" << std::endl;
    std::getline(std::cin, path);
    file_reader.open(path);
  }

  // Read length of first line and get the size of the image
  std::string line;
  std::getline(file_reader, line);
  image_size_ = line.length();

  // Close and reopen file to start from the top
  file_reader.close();
  file_reader.clear();
  file_reader.open(path);

  size_t i = 0;
  while (i++ < training_labels_.size()) {
    Image image;
    image.SetImageSize(image_size_);
    file_reader >> image;
    training_images_.push_back(image);
  }

  file_reader.close();
}

std::map<size_t, std::vector<Image>> Parser::GetLabelImagePairs() {
  GetLabelsFromFile();
  GetImagesFromFile();

  std::map<size_t, std::vector<Image>> training_data;

  for (size_t i = 0; i < training_labels_.size(); i++) {\
    size_t label = training_labels_[i];
    if (training_data.count(label) == 0) {
      std::vector<Image> images;
      images.push_back(training_images_[i]);
      training_data.insert(std::make_pair(label, images));
    }
    else {
      training_data.find(label)->second.push_back(training_images_[i]);;
    }
  }

  return training_data;
}

size_t Parser::GetImageSize() {
  return image_size_;
}