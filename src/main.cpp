#include <GL/glut.h>
#include <iostream>
#include "grid.hpp"

#define BLOCK_MODE 0
#define FILL_MODE 1

Grid grid = Grid(50);

int currentMode = BLOCK_MODE;

GLvoid onMouseClick(int button, int state, int x, int y) {
  std::cout << "MouseClick func ran!\n";
  if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
    grid.onMouseClick(x, y, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
  }

  glutPostRedisplay();
}

GLvoid onDisplay() {
  std::cout << "Display func ran!\n";
  glClear(GL_COLOR_BUFFER_BIT);

  glPushMatrix();
  grid.render();
  glPopMatrix();

  glFlush();
}

GLvoid onReshape(int w, int h) {
  std::cout << "Reshape func ran!\n";
  glViewport(0, 0, w, h);
}

GLvoid onMenuItemSelected(int mode) {
  std::cout << "Selected mode: " << mode << '\n';

  currentMode = mode;
}

void initMenu() {
  int temp = glutCreateMenu( onMenuItemSelected );
  glutAddMenuEntry("Block Mode", BLOCK_MODE);
  glutAddMenuEntry("Fill Mode", FILL_MODE);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void init(void) {
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0.0f, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0.0f);
  glClearColor(1.0, 1.0, 1.0, 1.0);
}

int main(int argc, char* argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

  glutInitWindowSize(800, 800);
  glutInitWindowPosition(200, 50);
  glutCreateWindow("Flood Fill");

  initMenu();

  glutDisplayFunc( onDisplay );
  glutReshapeFunc( onReshape );
  glutMouseFunc( onMouseClick );
  init();


  glutMainLoop();

  return 0;
}
