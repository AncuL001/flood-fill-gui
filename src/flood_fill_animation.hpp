#pragma once

#include "grid.hpp"
#include "point.hpp"
#include <queue>
#include <array>

class FloodFillAnimation
{
public:
    Grid* affectedGrid;
    bool isFinished = false;
    int newColor;
    int oldColor;
    std::queue<Point> tilesToFill;

    FloodFillAnimation(Grid* affectedGrid, Point startingPoint, int mewColor) : 
        affectedGrid(affectedGrid),
        newColor(newColor) 
    {
        tilesToFill.push(startingPoint);
        oldColor = affectedGrid->at(startingPoint);
    }

    void forward() {
        const int LEFT_BORDER = 0;
        const int UPPER_BORDER = 0;
        const int LOWER_BORDER = affectedGrid->grid.size() - 1;
        const int RIGHT_BORDER = affectedGrid->grid[0].size() - 1;

        std::queue<Point> temp;

        while (!tilesToFill.empty()) {
            auto t = tilesToFill.front();
            tilesToFill.pop();
            affectedGrid->grid[t.y][t.x] = newColor;

            if (t.y != UPPER_BORDER && affectedGrid->at({t.x, t.y - 1}) == oldColor)
                temp.push({t.x, t.y - 1});

            if (t.y != LOWER_BORDER && affectedGrid->at({t.x, t.y + 1}) == oldColor)
                temp.push({t.x, t.y + 1});

            if (t.x != LEFT_BORDER && affectedGrid->at({t.x - 1, t.y}) == oldColor)
                temp.push({t.x - 1, t.y});

            if (t.x != RIGHT_BORDER && affectedGrid->at({t.x + 1, t.y}) == oldColor)
                temp.push({t.x + 1, t.y});
        }

        tilesToFill = temp;

        if (tilesToFill.empty()) {
            isFinished = true;
        }

    }
};