# Project name.
project(CPPUtilsExamples)

# Set CXX standard.
if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++20")
else(MSVC)
  set(CMAKE_CXX_STANDARD 20)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif(MSVC)

# Add the example build targets.
add_executable(CountingIteratorExample CountingIteratorExample.cpp)
add_executable(SampleStatisticsExample SampleStatisticsExample.cpp)
add_executable(SplitOnDelimiterExample SplitOnDelimiterExample.cpp)
add_executable(ZipIteratorExample ZipIteratorExample.cpp)
add_executable(TimerExample TimerExample.cpp)
add_executable(PathFindingExample PathFindingExample.cpp)

