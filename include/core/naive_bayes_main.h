#pragma once

#include <string>
#include "read_data.h"
#include <core/model.h>
#include <iostream>
#include <ostream>

namespace naivebayes {

class Main {

 public:

  void TrainModel();

 private:

  void WriteToFile(std::vector<std::vector<std::vector<double>>> features);

  Parser parser_;

};

}  // namespace naivebayes
