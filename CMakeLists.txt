cmake_minimum_required(VERSION 3.19)

project(DALY_fuzzing LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)
include(cmake/all.cmake)

include(${CMAKE_CURRENT_LIST_DIR}/cmake/fuzzing.cmake)

find_package(doctest REQUIRED)
find_package(OpenCV REQUIRED COMPONENTS core imgproc imgcodecs)
find_package(CUDAToolkit REQUIRED)
file(GLOB fuzzing_sources ${CMAKE_CURRENT_SOURCE_DIR}/fuzz_test/*.cpp)

set(ENV{FUZZING_TIMEOUT} 10)
set(ENV{MAX_FUZZING_TIME} 60)
set(ENV{FUZZING_RSS_LIMIT} 8192)
set(ENV{FUZZING_MAX_LEN} 1048576)
foreach(fuzzing_source IN LISTS fuzzing_sources)
  get_filename_component(fuzzing_prog ${fuzzing_source} NAME_WE)
  add_executable(fuzz_${fuzzing_prog} ${fuzzing_source})
  target_include_directories(fuzz_${fuzzing_prog}
                             PRIVATE ${CMAKE_INSTALL_PREFIX}/include)
  target_include_directories(fuzz_${fuzzing_prog}
                             PRIVATE /home/cyy/cbuild/.internal/sources/DALI/third_party/libcudacxx/include)
  target_include_directories(fuzz_${fuzzing_prog}
                             PRIVATE ${CMAKE_INSTALL_PREFIX})
  target_link_directories(fuzz_${fuzzing_prog} PRIVATE
                          ${CMAKE_INSTALL_PREFIX}/lib)
  target_link_libraries(fuzz_${fuzzing_prog}
                        PRIVATE dali dali_core dali_operators dali_kernels)
  target_include_directories(fuzz_${fuzzing_prog} PUBLIC ${OpenCV_INCLUDE_DIRS})
  target_link_libraries(fuzz_${fuzzing_prog} PRIVATE CUDA::cudart CUDA::cuda_driver)
  add_fuzzing(TARGET fuzz_${fuzzing_prog} WITH_GPU_ANALYSIS ON)
endforeach()
