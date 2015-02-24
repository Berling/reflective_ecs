#include <ecs/entity_manager.hpp>


namespace gdw {
    entity_manager::entity_manager(game& game) noexcept : game_(game) { }

    entity& entity_manager::emplace(const glm::vec3& position, const glm::quat& rotation,
    const glm::vec3& scalation) {
        auto entity_ptr = std::make_unique<entity>(game_, position, rotation, scalation);
        entities_.insert(std::make_pair(entity_ptr->id(), std::move(entity_ptr)));
        return *entity_ptr;
    }

    void entity_manager::erase(unsigned long id) {
        auto entity = entities_.find(id);
        if (entity != entities_.end()) {
            deletions_.push(id);
        } else {
            // TODO: warning
        }
    }

    void entity_manager::clear() {
        while (!deletions_.empty()) {
            unsigned int kill = deletions_.front();
            auto entity = entities_.find(kill);
            if (entity != entities_.end()) {
                entities_.erase(entity);
                deletions_.pop();
            } else {
                // TODO: warning
            }
        }
    }

    entity* entity_manager::resolve(unsigned long id) {
        auto entity = entities_.find(id);
        if (entity != entities_.end()) {
            return entity->second.get();
        }
        return nullptr;
    }
}