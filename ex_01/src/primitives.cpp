#include "primitives.h"
#include <cstdio>


void draw_point()
{
    glBegin(GL_POINTS);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glEnd();
    glFlush();
}

void draw_line()
{
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glEnd();
    glFlush();
}

void draw_triangle(bool& showEdges)
{
    draw_polygon(3, showEdges);
}

void draw_quad(bool& showEdges)
{
    draw_polygon(4, showEdges);
}

void draw_pentagon(bool& showEdges)
{
    draw_polygon(5, showEdges);
}

void draw_hexagon(bool& showEdges)
{
    draw_polygon(6, showEdges);
}

void draw_heptagon(bool& showEdges)
{
    draw_polygon(7, showEdges);
}

void draw_octogon(bool& showEdges)
{
    draw_polygon(8, showEdges);
}

void draw_enneagon(bool& showEdges)
{
    draw_polygon(9,showEdges);
}

void draw_circle(bool& showEdges)
{
    draw_polygon(64, showEdges);
}

void input(GLFWwindow* window, displayM& displayM)
{
    glfwPollEvents();

    select_shape(window, displayM);

    change_shape_color(window);

    move_shape(window, displayM);

    show_edges(window, displayM);


    select_color_background(window, displayM);
}

void display(displayM& displayM)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glTranslatef(displayM.x, displayM.y, 0.f);

    display_color_background(displayM);

    draw_selected_shape(displayM);
    glPopMatrix();
}


void display_color_background(displayM& displayM)
{
    if (displayM.color_back_ground == RED)
        glClearColor(1., 0, 0, 1.f);
    if (displayM.color_back_ground == GREEN)
        glClearColor(0, 1.f, 0, 1.f);
    if (displayM.color_back_ground == BLUE)
        glClearColor(0, 0, 1.f, 1.f);
}


void draw_selected_shape(displayM& displayM)
{
    int& SS = displayM.select_shape;
    if (SS == CIRCLE)
        draw_circle(displayM.showEdges);
    else if (SS == POINT)
        draw_point();
    else if (SS == LINE)
        draw_line();
    else if (SS == TRIANGLE)
        draw_triangle(displayM.showEdges);
    else if (SS == QUADRILATERAL)
        draw_quad(displayM.showEdges);
    else if (SS == PENTAGON)
        draw_pentagon(displayM.showEdges);
    else if (SS == HEXAGON)
        draw_hexagon(displayM.showEdges);
    else if (SS == HEPTAGON)
        draw_heptagon(displayM.showEdges);
    else if (SS == OCTOGON)
        draw_octogon(displayM.showEdges);
    else if (SS == ENNEAGON)
        draw_enneagon(displayM.showEdges);
}

void select_shape(GLFWwindow* window, displayM& displayM)
{
    int& SS = displayM.select_shape;
    if (glfwGetKey(window, GLFW_KEY_0))
        SS = CIRCLE;
    else if (glfwGetKey(window, GLFW_KEY_1))
        SS = POINT;
    else if (glfwGetKey(window, GLFW_KEY_2))
        SS = LINE;
    else if (glfwGetKey(window, GLFW_KEY_3))
        SS = TRIANGLE;
    else if (glfwGetKey(window, GLFW_KEY_4))
        SS = QUADRILATERAL;
    else if (glfwGetKey(window, GLFW_KEY_5))
        SS = PENTAGON;
    else if (glfwGetKey(window, GLFW_KEY_6))
        SS = HEXAGON;
    else if (glfwGetKey(window, GLFW_KEY_7))
        SS = HEPTAGON;
    else if (glfwGetKey(window, GLFW_KEY_8))
        SS = OCTOGON;
    else if (glfwGetKey(window, GLFW_KEY_9))
        SS = ENNEAGON;
}

void select_color_background(GLFWwindow* window, displayM& displayM)
{
    if (glfwGetKey(window, GLFW_KEY_R) && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
        displayM.color_back_ground = RED;
    if (glfwGetKey(window, GLFW_KEY_G) && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
        displayM.color_back_ground = GREEN;
    if (glfwGetKey(window, GLFW_KEY_B) && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
        displayM.color_back_ground = BLUE;
}

void show_edges(GLFWwindow* window, displayM& displayM)
{
    bool minusPress = glfwGetKey(window, GLFW_KEY_MINUS);

	if (!displayM.keyPressed && minusPress)
		displayM.showEdges = !displayM.showEdges;

	displayM.keyPressed = minusPress;
}

void move_shape(GLFWwindow* window, displayM& displayM)
{
    if (glfwGetKey(window, GLFW_KEY_UP))
        displayM.y += 0.02f;
    if (glfwGetKey(window, GLFW_KEY_DOWN))
        displayM.y -= 0.02f;
    if (glfwGetKey(window, GLFW_KEY_LEFT))
        displayM.x -= 0.02f;
    if (glfwGetKey(window, GLFW_KEY_RIGHT))
        displayM.x += 0.02f;
}