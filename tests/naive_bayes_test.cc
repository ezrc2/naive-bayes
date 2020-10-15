#pragma once
#include <core/driver.h>

#include <catch2/catch.hpp>
#include <ostream>

Parser parser;
std::multimap<size_t, Image> pairs;
size_t image_size;

void before() {
  pairs = parser.GetLabelImagePairs();
  image_size = parser.GetImageSize();
}

TEST_CASE("Check for correct number of data") {
  before();
  SECTION("Correct number of labels and images") {
    REQUIRE(pairs.size() == 5000);
  }
  SECTION("Correct image size") {
    REQUIRE(image_size == 28);
  }
}

TEST_CASE("Test labels and images") {
  before();
  Model model(pairs, image_size);
  naivebayes::Driver driver;

  model.CalculateClassProbabilities();
  model.CalculateFeatureProbabilities();

  driver.TrainModel();
  SECTION("Test class probabilities") {
    std::vector<double> expected = {0.0958084, 0.112575,  0.0976048, 0.0986028,
                                    0.106986,  0.0868263, 0.1002,    0.10998,
                                    0.0924152, 0.099002};
    std::vector<double> calculated(model.GetClassProbabilities());
    REQUIRE_THAT(calculated, Catch::Approx(expected).epsilon(1.e-5));
  }
  SECTION("Test feature probabilities") {
    std::vector<std::vector<std::vector<double>>> feature_probabilities(
        model.GetFeatureProbabilities());
    REQUIRE(feature_probabilities[0][0][0] == Approx(0.002079));
    REQUIRE(feature_probabilities[0][14][14] == Approx(0.029106));
    REQUIRE(feature_probabilities[0][22][26] == Approx(0.004158));
  }
}

TEST_CASE("Test output file") {
  std::string output_path = "data/testing/test_trained_model";
  std::ifstream file_reader(output_path);

  SECTION("Test values") {
    std::string line;
    std::getline(file_reader, line);
    REQUIRE(std::stod(line) == Approx(0.0947631));
    std::getline(file_reader, line);
    REQUIRE(std::stod(line) == Approx(0.110973));
  }
}

TEST_CASE("Test GetPixels size") {
  std::vector<std::string> pixels = pairs.find(5)->second.GetPixels();
  REQUIRE(pixels.size() == 28);
  REQUIRE(pixels[0].size() == 28);
}

TEST_CASE("3x3 images 0 and 1") {
  before();
  Model model(pairs, image_size);
  naivebayes::Driver driver;

  model.CalculateClassProbabilities();
  model.CalculateFeatureProbabilities();

  driver.TrainModel();

  SECTION("Class probabilities") {
    std::vector<double> expected = {0.4, 0.6};
    std::vector<double> calculated(model.GetClassProbabilities());
    REQUIRE_THAT(calculated, Catch::Approx(expected).epsilon(1.e-5));
  }
  SECTION("Shaded Probabilities for class = 0") {
    std::vector<std::vector<double>> expected = {
        {0.666667, 0.666667, 0.666667},
        {0.666667, 0.333333, 0.666667},
        {0.666667, 0.666667, 0.666667}};

    std::vector<std::vector<std::vector<double>>> calculated(
        model.GetFeatureProbabilities());

    REQUIRE_THAT(calculated[0][0], Catch::Approx(expected[0]).epsilon(1.e-5));
    REQUIRE_THAT(calculated[0][1], Catch::Approx(expected[1]).epsilon(1.e-5));
    REQUIRE_THAT(calculated[0][2], Catch::Approx(expected[2]).epsilon(1.e-5));
  }
  SECTION("Shaded Probabilities for class = 1") {
    std::vector<std::vector<double>> expected = {
        {0.5, 0.75, 0.25}, {0.25, 0.75, 0.25}, {0.5, 0.75, 0.5}};

    std::vector<std::vector<std::vector<double>>> calculated(
        model.GetFeatureProbabilities());

    REQUIRE_THAT(calculated[0][0], Catch::Approx(expected[0]).epsilon(1.e-5));
    REQUIRE_THAT(calculated[0][1], Catch::Approx(expected[1]).epsilon(1.e-5));
    REQUIRE_THAT(calculated[0][2], Catch::Approx(expected[2]).epsilon(1.e-5));
  }
}
