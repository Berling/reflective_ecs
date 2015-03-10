#ifndef __GDW_DEMANGLE_HPP__
#define __GDW_DEMANGLE_HPP__

#include <string>

#include <cxxabi.h>

namespace utils {
    std::string demangle(const char* name);
}

#endif