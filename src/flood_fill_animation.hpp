#pragma once

#include "grid.hpp"

class FloodFillAnimation
{
public:
    Grid* affectedGrid;
    bool isFinished = false;

    void forward() {
        return;
    }
};