# Set CXX standard.
if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
else(MSVC)
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif(MSVC)

# Enable testing.
enable_testing()

# Find Boost.Test
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

# Add includes.
include_directories(${Boost_INCLUDE_DIRS})

# Algorithms.
set(ALGORITHMS_TESTS
  Algorithms/PathFinding.cpp
  Algorithms/Hashing.cpp
)
source_group(Tests/Algorithms FILES ${ALGORITHMS_TESTS})

# ContainterTools
set(CONTAINER_TOOLS_TESTS
  #
)
source_group(Tests/ContainerTools FILES ${CONTAINER_TOOLS_TESTS})

# Data Structures.
set(DATA_STRUCTURES_TESTS
  DataStructures/Graph.cpp
)
source_group(Tests/DataStructures FILES ${DATA_STRUCTURES_TESTS})

# IO
set(IO_TESTS
  #
)
source_group(Tests/IO FILES ${IO_TESTS})

# Iterators
set(ITERATORS_TESTS
  #
)
source_group(Tests/Iterators FILES ${ITERATORS_TESTS})

# Statistics
set(STATISTICS_TESTS
  #
)
source_group(Tests/Statistics FILES ${STATISTICS_TESTS})

# String Manipulation
set(STRING_MANIPULATION_TESTS
  #
)
source_group(Tests/StringManipulation FILES ${STRING_MANIPULATION_TESTS})

# Timing
set(TIMING_TESTS
  #
)
source_group(Tests/Timing FILES ${TIMING_TESTS})

# Generate an exec and add a test for each.
set(ALL_TESTS
  ${ALGORITHMS_TESTS}
  ${CONTAINER_TOOLS_TESTS}
  ${DATA_STRUCTURES_TESTS}
  ${IO_TESTS}
  ${ITERATORS_TESTS}
  ${STATISTICS_TESTS}
  ${STRING_MANIPULATION_TESTS}
  ${TIMING_TESTS}
)

foreach(test_fname ${ALL_TESTS})
  # Get the test module name.
  get_filename_component(test_name ${test_fname} NAME_WE)

  # Add the target.
  add_executable(${test_name} ${test_fname})
  
  # Register a test.
  add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()