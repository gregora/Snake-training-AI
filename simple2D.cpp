#include "simple2D.h"

int window_width;
int window_height;

int lastTime;

double background[] = {1, 1, 1};

void setColor(double r, double g, double b){
  glColor3f(r, g, b);
}

void setBackgroundColor(double r, double g, double b){

  background[0] = r;
  background[1] = g;
  background[2] = b;

}

void line(double x1, double y1, double x2, double y2, double width){

  glLineWidth(width);
  glBegin(GL_LINES);
    glVertex3f(2 * x1 / window_width, 2 * y1 / window_height, 0);
    glVertex3f(2 * x2 / window_width, 2 * y2 / window_height, 0);
  glEnd();

}

void triangle(double x1, double y1, double x2, double y2, double x3, double y3){

  glBegin(GL_TRIANGLES);


          glVertex3f(2 * x1 / window_width, 2 * y1 / window_height, 0);
          glVertex3f(2 * x2 / window_width, 2 * y2 / window_height, 0);
          glVertex3f(2 * x3 / window_width, 2 * y3 / window_height, 0);


  glEnd();

}

void rectangle(double x1, double y1, double x2, double y2){

  glBegin(GL_POLYGON);

    glVertex3f(2 * x1 / window_width, 2 * y1 / window_height, 0.0);
    glVertex3f(2 * x2 / window_width, 2 * y1 / window_height, 0.0);
    glVertex3f(2 * x2 / window_width, 2 * y2 / window_height, 0.0);
    glVertex3f(2 * x1 / window_width, 2 * y2 / window_height, 0.0);

  glEnd();

}

void polygon(int vertices_num, double coords[]){

  glBegin(GL_POLYGON);

  for(int i = 0; i < 2*vertices_num; i+=2){
    glVertex3f(2 * coords[i] / window_width, 2 * coords[i + 1] / window_height, 0.0);
  }

  glEnd();

}

void circle(double x, double y, double r){

  int segnum = (int) sqrt(r)*4;
  double step = 2*3.14159 / segnum;

  for(int i = 0; i < segnum; i++){
    //draw a triangle
    triangle(x, y, x + cos(step * i)*r, y + sin(step * i)*r, x + cos(step * (i + 1))*r, y + sin(step * (i + 1))*r);
  }

}

void text(double x, double y, void* font, std::string ta){

  int len = (int) ta.length();

  unsigned char str[len];
  int count = 0;

  for(char& c : ta){
    str[count] = c;
    count += 1;
  }

  glRasterPos2f(2 * x / window_width, 2 * y / window_height);
  glutBitmapString(font, str);

}

void rerender(){

  glutPostRedisplay();
  glutMainLoopEvent();

}

void onResize(int w, int h){

  window_width = (double) w;
  window_height = (double) h;

  glViewport(0,0,w,h);

}

void renderAll(){

  // clear the canvas
  glClearColor(background[0], background[1], background[2], 0);
  glClear(GL_COLOR_BUFFER_BIT);

  int currentTime = glutGet(GLUT_ELAPSED_TIME);
  double delta = (double) (currentTime - lastTime) / 1000;
  lastTime = currentTime;

  render(delta);

  // flush
  glFlush();

}

int start(int argc, char **argv, int width, int height, std::string title){

    window_width = width;
    window_height = height;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(200, 200);

    glutCreateWindow(title.c_str());

    glutKeyboardFunc(keyboardInput);

    lastTime = glutGet(GLUT_ELAPSED_TIME);

    glutDisplayFunc(renderAll);
    glutReshapeFunc(onResize);

    return 0;

}
