#pragma once

#include <GL/glut.h>

void colorHex(GLint hex) {
  glColor3f(
    (GLfloat)(hex & 0xff0000) / 0xff0000,
    (GLfloat)(hex & 0x00ff00) / 0x00ff00,
    (GLfloat)(hex & 0x0000ff) / 0x0000ff
  );
}