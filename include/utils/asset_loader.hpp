#ifndef __ASSETS_ASSET_LOADER_HPP__
#define __ASSETS_ASSET_LOADER_HPP__

#include <string>

#include <utils/asset.hpp>

namespace utils {
    class asset_loader {
    public:
        virtual std::shared_ptr<asset> load(std::string) const = 0;
    };
}

#endif