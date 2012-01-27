#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "sprite.hpp"

enum keycodes {
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT
};

class character {
    public:
        character(int pos_x, int pos_y, const std::string& directory);
        virtual ~character();
        
        //initializes sprites, mandatory step. without it anything else will work.
        void init(); 
        
        void set_pos(int x, int y) { set_x(x); set_y(y); }
        void set_x(int x) { this->x = x; }
        void set_y(int y) { this->y = y; }
        void set_state(const unsigned int state);
        unsigned int get_state() const { return state; }
        
        void handle_input(ALLEGRO_EVENT& ev);
        void update();
        void draw();
    
    protected:
        int x;
        int y;
        sprite spr;
        bool loaded;
        unsigned int state;
        std::string directory; //directory that contains the frames and the anim_info.txt file.
        bool keys[4];
        
        bool load_frames();
        virtual unsigned int impl_update() = 0;
        virtual void impl_draw()           = 0;

        
    private:
        character(const character& other);
        character& operator=(const character& other);
};

#endif //CHARACTER_HPP