#include <utils/asset.hpp>

namespace utils {
    asset::asset(std::string path, size_t size) : path_(path), content_(size) {}

    std::string asset::path() const {
        return path_;
    }

    std::vector<char>& asset::content() {
        return content_;
    }
}