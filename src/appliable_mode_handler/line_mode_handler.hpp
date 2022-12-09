#pragma once

#include "appliable_mode_handler.hpp"
#include "../point_generators/bresenham_point_generator.hpp"

class LineModeHandler : public AppliableModeHandler
{
public:
    LineModeHandler(Grid& grid, Point startingPoint, Colors::Color lineColor) : 
        AppliableModeHandler(grid, startingPoint, lineColor)
        {
            pointGenerator = std::make_unique<BresenhamPointGenerator>(BresenhamPointGenerator());
        }
};