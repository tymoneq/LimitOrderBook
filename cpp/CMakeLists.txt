cmake_minimum_required(VERSION 3.15)
project(LimitOrderBook VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# library target
add_library(limitorderbook STATIC)

# collect source/header files
file(GLOB_RECURSE LOB_SRC CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx")
file(GLOB_RECURSE LOB_HDR CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")

if(LOB_SRC)
  target_sources(limitorderbook PRIVATE ${LOB_SRC})
else()
  # placeholder if no source yet
  file(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/src/placeholder.cpp" "// placeholder source for limitorderbook library\n")
  target_sources(limitorderbook PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/placeholder.cpp")
endif()

target_include_directories(limitorderbook
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(limitorderbook PUBLIC cxx_std_20)

# Catch2 tests
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.8.1
)
FetchContent_MakeAvailable(Catch2)

add_executable(tests tests/test.cpp)
add_dependencies(tests limitorderbook)

target_link_libraries(tests PRIVATE limitorderbook Catch2::Catch2WithMain)

enable_testing()
add_test(NAME unit_tests COMMAND tests)

# Installation helpers (optional)
install(TARGETS limitorderbook
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)
install(DIRECTORY include/ DESTINATION include)
