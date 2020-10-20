#include <core/driver.h>

int main(int argc, char* argv[]) {
  naivebayes::Driver driver;
  std::string action = argv[2];

  if (action == "train") {
    // Train and save model only
    if (argc == 7) {
      driver.TrainModel(argv[3], argv[4], argv[6], false);
    }
    // Train, save, and test model
    else if (argc == 8 && std::string(argv[7]) == "test") {
      driver.TrainModel(argv[3], argv[4], argv[6], true);
    }
  }
  // Load and test model
  if (action == "load" && argc == 4) {
    driver.LoadModel(argv[3]);
  }

  return 0;
}
