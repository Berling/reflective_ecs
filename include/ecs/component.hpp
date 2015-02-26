#ifndef __GDW_COMPONENT_HPP__
#define __GDW_COMPONENT_HPP__

#include <ecs/base_component.hpp>
#include <ecs/demangle.hpp>
#include <ecs/property.hpp>
#include <ecs/rtti.hpp>

namespace ecs {
    class entity;
    class game;
}

namespace ecs {
    template <typename component_type>
    class component : public base_component {
    public:
        component(game& game, entity& owner) noexcept
        : base_component{game, owner} {}
        ~component() = 0;

        component(const component& rhs) = delete;
        component& operator=(const component& rhs) = delete;

        component(component&& rhs) = delete;
        component& operator=(component&& rhs) = delete;

        static auto& type_info() noexcept {
            static rtti type_info{demangle(typeid(component_type).name()), 
                (rtti::factory)(component_type::create),
                (rtti::reflection)(component_type::register_reflection)};
            return type_info;
        }

    protected:
        template <typename property_type>
        static void register_property(const std::string& name,
            typename property<component_type, property_type>::value value,
            typename property<component_type, property_type>::getter_type getter,
            typename property<component_type, property_type>::setter_type setter) {
            type_info().emplace_property(std::make_unique<property<component_type, property_type>>(name, value, getter, setter));
        }

    private:
        static auto create(game& game, entity& owner) {
            return std::move(std::make_unique<component_type>(game, owner));
        }

        static void register_reflection() {}
    };

    template <typename component_type>
    component<component_type>::~component() {}
}

#endif