#include <cstdio>
#include <iostream>

#include "../include/stack.h"
#include "../include/draw_number.h"
#include <SDL2/SDL.h>
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

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Stack", NULL, NULL);
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

    game game;
    game.window = window;
    float oldTimeSinceStart = 0;


    while (!glfwWindowShouldClose(window))
    {
        float timeSinceStart = SDL_GetTicks();
        float deltaTime = timeSinceStart - oldTimeSinceStart;
        oldTimeSinceStart = timeSinceStart;
        game.deltaTime = deltaTime;


        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(25.f / 255.f, 133.f / 255.f, 208.f / 255.f, 1.f);


        glfwPollEvents();
        game.Reshape();
        game.manage_camera();
        game.input();
        for (unsigned int i = 0; i < game.blockList.size(); ++i)
        {
            game.blockList[i].move(game);
            game.blockList[i].draw_shape();
        }

        game.display_score();

        glFlush();
        glfwSwapBuffers(window);
    }














    glfwTerminate();
    return 0;
}

