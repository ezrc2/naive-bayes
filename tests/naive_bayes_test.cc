#include <core/naive_bayes_main.h>

#include <catch2/catch.hpp>

std::string path_labels = "data/test_labels";
std::string path_images = "data/test_images";

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
  naive_bayes_main.TrainModel();
  SECTION("Test class probabilities") {
    std::vector<double> expected = {
      0.0947631,
      0.110973,
      0.0992519,
      0.098005,
      0.107481,
      0.0875312,
      0.101247,
      0.108229,
      0.0932668,
      0.0992519
    };
    std::vector<double> calculated(model.GetClassProbabilities());
    REQUIRE_THAT( calculated, Catch::Approx(expected).epsilon(1.e-5) );
  }
  SECTION("Test feature probabilities"){

  }
}

TEST_CASE("Test output file isn't blank") {

}
