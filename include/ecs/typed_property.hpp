#ifndef __GDW_TYPED_PROPERTY_HPP__
#define __GDW_TYPED_PROPERTY_HPP__

#include <ecs/abstract_property.hpp>
#include <ecs/property_type.hpp>

namespace ecs {
    class base_component;
}

namespace ecs {
    template <typename value_type>
    class typed_property : public abstract_property {
    public:
        typed_property(const std::string& name) noexcept
        : abstract_property{name} {}
        virtual ~typed_property() = default;

        virtual unsigned long type() const noexcept {
            return property_type<value_type>::type_id();
        }

        virtual value_type get(base_component* owner) const noexcept = 0;
        virtual void set(base_component* owner, const value_type& value) noexcept = 0;

    private:
        virtual void init(base_component* owner, const value_type& value) const noexcept = 0;

        template <typename type>
        friend class typed_value;
    };
}

#endif