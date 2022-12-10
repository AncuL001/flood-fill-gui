#pragma once

#include "appliable_mode_handler.hpp"
#include "../point_generators/triangle_point_generator.hpp"

class TriangleModeHandler : public AppliableModeHandler
{
public:
    TriangleModeHandler(Grid& grid, Point startingPoint, Colors::Color lineColor) : 
        AppliableModeHandler(grid, startingPoint, lineColor)
        {
            pointGenerator = std::make_unique<TrianglePointGenerator>(TrianglePointGenerator());
        }
};