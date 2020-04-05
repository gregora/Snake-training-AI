#ifndef SIMPLE2D
#define SIMPLE2D

#include "GL/freeglut.h"
#include "GL/gl.h"
#include <cmath>
#include <iostream>
#include <string>

//function start has to be called when opening a window
int start(int argc, char **argv, int width, int height, std::string title);

///functions required in main.cpp
void render(double delta); //inside this function you can rendering functios
void keyboardInput(unsigned char key, int x, int y); //keyboard input

//functions that can be called from render() function in main.cpp
void rerender(); // rerender the canvas

void setColor(double r, double g, double b);
void setBackgroundColor(double r, double g, double b);

void line(double x1, double y1, double x2, double y2, double width);
void triangle(double x1, double y1, double x2, double y2, double x3, double y3);
void rectangle(double x1, double y1, double x2, double y2);
void polygon(int vertices_num, double coords[]);
void circle(double x, double y, double r);

void text(double x, double y, void* font, std::string ta);

//internal functions
void renderAll();
void onResize(int w, int h);

#endif
