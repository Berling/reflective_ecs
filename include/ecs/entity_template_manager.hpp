#ifndef __ZOMBYE_ENTITY_TEMPLATE_MANAGER_HPP__
#define __ZOMBYE_ENTITY_TEMPLATE_MANAGER_HPP__

#include <memory>
#include <string>
#include <unordered_map>

#include <json/json.h>

#include <utils/cached_resource_manager.hpp>
#include <ecs/entity_template.hpp>

namespace core {
    class game;
}

namespace ecs {
    class entity_template_manager : public cached_resource_manager<const entity_template, entity_template_manager> {
    public:
        entity_template_manager(core::game& game) noexcept;
        ~entity_template_manager() = default;

        entity_template_manager(const entity_template_manager& rhs) = delete;
        entity_template_manager& operator=(const entity_template_manager& rhs) = delete;

        entity_template_manager(entity_template_manager&& rhs) = default;
        entity_template_manager& operator=(entity_template_manager&& rhs) = default;

    protected:
        std::shared_ptr<const entity_template> load_new(const std::string& name, const std::string& file);

    private:
        core::game& game_;
        Json::Reader reader_;

        friend class cached_resource_manager<const entity_template, entity_template_manager>;
    };
}

#endif