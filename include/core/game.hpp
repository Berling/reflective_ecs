#ifndef __CORE_GAME_HPP__
#define __CORE_GAME_HPP__

#include <assets/asset_manager.hpp>

namespace core {
    class game {
    public:
        static auto& asset_manager() noexcept {
            static assets::asset_manager asset_manager;
            return asset_manager;
        }
    };
}

#endif