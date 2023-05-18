#include "ApexCore/ApexCore.h"

ApexCore::Logger Log("default_test");

int main() {
  ApexCore::init();
  ApexCore::begin();
  return EXIT_SUCCESS;
}
