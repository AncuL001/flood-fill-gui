#pragma once

#include "appliable_mode_handler.hpp"
#include "../point_generators/midpoint_point_generator.hpp"

class CircleModeHandler : public AppliableModeHandler
{
public:
    CircleModeHandler(Grid& grid, Point startingPoint, Colors::Color lineColor) : 
        AppliableModeHandler(grid, startingPoint, lineColor)
        {
            pointGenerator = std::make_unique<MidpointPointGenerator>(MidpointPointGenerator());
        }
};