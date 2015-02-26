#ifndef __GDW_BASE_COMPONENT_HPP__
#define __GDW_BASE_COMPONENT_HPP__

namespace ecs {
    class game;
    class entity;
}

namespace ecs {
    class base_component {
    public:
        base_component(game& game, entity& owner) noexcept;
        virtual ~base_component() = 0;
        
        base_component(const base_component& rhs) = delete;
        base_component& operator=(const base_component& rhs) = delete;
        
        base_component(base_component&& rhs) = delete;
        base_component& operator=(base_component&& rhs) = delete;
        
        auto& owner() const noexcept {
            return owner_;
        }

    protected:
        game& game_;
        entity& owner_;
    };
}

#endif
