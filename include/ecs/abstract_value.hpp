#ifndef __ECS_ABSTRACT_VALUE_HPP__
#define __ECS_ABSTRACT_VALUE_HPP__

namespace ecs {
    class base_component;
}

namespace ecs {
    class abstract_value {
    public:
        virtual void assign(base_component* owner) = 0;
    };
}

#endif