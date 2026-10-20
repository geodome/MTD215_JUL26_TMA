#include <SDL2/SDL.h>
#include <iostream>

#define TITLE "Draw Circle App"
#define WIDTH 800
#define HEIGHT 600
#define WHITE {0xff, 0xff, 0xff, 0xff}
#define UNIT 10

void fillCircle(SDL_Renderer* gRenderer, int radius, int x, int y, SDL_Color fgcolor);

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << SDL_GetError() << "\n";
        return 1;
    };

    SDL_Window* gWindow = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    if(gWindow == nullptr) {
        std::cerr << SDL_GetError() << "\n";
        return 1;
    }

    SDL_Renderer *gRenderer = SDL_CreateRenderer(gWindow,-1, 0);
    if(gRenderer == nullptr) {
        std::cerr << SDL_GetError() << "\n";
        return 1;
    }

    // define circle coordinate
    int x = 100;
    int y = 100;
    int r = 20;
    int dx = 10;
    int dy = 10;

    // initial render with white background and black circle
    SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(gRenderer);
    fillCircle(gRenderer, r, x, y, {0x00, 0x00, 0x00, 0xff});
    SDL_RenderPresent(gRenderer);

    bool quit = false;
    SDL_Event e ;
    while (!quit){
        while(SDL_PollEvent(&e)) {
            switch(e.type) {
                case SDL_QUIT:
                quit = true;
                std::cout << "quit event triggered\n";
                break;
                case SDL_KEYDOWN:
                // specify handler for WASD (arrow) keys
                if(e.key.keysym.scancode == SDL_SCANCODE_W) {
                    dy = -UNIT;
                }
                if (e.key.keysym.scancode == SDL_SCANCODE_S){
                    dy = UNIT;
                }
                if (e.key.keysym.scancode == SDL_SCANCODE_A){
                    dx = - UNIT;
                }
                if (e.key.keysym.scancode == SDL_SCANCODE_D){
                    dy = UNIT;
                }
                if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE){
                    quit = true;
                }
                break;
                default:
                break;
            }
        }

        // update phase
        x += dx;
        y += dy;
        // if hits left wall
        if (x < 0) {
            x = 0;
            dx = (1 + rand() % 2) * UNIT;
        }
        // if hits right wall
        if (x + 2*r > WIDTH) {
            x = WIDTH - 2*r;
            dx = - (1 + rand() % 2) * UNIT;
        }
        // if hits top wall
        if (y < 0) {
            y = 0;
            dy = (1 + rand() % 2) * UNIT;
        }
        // if hits bottom wall
        if (y + 2*r > HEIGHT){
            y = HEIGHT - 2*r;
            dy = -(1 + rand() % 2) * UNIT;
        } 

        // render phase
        SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(gRenderer);
        fillCircle(gRenderer, r, x, y, {0x00, 0x00, 0x00, 0x00});
        SDL_RenderPresent(gRenderer);

        // Sleep
        SDL_Delay(17);
    }

    // SDL Cleanup
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);

    return 0;
}

void fillCircle(SDL_Renderer* gRenderer, int radius, int x, int y, SDL_Color fgcolor) {
    int x0 = x + radius;
    int y0 = y + radius;
    SDL_SetRenderDrawColor(gRenderer, fgcolor.r, fgcolor.g, fgcolor.b, fgcolor.a);
    for(int dx = 0; dx <= radius; dx++) {
        int dy = std::sqrt(radius*radius - dx*dx);
        int x1 = x0 + dx;
        int y1 = y0 + dy;
        int x2 = x1;
        int y2 = y0 - dy;
        int x3 = x0 - dx;
        int y3 = y2;
        int x4 = x0- dx;
        int y4 = y1; 
        SDL_RenderDrawLine(gRenderer, x1, y1, x2, y2);
        SDL_RenderDrawLine(gRenderer, x3, y3, x4, y4);
    }
    
}