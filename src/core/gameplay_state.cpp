#include <core/game.hpp>
#include <core/gameplay_state.hpp>
#include <utils/logger.hpp>

namespace core {
    gameplay_state::gameplay_state(game& game)
    : game_{game}, entity_manager_{game_} {

    }

    gameplay_state::~gameplay_state() {

    }

    void gameplay_state::enter() {
        entity_manager_.load_startup("entity/gameplay.startup");
    }

    void gameplay_state::leave() {

    }

    void gameplay_state::update(float delta_time) {

    }
}