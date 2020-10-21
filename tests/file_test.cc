#pragma once

#include <catch2/catch.hpp>
#include <iostream>

#include "core/driver.h"

TEST_CASE("Overloaded operators") {
  SECTION("Read in image") {
    std::ifstream input_stream("data/five");
    Image image;
    input_stream >> image;
  }
  SECTION("Save model") {

  }
  SECTION("Load model") {

  }
}