#include <ecs/rtti.hpp>

namespace ecs {
    rtti::rtti(const std::string& type_name, factory factory, reflection reflection)
    : type_id_{next_id()}, type_name_{type_name}, factory_{factory}, reflection_{reflection} {}
}