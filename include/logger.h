#ifndef LOGGER_H
#define LOGGER_H

#define INFO(Format, ...) gLogger->Info(gLogger, Format, ##__VA_ARGS__);
#define DEBUG(Format, ...) gLogger->Debug(gLogger, __FUNCTION__, __LINE__, Format, ##__VA_ARGS__);
#define WARN(Format, ...) gLogger->Warning(gLogger, Format, ##__VA_ARGS__);
#define ERROR(Format, ...) gLogger->Error(gLogger, __FUNCTION__, __LINE__, Format, ##__VA_ARGS__);

typedef enum OutputType {
  NONE,
  STDOUT,
  BINARY_FILE,
  BOTH
} OUTPUT;

typedef enum LoggerLevel {
  ONLY_ERRORS,
  INFOS_AND_ERRORS,
  ALL_MESSAGES_WITHOUT_DEBUG,
  ALL_MESSAGES
} LOGGER_LEVEL;

typedef struct LOGGER_STRUCTURE {
  void (*Dispose) (struct LOGGER_STRUCTURE* This);
  void (*Info) (struct LOGGER_STRUCTURE* This, const char* Format, ...);
  void (*Debug) (struct LOGGER_STRUCTURE* This, const char* Function, int Line, const char* Format, ...);
  void (*Error) (struct LOGGER_STRUCTURE* This, const char* Function, int Line, const char* Format, ...);
  void (*Warning) (struct LOGGER_STRUCTURE* This, const char* Format, ...);
} LOGGER;

LOGGER* Logger_New(OUTPUT Output, LOGGER_LEVEL LoggerLevel, ...);

extern LOGGER* gLogger;

#endif
