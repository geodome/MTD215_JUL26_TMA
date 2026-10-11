#ifndef WIDGETS_H
#define WIDGETS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

#include "guiobject.h"
#include "formula.h"

class TextDisplay: public GUIObject {
    private:
    std::string text = "";
    std::string previous = text;
    SDL_Texture* textTexture;
    SDL_Rect dest;
    bool decimal = false;
    bool modulus = false;

    public:
    TextDisplay(std::string t = ""): GUIObject(30) {
        text = t;
    }

    std::string read() {
        return text;
    }

    void replace(const std::string& t) {
        text = t;
    }

    void append(const std::string& t) {
        text += t;
    }

    void render(SDL_Renderer* gRenderer, TTF_Font* fonts[], size_t size, int row, int col, int hspan, int vspan) override {
        if(previous != text) {
            auto final = text + " ";
            auto textSurface = TTF_RenderText_Blended(fonts[LARGE], final.c_str(), {0xff, 0xff, 0xff, 0xff});
            textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
            dest = {col*UNIT + hspan*UNIT - textSurface->w, row*UNIT + (vspan*UNIT - textSurface->h)/2, textSurface->w, textSurface->h};
            SDL_FreeSurface(textSurface);
            previous = text;
        }
        SDL_RenderCopy(gRenderer, textTexture, nullptr, &dest);
        SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderDrawLine(gRenderer, col*UNIT, (row + vspan)*UNIT-10, (col + hspan)*UNIT, (row + vspan)*UNIT-10);
    } 

};

class Button: public GUIObject{
    std::string lbl;
    bool toggle_on = false;
    SDL_Texture* textTexture = nullptr;
    SDL_Rect dest;
    SDL_Color color_on, color_off, color_text;

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

    public:
    Button(const char* l, const SDL_Color& text_color, const SDL_Color& on_color, const SDL_Color& off_color): GUIObject(10) {
        lbl = l;
        color_on = on_color;
        color_off = off_color;
        color_text = text_color;
    }

    std::string label() {
        return lbl;
    }

    void toggle() {
        toggle_on = !toggle_on;
    }

    void render(SDL_Renderer* gRenderer, TTF_Font* fonts[], size_t size, int row, int col, int hspan, int vspan) override {
        int x = col*UNIT;
        int y = row*UNIT;
        int x0 = x + (hspan*UNIT)/2;
        int y0 = y + (vspan*UNIT)/2;
        int r = UNIT / 2 - 5;
        if(toggle_on)
            fillCircle(gRenderer, x0, y0, r, color_on);
        else 
            fillCircle(gRenderer, x0, y0, r, color_off);
        if(textTexture == nullptr) {
            auto textSurface = TTF_RenderUTF8_Blended(fonts[MEDIUM], lbl.c_str(), color_text);
            textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
            dest = {x0-textSurface->w/2,y0 - textSurface->h/2,textSurface->w, textSurface->h};
            SDL_FreeSurface(textSurface);
        }
        SDL_RenderCopy(gRenderer, textTexture, nullptr, &dest);
    }
    virtual ~Button() {
        SDL_DestroyTexture(textTexture);
    }
};

class BackspaceButton: public Button {
    TextDisplay* txt;
    Formula* formula;
    public:
    BackspaceButton(TextDisplay* t, Formula* f): Button("«" , WHITE, ORANGE, GREY) {
        txt = t;
        formula = f;
    }
    void on_mousedown(const SDL_MouseButtonEvent& e) override {
        if(formula->backspace()) txt->replace(formula->to_string());
        toggle();
    }
    void on_mouseup(const SDL_MouseButtonEvent& e) override {
        toggle();
    }
};

class AllClearButton: public Button {
    TextDisplay* txt;
    Formula* formula;
    public:
    AllClearButton(TextDisplay* t, Formula* f): Button("AC", WHITE, ORANGE, GREY) {
        txt = t;
        formula = f;
    }
    void on_mousedown(const SDL_MouseButtonEvent& e) override {
        if(formula->all_clear()) txt->replace("");
        toggle();
    }
    void on_mouseup(const SDL_MouseButtonEvent& e) override {
        toggle();
    }
};

class ModuloButton: public Button {
    TextDisplay* txt;
    Formula* formula;
    public:
    ModuloButton(TextDisplay* t, Formula* f): Button("%", WHITE, ORANGE, GREY) {
        txt = t;
        formula = f;
    }
    void on_mousedown(const SDL_MouseButtonEvent& e) override {
        if(formula->append('%')) txt->replace(formula->to_string());
        toggle();
    }
    void on_mouseup(const SDL_MouseButtonEvent& e) override {
        toggle();
    }
};

class DivButton: public Button {
    TextDisplay* txt;
    Formula* formula;
    public:
    DivButton(TextDisplay* t, Formula* f): Button("÷", WHITE, GREY, ORANGE) {
        txt = t;
        formula = f;
    }
    void on_mousedown(const SDL_MouseButtonEvent& e) override {
        if(formula->append('/')) txt->replace(formula->to_string());
        toggle();
    }
    void on_mouseup(const SDL_MouseButtonEvent& e) override {
        toggle();
    }
};

class MultiButton: public Button {
    TextDisplay* txt;
    Formula* formula;
    public:
    MultiButton(TextDisplay* t, Formula* f): Button("x", WHITE, GREY, ORANGE) {
        txt = t;
        formula = f;
    }
    void on_mousedown(const SDL_MouseButtonEvent& e) override {
        if(formula->append('x')) txt->replace(formula->to_string());
        toggle();
    }
    void on_mouseup(const SDL_MouseButtonEvent& e) override {
        toggle();
    }

};

class SubButton: public Button {
    TextDisplay* txt;
    Formula* formula;
    public:
    SubButton(TextDisplay* t, Formula* f): Button("-", WHITE, GREY, ORANGE) {
        txt = t;
        formula = f;
    }
    void on_mousedown(const SDL_MouseButtonEvent& e) override {
        if(formula->append('-')) txt->replace(formula->to_string());
        toggle();
    }
    void on_mouseup(const SDL_MouseButtonEvent& e) override {
        toggle();
    }
};

class AddButton: public Button {
    TextDisplay* txt;
    Formula* formula;
    public:
    AddButton(TextDisplay* t, Formula* f): Button("+", WHITE, GREY, ORANGE) {
        txt = t;
        formula = f;
    }
    void on_mousedown(const SDL_MouseButtonEvent& e) override {
        if(formula->append('+')) txt->replace(formula->to_string());
        toggle();
    }
    void on_mouseup(const SDL_MouseButtonEvent& e) override {
        toggle();
    }

};

class EvalButton: public Button {
    TextDisplay* txt;
    Formula* formula;
    public:
    EvalButton(TextDisplay* t, Formula* f): Button("=", WHITE, GREY, ORANGE) {
        txt = t;
        formula = f;
    }
    void on_mousedown(const SDL_MouseButtonEvent& e) override {
        if(formula->evaluate()) txt->replace(formula->to_string());
        toggle();
    }
    void on_mouseup(const SDL_MouseButtonEvent& e) override {
        toggle();
    }

};

class DigitButton: public Button {
    TextDisplay* txt;
    Formula* formula;
    char c;
    public:
    DigitButton(int d, TextDisplay* t, Formula* f): Button(std::to_string(d).c_str(), WHITE, ORANGE, GREY) {
        txt = t;
        formula = f;
        c = 48 + d;
    };
    void on_mousedown(const SDL_MouseButtonEvent& e) override {
        if(formula->append(c)) txt->replace(formula->to_string());
        toggle();
    }
    void on_mouseup(const SDL_MouseButtonEvent& e) override {
        toggle();
    }
    
};

class DecButton: public Button {
    TextDisplay* txt;
    Formula* formula;
    public:
    DecButton(TextDisplay* t, Formula* f): Button(".", WHITE, ORANGE, GREY) {
        txt = t;
        formula = f;
    }
    void on_mousedown(const SDL_MouseButtonEvent& e) override {
        if(formula->append('.')) txt->replace(formula->to_string());
        toggle();
    }
    void on_mouseup(const SDL_MouseButtonEvent& e) override {
        toggle();
    }

};

class SignButton: public Button {
    TextDisplay* txt;
    Formula* formula;
    public:
    SignButton(TextDisplay* t, Formula* f): Button("±", WHITE, ORANGE, GREY) {
        txt = t;
        formula = f;
    }
    void on_mousedown(const SDL_MouseButtonEvent& e) override {
        if(formula->invert_sign()) txt->replace(formula->to_string());
        toggle();
    }
    void on_mouseup(const SDL_MouseButtonEvent& e) override {
        toggle();
    }

};

#endif 