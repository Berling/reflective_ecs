#ifndef __UTILS_GAME_STATE_HPP__
#define __UTILS_GAME_STATE_HPP__

namespace utils {
    class state {
    public:
        virtual void enter() = 0;
        virtual void leave() = 0;
        virtual void update(float delta_time) = 0;
    };
}

#endif