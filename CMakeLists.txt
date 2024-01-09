# How to use:
#   mkdir build
#   cd build
#   cmake ..
#   make
#
cmake_minimum_required(VERSION 3.18...3.21)

project(FISK
  VERSION 0.1.0
)

find_package(gf REQUIRED COMPONENTS graphics net core)
 

add_executable(client
  src/client/client.cc
  src/client/GameHub.cc
  src/client/MainScene.cc
  src/client/MapEntity.cc
  src/client/LandEntity.cc
  src/common/Land.cc
  # and the rest of your sources
)

target_link_libraries(client
  PRIVATE
    gf::graphics
    gf::net
    gf::core
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
