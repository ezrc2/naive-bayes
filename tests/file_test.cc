#pragma once

#include <catch2/catch.hpp>
#include <iostream>

#include "core/driver.h"

const std::string kZeroImagePath = "data/zero";
const std::string k_3x3LabelsPath = "data/3x3labels";
const std::string k_3x3ImagesPath = "data/3x3images";
const std::string k_3x3ModelPath = "data/3x3model";
const std::string kSavedFilePath = "data/saved_file";

TEST_CASE("Image overloaded operator") {
  std::ifstream input_stream(kZeroImagePath);
  Image image;
  input_stream >> image;

  std::vector<std::vector<char>> pixels = image.GetPixels();
  std::vector<std::string> expected = {"#####", "+   #", "#   +", "#   #",
                                       "++###"};

  for (size_t row = 0; row < pixels.size(); row++) {
    for (size_t col = 0; col < pixels[row].size(); col++) {
      REQUIRE(pixels[row][col] == expected[row][col]);
    }
  }
  input_stream.close();
}

TEST_CASE("Save model with overloaded operator") {
  SECTION("Test that whole file is saved") {
    naivebayes::Driver driver;
    driver.TrainModel(k_3x3LabelsPath, k_3x3ImagesPath, k_3x3ModelPath, false);

    std::ifstream input_stream(k_3x3ModelPath);
    std::vector<std::string> expected = {"0 0.4",
                                         "1 0.6",
                                         "",
                                         "0",
                                         "0.666667 0.666667 0.666667",
                                         "0.666667 0.333333 0.666667",
                                         "0.666667 0.666667 0.666667",
                                         "",
                                         "1",
                                         "0.5 0.75 0.25",
                                         "0.25 0.75 0.25",
                                         "0.5 0.75 0.5"};
    size_t i = 0;
    std::string line;
    while (std::getline(input_stream, line)) {
      REQUIRE(line == expected[i++]);
    }

    input_stream.close();
  }

  SECTION("Test overloaded operator itself") {
    std::ofstream output_stream(kSavedFilePath);
    std::vector<std::vector<double>> sample = {
        {0.1, 0.2, 0.3}, {0.4, 0.5, 0.6}, {0.7, 0.8, 0.9}};

    FeatureData data(0, sample);
    output_stream << data;

    std::ifstream input_stream(kSavedFilePath);
    std::vector<std::string> expected = {
        {"0.1 0.2 0.3"}, {"0.4 0.5 0.6"}, {"0.7 0.8 0.9"}};

    size_t i = 0;
    std::string line;
    while (std::getline(input_stream, line)) {
      REQUIRE(line == expected[i++]);
    }

    input_stream.close();
    output_stream.close();
  }
}

TEST_CASE("Load model overloaded operator") {
  naivebayes::Driver driver;
  driver.LoadModel(k_3x3ModelPath, false);

  std::ifstream input_stream(k_3x3ModelPath);

  std::vector<std::vector<double>> empty;

  FeatureData data(0, empty);
  input_stream >> data;

  std::vector<std::vector<double>> expected = {
      {0.1, 0.2, 0.3}, {0.4, 0.5, 0.6}, {0.7, 0.8, 0.9}};

  for (size_t row = 0; row < data.features_.size(); row++) {
    for (size_t col = 0; col < data.features_[row].size(); col++) {
      REQUIRE(data.features_[row][col] == expected[row][col]);
    }
  }

  input_stream.close();
}
