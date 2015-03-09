#ifndef __ECS_TYPED_VALUE_HPP__
#define __ECS_TYPED_VALUE_HPP__

#include <ecs/abstract_value.hpp>
#include <ecs/typed_property.hpp>

namespace ecs {
    class base_component;
}

namespace ecs {
    template <typename type>
    class typed_value : public abstract_value {
    public:
        typed_value(const typed_property<type>& assigner, const type& value) noexcept
        : assigner_{assigner}, value_{value} {}

        ~typed_value() = default;

        typed_value(const typed_value& rhs) = delete;
        typed_value& operator= (const typed_value& rhs) = delete;

        typed_value(typed_value&& rhs) = default;
        typed_value& operator= (typed_value&& rhs) = default;

        void assign(base_component* owner) {
            assigner_.init(owner, value_);
        }

    private:
        const typed_property<type>& assigner_;
        type value_;
    };
}

#endif