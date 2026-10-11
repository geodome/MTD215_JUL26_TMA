#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#include "guiobject.h"
#include "circle.h"

class Window: public GUIObject {
    private:
    std::string title;
    int width, height;
    SDL_Window* gWindow;
    SDL_Renderer* gRenderer;
    std::vector<GUIObject*> objs;
    bool quit = false;
    bool paused = false;

    bool sdl_init() {
        if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            std::cerr << SDL_GetError() << std::endl;
            return false;
        }
        // create a blank window
        gWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
        if(gWindow == nullptr) {
            std::cerr << SDL_GetError() << std::endl;
            SDL_Quit();
            return false;
        }
        // create renderer
        gRenderer = SDL_CreateRenderer(gWindow, -1, 0);
        if(gRenderer == nullptr) {
            std::cerr << SDL_GetError() << std::endl;
            SDL_DestroyWindow(gWindow);
            SDL_Quit();
            return false;
        }
        return true;
    }

    void sdl_close() {
        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);
        SDL_Quit();
    }

    public:
    Window(std::string title, int width, int height): GUIObject() {        
        this->title = title;
        this->width = width;
        this->height = height;
       if(!sdl_init()) throw std::runtime_error("Fail to initialise SDL2");
    }

    void add(GUIObject* obj) {
        objs.push_back(obj);
    }

    void mainloop() {
        // initial render
        SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(gRenderer);
        for(auto& obj: objs) {
            obj->render(gRenderer);
        }
        SDL_RenderPresent(gRenderer);

        // main loop
        SDL_Event e;
        do {
            // process event queue
            while(SDL_PollEvent(&e)) {
                switch(e.type) {
                    case SDL_QUIT:
                    std::cout << "closing window" << std::endl;
                    quit = true;
                    break;
                    case SDL_KEYDOWN:
                    on_keydown(e.key.keysym.scancode);
                    if(!paused) {
                        for(auto& obj: objs) {
                            obj->on_keydown(e.key.keysym.scancode);
                        }
                    }
                    break;
                    case SDL_KEYUP:
                    on_keyup(e.key.keysym.scancode);
                    if(!paused) {
                        for(auto& obj: objs) {
                            obj->on_keyup(e.key.keysym.scancode);
                        }
                    }
                    break;
                    default:
                    break;
                }
            }
            if(!paused) {
                // update GUI Object's state
                for(auto& obj: objs) {
                    obj->tick();
                    obj->update();
                }

                // Render each GUIObject
                SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
                SDL_RenderClear(gRenderer);
                for(auto& obj: objs) {
                    obj->render(gRenderer);
                }
                SDL_RenderPresent(gRenderer);
            }

            // animate at 60fps
            SDL_Delay(17);
        } while(!quit);
    }

    // Press Q to quit, Space to toggle pause state
    void on_keydown(SDL_Scancode sc) override {
        switch(sc) {
            case SDL_SCANCODE_Q:
            quit = true;
            std::cout << "quiting\n";
            break;
            case SDL_SCANCODE_SPACE:
            paused = !paused;
            std::cout << "pause toggled\n";
            break;
            default:
            break;
        }
    }

    ~Window() {
        sdl_close();
    }
};

#endif 