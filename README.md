# logger-c [![CircleCI](https://circleci.com/gh/eiguike/logger-c.svg?style=svg)](https://circleci.com/gh/eiguike/logger-c)
---

Create logs for your application.

## Motivations:
Just to improve my skills with C and to learn unit tests with cmake.


## Build:

1. Clone this repository
```
$ git clone https://github.com/eiguike/logger-c.git
```
2. Builds logger-c 
```
 $ mkdir build && cd build && cmake .. && make
```
3. Runs tests
```
 $ make test
```
4. Install it
```
 $ sudo make install
```

## Usage:
1. Include `logger.h` file

2. Create variable to store data structure
```c
  LOGGER* Logger;
```

3. Instance it passing the type of output (refers to `logger.h`)
```c
  Logger_New(NONE, ALL_MESSAGES); 
  Logger_New(STDOUT, ALL_MESSAGES); 
  Logger_New(FILE, ALL_MESSAGES, "filename.log"); 
  Logger_New(BOTH, ALL_MESSAGES, "filename.log"); 
```

4. Use it!
```c
  INFO("Hy my name is %s project!", "Logger-c")
  INFO("I can do math! %d + %d = %d", 2, 2, 4)
  DEBUG("This is a debug message!");
  WARN("This is a warning message!");
  ERROR("Serious! This is a error message!");
```

5. Don't forget to link logger-c to your application when compiling.
