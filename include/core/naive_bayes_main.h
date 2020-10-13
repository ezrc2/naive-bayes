#pragma once

#include <string>
#include "read_data.h"
#include <core/model.h>

namespace naivebayes {

class Main {

 public:

  void TrainModel();
  void WriteToFile();

 private:

  Parser parser_;

};

}  // namespace naivebayes
