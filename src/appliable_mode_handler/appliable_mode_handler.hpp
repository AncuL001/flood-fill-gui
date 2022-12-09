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

    AppliableModeHandler(Grid& grid, Point startingPoint, Colors::Color lineColor) : 
        grid(grid),
        startingPoint(startingPoint),
        endPoint(startingPoint),
        lineColor(lineColor)
        {}

public:
    Point endPoint;

    void renderPreview() {
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
    };

    virtual void apply() {
        for (const auto& point: pointGenerator->generate(startingPoint, endPoint)) {
            grid.grid[point.y][point.x] = lineColor.color;
        }
    };
};
