#ifndef __GDW_RTTI_HPP__
#define __GDW_RTTI_HPP__
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <ecs/abstract_property.hpp>

namespace ecs {
    class base_component;
    class entity;
    class game;
}

namespace ecs {
    class rtti {
    public:
        using factory = std::unique_ptr<base_component> (*)(game& game, entity& owner);
        using reflection = void (*)();
        using property_list = std::vector<std::unique_ptr<abstract_property>>;

        rtti(const std::string& type_name, factory factory, reflection reflection);
        ~rtti() = default;

        rtti(const rtti& rhs) = delete;
        rtti& operator=(const rtti& rhs) = delete;

        rtti(rtti&& rhs) = delete;
        rtti& operator=(rtti&& rhs) = delete;

        void emplace_property(std::unique_ptr<abstract_property>&& property) {
            properties_.emplace_back(std::move(property));
        }

        auto type_id() const noexcept {
            return type_id_;
        }

        auto& type_name() const noexcept {
            return type_name_;
        }

    private:
        auto next_id() const noexcept {
            static auto id_geneartor = 0ul;
            return ++id_geneartor;
        }

    private:
        unsigned long type_id_;
        std::string type_name_;
        factory factory_;
        reflection reflection_;
        property_list properties_;

        friend class entity;
    };
}

#endif