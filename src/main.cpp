#include <GL/glut.h>
#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>
#include "grid.hpp"
#include "grid_block_mode_handler.hpp"
#include "flood_fill_animation.hpp"

#define BLOCK_MODE 0
#define FILL_MODE 1
#define OPTION_RESET 0

Grid grid = Grid(50);
GridBlockModeHandler gridBlockModeHandler{grid};
FloodFillAnimation* currentAnimation = nullptr;
Colors::Color selectedColor = Colors::black();

int currentMode = BLOCK_MODE;

GLvoid onMouseClick(int button, int state, int x, int y) {
  std::cout << "MouseClick func ran!\n";

  if (!currentAnimation) {
    switch (currentMode) {
      case BLOCK_MODE:
        if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
          gridBlockModeHandler.onMouseClick(x, y, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), selectedColor);
        }
        break;

      case FILL_MODE:
        currentAnimation = new FloodFillAnimation(&grid, 
                                                  grid.getCoordinate(x, y, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)), 
                                                  selectedColor);
        break;

      default:
        break;
    }
  }

  glutPostRedisplay();
}

GLvoid onDisplay() {
  std::cout << "Display func ran!\n";

  if (currentAnimation) {
    currentAnimation->forward();

    if (currentAnimation->isFinished) {
      delete currentAnimation;
      currentAnimation = nullptr;
    }
  }

  glClear(GL_COLOR_BUFFER_BIT);

  glPushMatrix();
  grid.render();
  glPopMatrix();

  glFlush();
}

GLvoid onIdle() {
  if (currentAnimation) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    glutPostRedisplay();
  }
}

GLvoid onReshape(int w, int h) {
  std::cout << "Reshape func ran!\n";
  glViewport(0, 0, w, h);
}

GLvoid onMenuItemSelected(int option) {
  if (option == OPTION_RESET) {
    grid = Grid(grid.grid.size());
  }

  glutPostRedisplay();
}

GLvoid onColorSubmenuItemSelected(int colorIndex) {
  selectedColor = Colors::colorList[colorIndex];
}

GLvoid onModeSubmenuItemSelected(int mode) {
  std::cout << "Selected mode: " << mode << '\n';

  currentMode = mode;
}

GLvoid onResizeSubmenuItemSelected(int size) {
  if (size == 0) {}

  else {
    grid = Grid(size);
  }
}

void initMenu() {
  int colorSubmenuId = glutCreateMenu( onColorSubmenuItemSelected );
  for (int i = 0; i < Colors::colorList.size(); i++) {
    glutAddMenuEntry(Colors::colorList[i].name.c_str(), i);
  }

  int modeSubmenuId = glutCreateMenu( onModeSubmenuItemSelected );
  glutAddMenuEntry("Block Mode", BLOCK_MODE);
  glutAddMenuEntry("Fill Mode", FILL_MODE);

  int resizeSubmenuId = glutCreateMenu( onResizeSubmenuItemSelected );
  std::vector<int> sizeOptions = {10, 30, 50, 70, 100};
  for (const int& sizeOption: sizeOptions) {
    std::stringstream temp;
    temp << sizeOption << "x" << sizeOption;
    glutAddMenuEntry(temp.str().c_str(), sizeOption);
  }

  glutCreateMenu( onMenuItemSelected );
  glutAddSubMenu("Select Mode", modeSubmenuId);
  glutAddSubMenu("Select Color", colorSubmenuId);
  glutAddSubMenu("Resize Canvas", resizeSubmenuId);
  glutAddMenuEntry("Reset", OPTION_RESET);
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
  glutIdleFunc( onIdle );
  init();


  glutMainLoop();

  return 0;
}
