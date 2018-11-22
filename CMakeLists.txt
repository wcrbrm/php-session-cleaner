cmake_minimum_required (VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(Boost_USE_STATIC_LIBS ON)

project(php-session-cleaner)

find_package(Boost REQUIRED COMPONENTS system filesystem)

include_directories(${Boost_INCLUDE_DIRS})
add_executable(php-session-cleaner php-session-cleaner.cpp)

target_link_libraries(php-session-cleaner -static -static-libgcc -static-libstdc++ Boost::system Boost::filesystem)
