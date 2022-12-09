#pragma once

#include "point_generator.hpp"
#include <cmath>

class MidpointPointGenerator: public PointGenerator
{
    std::vector<Point> generate(const Point& p1, const Point& p2) override {
        std::vector<Point> res;
        int x = abs(std::hypot(int64_t(p2.x) - int64_t(p1.x), int64_t(p2.y) - int64_t(p1.y)));
        int y = 0;
        int err = 0;

        while (x >= y){
            res.push_back({p1.x + x,  p1.y + y});
            res.push_back({p1.x + y,  p1.y + x});
            res.push_back({p1.x - y,  p1.y + x});
            res.push_back({p1.x - x,  p1.y + y});
            res.push_back({p1.x - x,  p1.y - y});
            res.push_back({p1.x - y,  p1.y - x});
            res.push_back({p1.x + y,  p1.y - x});
            res.push_back({p1.x + x,  p1.y - y});

            if (err <= 0){
                y += 1;
                err += 2*y + 1;
            }

            if (err > 0){
                x -= 1;
                err -= 2*x + 1;
            }
        }

        return res;
    }
};