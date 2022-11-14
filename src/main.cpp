#include <GL/glut.h>
#include <iostream>
#include <array>

int gridSize;
std::array<std::array<int, 50>, 50> grid;

GLvoid initGrid() {
  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 25; j++) {
      grid[i][j] = 0;
    }
  }
}

GLvoid onMouseClick(int button, int state, int x, int y) {
  std::cout << x << ' ' << y << '\n';

  GLfloat gridWidth = GLfloat(glutGet(GLUT_WINDOW_WIDTH)) / gridSize;
  GLfloat gridHeight = GLfloat(glutGet(GLUT_WINDOW_HEIGHT)) / gridSize;

  std::cout << int(x / gridWidth) << ' ' << int(y / gridHeight) << "\n\n";

  if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
    grid[int(y / gridHeight)][int(x / gridWidth)] = 1;
  }
}

GLvoid drawGrids() {
  GLfloat gridWidth = GLfloat(glutGet(GLUT_WINDOW_WIDTH)) / gridSize;
  GLfloat gridHeight = GLfloat(glutGet(GLUT_WINDOW_HEIGHT)) / gridSize;

  for (int row = 0; row < gridSize; row++) {
    glPushMatrix();

    for (int column = 0; column < gridSize; column++) {
      if (grid[row][column] == 0){
        glColor3f(0.0, 0.0, 0.0);
      }
      else {
        glColor3f(1.0, 1.0, 1.0);
      }

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

GLvoid onDisplay() {
  std::cout << "Display func ran!\n";
  glClear(GL_COLOR_BUFFER_BIT);

  glPushMatrix();
  drawGrids();
  glPopMatrix();

  glFlush();
}

GLvoid onReshape(int w, int h) {
  std::cout << "Reshape func ran!\n";
  glViewport(0, 0, w, h);

  glutPostRedisplay();
}

void init(void) {
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0.0f, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0.0f);
  glClearColor(1.0, 1.0, 1.0, 1.0);

  gridSize = 50;
  initGrid();
}

int main(int argc, char* argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

  glutInitWindowSize(800, 800);
  glutInitWindowPosition(200, 50);
  glutCreateWindow("Flood Fill");

  glutDisplayFunc( onDisplay );
  glutReshapeFunc( onReshape );
  glutMouseFunc( onMouseClick );
  init();


  glutMainLoop();

  return 0;
}
