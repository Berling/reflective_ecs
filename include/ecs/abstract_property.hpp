#ifndef __GDW_ABSTRACT_PROPERTY_HPP__
#define __GDW_ABSTRACT_PROPERTY_HPP__

#include <string>

namespace ecs {
    class abstract_property {
    public:
        abstract_property(const std::string& name) noexcept
        : name_{name} {}
        virtual ~abstract_property() = default;

        abstract_property(const abstract_property& rhs) = delete;
        abstract_property& operator=(const abstract_property& rhs) = delete;

        abstract_property(abstract_property&& rhs) = delete;
        abstract_property& operator=(abstract_property&& rhs) = delete;

        auto& name() const noexcept {
            return name_;
        }

        virtual unsigned long type() const noexcept = 0;

    protected:
        std::string name_;
    };
}

#endif