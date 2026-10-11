#ifndef GUIOBJECT_H
#define GUIOBJECT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define UNIT 80
#define WHITE {0xff, 0xff, 0xff, 0xff}
#define GREY {0x7e, 0x7e, 0x7e, 0xff}
#define DARKGREY {0xa9, 0xa9, 0xa9, 0xff}
#define ORANGE {0xff, 0xa5, 0x00, 0xff}

#define SMALL 0
#define MEDIUM 1
#define LARGE 2

class GUIObject {
    size_t t = 0;
    size_t p;
    public:
    GUIObject(size_t period) {
        p = period;
    }
    void tick() {
        t = (t + 1) % p;
    }
    size_t ticker() {
        return t;
    }
    virtual ~GUIObject() {}
    virtual void update() {}
    virtual void render(SDL_Renderer* gRenderer, TTF_Font* fonts[], size_t size, int row, int col, int hspan, int vspan) {} 
    virtual void on_mousedown(const SDL_MouseButtonEvent& e) {}
    virtual void on_mouseup(const SDL_MouseButtonEvent& e) {}
};

#endif