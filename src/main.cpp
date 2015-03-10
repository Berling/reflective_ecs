#include <iostream>

#include <ecs/component.hpp>
#include <ecs/entity.hpp>
#include <ecs/entity_manager.hpp>
#include <ecs/property_type.hpp>
#include <ecs/rtti.hpp>
#include <core/game.hpp>
#include <utils/logger.hpp>

using namespace ecs;
using namespace utils;

class test_component : public component<test_component> {
public:
    test_component(core::game& game, entity& owner) noexcept
    : component{game, owner}, value_{1.f} {}

    auto test_value() const noexcept {
        return value_;
    }

private:
    static void register_reflection() {
        register_property<float>("test_value", &test_component::value_, &test_component::test_value, nullptr);
    }

private:
    float value_;

    friend class component<test_component>;
};

int main(int argc, char const* argv[]) {
    entity::register_type<test_component>();
    core::game g;
    return 0;
}