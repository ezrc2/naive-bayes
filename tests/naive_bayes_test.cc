#pragma once
#include <core/naive_bayes_main.h>

#include <ostream>
#include <catch2/catch.hpp>

Parser parser;

std::multimap<size_t, Image> pairs(parser.GetLabelImagePairs());
size_t image_size = parser.GetImageSize();

Model model(pairs, image_size);
naivebayes::Main naive_bayes_main;

TEST_CASE("Check for correct number of data") {
  SECTION("Correct number of labels and images") {
    REQUIRE(pairs.size() == 5000);
  }
  SECTION("Correct image size") {
    REQUIRE(image_size == 28);
  }
}

TEST_CASE("Test labels and images") {
  model.CalculateClassProbabilities();
  model.CalculateFeatureProbabilities();

  naive_bayes_main.TrainModel();
  SECTION("Test class probabilities") {
    std::vector<double> expected = {0.0947631, 0.110973,  0.0992519, 0.098005,
                                    0.107481,  0.0875312, 0.101247,  0.108229,
                                    0.0932668, 0.0992519};
    std::vector<double> calculated(model.GetClassProbabilities());
    REQUIRE_THAT(calculated, Catch::Approx(expected).epsilon(1.e-5));
  }
  SECTION("Test feature probabilities") {
    std::vector<std::vector<std::vector<double>>> feature_probabilities(
        model.GetFeatureProbabilities());
    REQUIRE(feature_probabilities[0][0][0] == Approx(0.0527421));
    REQUIRE(feature_probabilities[0][0][0] == Approx(0.0313684));
    REQUIRE(feature_probabilities[0][0][0] == Approx(0.0760837));
  }
}

TEST_CASE("Test output file") {
  std::string output_path = "data/test_model_probabilities";
  std::ifstream file_reader(output_path);

  SECTION("File isn't empty") {
    REQUIRE(file_reader.peek() == std::ifstream::traits_type::eof() == false);
  }
  SECTION("Test values") {
    std::string line;
    std::getline(file_reader, line);
    REQUIRE(std::stod(line) == Approx(0.0947631));
    std::getline(file_reader, line);
    REQUIRE(std::stod(line) == Approx(0.110973));
  }
}

TEST_CASE("Test GetPixels") {
  std::vector<std::vector<char>> pixels = pairs.find(5)->second.GetPixels();
  REQUIRE(pixels.size() == 28);
  REQUIRE(pixels[0].size() == 28);
}
