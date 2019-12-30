#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "logger_internals.h"

void Logger_Debug (LOGGER_INTERNAL* This, const char* Function, int Line, const char* Format, ...) {
  if (ALL_MESSAGES > This->LoggerLevel) return;

  fprintf(This->FileBuffer, "DEBUG %s:%d: ", Function, Line);

  va_list arg;
  va_start (arg, Format);
  vfprintf (This->FileBuffer, Format, arg);
  va_end (arg);

  fprintf(This->FileBuffer, "\n");
}

void Logger_Info (LOGGER_INTERNAL* This, const char* Format, ...) {
  if (INFOS_AND_ERRORS > This->LoggerLevel) return;

  fprintf(This->FileBuffer, "INFO: ");

  va_list arg;
  va_start (arg, Format);
  vfprintf (This->FileBuffer, Format, arg);
  va_end (arg);

  fprintf(This->FileBuffer, "\n");
}

void Logger_Error (LOGGER_INTERNAL* This, const char* Function, int Line, const char* Format, ...) {
  if (ONLY_ERRORS > This->LoggerLevel) return;

  fprintf(This->FileBuffer, "ERROR %s:%d: ", Function, Line);

  va_list arg;
  va_start (arg, Format);
  vfprintf (This->FileBuffer, Format, arg);
  va_end (arg);

  fprintf(This->FileBuffer, "\n");
}

void Logger_Warning (LOGGER_INTERNAL* This, const char* Format, ...) {
  if (ALL_MESSAGES_WITHOUT_DEBUG > This->LoggerLevel) return;

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

void LoggerInternals_SetOutput(LOGGER_INTERNAL* Logger, OUTPUT Output, va_list arg) {
  va_list Argument;

  if (Logger == NULL) {
    goto FINISH;
  }

  Logger->Output = Output;

  switch(Logger->Output) {
    case NONE:
      Logger->FileBuffer = fopen("/dev/null", "w");
      if (Logger->FileBuffer == NULL) {
        Logger->FileBuffer = fopen("nul", "w");
      }
      break;
    case STDOUT:
      Logger->FileBuffer = stdout;
      break;
    case BINARY_FILE:
    case BOTH:
      va_copy(Argument, arg);
      Logger->FileBuffer = fopen(va_arg(Argument, char*), "a+");
      va_end(Argument);
      break;
    default:
      Logger->Output = STDOUT;
      Logger->FileBuffer = stdout;
      goto FINISH;
  }

FINISH:
  return;
}

LOGGER* Logger_New(OUTPUT Output, LOGGER_LEVEL LoggerLevel, ...) {
  LOGGER_INTERNAL* Logger = NULL;

  Logger = calloc(1, sizeof(LOGGER_INTERNAL));
  if (Logger == NULL) {
    printf("ERROR: Allocate Logger data strucuture failed\n");
    goto FINISH;
  }

  va_list arg;
  va_start(arg, LoggerLevel);
  LoggerInternals_SetOutput(Logger, Output, arg);
  va_end (arg);

  Logger->LoggerLevel = LoggerLevel;
  Logger->Dispose = Logger_Dispose;
  Logger->Info = Logger_Info;
  Logger->Debug = Logger_Debug;
  Logger->Error = Logger_Error;
  Logger->Warning = Logger_Warning;

FINISH:
  if (Logger != NULL) Logger->Info(Logger, "Logger ready");

  return (LOGGER*) Logger;
}
