#ifndef _PRIMITIVES_H_
#define _PRIMITIVES_H_

#define PI 3.141592
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define SCALE  250
#define MOUSE_SENSITIVITY 0.1


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


struct camera
{
    double posCamX    = 0;
    double posCamZ    = 0;

    double rotateCamX = 0;
    double rotateCamY = 0;
};


struct displayM
{
    bool keyPressed = false;
    bool showEdges  = false;

    std::vector<GLuint> textures;
    std::vector<char>   map;

    camera playerCam;
};


void Reshape(displayM& displayM);

void draw_sphere(displayM& displayM);

void display_shape(displayM& displayM);

void display(GLFWwindow* window, displayM& displayM);

void input(GLFWwindow* window, displayM& displayM);

void show_edges(GLFWwindow* window, displayM& displayM);

void draw_cone_ref(int axe);

void draw_cube(displayM& displayM);

GLuint loadBMP(const char* fileName);

void manage_player_cam(GLFWwindow* window, displayM& displayM);

void draw_maze(displayM& displayM);

void init_map(displayM& displayM);

void manage_player_cam_translation(GLFWwindow* window, displayM& displayM);

void manage_player_cam_rotation(GLFWwindow* window, displayM& displayM);



#endif