#ifndef __ZOMBYE_ENTITY_HPP__
#define __ZOMBYE_ENTITY_HPP__

#include <memory>
#include <stdexcept>
#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <ecs/base_component.hpp>

namespace gdw {
    class game;
}

namespace gdw {
    class entity {
    public:
        entity(game& game, glm::vec3 position, glm::quat rotation, glm::vec3 scale) noexcept;
        ~entity() = default;

        entity(const entity& rhs) = delete;
        entity& operator=(const entity& rhs) = delete;
        
        entity(entity&& rhs) = delete;
        entity& operator=(entity&& rhs) = delete;

        template <typename component_type, typename... arguments>
        component_type& emplace(arguments&&... args) {

        }

        template <typename component_type>
        void erase() {

        }

        template <typename component_type>
        component_type* component() noexcept {
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

    private:
        game& game_;
        unsigned long id_;
        std::unordered_map<unsigned long, std::unique_ptr<base_component>> components_;

        glm::vec3 position_;
        glm::quat rotation_;
        glm::vec3 scale_;

        static unsigned long next_id_;
    };
}

#endif
