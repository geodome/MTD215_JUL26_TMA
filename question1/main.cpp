#include <iostream>
#include <SDL2/SDL.h>
#include <algorithm>

#define TITLE "Display Rectangles"

class Rectangle {
    friend std::ostream& operator << (std::ostream&, const Rectangle&);
private:
    int length, height;
public:
    Rectangle(int l, int h) {
        length = l;
        height = h;
    }
    int area() const{
        // the const suffix indicates that this function does not modify any property.
        return length*height;
    }
};

std::ostream& operator<<(std::ostream& out, const Rectangle& r) {
    out << "length " << r.length << " height " << r.height << " Area " << r.area();
    return out; 
}

int main() {
    int length, height;
    std::cout << "Enter length: ";
    std::cin >> length;
    std::cout << "Enter height: ";
    std::cin >> height;

    Rectangle rect1{length, height}, rect2{length, 2*height}, rect3{length/2, height};
    SDL_Rect sdlr1{10,10,length, height}, sdlr2{10+length+10, 10, length, 2*height}, sdlr3{10, 20+height, length/2,height};
    
    std::cout << "First rectangle: " << rect1 << "\n";
    std::cout << "Second rectangle: " << rect2 << "\n";
    std::cout << "3rd rectangle: " << rect3 << "\n";

    // initialise SDL2 subsystems
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << SDL_GetError() << std::endl;
        return 1;
    }
    // create a blank window
    int win_width = std::max(400, 2*length+30);
    int win_height = std::max(400, 2*height+30);
    SDL_Window* gWindow = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_width, win_height, 0);
    if(gWindow == nullptr) {
        std::cerr << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    // create window surface
    SDL_Surface *gSurface = SDL_GetWindowSurface(gWindow);
    if(gSurface == nullptr) {
        std::cerr << SDL_GetError() << std::endl;
        SDL_DestroyWindow(gWindow);
        SDL_Quit();
        return 1;
    }

    // white background
    SDL_FillRect(gSurface, nullptr, SDL_MapRGB(gSurface->format, 0xff, 0xff, 0xff));
    // Display first rectangle as red rectangle
    SDL_FillRect(gSurface, &sdlr1, SDL_MapRGB(gSurface->format,  0xff, 0x00, 0x00));
    // Display second rectangle as green rectangle
    SDL_FillRect(gSurface, &sdlr2, SDL_MapRGB(gSurface->format, 0x00, 0xff, 0x00));
    // display third rectangle as black rectangle
    SDL_FillRect(gSurface, &sdlr3, SDL_MapRGB(gSurface->format, 0x00, 0x00, 0x00));
    // Update window surface
    SDL_UpdateWindowSurface(gWindow);
    
    // main loop
    bool quit = false;
    SDL_Event e;
    while(!quit) {
        while(SDL_PollEvent(&e)) {
            switch(e.type) {
                case SDL_QUIT:
                std::cout << "closing window" << std::endl;
                quit = true;
                break;
                default:
                break;
            }
        }
        SDL_Delay(17);
    }

    // clean up
    SDL_FreeSurface(gSurface);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
    
    return 0;
}