#include "game.hpp"
#include "rpg_char.hpp"
#include "char_2d.hpp"

#define ALLEGRO_STATICLINK
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

game::game(): chars() {
    al_init();
    al_install_keyboard();
    
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();

    keys[KEY_UP]    = false;
    keys[KEY_DOWN]  = false;
    keys[KEY_LEFT]  = false;
    keys[KEY_RIGHT] = false;
    
    init_chars();
}

game::~game() {
    if (!chars.empty()) {
        for (unsigned int i = 0; i < chars.size(); ++i) {
            delete chars[i];
        }
    }
}

void game::init_chars() {
    character *charrpg = new rpg_char(640/3, 480/4, "resources//rpgmaker");
    charrpg->init();
    charrpg->set_state(STILL_DOWN);
    chars.push_back(charrpg);

    character *char2d = new char_2d(640/3, 480/4, "resources//ken");
    char2d->init();
    char2d->set_state(CHAR2D_STILL_RIGHT);
    chars.push_back(char2d);
    
    char2d = new char_2d(640/3, 480/4 + 200, "resources//mariobros");
    char2d->init();
    char2d->set_state(CHAR2D_STILL_RIGHT);
    chars.push_back(char2d);
}

void game::run() {
    //acquire allegro resources
    ALLEGRO_DISPLAY *display = al_create_display(640,480);
    ALLEGRO_FONT *font = al_load_font("resources//fonts//pirulen.ttf", 32, 0);
    ALLEGRO_FONT *infofont = al_load_font("resources//fonts//pirulen.ttf", 14, 0);
    //ALLEGRO_FONT *debugfont = al_load_font("resources//fonts//pirulen.ttf", 10, 0);
    ALLEGRO_TIMER *timer = al_create_timer(1.0/60);
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    
    //register event sources
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    
    bool exit   = false; //exit game
    bool redraw = false; //redraw screen

    al_start_timer(timer);
        	
    while (!exit) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
        
        //if user closes window
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            exit = true;
        }
        
        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            //pressing ESC also exits the loop.
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                exit = true;
            }
        }
        
        for (unsigned int i = 0; i < chars.size(); ++i) {
            chars[i]->handle_input(event);
        }

        if (event.type == ALLEGRO_EVENT_TIMER) {
            
            for (unsigned int i = 0; i < chars.size(); ++i) {
                chars[i]->update();
            }
            redraw = true;
        }
        
        if (redraw && al_is_event_queue_empty(event_queue)) {
            al_clear_to_color(al_map_rgb(0,0,0));
            
            //title
            al_draw_text(font, al_map_rgb(255,255,255), 640/2, 0, ALLEGRO_ALIGN_CENTRE, "Animation Demo");
            
            //instructions
            al_draw_text(infofont, al_map_rgb(255,255,255), 640/2, 30, ALLEGRO_ALIGN_CENTRE, 
                "Press arrow keys to move character; ESC to exit");
            
            for (unsigned int i = 0; i < chars.size(); ++i) {
                chars[i]->draw();
            }
            
            al_flip_display();
            redraw = false;
        }
    }
    
    //release allegro resources
    al_destroy_display(display);
    al_destroy_font(font);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
}