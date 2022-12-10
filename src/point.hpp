#pragma once

struct Point {
    int64_t x;
    int64_t y;

    Point() : x(0), y(0) {};
    Point(const int64_t& x, const int64_t& y) : x(x), y(y) {};
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
    int64_t operator()(const Point& pointToHash) const noexcept {
        int64_t hash = pointToHash.x + 10 * pointToHash.y;
        return hash;
    };

};

namespace std {
    template<> struct hash<Point>
    {
        std::int64_t operator()(const Point& p) const noexcept
        {
            return p(p);
        }
    };
}