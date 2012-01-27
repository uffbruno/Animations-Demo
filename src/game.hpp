#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include "character.hpp"

typedef enum keycodes keycodes;
typedef std::vector<character*> coll_character;

class game {
	public:
		game();
		~game();

		void run();

    private:
        coll_character chars;
        
        bool keys[4];
        
        void init_chars();

        //can't use copy constructor
		game(const game&);
        
        //can't use assignment operator
		game& operator=(const game&);
};

#endif //GAME_HPP