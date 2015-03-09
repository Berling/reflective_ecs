#include <ecs/entity_manager.hpp>
#include <utils/logger.hpp>

namespace ecs {
    entity_manager::entity_manager(core::game& game) noexcept
    : game_{game}, entity_template_manager_{game_} {}

    entity& entity_manager::emplace(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scalation) {
        auto entity_ptr = std::make_unique<entity>(game_, position, rotation, scalation);
        entities_.insert(std::make_pair(entity_ptr->id(), std::move(entity_ptr)));
        return *entity_ptr;
    }

    entity& entity_manager::emplace(const std::string& name, const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scalation) {
        auto entity = std::make_unique<ecs::entity>(game_, position, rotation, scalation);
        auto entity_ptr = entity.get();
        entities_.insert(std::make_pair(entity->id(), std::move(entity)));
        auto entity_template = entity_template_manager_.load(name, "entity/" + name + ".template");
        if (!entity_template) {
            utils::log(utils::LOG_FATAL) << "could not load entity template " << name << std::endl; 
        }
        for (auto& pack : entity_template->get()) {
            entity_ptr->emplace(pack->name(), *pack);
        }
        return *entity_ptr;
    }

    void entity_manager::erase(unsigned long id) {
        auto entity = entities_.find(id);
        if (entity != entities_.end()) {
            deletions_.push(id);
        } else {
            utils::log(utils::LOG_WARNING) << "entity " << id << " doesn't exist" << std::endl;
        }
    }

    void entity_manager::clear() {
        while (!deletions_.empty()) {
            auto kill = deletions_.front();
            auto entity = entities_.find(kill);
            if (entity != entities_.end()) {
                entities_.erase(entity);
            } else {
                utils::log(utils::LOG_WARNING) << "entity " << kill << " was already destroyed" << std::endl;
            }
            deletions_.pop();
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