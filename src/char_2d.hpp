#ifndef CHAR_2D_HPP
#define CHAR_2D_HPP

#include "character.hpp"

enum char2d_state {
    CHAR2D_STILL_LEFT,
    CHAR2D_STILL_RIGHT,
    CHAR2D_WALKING_LEFT,
    CHAR2D_WALKING_RIGHT
};

typedef enum char2d_state char2d_state;

class char_2d: public character {
    public:
        char_2d(int x, int y, const std::string& directory);
        virtual ~char_2d();
    private:
        virtual unsigned int impl_update();
        virtual void impl_draw();
        
        char_2d(const char_2d& other);
        char_2d& operator=(const char_2d& other);
};

#endif //CHAR_2D_HPP