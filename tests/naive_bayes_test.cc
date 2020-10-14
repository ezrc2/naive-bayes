#pragma once
#include <core/naive_bayes_main.h>

#include <catch2/catch.hpp>
#include <ostream>

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

TEST_CASE("3x3 images from prairielearn") {
  SECTION("Class probabilities") {
    std::vector<double> expected = {0.4, 0.6};
    std::vector<double> calculated(model.GetClassProbabilities());
    REQUIRE_THAT(calculated, Catch::Approx(expected).epsilon(1.e-5));
  }
  SECTION("Shaded Probabilities for class = 0") {
    std::vector<std::vector<double>> expected = {
        {0.666666, 0.666666, 0.666666},
        {0.666666, 0.333333, 0.666666},
        {0.666666, 0.666666, 0.666666}};

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
