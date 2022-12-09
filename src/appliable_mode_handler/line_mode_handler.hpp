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

    void renderPreview() override {
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

    void apply() override {
        for (const auto& point: pointGenerator->generate(startingPoint, endPoint)) {
            grid.grid[point.y][point.x] = lineColor.color;
        }
    }
};