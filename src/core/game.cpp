#include <core/game.hpp>
#include <core/gameplay_state.hpp>

namespace core {
    game::game() noexcept
    : state_machine_{*this} {
        state_machine_.add<gameplay_state>(*this);
        state_machine_.use("gameplay_state");
    }

    void game::update(float delta_time) {
        state_machine_.update(delta_time);
    }
}