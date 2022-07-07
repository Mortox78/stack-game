#ifndef _MY_OPENGL_FUNC_H_
#define _MY_OPENGL_FUNC_H_

#define PI 3.14
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define SCALE  250

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <math.h>

enum
{
    RED   = 1,
    GREEN = 2,
    BLUE  = 3
};


void draw_polygon(int edges, bool& showEdges);

void change_shape_color(GLFWwindow* window);


#endif