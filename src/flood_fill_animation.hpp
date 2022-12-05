#pragma once

#include "grid.hpp"
#include "point.hpp"
#include "colors.hpp"
#include <queue>
#include <array>
#include <unordered_set>

class FloodFillAnimation
{
public:
    Grid* affectedGrid;
    bool isFinished = false;
    Colors::Color newColor;
    int oldColor;
    std::queue<Point> tilesToFill;

    FloodFillAnimation(Grid* affectedGrid, Point startingPoint, Colors::Color newColor) : 
        affectedGrid(affectedGrid),
        newColor(newColor) 
    {
        tilesToFill.push(startingPoint);
        oldColor = affectedGrid->at(startingPoint);
    }

    void forward() {
        const size_t LEFT_BORDER = 0;
        const size_t UPPER_BORDER = 0;
        const size_t LOWER_BORDER = affectedGrid->grid.size() - 1;
        const size_t RIGHT_BORDER = affectedGrid->grid[0].size() - 1;

        std::unordered_set<Point> temp;
        while (!tilesToFill.empty()) {
            auto t = tilesToFill.front();
            tilesToFill.pop();
            affectedGrid->grid[t.y][t.x] = newColor.color;

            if (t.y != UPPER_BORDER && affectedGrid->at({t.x, t.y - 1}) == oldColor)
                temp.insert({t.x, t.y - 1});

            if (t.y != LOWER_BORDER && affectedGrid->at({t.x, t.y + 1}) == oldColor)
                temp.insert({t.x, t.y + 1});

            if (t.x != LEFT_BORDER && affectedGrid->at({t.x - 1, t.y}) == oldColor)
                temp.insert({t.x - 1, t.y});

            if (t.x != RIGHT_BORDER && affectedGrid->at({t.x + 1, t.y}) == oldColor)
                temp.insert({t.x + 1, t.y});
        }

        for (const auto& item: temp) {
            tilesToFill.push(item);
        }

        if (tilesToFill.empty()) {
            isFinished = true;
        }

    }
};