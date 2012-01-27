#include "animation.hpp"

animation::animation(float speed): speed(speed),
    curr_speed(0), current_frame(0), frames() {
}

animation::~animation() {
    for (unsigned int i = 0; i < frames.size(); ++i) {
        al_destroy_bitmap(frames[i]);
    }

    frames.clear();
}

void animation::add_frame(ALLEGRO_BITMAP *frame) {
    if (frame == NULL) return;
    
    //take a pixel from background color and use it as transparency pixel
    al_convert_mask_to_alpha(frame, al_get_pixel(frame, 0, 0));

    //add frame to collection
    frames.push_back(frame);
}

void animation::set_speed(const float speed) {
    this->speed = speed;
}

float animation::get_speed() const {
    return this->speed;
}

void animation::next() {
    ++curr_speed;
    if (curr_speed >= speed) {
        ++current_frame;
        current_frame %= frames.size();
        curr_speed = 0;
    }
}

ALLEGRO_BITMAP* animation::get_frame() {
    if (current_frame == -1) current_frame = 0;
    return frames.at(current_frame);
}