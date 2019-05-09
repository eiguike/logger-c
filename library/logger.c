#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "logger_internals.h"

void Logger_Debug (LOGGER_INTERNAL* This, const char* Format, ...) {
  fprintf(This->FileBuffer, "DEBUG: ");

  va_list arg;
  va_start (arg, Format);
  vfprintf (This->FileBuffer, Format, arg);
  va_end (arg);

  fprintf(This->FileBuffer, "\n");
  return;
}

void Logger_Info (LOGGER_INTERNAL* This, const char* Format, ...) {
  fprintf(This->FileBuffer, "INFO: ");

  va_list arg;
  va_start (arg, Format);
  vfprintf (This->FileBuffer, Format, arg);
  va_end (arg);

  fprintf(This->FileBuffer, "\n");
  return;
}

void Logger_Error (LOGGER_INTERNAL* This, const char* Function, int Line, const char* Format, ...) {
  fprintf(This->FileBuffer, "ERROR %s.c:%d: ", Function, Line);

  va_list arg;
  va_start (arg, Format);
  vfprintf (This->FileBuffer, Format, arg);
  va_end (arg);

  fprintf(This->FileBuffer, "\n");
}

void Logger_Warning (LOGGER_INTERNAL* This, const char* Format, ...) {
  fprintf(This->FileBuffer, "WARNING: ");

  va_list arg;
  va_start (arg, Format);
  vfprintf (This->FileBuffer, Format, arg);
  va_end (arg);

  fprintf(This->FileBuffer, "\n");
}

void Logger_Dispose(LOGGER_INTERNAL* This) {
  if (This != NULL) {
    if (This->Output == BINARY_FILE) {
      fclose(This->FileBuffer);
      This->FileBuffer = NULL;
    }

    free(This);
    This = NULL;
  }
}

LOGGER* Logger_New(OUTPUT Output, ...) {
  LOGGER_INTERNAL* Logger = NULL;

  Logger = calloc(1, sizeof(LOGGER_INTERNAL));
  if (Logger == NULL) {
    printf("ERROR: Allocate Logger data strucuture failed\n");
    goto FINISH;
  }

  if (Output == BINARY_FILE) {
    va_list arg;
    va_start (arg, Output);
    Logger->FileBuffer = fopen(va_arg(arg, char*), "a+");
    va_end (arg);
  } else {
    Logger->FileBuffer = stdout;
  }
  Logger->Output = Output;

  Logger->Dispose = Logger_Dispose;
  Logger->Info = Logger_Info;
  Logger->Debug = Logger_Debug;
  Logger->Error = Logger_Error;
  Logger->Warning = Logger_Warning;

FINISH:
  if (Logger != NULL) Logger->Info(Logger, "Logger ready");

  return (LOGGER*) Logger;
}
