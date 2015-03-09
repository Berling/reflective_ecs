#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include <ecs/entity.hpp>

namespace ecs {
    entity::entity(core::game& game, glm::vec3 position, glm::quat rotation, glm::vec3 scale) noexcept
    : game_{game}, id_{next_id()}, position_{position}, rotation_{rotation}, scale_{scale} {}

    base_component& entity::emplace(const std::string& name, const value_pack& value_pack) {
        auto type_info_it = components_rtti().find(name);
        if (type_info_it == components_rtti().end()) {
            utils::log(utils::LOG_FATAL) << name << " has no runtime typeinformation" << std::endl;
        }
        auto type_info = type_info_it->second;
        auto it = components_.find(type_info->type_id());
        if (it == components_.end()) {
            auto component = type_info->factory_(game_, *this);
            auto component_ptr = component.get();
            components_.insert(std::make_pair(type_info->type_id(), std::move(component)));
            for (auto& v : value_pack.get()) {
                v->assign(component_ptr);
            }
            return *component_ptr;
        } else {
            utils::log(utils::LOG_WARNING) << "entity " << id_ << " already has component of type "
                << type_info->type_name() << std::endl;
            return *it->second;
        }
    }

    glm::mat4 entity::transform() const {
        auto norm = glm::normalize(rotation_);
        auto transform = glm::toMat4(norm);
        auto scale = glm::scale(glm::mat4{}, scale_);
        transform =  transform * scale;
        transform[3].x = position_.x;
        transform[3].y = position_.y;
        transform[3].z = position_.z;
        return transform;
    }
}