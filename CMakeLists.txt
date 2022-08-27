# This is a header only library, however sources 
# are listed here so that they are organised nicely 
# in an IDE.

# Set project name and minimum CMake version.
project(CPPUtils)
cmake_minimum_required(VERSION 3.18)
enable_language(CXX)

# Set standard.
set(CMAKE_CXX_STANDARD 20)

# Algorithms.
set(ALGORITHMS_HEADERS
  CPPUtils/Algorithms/GradientOptimizers.hpp
  CPPUtils/Algorithms/Hashing.hpp
  CPPUtils/Algorithms/PathFinding.hpp
)
source_group(Algorithms FILES ${ALGORITHMS_HEADERS})

# ContainterTools
set(CONTAINER_TOOLS_HEADERS
  CPPUtils/ContainerTools/TupleTools.hpp
)
source_group(ContainerTools FILES ${CONTAINER_TOOLS_HEADERS})

# Data Structures.
set(DATA_STRUCTURES_HEADERS
  CPPUtils/DataStructures/Graph.hpp
  CPPUtils/DataStructures/Buffers.hpp
)
source_group(DataStructures FILES ${DATA_STRUCTURES_HEADERS})

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

# Add option to add Linear Algebra utils. Requires BLAS & LAPACK.
option(ENABLE_LINEAR_ALGEBRA "Enable Linear Algebra?" OFF)
if(ENABLE_LINEAR_ALGEBRA)
  find_package(LAPACK REQUIRED)

  set(LINEAR_ALGEBRA_HEADERS
    CPPUtils/LinearAlgebra/BLAS.hpp
    CPPUtils/LinearAlgebra/LAPACK.hpp
    CPPUtils/LinearAlgebra/Matrix.hpp
    CPPUtils/LinearAlgebra/Vector.hpp
  )
  source_group(LinearAlgebra FILES ${LINEAR_ALGEBRA_HEADERS})
endif(ENABLE_LINEAR_ALGEBRA)

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

# Create a custom target so that headers show in a VS solution.
set(ALL_HEADERS
  ${ALGORITHMS_HEADERS}
  ${CONTAINER_TOOLS_HEADERS}
  ${DATA_STRUCTURES_HEADERS}
  ${IO_HEADERS}
  ${ITERATORS_HEADERS}
  ${LINEAR_ALGEBRA_HEADERS}
  ${STATISTICS_HEADERS}
  ${STRING_MANIPULATION_HEADERS}
  ${TIMING_HEADERS}
)
add_custom_target(${PROJECT_NAME}_ SOURCES ${ALL_HEADERS})

# Add option to build examples.
option(BUILD_EXAMPLES "Build Examples?" OFF)
if(BUILD_EXAMPLES)
  add_subdirectory(Examples)
endif(BUILD_EXAMPLES)

# Add options to build examples.
option(BUILD_TESTS "Build Tests?" OFF)
if(BUILD_TESTS)
  add_subdirectory(Tests)
endif(BUILD_TESTS)
