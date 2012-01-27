#include "character.hpp"
#include <sstream>
#include <fstream>
#include <iostream>

character::character(int pos_x, int pos_y, const std::string& directory): x(pos_x), y(pos_y), spr(), 
    loaded(false), state(0), directory(directory.c_str()) {
    keys[KEY_LEFT] = keys[KEY_RIGHT] = keys[KEY_UP] = keys[KEY_DOWN] = false;
}

character::~character() {
}

void character::init() {
    if (!loaded) {
        loaded = load_frames();
    }
}

bool character::load_frames() {
    std::ostringstream oss;
    oss << directory << "//anim_info.txt";

    std::ifstream file(oss.str().c_str());
  
    if (!file) {
        return false;
    }
    
    std::string line;
    animation *anim = NULL;
    
    
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#' || line[0] == '\n') {
            continue;
        } else if (line[0] == '.') {
            if (anim != NULL) {
                spr.add_animation(anim);
            }
            
            anim = NULL;
        } else {
            std::ostringstream oss_frame;        
            oss_frame << directory << "//" << line;

            if (anim == NULL) {
                anim = new animation(8.0);
            }

            std::cout << "opening " << oss_frame.str().c_str() << std::endl;
            ALLEGRO_BITMAP *frame = al_load_bitmap(oss_frame.str().c_str());
            if (frame == NULL) {
                std::cout << "error loading frame" << std::endl;
            } else {
                anim->add_frame(frame);
            }
        }
    }
    
    file.close();
    return true;
}

void character::set_state(const unsigned int state) {
    unsigned int num_animations = spr.get_num_animations();
    if (state > num_animations) {
        this->state = 0;
    }
    else {
        this->state = state;
    }
}

void character::handle_input(ALLEGRO_EVENT& ev) {
    if (ev.type == ALLEGRO_EVENT_KEY_DOWN || ev.type == ALLEGRO_EVENT_KEY_UP) {
        switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
                keys[KEY_UP] = (ev.type == ALLEGRO_EVENT_KEY_DOWN);
                break;
            case ALLEGRO_KEY_DOWN:
                keys[KEY_DOWN] = (ev.type == ALLEGRO_EVENT_KEY_DOWN);
                break;
            case ALLEGRO_KEY_LEFT:
                keys[KEY_LEFT] = (ev.type == ALLEGRO_EVENT_KEY_DOWN);
                break;
            case ALLEGRO_KEY_RIGHT:
                keys[KEY_RIGHT] = (ev.type == ALLEGRO_EVENT_KEY_DOWN);
                break;
        }
    }
}

void character::update() {
    if (loaded) {
        state = impl_update();
        
        //animates the character
        spr.set_animation(state);
        spr.run_animation();
    }
}

void character::draw() {
    if (loaded) {
        impl_draw();
    }
}