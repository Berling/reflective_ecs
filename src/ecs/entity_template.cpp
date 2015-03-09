#include <ecs/entity_template.hpp>

namespace ecs {
    entity_template::entity_template(const std::string& name) noexcept 
    : name_(name) {}
}