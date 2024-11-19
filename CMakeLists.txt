cmake_minimum_required(VERSION 3.25)
project(xml_parser)

set(CMAKE_CXX_STANDARD 17)

include_directories(inc)
file(GLOB xml_parser_SRC CONFIGURE_DEPENDS "inc/*.h" "src/*.cpp")

add_executable(xml_parser ${xml_parser_SRC})