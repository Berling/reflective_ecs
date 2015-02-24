#include <ecs/base_component.hpp>

namespace gdw {
    base_component::base_component(game& game, entity& owner) noexcept
    : game_(game), owner_(owner) { }

    base_component::~base_component() { }
}
