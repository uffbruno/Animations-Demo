#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <vector>
#include "animation.hpp"

typedef std::vector<animation*> collection_animations;

class sprite {
    public:
        sprite();
        ~sprite();
        
        void add_animation(animation *anim);
        void set_animation(const unsigned int id);
        void run_animation();
        
        int get_num_animations() const { return animations.size(); }

        animation* get_animation();
        
    private:
        unsigned int current_animation;
        collection_animations animations;
    
        //non-copyable object
        sprite(const sprite& other);
        sprite& operator=(const sprite& other);
};

#endif //SPRITE_HPP