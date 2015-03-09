#ifndef __ASSETS_NATIVE_LOADER_HPP__
#define __ASSETS_NATIVE_LOADER_HPP__

#include <string>
#include <memory>
#include <fstream>

#include <utils/asset.hpp>
#include <utils/asset_loader.hpp>

namespace utils {
    class native_loader : public asset_loader {
    public:
        native_loader(std::string);

        std::shared_ptr<asset> load(std::string) const;
    private:
        std::string path_;
    };
}

#endif