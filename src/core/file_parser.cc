#include <core/file_parser.h>

void FileParser::GetLabelsFromFile(const std::string &labels_path) {
  std::ifstream input_stream(labels_path);
  std::string line;

  while (std::getline(input_stream, line)) {
    training_labels_.push_back(std::stoi(line));  // convert to int
  }

  input_stream.close();
}

void FileParser::GetImagesFromFile(const std::string &images_path) {
  std::ifstream input_stream(images_path);

  // Read length of first line and get the size of the image
  std::string line;
  std::getline(input_stream, line);
  image_size_ = line.length();

  // Close and reopen file to start from the top
  input_stream.close();
  input_stream.clear();
  input_stream.open(images_path);

  size_t i = 0;
  while (i++ < training_labels_.size()) {
    Image image;
    input_stream >> image;
    training_images_.push_back(image);
  }

  input_stream.close();
}

std::map<size_t, std::vector<Image>> FileParser::GetLabelImagePairs(
    const std::string &labels_path, const std::string &images_path) {
  GetLabelsFromFile(labels_path);
  GetImagesFromFile(images_path);

  std::map<size_t, std::vector<Image>> training_data;

  for (size_t i = 0; i < training_labels_.size(); i++) {
    size_t label = training_labels_[i];
    if (training_data.count(label) == 0) {
      std::vector<Image> images;
      images.push_back(training_images_[i]);
      training_data.insert(std::make_pair(label, images));
    } else {
      training_data.at(label).push_back(training_images_[i]);
    }
  }

  return training_data;
}

size_t FileParser::GetImageSize() {
  return image_size_;
}