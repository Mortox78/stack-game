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
    displayM.textures.push_back(loadBMP("media/Grass.bmp"));
    displayM.textures.push_back(loadBMP("media/Carbon_01.bmp"));
    displayM.textures.push_back(loadBMP("media/Water.bmp"));




    while (!glfwWindowShouldClose(window))
    {
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Reshape(displayM);

        input(window, displayM);
        display(window, displayM);

        glFlush();
        glfwSwapBuffers(window);
    }


    glfwTerminate();
    return 0;
}