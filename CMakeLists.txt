if (POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)

project(Cifer_Demos LANGUAGES CXX)

cmake_minimum_required(VERSION 3.16)

add_compile_definitions(CMAKE_NANA_FILESYSTEM_FORCE=1)

include(FetchContent)

FetchContent_Declare(
  nana
  GIT_REPOSITORY https://github.com/cnjinhao/nana.git
  GIT_TAG        master
)

FetchContent_GetProperties(nana)
if(NOT nana_POPULATED)
  FetchContent_Populate(nana)
  add_subdirectory(${nana_SOURCE_DIR} ${nana_BINARY_DIR})
endif()

add_executable(CiferDemos main.cpp)
target_link_libraries(CiferDemos nana)
target_compile_features(CiferDemos PUBLIC	cxx_std_17)