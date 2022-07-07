#ifndef _PRIMITIVES_H_
#define _PRIMITIVES_H_

#include "../../my_opengl_func.h"

enum
{
    CIRCLE,
    POINT,
    LINE,
    TRIANGLE,
    QUADRILATERAL,
    PENTAGON,
    HEXAGON,
    HEPTAGON,
    OCTOGON,
    ENNEAGON,
};

struct displayM
{
    int select_shape;
    int color_back_ground;
    int color_shape;
    bool showEdges  = false;
    bool keyPressed = false;
    float x = 0;
    float y = 0;

};


void draw_point();

void draw_line();

void draw_triangle(bool& showEdges);

void draw_quad(bool& showEdges);

void draw_pentagon(bool& showEdges);

void draw_hexagon(bool& showEdges);

void draw_heptagon(bool& showEdges);

void draw_octogon(bool& showEdges);

void draw_enneagon(bool& showEdges);

void draw_circle(bool& showEdges);

void input(GLFWwindow* window, displayM& displayM);

void display(displayM& displayM);

void draw_selected_shape(displayM& displayM);

void select_shape(GLFWwindow* window, displayM& displayM);

void select_color_background(GLFWwindow* window, displayM& displayM);

void show_edges(GLFWwindow* window, displayM& displayM);

void move_shape(GLFWwindow* window, displayM& displayM);

void display_color_background(displayM& displayM);


#endif