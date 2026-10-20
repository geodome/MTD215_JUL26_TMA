#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

struct Vector {
    int x, y;

    Vector operator+(const Vector& v) {
        return {x + v.x, y + v.y};
    }

    Vector operator-(const Vector& v) {
        return {x - v.x, y - v.y};
    }

    Vector& operator+=(const Vector& v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    Vector& operator-=(const Vector& v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    bool operator==(const Vector& v) {
        return x == v.x && y == v.y;
    }

    double magnitude() {
        return sqrt(x*x + y*y);
    }

    Vector direction() {
        return {x/abs(x), y/abs(y)};
    }
};

std::ostream& operator<<(std::ostream& out, const Vector& v) {
    out << "(" << v.x << ", " << v.y << ")";
    return out;
}

#endif 