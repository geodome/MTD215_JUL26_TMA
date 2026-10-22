#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "vector.h"
#include "definitions.h"

class BoundingBox {
    private:
    Vector* coord;
    int width, height;
    static Vector top_left, bottom_left, top_right;
    public:
    static const BoundingBox TOP, BOTTOM, LEFT, RIGHT;
    BoundingBox(Vector* coord,  int w, int h) {
        this->coord = coord;
        this->width = w;
        this->height = h;
    }

    bool overlap(const BoundingBox& other) {
        if(*this == other) return true;
        auto [x1, y1] = *coord;
        auto [x2, y2] = *other.coord;
        auto overlap1 = (x1 <= x2 && x2 <= x1 + width) || (x1 > x2 && x1 <= x2 + other.width);
        auto overlap2 = (y1 <= y2 && y2 <= y1 + height) || (y1 > y2 && y1 <= y2 + other.height);
        return overlap1 && overlap2;
    }

    bool operator==(const BoundingBox& other) {
        return *coord == *other.coord  &&  width == other.width && height == other.height;
    }
};

Vector BoundingBox::top_left = {0,0};
Vector BoundingBox::bottom_left = {0,HEIGHT};
Vector BoundingBox::top_right = {WIDTH,0};

const BoundingBox BoundingBox::TOP = BoundingBox(&BoundingBox::top_left, WIDTH, 1);
const BoundingBox BoundingBox::BOTTOM = BoundingBox(&BoundingBox::bottom_left, WIDTH, 1);
const BoundingBox BoundingBox::LEFT = BoundingBox(&BoundingBox::top_left, 1, HEIGHT);
const BoundingBox BoundingBox::RIGHT = BoundingBox(&BoundingBox::top_right, 1, HEIGHT);

#endif