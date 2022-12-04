#pragma once

#include "grid.hpp"
#include "colors.hpp"


class GridBlockModeHandler
{
  Grid& grid;

public:
  GridBlockModeHandler(Grid& grid) : grid(grid) {};

  GLvoid onMouseClick(int x, int y, int windowWidth, int windowHeight, Colors::Color selectedColor) {
    auto coord = grid.getCoordinate(x, y, windowWidth, windowHeight);

    grid.grid[coord.y][coord.x] = selectedColor.color;
  }
};