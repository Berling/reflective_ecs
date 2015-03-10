#include <glm/gtx/string_cast.hpp>
#include <json/json.h>

#include <ecs/entity_manager.hpp>
#include <core/game.hpp>
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

    void entity_manager::clean_up() {
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

    void entity_manager::clear() {
        entities_.clear();
    }

    entity* entity_manager::resolve(unsigned long id) {
        auto entity = entities_.find(id);
        if (entity != entities_.end()) {
            return entity->second.get();
        }
        return nullptr;
    }

    void entity_manager::load_startup(const std::string& name) {
        auto asset = game_.asset_manager().load(name);
        if (!asset) {
            utils::log(utils::LOG_ERROR) << "could not load startup file " << name << std::endl;
            return;
        }
        static Json::Reader reader;
        Json::Value root;
        if (!reader.parse(&(*asset->content().begin()), &(*asset->content().end()), root)) {
            utils::log(utils::LOG_ERROR) << "could not parse " << name << " " << reader.getFormattedErrorMessages() << std::endl;
            return;
        }
        auto insert = root["insert"];
        if (insert.isNull()) {
            utils::log(utils::LOG_ERROR) << "no insertion specified" << std::endl;
            return;
        }
        for (auto& v : insert) {
            auto entity = v["entity"];
            if (entity.isNull()) {
                utils::log(utils::LOG_ERROR) << "no entity template specified" << std::endl;
            }
            auto position = v["position"];
            auto pos = glm::vec3{1.f};
            if (position.isNull()) {
                utils::log(utils::LOG_WARNING) << "no position specified for entity " << entity << std::endl;
            } else {
                for (auto i = 0; i < 3; ++i) {
                    pos[i] = position[i].asFloat();
                }
            }
            auto rotation = v["rotation"];
            auto rot = glm::angleAxis(0.f, glm::vec3{0.f});
            if (rotation.isNull()) {
                utils::log(utils::LOG_WARNING) << "no rotation specified for entity " << entity << std::endl;
            } else {
                auto angle = rotation[0].asFloat();
                auto axis = glm::vec3{0.f};
                for (auto i = 1; i < 4; ++i) {
                    axis[i - 1] = rotation[i].asFloat();
                }
                rot = glm::angleAxis(angle, axis);
            }
            auto scale = v["scale"];
            auto scl = glm::vec3{1.f};
            if (scale.isNull()) {
                utils::log(utils::LOG_WARNING) << "no scale specified for entity " << entity << std::endl;
            } else {
                for (auto i = 0; i < 3; ++i) {
                    scl[i] = scale[i].asFloat();
                }
            }
            emplace(entity.asString(), pos, rot, scl);
        }
    }
}