#include <iostream>
#include "my_opengl_func.h"




void draw_polygon(int edges, bool& showEdges)
{
    if (!showEdges)
        glBegin(GL_TRIANGLE_FAN);
    else
        glBegin(GL_LINE_LOOP);

    for (int i = 0; i < edges; ++i)
    {
        glVertex3f((cos(i * 2.f * PI / edges) * SCALE / SCREEN_WIDTH), (sin(i * 2.f * PI / edges) * SCALE / SCREEN_HEIGHT), 0.0f);
    }
    glEnd();
    glFlush();
}

void change_shape_color(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_R) && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == false)
        glColor3f(1.f, 0, 0);
    else if (glfwGetKey(window, GLFW_KEY_G) && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == false)
        glColor3f(0, 1.f, 0);
    else if (glfwGetKey(window, GLFW_KEY_B) && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == false)
        glColor3f(0, 0, 1.f);
}