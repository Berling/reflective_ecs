#ifndef __CORE_GAME_HPP__
#define __CORE_GAME_HPP__

#include <utils/asset_manager.hpp>

namespace core {
    class game {
    public:
        static auto& asset_manager() noexcept {
            static utils::asset_manager asset_manager;
            return asset_manager;
        }
    };
}

#endif