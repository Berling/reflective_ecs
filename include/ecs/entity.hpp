#ifndef __GDW_ENTITY_HPP__
#define __GDW_ENTITY_HPP__

#include <memory>
#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <ecs/base_component.hpp>
#include <ecs/rtti.hpp>
#include <utils/logger.hpp>

namespace ecs {
    class game;
}

namespace ecs {
    class entity {
    private:
        static auto& components_rtti() noexcept {
            static std::unordered_map<std::string, rtti*> components_rtti_;
            return components_rtti_;
        }

    public:
        entity(game& game, glm::vec3 position, glm::quat rotation, glm::vec3 scale) noexcept;
        ~entity() = default;

        entity(const entity& rhs) = delete;
        entity& operator=(const entity& rhs) = delete;
        
        entity(entity&& rhs) = delete;
        entity& operator=(entity&& rhs) = delete;

        template <typename component_type, typename... arguments>
        component_type& emplace(arguments&&... args) {
            auto& type_info = component_type::type_info();
            auto type_id = type_info.type_id();
            auto it = components_.find(type_id);
            if (it == components_.end()) {
                auto component = std::make_unique<component_type>(std::forward<arguments>(args)...);
                auto component_ptr = component.get();
                components_.insert(std::make_pair(type_id, std::move(component)));
                return *component_ptr;
            } else {
                utils::log(utils::warning) << "entity " << id_ << " already has component of type "
                    << type_info->type_name() << std::endl;
                return *static_cast<component_type*>(it->second.get());
            }
        }

        template <typename component_type>
        void erase() {
            auto& type_info = component_type::type_info();
            auto type_id = component_type::type_id();
            auto it = components_.find(type_id);
            if (it != components_.end()) {
                components_.erase(it);
            } else {
                utils::log(utils::warning) << "entity " << id_ << " has no component of type"
                    << type_info->type_name() << std::endl;
            }
        }

        template <typename component_type>
        component_type* component() noexcept {
            auto& type_info = component_type::type_info();
            auto type_id = component_type::type_id();
            auto it = components_.find(type_id);
            if (it != components_.end()) {
                auto component = components_[type_id];
                return static_cast<component_type*>(component.get());
            }
            return nullptr;
        }

        auto id() const noexcept {
            return id_;
        }

        auto position() const noexcept {
            return position_;
        }

        void position(const glm::vec3& position) noexcept {
            position_ = position;
        }

        auto rotation() const noexcept {
            return rotation_;
        }

        void rotation(const glm::quat& rotation) noexcept {
            rotation_ = rotation;
        }

        auto scale() const noexcept {
            return scale_;
        }

        void scale(const glm::vec3& scale) noexcept {
            scale_ = scale;
        }

        glm::mat4 transform() const;

        template <typename component_type>
        static void register_type() {
            auto& type_info = component_type::type_info();
            type_info.reflection_();
            auto type_name = type_info.type_name();
            auto it = components_rtti().find(type_name);
            if (it == components_rtti().end()) {
                components_rtti().insert(std::make_pair(type_name, &type_info));
            }
        }

    private:
        auto next_id() const noexcept {
            static auto id_geneartor = 0ul;
            return ++id_geneartor;
        }


    private:
        game& game_;
        unsigned long id_;
        std::unordered_map<unsigned long, std::unique_ptr<base_component>> components_;

        glm::vec3 position_;
        glm::quat rotation_;
        glm::vec3 scale_;
    };
}

#endif
