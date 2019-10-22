# This is a header only library, however sources 
# are listed here so that they are organised nicely 
# in an IDE.

# Set project name and minimum CMake version.
project(CPPUtils)
cmake_minimum_required(VERSION 3.15)

# ContainterTools
set(CONTAINER_TOOLS_HEADERS
  CPPUtils/ContainterTools/TupleTools.h
)
source_group(ContainterTools FILES ${CONTAINER_TOOLS_HEADERS})

# IO
set(IO_HEADERS
  CPPUtils/IO/CSVFile.hpp
)
source_group(IO FILES ${IO_HEADERS})

# Iterators
set(ITERATORS_HEADERS
  CPPUtils/Iterators/CountingIterator.hpp
  CPPUtils/Iterators/ZipIterator.hpp
)
source_group(Iterators FILES ${ITERATORS_HEADERS})

# Statistics
set(STATISTICS_HEADERS
  CPPUtils/Statistics/SampleStatistics.hpp
)
source_group(Statistics FILES ${STATISTICS_HEADERS})

# String Manipulation
set(STRING_MANIPULATION_HEADERS
  CPPUtils/StringManipulation/Tokenizing.hpp
)
source_group(StringManipulation FILES ${STRING_MANIPULATION_HEADERS})

# Timing
set(TIMING_HEADERS
  CPPUtils/Timing/Timer.hpp
)
source_group(Timing FILES ${TIMING_HEADERS})

# Add this top level directory to the includes.
include_directories(${PROJECT_SOURCE_DIR})

# Add option to build examples.
option(BUILD_EXAMPLES "Build Examples?" OFF)
if(BUILD_EXAMPLES)
  add_subdirectory(Examples)
endif(BUILD_EXAMPLES)