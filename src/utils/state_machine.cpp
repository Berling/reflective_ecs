#include <core/game.hpp>
#include <utils/logger.hpp>
#include <utils/state.hpp>
#include <utils/state_machine.hpp>

namespace utils {
    state_machine::state_machine(core::game& game) noexcept
    : game_{game} {}

    state_machine::~state_machine() {
        if (current_) {
            current_->leave();
        }
    }

    void state_machine::use(const std::string& name) {
        auto it = states_.find(name);
        if (it != states_.end()) {
            if (current_) {
                current_->leave();
            }

            current_ = it->second.get();
            current_->enter();
        } else {
            utils::log(utils::LOG_ERROR) << "unknown state " << name << std::endl;
        }
    }

    void state_machine::update(float delta_time) {
        if (current_) {
            current_->update(delta_time);
        }
    }
}