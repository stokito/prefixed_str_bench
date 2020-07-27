cmake_minimum_required(VERSION 2.8)
project(PrefixedStrBenchmark CXX)

find_package(benchmark REQUIRED)
#file(GLOB_RECURSE SOURCE_FILES headers/* src/*)
#add_executable(PrefixedStrBenchmark ${SOURCE_FILES})
add_executable(PrefixedStrBenchmark src/cmpstr.h src/cmpstr.cpp src/main.cpp)
target_link_libraries(PrefixedStrBenchmark benchmark::benchmark)
add_executable(exec src/cmpstr.h src/cmpstr.cpp src/exec.cpp)
