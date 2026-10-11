#ifndef GRIDWINDOW_H
#define GRIDWINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdexcept>
#include <iostream>

#include "guiobject.h"

#define TITLE "MTD215 Calculator App"
#define FONTFILE "assets/arial-geo-bold-webfont.ttf"
#define SMALL 0
#define MEDIUM 1
#define LARGE 2

struct GridWidget {
    int row, col;
    int hspan, vspan;
    GUIObject* obj;
};

class GridWindow {
    private:
    int nrows, ncols;
    int nwidgets = 0;
    GridWidget *widgets;
    GridWidget **grid;
    SDL_Window *gWindow;
    SDL_Renderer *gRenderer;
    TTF_Font *fonts[3];

    int width() {
        return ncols * UNIT;
    }

    int height() {
        return nrows * UNIT;
    }

    void init_sdl() {
        if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            std::cerr << SDL_GetError() << std::endl;
            throw std::runtime_error("SDL fails to initialise");
        }

        if(TTF_Init() != 0) {
            std::cerr << TTF_GetError() << std::endl;
            SDL_Quit();
            throw std::runtime_error("SDL_TTF fails to initialise");
        }

        gWindow = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width(), height(), 0);
        if(gWindow == nullptr) {
            std::cerr << SDL_GetError() << std::endl;
            TTF_Quit();
            SDL_Quit();
            throw std::runtime_error("SDL cannot create Window");
        }

        gRenderer = SDL_CreateRenderer(gWindow, -1, 0);
        if(gRenderer == nullptr) {
            std::cerr << SDL_GetError() << std::endl;
            SDL_DestroyWindow(gWindow);
            TTF_Quit();
            SDL_Quit();
            throw std::runtime_error("SDL cannot create renderer");
        }

        fonts[SMALL] = TTF_OpenFont(FONTFILE, 26);
        if(fonts[SMALL] == nullptr) {
            std::cerr <<  TTF_GetError() << std::endl;
            SDL_DestroyRenderer(gRenderer);
            SDL_DestroyWindow(gWindow);
            TTF_Quit();
            SDL_Quit();
            throw std::runtime_error("Fail to load Free Sans Bold 24 font small");
        }
        
        fonts[MEDIUM] = TTF_OpenFont(FONTFILE, 34);
        if(fonts[MEDIUM] == nullptr) {
            std::cerr <<  TTF_GetError() << std::endl;
            TTF_CloseFont(fonts[0]);
            SDL_DestroyRenderer(gRenderer);
            SDL_DestroyWindow(gWindow);
            TTF_Quit();
            SDL_Quit();
            throw std::runtime_error("Fail to load Free Sans Bold 28 font medium");
        }

        fonts[LARGE] = TTF_OpenFont(FONTFILE, 42);
        if(fonts[LARGE] == nullptr) {
            std::cerr <<  TTF_GetError() << std::endl;
            TTF_CloseFont(fonts[0]);
            SDL_DestroyRenderer(gRenderer);
            SDL_DestroyWindow(gWindow);
            TTF_Quit();
            SDL_Quit();
            throw std::runtime_error("Fail to load Free Sans Bold 28 font large");
        }

    }
    
    void close_sdl() {
        TTF_CloseFont(fonts[LARGE]);
        TTF_CloseFont(fonts[MEDIUM]);
        TTF_CloseFont(fonts[SMALL]);
        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);
        TTF_Quit();
        SDL_Quit();
    }

    public:
    GridWindow(int rows, int cols) {
        if(rows <= 0 || cols <= 0) throw std::invalid_argument("must provide a positive number for rows and cols");
        nrows = rows;
        ncols = cols;
        widgets = new GridWidget[rows*cols];
        grid = new GridWidget*[rows*cols];
        for(int i=0; i<rows*cols; i++) {
            grid[i] = nullptr;
        }
        init_sdl();
    }

    void pack(GUIObject* obj, int row, int col, int hspan, int vspan) {
        if(nwidgets == nrows*ncols) throw std::logic_error("grid window is full");
        if(hspan <= 0 || vspan <= 0) throw std::invalid_argument("hspan or vspan must be > 0");
        if(row < 0 || row >= nrows) throw std::invalid_argument("invalid row index");
        if(col < 0 || col >= ncols) throw std::invalid_argument("invalid col index");
        if(grid[row*ncols + col] != nullptr) throw std::logic_error("grid coordinate is occupied already");
        // add widget
        widgets[nwidgets] = {row, col, hspan, vspan, obj};
        for(int i = 0; i < vspan; i++) {
            int r = row + i;
            for(int  j = 0; j < hspan; j++) {
                int c = col + j;
                int index = r*ncols + c;
                grid[index] = &(widgets[nwidgets]);
            }
        }
        nwidgets++;
    }

    void mainloop() {
        SDL_Event e;
        bool quit = false;
        while(!quit) {
            while(SDL_PollEvent(&e)) {
                switch(e.type) {
                    case SDL_QUIT:
                    quit = true;
                    break;
                    case SDL_MOUSEBUTTONDOWN:
                    if(e.button.x > 0 && e.button.x < width() && e.button.y > 0 && e.button.y < height()) {
                        int col = e.button.x / UNIT;
                        int row = e.button.y / UNIT;
                        int index = row*ncols + col;
                        if(grid[index]) grid[index]->obj->on_mousedown(e.button);
                    }
                    break;
                    case SDL_MOUSEBUTTONUP:
                    if(e.button.x > 0 && e.button.x < width() && e.button.y > 0 && e.button.y < height()) {
                        int col = e.button.x / UNIT;
                        int row = e.button.y / UNIT;
                        int index = row*ncols + col;
                        if(grid[index]) grid[index]->obj->on_mouseup(e.button);
                    }
                    break;
                    default:
                    break;
                }
            }
            for(int i = 0; i<nwidgets; i++) {
                widgets[i].obj->tick();
                widgets[i].obj->update();
            }
            SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xff);
            SDL_RenderClear(gRenderer);
            for(int i = 0; i < nwidgets; i++) {
                widgets[i].obj->render(gRenderer, fonts, 3, widgets[i].row, widgets[i].col, widgets[i].hspan, widgets[i].vspan);
            }
            SDL_RenderPresent(gRenderer);
            SDL_Delay(17);
        }
    }

    ~GridWindow() {
        close_sdl();
    }
};

#endif