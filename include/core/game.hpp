#ifndef __CORE_GAME_HPP__
#define __CORE_GAME_HPP__

#include <utils/asset_manager.hpp>
#include <utils/state_machine.hpp>

namespace core {
    class game {
    public:
        game() noexcept;

        void update(float delta_time);

        static auto& asset_manager() noexcept {
            static utils::asset_manager asset_manager;
            return asset_manager;
        }

    private:
        utils::state_machine state_machine_;
    };
}

#endif