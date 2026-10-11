#ifndef GUIOBJECT_H
#define GUIOBJECT_H

#include <SDL2/SDL.h>

class GUIObject {
    private:
    int t = 0;
    int p;
    public:
    GUIObject(int period = 1) {
        p = period;
    }
    void tick() {
        t = (t + 1) % p;
    }
    int ticker() {
        return t;
    }
    virtual void update() {} 
    virtual void render(SDL_Renderer*) {}
    virtual void on_keydown(SDL_Scancode k) {}
    virtual void on_keyup(SDL_Scancode k) {}
    virtual ~GUIObject() {}
};

#endif