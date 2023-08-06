cmake_minimum_required(VERSION 3.0.0)
project(sylar)

set(CMAKE_VERBOSE_MAKEFILE NO)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O0 -ggdb -g -std=c++11 -Wall -Wno-deprecated -Wno-unused-function")

include_directories(.)
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

find_library(YAMLCPP yaml-cpp)
message("***",${YAMLCPP})


set(LIB_SRC
    sylar/log.cc
    sylar/util.cc
    sylar/config.cc
    )

add_library(sylar SHARED ${LIB_SRC})

add_executable(test tests/test.cc)
add_dependencies(test sylar)
target_link_libraries(test sylar ${YAMLCPP})

add_executable(test_config tests/test_config.cc)
add_dependencies(test_config sylar)
target_link_libraries(test_config sylar ${YAMLCPP})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
