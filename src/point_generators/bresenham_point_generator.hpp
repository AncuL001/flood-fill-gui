#pragma once

#include "point_generator.hpp"

class BresenhamPointGenerator: public PointGenerator
{
    std::vector<Point> generate(const Point& p1, const Point& p2) override {
        int64_t dx = abs(int64_t(p2.x - p1.x));
        int64_t dy = abs(int64_t(p2.y - p1.y));

        if (dx > dy) return bresenhamInnerImpl(p1.x, p1.y, p2.x, p2.y, dx, dy, 0);
        return bresenhamInnerImpl(p1.y, p1.x, p2.y, p2.x, dy, dx, 1);
    }

private:
    std::vector<Point> bresenhamInnerImpl(size_t x1, size_t y1, size_t x2, size_t y2, int64_t dx, int64_t dy, int decide) {
        std::vector<Point> res;

        int64_t pk = 2 * dy - dx;
        for (int64_t i = 0; i <= dx; i++) {
            if (decide == 0) res.push_back({x1, y1});
            else res.push_back({y1, x1});

            x1 < x2 ? x1++ : x1--;
            if (pk < 0) {
                if (decide == 0) pk = pk + 2 * dy;
                else pk = pk + 2 * dy;
            }
            else {
                y1 < y2 ? y1++ : y1--;
                pk = pk + 2 * dy - 2 * dx;
            }
        }
        return res;
    }
};