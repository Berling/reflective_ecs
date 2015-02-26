#include <ecs/base_component.hpp>

namespace ecs {
    base_component::base_component(game& game, entity& owner) noexcept
    : game_{game}, owner_{owner} {}

    base_component::~base_component() {}
}
