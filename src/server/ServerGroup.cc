#include "ServerGroup.h"
#include <algorithm>

namespace fisk {

    ServerGroup::~ServerGroup() = default;

    void ServerGroup::addPlayer(ServerPlayer& player) {
        m_players.push_back(player);
    }

    void ServerGroup::removePlayer(ServerPlayer& player) {
        m_players.erase(std::remove(m_players.begin(), m_players.end(), player), m_players.end());
    }

    std::vector<PlayerData> ServerGroup::getPlayers() {
        std::vector<PlayerData> list;

        for (const ServerPlayer& player : m_players) {
        if (player.name.empty()) {
            continue;
        }

        PlayerData data;
        data.id = player.id;
        data.name = player.name;
        data.ready = player.ready;
        list.push_back(std::move(data));
        }

        return list;
    }

    bool ServerGroup::areAllPlayersReady() {
        return std::all_of(m_players.begin(), m_players.end(), [](ServerPlayer& player) { return player.ready; });
    }

    void ServerGroup::cloneTo(ServerGroup& group) {
        
        group.m_players.clear();

        for (auto& player : m_players) {
        group.addPlayer(player);
        }
    }

}