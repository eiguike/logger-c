#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "logger.h"

extern LOGGER* Logger;

int main() {
  Logger_New(BINARY_FILE, "test.log");
  Logger->Info("This is a information message!");
  Logger->Warning("This is a warning message!");
  Logger->Error(__FUNCTION__, __LINE__, "This is a error message!");
  Logger->Dispose();

  Logger_New(STDOUT);
  Logger->Info("This is a information message!");
  Logger->Warning("This is a warning message!");
  Logger->Error(__FUNCTION__, __LINE__, "This is a error message!");
  Logger->Dispose();

  return 0;
}
