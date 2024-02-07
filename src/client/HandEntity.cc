
#include "GameHub.h"
#include "HandEntity.h"
#include "CardEntity.h"
#include <gf/Entity.h>
#include <gf/Log.h>
#include <gf/ResourceManager.h>
#include <mutex>
#include <vector>

namespace fisk {


    HandEntity::HandEntity(GameHub& gm): game_hub(gm), ressources(gm.resources) {
        position = {0, 0};
        dimensions = {0, 0};

    }

    void HandEntity::setPosition(gf::Vector2i pos) {
        position = pos;
    }

    gf::Vector2i HandEntity::getDimensions() {
        return dimensions;
    }

    void HandEntity::update(gf::Time time) {
        std::lock_guard<std::mutex> guard(game_hub.clientNetwork.m_mutex);
        if (game_hub.clientNetwork.hasGameModel()) {
            auto& gm = game_hub.clientNetwork.getGameModel();
            PlayerId player = game_hub.clientNetwork.getClientId();
            std::vector<CardId> hand = (player > 0 && player <= gm.get_nb_players()) ? gm.get_player(player).getHand(): std::vector<CardId>();
            cards.clear();
            for (auto card : hand) {
                cards.push_back(CardEntity(gm.get_card(card), ressources,gm.get_land(gm.get_card(card).getLand()).getName()));

            }
            dimensions = {CARD_WIDTH * (int)cards.size(), CARD_HEIGHT};
        }
      
    }
    
    void HandEntity::render(gf::RenderTarget& target,const gf::RenderStates& states) {
        
        int offset=0;
        for (auto card : cards) {
            card.setPosition(position + gf::Vector2i({offset*CARD_WIDTH, 0}));
            card.render(target, states);
        }
    }
;   
}
