#pragma once

#include "appliable_mode_handler.hpp"
#include "../point_generators/rectangle_point_generator.hpp"

class RectangleModeHandler : public AppliableModeHandler
{
public:
    RectangleModeHandler(Grid& grid, Point startingPoint, Colors::Color lineColor) : 
        AppliableModeHandler(grid, startingPoint, lineColor)
        {
            pointGenerator = std::make_unique<RectanglePointGenerator>(RectanglePointGenerator());
        }
};