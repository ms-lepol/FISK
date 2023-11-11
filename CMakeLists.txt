cmake_minimum_required(VERSION 3.10)
 
project(FISK
  VERSION 0.1.0
)
 
find_package(gf REQUIRED)
 
add_executable(foogame
  src/client/client.cc
  # and the rest of your sources
)
 
target_link_libraries(foogame
  PRIVATE
    gf::graphics
    gf::net
)
