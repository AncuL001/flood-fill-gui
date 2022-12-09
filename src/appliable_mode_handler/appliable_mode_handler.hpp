#pragma once

#include <vector>
#include <memory>
#include <math.h>
#include "../grid.hpp"
#include "../point.hpp"
#include "../colors.hpp"
#include "../point_generators/point_generator.hpp"

class AppliableModeHandler
{
protected:
    Grid& grid;
    Point startingPoint;
    Colors::Color lineColor;

    // Apparently this variable gets destroyed on class constructor call???
    std::unique_ptr<PointGenerator> pointGenerator;

public:
    Point endPoint;

    AppliableModeHandler(Grid& grid, Point startingPoint, Colors::Color lineColor) : 
        grid(grid),
        startingPoint(startingPoint),
        endPoint(startingPoint),
        lineColor(lineColor)
        {}

    virtual void renderPreview() = 0;
    virtual void apply() = 0;
};
