#ifndef __GDW_PROPERTY_TYPE_HPP__
#define __GDW_PROPERTY_TYPE_HPP__

namespace ecs {
    static auto next_id() noexcept {
        static auto id_generator = 0ul;
        return ++id_generator;
    }

    template <typename type>
    struct property_type {
        static auto type_id() noexcept {
            static auto type_id = next_id();
            return type_id;
        }
    };
}

#endif