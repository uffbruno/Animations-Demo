#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

typedef std::vector<ALLEGRO_BITMAP*> collection_frames;

class animation {
    public:
        animation(float speed);
        ~animation();
        
        void add_frame(ALLEGRO_BITMAP* frame);
        void set_speed(const float speed);
        float get_speed() const;
        void next();
        ALLEGRO_BITMAP* get_frame();
        
    private:
        float speed;
        float curr_speed;
        int current_frame; //time between frames.
        collection_frames frames;
        
        //can't use copy constructor
        animation(const animation& other);
        
        //can't use assignment operator
        animation& operator=(const animation& other);
};

#endif //ANIMATION_HPP