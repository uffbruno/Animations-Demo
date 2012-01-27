#ifndef RPG_CHAR_HPP
#define RPG_CHAR_HPP

#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "character.hpp"

enum state {
    //walking status
    WALKING_UP = 0,
    WALKING_LEFT,
    WALKING_RIGHT,
    WALKING_DOWN,

    //still status
    STILL_UP,
    STILL_LEFT,
    STILL_RIGHT,
    STILL_DOWN
};

typedef enum state state;

class rpg_char: public character {
    public:
        rpg_char(int pos_x, int pos_y, const std::string& directory);
        ~rpg_char();

    private:
        virtual void impl_draw();
        virtual unsigned int impl_update();

        rpg_char(const rpg_char& other);
        rpg_char& operator=(const rpg_char& other);
};

#endif //RPG_CHAR_HPP