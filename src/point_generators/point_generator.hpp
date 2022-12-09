#pragma once

#include "../point.hpp"
#include <vector>
#include <iostream>

class PointGenerator
{
public:
    virtual std::vector<Point> generate(const Point& p1, const Point& p2) = 0;
};