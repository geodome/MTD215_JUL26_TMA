#ifndef CIRCLE_H
#define CIRCLE_H

#include <SDL2/SDL.h>
#include "guiobject.h"
#include "vector.h"
#include "boundingbox.h"
#include "definitions.h"

class Circle: public GUIObject {
    private:
    int radius;
    Vector coord, velocity;
    SDL_Color color;
    BoundingBox *box;

    void fillCircle(SDL_Renderer* gRenderer, int x0, int y0, int radius, const SDL_Color& fgcolor) {
        SDL_SetRenderDrawColor(gRenderer, fgcolor.r, fgcolor.g, fgcolor.b, fgcolor.a);
        for(int x = 0; x <= radius; x++) {
            int y = sqrt(radius*radius - x*x);
            int x1 = x0 + x;
            int y1 = y0 - y;
            int x2 = x1;
            int y2 = y0 + y;
            int x3 = x0 - x;
            int y3 = y2;
            int x4 = x0 - x;
            int y4 = y1;
            SDL_RenderDrawLine(gRenderer, x1, y1, x2, y2);
            SDL_RenderDrawLine(gRenderer, x3, y3, x4, y4);
        }
    }

    Vector inital_velocity() {
        int i = rand() % 8;
        int sign[2] = {-1, 1};
        int m_x[8] = {12,16,10,24, 8,15, 7,24};
        int m_y[8] = {16,12,24,10,15, 8,24, 7};
        return {sign[rand() % 2]*m_x[i], sign[rand() % 2]*m_y[i]};
    }

    int max(int i, int j) {
        if( i > j) return i;
        return j;
    }

    int min(int i, int j) {
        if(i < j) return i;
        return j;
    }

    public:
    Circle(int r, int x, int y, SDL_Color c): GUIObject(PERIOD) {
        velocity = inital_velocity();
        radius = r;
        color = c;
        coord = {x, y};
        box = new BoundingBox(&coord, 2*r, 2*r);
    }
    void on_keydown(SDL_Scancode k) override {
        std::cout << "velocity changed from " << velocity;
        switch(k) {
            case SDL_SCANCODE_W:
            if(velocity.y > 0) velocity.y = - velocity.y;
            break;
            case SDL_SCANCODE_A:
            if(velocity.x > 0) velocity.x = -velocity.x;
            break;
            case SDL_SCANCODE_S:
            if(velocity.y < 0) velocity.y = -velocity.y;
            break;
            case SDL_SCANCODE_D:
            if(velocity.x < 0) velocity.x = -velocity.x;
            break;
            default:
            break;
        }
        std::cout << " to " << velocity << "\n";
    }

    void update() override {
        if(ticker() != 0) return;
        auto dir = velocity.direction();
        int m_x[8] = {12,16,10,24, 8,15, 7,24};
        int m_y[8] = {16,12,24,10,15, 8,24, 7};

        coord += velocity;
        coord.x = max(0, coord.x);
        coord.x = min(WIDTH - 2*radius, coord.x);
        coord.y = max(0, coord.y);
        coord.y = min(HEIGHT - 2*radius, coord.y);
        if(box->overlap(BoundingBox::TOP) && box->overlap(BoundingBox::LEFT)) {
            std::cout << "collided top and left walls. " << velocity;
            int i = rand() % 8;
            velocity.x = m_x[i];
            velocity.y = m_y[i];
            std::cout << " to " << velocity << "\n";
        } 
        else if (box->overlap(BoundingBox::TOP) && box->overlap(BoundingBox::RIGHT)) {
            std::cout << "collided top and right walls. " << velocity;
            int i = rand() % 8;
            velocity.x = m_x[i];
            velocity.y = m_y[i];
            velocity.x = - velocity.x;
            std::cout << " to " << velocity << "\n";
        } 
        else if (box->overlap(BoundingBox::BOTTOM) && box->overlap(BoundingBox::LEFT)) {
            std::cout << "collied bottom and left walls\n";
            int i = rand() % 8;
            velocity.x = m_x[i];
            velocity.y = m_y[i];
            velocity.y = - velocity.y;
        } 
        else if (box->overlap(BoundingBox::BOTTOM) && box->overlap(BoundingBox::RIGHT)) {
            std::cout << "collided bottom and right walls\n";
            int i = rand() % 8;
            velocity.x = m_x[i];
            velocity.y = m_y[i];
            velocity.x = - velocity.x;
            velocity.y = - velocity.y;
        } 
        else if(box->overlap(BoundingBox::TOP)) {
            std::cout << "collided top wall\n";
            int i = rand() % 8;
            velocity.x = m_x[i];
            velocity.y = m_y[i];
            velocity.x = dir.x * velocity.x;
        }
        else if(box->overlap(BoundingBox::BOTTOM)) {
            std::cout << "collided bottom wall\n";
            int i = rand() % 8;
            velocity.x = m_x[i];
            velocity.y = m_y[i];
            velocity.x = dir.x*velocity.x;
            velocity.y = - velocity.y;
        }
        else if(box->overlap(BoundingBox::LEFT)) {
            std::cout << "colllided left wall\n";
            int i = rand() % 8;
            velocity.x = m_x[i];
            velocity.y = m_y[i];
            velocity.y = dir.y * velocity.y;
        }
        else if(box->overlap(BoundingBox::RIGHT)) {
            std::cout << "collided right wall\n";
            int i = rand() % 8;
            velocity.x = m_x[i];
            velocity.y = m_y[i];
            velocity.x = - velocity.x;
            velocity.y = dir.y * velocity.y;
        }
        
    }

    void render(SDL_Renderer* gRenderer) override {
        fillCircle(gRenderer, coord.x + radius, coord.y + radius, radius, color);
    }

    ~Circle() {
        delete box;
    }
};

#endif