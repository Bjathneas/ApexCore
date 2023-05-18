#include "ApexCore/LogCore.h"

int main() {
  ApexCore::Logger Log("log_test");

  Log.debug("Debugging Message");
  Log.warning("Warning Message");
  Log.error("Error Message");

  Log.log("Debugging Message");
  Log.log("Warning Message", ApexCore::LOG_LEVEL::WARNING);
  Log.log("Error Message", ApexCore::LOG_LEVEL::ERROR);
  
  return EXIT_SUCCESS;
}
