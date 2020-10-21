#pragma once

#include <catch2/catch.hpp>
#include <iostream>

#include "core/driver.h"

const std::string kSavedModelPath = "data/saved_model";
const std::string k_3x3LabelsPath = "data/3x3labels";
const std::string k_3x3ImagesPath = "data/3x3images";

TEST_CASE("Test priors") {
  naivebayes::Driver driver;
  driver.LoadModel(kSavedModelPath, false);
  std::map<size_t, double> priors = driver.GetPriors();

  std::vector<double> expected = {0.0958084, 0.112575,  0.0976048, 0.0986028,
                                  0.106986,  0.0868263, 0.1002,    0.10998,
                                  0.0924152, 0.099002};

  size_t i = 0;
  for (const auto& iter : priors) {
    std::cout << iter.second << std::endl;
    REQUIRE(iter.second == Approx(expected[i++]));
  }
}

TEST_CASE("Test feature probabilities") {
  FileParser file_parser;
  std::map<size_t, std::vector<Image>> training_data =
      file_parser.GetLabelImagePairs(k_3x3LabelsPath, k_3x3ImagesPath);
  size_t image_size = file_parser.GetImageSize();

  Model model(training_data, image_size);
  model.CalculateFeatureProbabilities();

  SECTION("Shaded Probabilities for class = 0") {
    std::vector<std::vector<double>> expected = {
        {0.666667, 0.666667, 0.666667},
        {0.666667, 0.333333, 0.666667},
        {0.666667, 0.666667, 0.666667}};

    std::map<size_t, FeatureData> calculated = model.GetFeatureProbabilities();

    REQUIRE_THAT(calculated.at(0).features_[0],
                 Catch::Approx(expected[0]).epsilon(1.e-5));
    REQUIRE_THAT(calculated.at(0).features_[1],
                 Catch::Approx(expected[1]).epsilon(1.e-5));
    REQUIRE_THAT(calculated.at(0).features_[2],
                 Catch::Approx(expected[2]).epsilon(1.e-5));
  }
  SECTION("Shaded Probabilities for class = 1") {
    std::vector<std::vector<double>> expected = {
        {0.5, 0.75, 0.25}, {0.25, 0.75, 0.25}, {0.5, 0.75, 0.5}};

    std::map<size_t, FeatureData> calculated = model.GetFeatureProbabilities();

    REQUIRE_THAT(calculated.at(0).features_[0],
                 Catch::Approx(expected[0]).epsilon(1.e-5));
    REQUIRE_THAT(calculated.at(0).features_[1],
                 Catch::Approx(expected[1]).epsilon(1.e-5));
    REQUIRE_THAT(calculated.at(0).features_[2],
                 Catch::Approx(expected[2]).epsilon(1.e-5));
  }
}
