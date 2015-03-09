#ifndef __CORE_GAMEPLAY_STATE_HPP__
#define __CORE_GAMEPLAY_STATE_HPP__

#include <ecs/entity_manager.hpp>
#include <utils/state.hpp>

namespace core {
    class game;
}

namespace core {
    class gameplay_state : public utils::state {
    public:
        gameplay_state(game& game);
        ~gameplay_state();

        void enter();
        void leave();
        void update(float delta_time);

    private:
        game& game_;
        ecs::entity_manager entity_manager_;
    };
}

#endif