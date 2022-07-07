#ifndef _PRIMITIVES_H_
#define _PRIMITIVES_H_

#include "../../my_opengl_func.h"

enum
{
    CIRCLE      = 0,
    TRIHEDRAL   = 3,
    TETRAHEDRON = 4,
    PENTAHEDRAL = 5,
    HEXAHEDRON  = 6,
    HEPTAHEDRON = 7,
    OCTAHEDRON  = 8,
    ENNEAHEDRON = 9
};




struct displayM
{
    int select_shape;
    int color_back_ground;
    bool keyPressed = false;
    bool showEdges  = false;
    float x = 0;
    float y = 0;
    float rotation;

};

void Reshape();

void draw_trihedral(displayM& displayM);

void draw_tetrahedron(displayM& displayM);

void draw_pentahedral(displayM& displayM);

void draw_hexahedron(displayM& displayM);

void draw_heptahedron(displayM& displayM);

void draw_octahedron(displayM& displayM);

void draw_enneahedron(displayM& displayM);

void draw_sphere(displayM& displayM);

void display_shape(displayM& displayM);

void display(GLFWwindow* window, displayM& displayM);

void input(GLFWwindow* window, displayM& displayM);

void select_shape(GLFWwindow* window, displayM& displayM);

void select_color_background(GLFWwindow* window, displayM& displayM);

void display_color_background(displayM& displayM);

void show_edges(GLFWwindow* window, displayM& displayM);



void draw_shape(int nbFaces);


#endif