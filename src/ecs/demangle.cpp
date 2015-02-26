#include <cstdlib>

#include <ecs/demangle.hpp>

namespace ecs {
    std::string demangle(const char* name) {
        char* realname;
        std::size_t len;
        int stat;
        realname = abi::__cxa_demangle(name, nullptr, &len, &stat);
        if (realname) {
            std::string out(realname);
            std::free(realname);
            auto pos = out.find("::");
            if (pos != std::string::npos) {
                return out.substr(pos + 2, out.length());
            }
            return out;
        }
        return std::string(name);
    }
}
