#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "logger.h"

LOGGER* Logger;

int main() {

  Logger = Logger_New(STDOUT, ALL_MESSAGES, "test.log");
  INFO("Hy my name is %s project!", "Logger-c")
  INFO("I can do math! %d + %d = %d", 2, 2, 4)
  DEBUG("This is a debug message!");
  WARN("This is a warning message!");
  ERROR("Serious! This is a error message!");
  Logger->Dispose(Logger);

  Logger = Logger_New(BINARY_FILE, ALL_MESSAGES,"test.log");
  INFO("Hy my name is %s project!", "Logger-c")
  INFO("I can do math! %d + %d = %d", 2, 2, 4)
  DEBUG("This is a debug message!");
  WARN("This is a warning message!");
  ERROR("Serious! This is a error message!");
  Logger->Dispose(Logger);

  Logger = Logger_New(STDOUT, ONLY_ERRORS,"test.log");
  INFO("You shouldn't seeing me")
  DEBUG("You shouldn't seeing me")
  WARN("You shouldn't seeing me")
  ERROR("Serious! This is a error message!");
  Logger->Dispose(Logger);

  return 0;
}
