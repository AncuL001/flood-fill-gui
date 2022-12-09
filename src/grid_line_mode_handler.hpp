#pragma once

#include <vector>
#include <math.h>
#include "grid.hpp"
#include "point.hpp"
#include "colors.hpp"

class GridLineModeHandler
{
public:
    Grid& grid;
    Point startingPoint;
    Point endPoint;
    Colors::Color lineColor;

    GridLineModeHandler(Grid& grid, Point startingPoint, Colors::Color lineColor) : 
        grid(grid),
        startingPoint(startingPoint),
        endPoint(startingPoint),
        lineColor(lineColor)
        {}

    void render() {
        GLfloat gridWidth = GLfloat(glutGet(GLUT_WINDOW_WIDTH)) / grid.grid[0].size();
        GLfloat gridHeight = GLfloat(glutGet(GLUT_WINDOW_HEIGHT)) / grid.grid.size();

        for (const auto& point: bresenhamGeneratePoints(startingPoint, endPoint)) {
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
        for (const auto& point: bresenhamGeneratePoints(startingPoint, endPoint)) {
            grid.grid[point.y][point.x] = lineColor.color;
        }
    }

    static std::vector<Point> bresenhamGeneratePoints(Point p1, Point p2) {
        int64_t dx = abs(int64_t(p2.x - p1.x));
        int64_t dy = abs(int64_t(p2.y - p1.y));

        if (dx > dy) return bresenhamInnerImpl(p1.x, p1.y, p2.x, p2.y, dx, dy, 0);
        return bresenhamInnerImpl(p1.y, p1.x, p2.y, p2.x, dy, dx, 1);
    }

private:
    static std::vector<Point> bresenhamInnerImpl(size_t x1, size_t y1, size_t x2, size_t y2, int64_t dx, int64_t dy, int decide) {
        std::vector<Point> res;

        int64_t pk = 2 * dy - dx;
        for (int64_t i = 0; i <= dx; i++) {
            if (decide == 0) res.push_back({x1, y1});
            else res.push_back({y1, x1});

            x1 < x2 ? x1++ : x1--;
            if (pk < 0) {
                if (decide == 0) pk = pk + 2 * dy;
                else pk = pk + 2 * dy;
            }
            else {
                y1 < y2 ? y1++ : y1--;
                pk = pk + 2 * dy - 2 * dx;
            }
        }
        return res;
    }
};