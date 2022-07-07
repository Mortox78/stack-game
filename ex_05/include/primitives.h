#ifndef _PRIMITIVES_H_
#define _PRIMITIVES_H_

#define PI 3.141592
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define SCALE  250

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <vector>

typedef struct t_point
{
    double x;
    double y;
}t_vector;

enum
{
    SPHERE = 1,
    CUBE   = 2
};


struct displayM
{
    int select_shape     = 0;

    bool keyPressed      = false;
    bool showEdges       = false;
    bool showReferential = false;

    bool canRotateX      = false;
    bool canRotateY      = false;
    bool canRotateZ      = false;
     
    bool keyXPressed     = false;
    bool keyYPressed     = false;
    bool keyZPressed     = false;
     
    float rotationX      = 0;
    float rotationY      = 0;
    float rotationZ      = 0;

    bool init            = false;
    float scale          = 1;
    float rotmat[16];

    bool wayFinished                = false;
    unsigned int indexMovement      = 1;

    t_vector vecMove;

    std::vector<t_point> pointList;
    std::vector<GLuint> textures;




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

void draw_the_way(displayM& displayM);

void manage_the_way(GLFWwindow* window, displayM& displayM);

void draw_shape(int nbFaces, displayM& displayM);

t_vector unitaryVector(t_vector vector);

float calculateLengthOfVector(t_vector vector);

t_vector get_vector_from_points(t_point firstPoint, t_point secondPoint);

void manage_shape_movement(displayM& displayM);

GLuint loadBMP(const char* textureLocalisation);

void select_texture(GLFWwindow* window, displayM& displayM);



#endif