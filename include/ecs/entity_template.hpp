#ifndef __ECS_ENTITY_TEMPLATE_HPP__
#define __ECS_ENTITY_TEMPLATE_HPP__

#include <string>
#include <vector>

#include <ecs/value_pack.hpp>

namespace ecs {
    class entity_template {
    public:
        explicit entity_template(const std::string& name) noexcept;
        ~entity_template() = default;

        entity_template(const entity_template& rhs) = delete;
        entity_template& operator= (const entity_template& rhs) = delete;

        entity_template(entity_template&& rhs) noexcept = default;
        entity_template& operator= (entity_template&& other) noexcept = default;

        template <typename... arguments>
        void emplace_back(arguments&&... args) {
            value_packs_.emplace_back(std::forward<arguments>(args)...);
        }

        const std::string& name() const {
            return name_;
        }

        auto begin() const {
            return value_packs_.begin();
        }

        auto end() const {
            return value_packs_.end();
        }

        const auto& get() const {
            return value_packs_;
        }

    private:
        using value_packs = std::vector<std::unique_ptr<value_pack>>;

        std::string name_;
        value_packs value_packs_;
    };
}

#endif