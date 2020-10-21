#pragma once

#include <catch2/catch.hpp>
#include <iostream>

#include "core/driver.h"

std::string model_path = "data/saved_model";

TEST_CASE("Test model accuracy") {
  naivebayes::Driver driver;
  driver.LoadModel(model_path, true);
  REQUIRE(driver.GetModelAccuracy() >= 0.7);
}

TEST_CASE("Classify images") {
  naivebayes::Driver driver;
  driver.LoadModel("data/subset_model", false);
  // 10 images, 1 image of each digit, should all be correct
  REQUIRE(driver.GetModelAccuracy() == 1.0);
}

TEST_CASE("Test Likelihoods") {
  naivebayes::Driver driver;
  driver.LoadModel(model_path, false);

  std::ifstream input_stream("data/five");
  Image image;
  input_stream >> image;

  driver.ClassifySingleImage(image.GetPixels());

  std::vector<double> expected = {};
}