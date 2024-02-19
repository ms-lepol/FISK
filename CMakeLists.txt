# How to use:
#   mkdir build
#   cd build
#   cmake ..
#   make
#
cmake_minimum_required(VERSION 3.18...3.21)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)

project(FISK
  VERSION 0.1.0
)

find_package(gf REQUIRED COMPONENTS graphics net core)
 

add_executable(fisk_client
  src/client.cc
  src/client/GameHub.cc
  src/client/MainScene.cc
  src/client/MapEntity.cc
  src/client/LandEntity.cc
  src/client/TurnInterface.cc
  src/client/PhaseIndicator.cc
  src/client/HudButtons.cc
  src/client/ClientNetwork.cc
  src/common/FiskColors.cc
  src/client/LobbyPlayer.cc
  src/common/Land.cc
  src/common/Card.cc
  src/common/Continent.cc
  src/client/LobbyScene.cc
  src/client/TitleScene.cc
  src/client/CardScene.cc
  src/common/Game.cc
  src/common/Player.cc
  src/client/CardEntity.cc
  src/client/HandEntity.cc
  src/client/UnitSelector.cc
  # and the rest of your sources
)

target_link_libraries(fisk_client
  PRIVATE
    gf::graphics
    gf::net
    gf::core
)

target_compile_options(fisk_client
  PRIVATE
  "-g" "-fsanitize=address,undefined"
)

target_compile_features(fisk_client
  PUBLIC
    cxx_std_17
)

set_target_properties(fisk_client
  PROPERTIES
    CXX_EXTENSIONS OFF
    LINK_FLAGS "-fsanitize=address,undefined"
)


add_executable(fisk_server
  src/server.cc
  src/server/ServerNetwork.cc
  src/server/ServerLobby.cc
  src/server/ServerPlayer.cc
  src/server/ServerGroup.cc
  src/server/GameInstance.cc
  src/server/Map1Factory.cc
  src/common/Land.cc
  src/common/Card.cc
  src/common/Continent.cc
  src/common/Player.cc
  src/common/Game.cc
  src/common/FiskColors.cc
)

target_link_libraries(fisk_server
  PRIVATE
    gf::net
    gf::core
)

target_compile_options(fisk_server
  PRIVATE
  "-g" "-fsanitize=address,undefined"
)

target_compile_features(fisk_server
  PUBLIC
    cxx_std_17
)

set_target_properties(fisk_server
  PROPERTIES
    CXX_EXTENSIONS OFF
    LINK_FLAGS "-fsanitize=address,undefined"
)
