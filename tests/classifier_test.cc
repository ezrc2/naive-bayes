#pragma once

#include <catch2/catch.hpp>
#include <iostream>

#include "core/driver.h"

const std::string kSavedModelPath = "data/saved_model";
const std::string kSubsetModelPath= "data/subset_model";
const std::string kFiveImagePath = "data/five";

TEST_CASE("Test model accuracy") {
  naivebayes::Driver driver;
  driver.LoadModel(kSavedModelPath, true);
  REQUIRE(driver.GetModelAccuracy() >= 0.7);
}

TEST_CASE("Classify images") {
  naivebayes::Driver driver;
  driver.LoadModel(kSubsetModelPath, false);
  // 10 images, 1 image of each digit, should all be correct
  REQUIRE(driver.GetModelAccuracy() == 1.0);
}

TEST_CASE("Test Likelihoods") {
  naivebayes::Driver driver;
  driver.LoadModel(kSavedModelPath, false);

  std::ifstream input_stream(kFiveImagePath);
  Image image;
  input_stream >> image;

  driver.ClassifySingleImage(image.GetPixels());
  std::map<size_t, double> likelihoods = driver.GetLikelihoods();

  std::vector<double> expected = {-320.148, -355.109, -283.685, -214.068,
                                  -330.766, -213.046, -341.593, -307.135,
                                  -240.967, -311.459};

  size_t i = 0;
  for (const auto& iter : likelihoods) {
    REQUIRE(iter.second == Approx(expected[i++]));
  }
  input_stream.close();
}