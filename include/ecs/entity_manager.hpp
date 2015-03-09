#ifndef __GDW_ENTITY_MANAGER_HPP__
#define __GDW_ENTITY_MANAGER_HPP__

#include <memory>
#include <queue>
#include <unordered_map>

#include <ecs/entity.hpp>
#include <ecs/entity_template_manager.hpp>

namespace core {
    class game;
}

namespace ecs {
    class entity_manager {
    public:
        entity_manager(core::game& game) noexcept;
        ~entity_manager() = default;

        entity_manager(const entity_manager& rhs) = delete;
        entity_manager& operator=(const entity_manager& rhs) = delete;
        
        entity_manager(entity_manager&& rhs) = delete;
        entity_manager& operator=(entity_manager&& rhs) = delete;
        
        entity& emplace(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale = glm::vec3{1.f});
        entity& emplace(const std::string& name, const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale = glm::vec3{1.f});
        void erase(unsigned long id);
        void clear();
        entity* resolve(unsigned long id);

    private:
        core::game& game_;
        std::unordered_map<unsigned long, std::unique_ptr<entity>> entities_;
        std::queue<unsigned long> deletions_;
        entity_template_manager entity_template_manager_;
    };
}

#endif