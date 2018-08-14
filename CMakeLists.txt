set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g  -std=c++11 ")

find_package(LLVM REQUIRED CONFIG)
if (${LLVM_PACKAGE_VERSION} VERSION_GREATER "3.4")
  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${LLVM_DIR}")
  include(LLVMConfig)
endif()
include(AddLLVM)

add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})

if (LLVM_SRC_PATH)
  include_directories(${LLVM_SRC_PATH}/include)
  SET(LLVM_INCLUDE_DIRS ${LLVM_SRC_PATH}/include)
  message(STATUS "Got LLVM_SRC_PATH ${LLVM_SRC_PATH}")
endif(LLVM_SRC_PATH)
if (LLVM_BUILD_PATH)
  include_directories(${LLVM_BUILD_PATH}/include)
  link_directories(${LLVM_BUILD_PATH}/lib)
  SET(LLVM_LIBRARY_DIRS ${LLVM_BUILD_PATH}/lib)
  message(STATUS "Got LLVM_BUILD_PATH ${LLVM_BUILD_PATH}")
endif(LLVM_BUILD_PATH)

if (${LLVM_PACKAGE_VERSION} VERSION_GREATER "3.4")
  llvm_map_components_to_libnames(llvm_libs support core irreader bitwriter transformutils)
else()
  llvm_map_components_to_libraries(llvm_libs support core irreader bitwriter transformutils)
endif()

add_library(RA SHARED
    RangeAnalysis.h
    RangeAnalysis.cpp
)
