#ifndef __UTILS_STATE_MACHINE_HPP__
#define __UTILS_STATE_MACHINE_HPP__

#include <string>
#include <unordered_map>

#include <utils/demangle.hpp>

namespace core {
    class game;
}

namespace utils {
    class state;
}

namespace utils {
    class state_machine {
    public:
        state_machine(core::game& game) noexcept;
        ~state_machine();

        template<typename type, typename... arguments>
        void add(arguments&&... args) {
            states_.insert(std::make_pair(utils::demangle(typeid(type).name()), std::make_unique<type>(std::forward<arguments>(args)...)));
        }

        void use(const std::string& name);
        void update(float delta_time);

        auto current() const noexcept {
            return current_;
        }

    private:
        core::game& game_;
        std::unordered_map<std::string, std::unique_ptr<state>> states_;
        state *current_ = nullptr;
    };
}

#endif