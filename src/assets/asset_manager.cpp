#include <assets/asset_manager.hpp>
#include <utils/logger.hpp>

namespace assets {
    asset_manager::asset_manager() {
        // create asset loaders
        loaders_.emplace_back(new native_loader("assets"));
    }

    std::shared_ptr<asset> asset_manager::load(std::string path) const {
        for(auto &loader : loaders_) {
            auto ptr = loader->load(path);

            if(ptr) {
                return ptr;
            }
        }

        utils::log(utils::LOG_WARNING) << "Could not find asset: " << path << std::endl;

        return nullptr;
    }
}