#include "rpg_char.hpp"
#include <sstream>
#include <fstream>
#include <iostream>

rpg_char::rpg_char(int x, int y, const std::string& directory): character(x, y, directory) {
}

rpg_char::~rpg_char() {
}

unsigned int rpg_char::impl_update() {
    //determine character state based on pressed keys.
    //if any key is pressed, character is walking on correspondent direction
    if (keys[KEY_UP]) {
        state = WALKING_UP;
        y -= 1;
    } else if (keys[KEY_DOWN]) {
        y += 1;
        state = WALKING_DOWN;
    } else if (keys[KEY_LEFT]) {
        x -= 1;
        state = WALKING_LEFT;
    } else if (keys[KEY_RIGHT]) {
        x += 1;
        state = WALKING_RIGHT;
    } else { 
        //if no keys are pressed, character is still, and facing direction
        //he / she was originally moving
        if (state == WALKING_UP) state = STILL_UP;
        else if (state == WALKING_DOWN) state = STILL_DOWN;
        else if (state == WALKING_LEFT) state = STILL_LEFT;
        else if (state == WALKING_RIGHT) state = STILL_RIGHT;
    }
    
    return state;
}

void rpg_char::impl_draw() {
    ALLEGRO_BITMAP *frame = spr.get_animation()->get_frame();
    al_draw_bitmap(frame, x, y, 0);
}