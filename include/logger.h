#ifndef LOGGER_H
#define LOGGER_H

#define INFO(Format, ...) Logger->Info(Format, ##__VA_ARGS__);
#define DEBUG(Format, ...) Logger->Debug(Format, ##__VA_ARGS__);
#define WARN(Format, ...) Logger->Warning(Format, ##__VA_ARGS__);
#define ERROR(Format, ...) Logger->Error(__FUNCTION__, __LINE__, Format, ##__VA_ARGS__);

typedef enum OutputType {
  STDOUT,
  BINARY_FILE
} OUTPUT;

typedef struct LOGGER_STRUCTURE {
  void (*Dispose) ();
  void (*Info) (const char* Format, ...);
  void (*Debug) (const char* Format, ...);
  void (*Error) (const char* Function, int Line, const char* Format, ...);
  void (*Warning) (const char* Format, ...);
} LOGGER;

int Logger_New(OUTPUT Output, ...);

extern LOGGER* Logger;

#endif
