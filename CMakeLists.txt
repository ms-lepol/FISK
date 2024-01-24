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
  src/client.cc
  src/client/GameHub.cc
  src/client/MainScene.cc
  src/client/MapEntity.cc
  src/client/LandEntity.cc
  src/client/TurnInterface.cc
  src/client/PhaseIndicator.cc
  src/client/HudButtons.cc
  src/client/ClientNetwork.cc
  src/common/Land.cc
  src/common/Card.cc
  src/common/Continent.cc
  src/common/Game.cc
  src/client/LobbyScene.cc
  src/client/TitleScene.cc
  src/client/CardScene.cc
  # and the rest of your sources
)

target_link_libraries(client
  PRIVATE
    gf::graphics
    gf::net
    gf::core
)


add_executable(server
  src/server.cc
  src/server/ServerNetwork.cc
  src/server/ServerLobby.cc
  src/server/ServerPlayer.cc
  src/server/ServerGroup.cc
  src/server/GameInstance.cc
  src/server/GameFactory.cc
  src/common/Land.cc
  src/common/Card.cc
  src/common/Continent.cc
  src/common/Game.cc
)

target_link_libraries(server
  PRIVATE
    gf::net
    gf::core
)

add_executable(connect_test
  src/clientServ.cc
  src/client/ClientNetwork.cc
)

target_link_libraries(connect_test
  PRIVATE
    gf::net
    gf::core
)
