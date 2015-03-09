#include <ecs/assign.hpp>
#include <ecs/entity.hpp>
#include <ecs/entity_template_manager.hpp>
#include <core/game.hpp>

using namespace Json;
using namespace utils;

namespace ecs {
    entity_template_manager::entity_template_manager(core::game& game) noexcept
    : game_{game} {}

    std::shared_ptr<const entity_template> entity_template_manager::load_new(const std::string& name, const std::string& file) {
        auto asset = game_.asset_manager().load(file);
        if (!asset) {
            return nullptr;
        }
        Json::Value root;
        if (!reader_.parse(&(*asset->content().begin()), &(*asset->content().end()), root)) {
            utils::log(LOG_ERROR) << "could not parse " << file << " " << reader_.getFormattedErrorMessages() << std::endl;
            return nullptr;
        }
        auto entity_type = root[name];
        if (entity_type.isNull()) {
            utils::log(LOG_ERROR) << "no template " << name << " in " << file << std::endl;
            return nullptr;
        }
        if (!entity_type.isObject()) {
            utils::log(LOG_ERROR) << "template " << name << " is not an object" << std::endl;
            return nullptr;
        }
        auto entity_template = std::make_shared<ecs::entity_template>(name);
        for (auto it = entity_type.begin(); it != entity_type.end(); ++it) {
            auto name = it.key().asString();
            auto rtti = entity::type_info(name);
            if (!rtti) {
                utils::log(LOG_ERROR) << name << " has no runtime type information" << std::endl;
                return nullptr;
            }
            auto value_pack = assign_values(name, *it, rtti->properties_);
            if (!value_pack) {
                utils::log(LOG_ERROR) << "values could not be assigned to "  << name << " value pack" << std::endl;
                return nullptr;
            }
            entity_template->emplace_back(std::move(value_pack));
        }
        return entity_template;
    }
}