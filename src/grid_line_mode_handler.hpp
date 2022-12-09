#pragma once

#include <vector>
#include <memory>
#include <math.h>
#include "grid.hpp"
#include "point.hpp"
#include "colors.hpp"
#include "point_generators/bresenham_point_generator.hpp"

class GridLineModeHandler
{
public:
    Grid& grid;
    Point startingPoint;
    Point endPoint;
    Colors::Color lineColor;
    std::unique_ptr<PointGenerator> pointGenerator = std::make_unique<BresenhamPointGenerator>(BresenhamPointGenerator());

    GridLineModeHandler(Grid& grid, Point startingPoint, Colors::Color lineColor) : 
        grid(grid),
        startingPoint(startingPoint),
        endPoint(startingPoint),
        lineColor(lineColor)
        {}

    void render() {
        GLfloat gridWidth = GLfloat(glutGet(GLUT_WINDOW_WIDTH)) / grid.grid[0].size();
        GLfloat gridHeight = GLfloat(glutGet(GLUT_WINDOW_HEIGHT)) / grid.grid.size();

        for (const auto& point: pointGenerator->generate(startingPoint, endPoint)) {
            GLfloat startX = point.x * gridWidth;
            GLfloat startY = point.y * gridHeight;

            colorHex(lineColor.color);
            glBegin(GL_POLYGON);
                glVertex2f(startX, startY);
                glVertex2f(startX, startY + gridHeight);
                glVertex2f(startX + gridWidth, startY + gridHeight);
                glVertex2f(startX + gridWidth, startY);
            glEnd();
        }
    }

    void apply() {
        for (const auto& point: pointGenerator->generate(startingPoint, endPoint)) {
            grid.grid[point.y][point.x] = lineColor.color;
        }
    }
};