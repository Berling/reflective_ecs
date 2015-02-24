#ifndef __ZOMBYE_ENTITY_MANAGER_HPP__
#define __ZOMBYE_ENTITY_MANAGER_HPP__

#include <memory>
#include <queue>
#include <unordered_map>

#include <ecs/entity.hpp>

namespace gdw {
    class game;
}

namespace gdw {
    class entity_manager {
    public:
        entity_manager(game& game) noexcept;
        ~entity_manager() = default;

        entity_manager(const entity_manager& rhs) = delete;
        entity_manager& operator=(const entity_manager& rhs) = delete;
        
        entity_manager(entity_manager&& rhs) = delete;
        entity_manager& operator=(entity_manager&& rhs) = delete;
        
        entity& emplace(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale = glm::vec3{1.f});
        void erase(unsigned long id);
        void clear();
        entity* resolve(unsigned long id);

    private:
        game& game_;
        std::unordered_map<unsigned long, std::unique_ptr<entity>> entities_;
        std::queue<unsigned long> deletions_;
    };
}

#endif