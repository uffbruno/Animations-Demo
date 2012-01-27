#include "char_2d.hpp"

char_2d::char_2d(int x, int y, const std::string& directory): character(x, y, directory) {
}

char_2d::~char_2d() {
}

unsigned int char_2d::impl_update() {
    //determine character state based on pressed keys.
    //if any key is pressed, character is walking on correspondent direction
    if (keys[KEY_LEFT]) {
        x -= 1;
        state = CHAR2D_WALKING_LEFT;
    } else if (keys[KEY_RIGHT]) {
        x += 1;
        state = CHAR2D_WALKING_RIGHT;
    } else { 
        //if no keys are pressed, character is still, and facing direction
        //he / she was originally moving
        if (state == CHAR2D_WALKING_LEFT) state = CHAR2D_STILL_LEFT;
        else if (state == CHAR2D_WALKING_RIGHT) state = CHAR2D_STILL_RIGHT;
    }
   
    return state;
}

void char_2d::impl_draw() {
    ALLEGRO_BITMAP *frame = spr.get_animation()->get_frame();
    al_draw_bitmap(frame, x, y, 0);
}