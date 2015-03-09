#ifndef __ECS_VALUE_PACK_HPP__
#define __ECS_VALUE_PACK_HPP__

#include <memory>
#include <string>
#include <vector>

#include <ecs/typed_property.hpp>
#include <ecs/typed_value.hpp>

namespace ecs {
    class value_pack {
    public:
        value_pack(const std::string& name) noexcept 
        : name_{name} {}

        ~value_pack() = default;

        value_pack(const value_pack& other) = delete;
        value_pack& operator= (const value_pack& other) = delete;

        value_pack(value_pack&& other) noexcept = default;
        value_pack& operator= (value_pack&& other) noexcept = default;

        template <typename... arguments>
        void emplace_back(arguments&&... args) {
            values_.emplace_back(std::forward<arguments>(args)...);
        }

        const auto& name() const  {
            return name_;
        }

        auto begin() const {
            return values_.begin();
        }

        auto end() const {
            return values_.end();
        }

        const auto& get() const {
            return values_;
        }

    private:
        using values = std::vector<std::unique_ptr<abstract_value>>;

        std::string name_;
        values values_;
    };
}

#endif