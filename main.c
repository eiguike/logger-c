#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "logger.h"

extern LOGGER* Logger;

int main() {
  Logger_New(BINARY_FILE, "test.log");
  INFO("Hy my name is %s project!", "Logger-c")
  INFO("I can do math! %d + %d = %d", 2, 2, 4)
  DEBUG("This is a debug message!");
  WARN("This is a warning message!");
  ERROR("Serious! This is a error message!");
  Logger->Dispose();

  Logger_New(STDOUT);
  INFO("Hy my name is %s project!", "Logger-c")
  INFO("I can do math! %d + %d = %d", 2, 2, 4)
  DEBUG("This is a debug message!");
  WARN("This is a warning message!");
  ERROR("Serious! This is a error message!");
  Logger->Dispose();

  return 0;
}
