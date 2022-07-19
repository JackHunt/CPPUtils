# Enable testing.
enable_testing()

# Get Googletest.
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

if(MSVC)
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
endif(MSVC)

# Algorithms.
set(ALGORITHMS_TESTS
  Algorithms/PathFinding.cpp
  Algorithms/Hashing.cpp
)
source_group(Tests/Algorithms FILES ${ALGORITHMS_TESTS})

# ContainterTools
set(CONTAINER_TOOLS_TESTS
  ContainerTools/TupleTools.cpp
)
source_group(Tests/ContainerTools FILES ${CONTAINER_TOOLS_TESTS})

# Data Structures.
set(DATA_STRUCTURES_TESTS
  DataStructures/Graph.cpp
)
source_group(Tests/DataStructures FILES ${DATA_STRUCTURES_TESTS})

# IO
set(IO_TESTS
  IO/CSVFile.cpp
)
source_group(Tests/IO FILES ${IO_TESTS})

# Iterators
set(ITERATORS_TESTS
  Iterators/CountingIterator.cpp
  Iterators/ZipIterator.cpp
)
source_group(Tests/Iterators FILES ${ITERATORS_TESTS})

# Statistics
set(STATISTICS_TESTS
  Statistics/SampleStatistics.cpp
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

include(GoogleTest)

foreach(test_fname ${ALL_TESTS})
  # Get the test module name.
  get_filename_component(test_name ${test_fname} NAME_WE)

  # Add the target.
  add_executable(${test_name} ${test_fname})
  set_target_properties(${test_name} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
  )

  target_link_libraries(${test_name} GTest::gtest_main)
  
  gtest_discover_tests(${test_name})
endforeach()
