#include <cstdio>

#include "primitives.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <GL/gl.h>


int main()
{
    if (!glfwInit()) 
    {
        fprintf(stderr, "glfwInit Failed.\n");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL", NULL, NULL);
    if (!window) 
    {
        fprintf(stderr, "glfwCreateWindow failed.\n");
        glfwTerminate();
        return -1;
    }


    glfwSwapInterval(1);
    glfwMakeContextCurrent(window);
    if (!gladLoadGL())
    {
        fprintf(stderr, "gladLoadGL failed.\n");
        glfwTerminate();
        return -1;
    }

    displayM displayM;

    while (!glfwWindowShouldClose(window))
    {
        input(window, displayM);
        display(displayM);
        
        glfwSwapBuffers(window);
    }


    glfwTerminate();
    return 0;
}