#pragma once

#include <GL/glut.h>
#include <vector>
#include "helpers.hpp"

class Grid
{
    std::vector<std::vector<int>> grid;

public:
    Grid(int size) {
        for (int i = 0; i < size; i++) {
            grid.push_back(std::vector<int>(size, 0xFFFFFF));
        }
    }

    GLvoid onMouseClick(int x, int y, int windowWidth, int windowHeight) {
        GLfloat gridWidth = GLfloat(windowWidth) / grid[0].size();
        GLfloat gridHeight = GLfloat(windowHeight) / grid.size();

        grid[int(y / gridHeight)][int(x / gridWidth)] = 0x000000;
    }

    GLvoid render() {
        GLfloat gridWidth = GLfloat(glutGet(GLUT_WINDOW_WIDTH)) / grid[0].size();
        GLfloat gridHeight = GLfloat(glutGet(GLUT_WINDOW_HEIGHT)) / grid.size();

        for (int row = 0; row < grid.size(); row++) {
            glPushMatrix();

            for (int column = 0; column < grid[0].size(); column++) {
                colorHex(grid[row][column]);
                glBegin(GL_POLYGON);
                    glVertex2f(0, 0);
                    glVertex2f(0, gridHeight);
                    glVertex2f(gridWidth, gridHeight);
                    glVertex2f(gridWidth, 0);
                glEnd();

                glTranslatef(gridWidth, 0, 0);
            }

            glPopMatrix();
            glTranslatef(0, gridHeight, 0);
        }
    }
};