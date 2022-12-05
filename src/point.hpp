#pragma once

struct Point {
    size_t x;
    size_t y;

    Point() : x(0), y(0) {};
    Point(const size_t& x, const size_t& y) : x(x), y(y) {};
    Point(const Point& other){
        x = other.x;
        y = other.y;
    };

    Point& operator=(const Point& other) {
        x = other.x;
        y = other.y;
        return *this;
    };

    bool operator==(const Point& other) const {
        if (x == other.x && y == other.y)
            return true;
        return false;
    };

    bool operator<(const Point& other) {
        if (x < other.x )
            return true;
        else if (x == other.x && y == other.y)
            return true;

        return false;
    };

    // this could be moved in to std::hash<Point>::operator()
    size_t operator()(const Point& pointToHash) const noexcept {
        size_t hash = pointToHash.x + 10 * pointToHash.y;
        return hash;
    };

};

namespace std {
    template<> struct hash<Point>
    {
        std::size_t operator()(const Point& p) const noexcept
        {
            return p(p);
        }
    };
}