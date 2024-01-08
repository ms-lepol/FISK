# How to use:
#   mkdir build
#   cd build
#   cmake ..
#   make
#
cmake_minimum_required(VERSION 3.10)
 
project(FISK
  VERSION 0.1.0
)
 
find_package(gf REQUIRED)
 
add_executable(foogame
  src/client/testGF.cc
  src/common/Land.cc
  src/client/LandShape.cc
  # and the rest of your sources
)

target_link_libraries(foogame
  PRIVATE
    gf::graphics
    gf::net
    
)

 
add_executable(client
  src/client/client.cc
  src/common/Land.cc
  src/client/LandSprite.cc
  # and the rest of your sources
)

target_link_libraries(client
  PRIVATE
    gf::graphics
    gf::net
)


add_executable(server
  src/server/server.cc
)

target_link_libraries(server
  PRIVATE
    gf::net
)

add_executable(clientServ
  src/client/clientServ.cc
)

target_link_libraries(clientServ
  PRIVATE
    gf::net
)