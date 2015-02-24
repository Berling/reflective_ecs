#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include <ecs/entity.hpp>

namespace gdw {
    entity::entity(game& game, glm::vec3 position, glm::quat rotation, glm::vec3 scale) noexcept
    : game_(game), id_(++next_id_), position_(position), rotation_(rotation), scale_(scale) { }

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

    unsigned long entity::next_id_ = 0;
}