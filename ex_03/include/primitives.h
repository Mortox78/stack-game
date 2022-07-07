#ifndef _PRIMITIVES_H_
#define _PRIMITIVES_H_

#include "../../my_opengl_func.h"


enum
{
    SPHERE = 1,
    CUBE   = 2
};

struct displayM
{
    int select_shape = 0;

    bool keyPressed = false;
    bool showEdges  = false;
    bool showReferential = false;

    bool rotateX     = false;
    bool keyXPressed = false;

    bool rotateY     = false;
    bool keyYPressed = false;

    bool rotateZ     = false;
    bool keyZPressed = false;

    bool init        = false;
    float rotmat[16];
    float scale     = 1;
};

void Reshape(displayM& displayM);

void draw_sphere(displayM& displayM);

void display_shape(displayM& displayM);

void display(GLFWwindow* window, displayM& displayM);

void input(GLFWwindow* window, displayM& displayM);

void manage_shape(GLFWwindow* window, displayM& displayM);

void show_edges(GLFWwindow* window, displayM& displayM);

void draw_cone_ref(int axe);

void draw_cube(displayM& displayM);

void draw_referential(displayM& displayM);

void rotate_x(GLFWwindow* window,displayM& displayM);
void rotate_y(GLFWwindow* window,displayM& displayM);
void rotate_z(GLFWwindow* window,displayM& displayM);

void manage_rotation(GLFWwindow* window, displayM& displayM);


void draw_shape(int nbFaces, displayM& displayM);

#endif