#pragma once

#include "point_generator.hpp"
#include "point_rotator.hpp"
#include "bresenham_point_generator.hpp"
#include <cmath>

class TrianglePointGenerator: public PointGenerator
{
    std::vector<Point> generate(const Point& p1, const Point& p2) override {
        Point p3 = PointRotator::rotate(p2, p1, PointRotator::d2r(120));
        Point p4 = PointRotator::rotate(p3, p1, PointRotator::d2r(120));

        std::unique_ptr<PointGenerator> pg = std::make_unique<BresenhamPointGenerator>(BresenhamPointGenerator());

        std::vector<Point> res;
        for (const auto& p: pg->generate(p2, p3)) {
            res.push_back(p);
        }
        for (const auto& p: pg->generate(p3, p4)) {
            res.push_back(p);
        }
        for (const auto& p: pg->generate(p2, p4)) {
            res.push_back(p);
        }

        return res;
    }
};