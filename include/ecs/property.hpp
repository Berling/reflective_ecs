#ifndef __GDW_PROPERTY_HPP__
#define __GDW_PROPERTY_HPP__

#include <ecs/typed_property.hpp>
#include <utils/logger.hpp>

namespace ecs {
    template <typename owner_type, typename value_type>
    class property : public typed_property<value_type> {
    public:
        using getter_type = value_type (owner_type::*)() const;
        using setter_type = void (owner_type::*)(const value_type& value);
        using value = value_type owner_type::*;

        property(const std::string& name, value value, getter_type getter, setter_type setter) noexcept
        : typed_property<value_type>{name}, value_{value}, getter_{getter}, setter_{setter} {}
        virtual ~property() = default;

        virtual value_type get(base_component* owner) const noexcept {
            return (static_cast<owner_type*>(owner)->*getter_)();
        }

        virtual void set(base_component* owner, const value_type& value) noexcept {
            if (!setter_) {
                utils::log(utils::LOG_WARNING) << "property " << this->name_ << " has no setter" << std::endl;
            }
            (static_cast<owner_type*>(owner)->*setter_)(value);
        }

    private:
        virtual void init(base_component* owner, const value_type& value) noexcept {
            (static_cast<owner_type*>(owner))->*value_ = value;
        }

    private:
        value value_;
        getter_type getter_;
        setter_type setter_;
    };
}

#endif