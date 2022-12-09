#include <GL/glut.h>
#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>
#include "grid.hpp"
#include "grid_block_mode_handler.hpp"
#include "flood_fill_animation.hpp"
#include "appliable_mode_handler/line_mode_handler.hpp"
#include "appliable_mode_handler/circle_mode_handler.hpp"
#include "appliable_mode_handler/rectangle_mode_handler.hpp"

#define BLOCK_MODE 0
#define FILL_MODE 1
#define LINE_MODE 2
#define CIRCLE_MODE 3
#define RECT_MODE 4
#define OPTION_RESET 0

Grid grid = Grid(50);
GridBlockModeHandler gridBlockModeHandler{grid};
FloodFillAnimation* currentAnimation = nullptr;
AppliableModeHandler* appliableModeHandler = nullptr;
Colors::Color selectedColor = Colors::black();

int currentMode = BLOCK_MODE;

GLvoid onMouseClick(int button, int state, int x, int y) {
  std::cout << "MouseClick func ran!\n";

  if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && !currentAnimation) {
    switch (currentMode) {
      case BLOCK_MODE:
          gridBlockModeHandler.onMouseClick(x, y, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), selectedColor);
        break;

      case FILL_MODE:
        currentAnimation = new FloodFillAnimation(&grid, 
                                                  grid.getCoordinate(x, y, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)), 
                                                  selectedColor);
        break;

      case LINE_MODE:
        if (appliableModeHandler == nullptr) {
          appliableModeHandler = new LineModeHandler(grid,
                                                    grid.getCoordinate(x, y, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)),
                                                    selectedColor
          );
        }
        else {
          appliableModeHandler->apply();
          delete appliableModeHandler;
          appliableModeHandler = nullptr;
        }
        break;
      
      case CIRCLE_MODE:
        if (appliableModeHandler == nullptr) {
          appliableModeHandler = new CircleModeHandler(grid,
                                                        grid.getCoordinate(x, y, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)),
                                                        selectedColor
          );
        }
        else {
          appliableModeHandler->apply();
          delete appliableModeHandler;
          appliableModeHandler = nullptr;
        }
        break;

      case RECT_MODE:
        if (appliableModeHandler == nullptr) {
          appliableModeHandler = new RectangleModeHandler(grid,
                                                          grid.getCoordinate(x, y, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)),
                                                          selectedColor
          );
        }
        else {
          appliableModeHandler->apply();
          delete appliableModeHandler;
          appliableModeHandler = nullptr;
        }
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
    glPushMatrix();
      grid.render();
    glPopMatrix();

    if (appliableModeHandler) {
      glPushMatrix();
        appliableModeHandler->renderPreview();
      glPopMatrix();
    }
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
    delete currentAnimation;
    currentAnimation = nullptr;

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
    delete currentAnimation;
    currentAnimation = nullptr;

    grid = Grid(size);
  }

  glutPostRedisplay();
}

GLvoid onPassiveMotion(int x, int y) {
  if (appliableModeHandler) {
    appliableModeHandler->endPoint = grid.getCoordinate(x, y, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
  }
  glutPostRedisplay();
}

void initMenu() {
  int colorSubmenuId = glutCreateMenu( onColorSubmenuItemSelected );
  for (int i = 0; i < Colors::colorList.size(); i++) {
    glutAddMenuEntry(Colors::colorList[i].name.c_str(), i);
  }

  int modeSubmenuId = glutCreateMenu( onModeSubmenuItemSelected );
  glutAddMenuEntry("Block Mode", BLOCK_MODE);
  glutAddMenuEntry("Fill Mode", FILL_MODE);
  glutAddMenuEntry("Line Mode", LINE_MODE);
  glutAddMenuEntry("Circle Mode", CIRCLE_MODE);
  glutAddMenuEntry("Rectangle Mode", RECT_MODE);

  int resizeSubmenuId = glutCreateMenu( onResizeSubmenuItemSelected );
  std::vector<int> sizeOptions = {10, 15, 20, 25, 30, 50, 70, 100};
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
  glutPassiveMotionFunc( onPassiveMotion );
  glutIdleFunc( onIdle );
  init();


  glutMainLoop();

  return 0;
}
