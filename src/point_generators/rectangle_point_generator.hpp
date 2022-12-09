#pragma once

#include "point_generator.hpp"

class RectanglePointGenerator: public PointGenerator
{
    std::vector<Point> generate(const Point& p1, const Point& p2) override {
        Point topLeft = {p1.x < p2.x ? p1.x : p2.x, p1.y < p2.y ? p1.y : p2.y};
        Point bottomRight = {p1.x > p2.x ? p1.x : p2.x, p1.y > p2.y ? p1.y : p2.y};

        return innerImpl(topLeft, bottomRight);
    }

    std::vector<Point> innerImpl(const Point& topLeft, const Point& bottomRight) {
        std::vector<Point> res;

        size_t currentX = topLeft.x;
        while (currentX <= bottomRight.x) {
            res.push_back({currentX, topLeft.y});
            res.push_back({currentX, bottomRight.y});

            currentX++;
        }

        size_t currentY = topLeft.y;
        while (currentY <= bottomRight.y) {
            res.push_back({topLeft.x, currentY});
            res.push_back({bottomRight.x, currentY});

            currentY++;
        }
        return res;
    }
};