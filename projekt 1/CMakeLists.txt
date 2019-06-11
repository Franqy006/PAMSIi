cmake_minimum_required(VERSION 3.10.2)
project( projkt)

include_directories(inc)
file(GLOB SOURCES "src/*.cpp")
add_executable (atak ${SOURCES})