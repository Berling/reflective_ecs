#include <iostream>

#include <assets/native_loader.hpp>

namespace assets {
    native_loader::native_loader(std::string path) {
        auto last = path.back();

        if(last != '/') {
            path += '/';
        }

        path_ = path;
    }

    std::shared_ptr<asset> native_loader::load(std::string path) const {
        auto full_path = path_ + path;

        std::ifstream stream(full_path, std::ios::binary);

        if(stream) {
            // get size
            stream.seekg(0, std::ios::end);

            auto size = stream.tellg();

            // load asset
            stream.seekg(0, std::ios::beg);

            auto asset = std::make_shared<assets::asset>(path, size);

            stream.read(asset->content().data(), size);

            stream.close();

            return asset;
        }

        return nullptr;
    }
}