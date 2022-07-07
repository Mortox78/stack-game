#include "primitives.h"
#include <cstdio>


void Reshape()
{
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1, 100);
}

void draw_trihedral(displayM& displayM)
{
    glBegin(GL_LINE_LOOP);
    glVertex3f( 0.0f,  0.0f, 0.0f);
    glVertex3f( 0.5f,  0.0f, 0.0f);
    glVertex3f( 0.0f,  0.0f, 0.0f);
    
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f( 0.0f,  0.0f, 0.0f);
    glVertex3f( 0.0f,  0.5f, 0.0f);
    glVertex3f( 0.0f,  0.0f, 0.0f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f( 0.0f,  0.0f, 0.0f);
    glVertex3f( 0.0f,  0.0f, 0.5f);
    glVertex3f( 0.0f,  0.0f, 0.0f);
    glEnd();
}


void draw_shape(int nbFaces, displayM& displayM)
{
    // draw the shape    
    if (displayM.showEdges == true)
        glBegin(GL_LINE_LOOP);
    else
        glBegin(GL_TRIANGLE_STRIP);

    glVertex3f(0.f, 0.5f, 0.f);

    for (int i = 0; i < nbFaces; ++i)
    {
        glVertex3f((cos(i * 2.f * PI / nbFaces) * SCALE / SCREEN_WIDTH), 0.0f, (sin(i * 2.f * PI / nbFaces) * SCALE / SCREEN_HEIGHT));
        glVertex3f(0.f, 0.5f, 0.f);
    }

    glVertex3f((cos(0 * 2.f * PI / nbFaces) * SCALE / SCREEN_WIDTH), 0.0f, (sin(0 * 2.f * PI / nbFaces) * SCALE / SCREEN_HEIGHT));

    glEnd();

    // draw the bottom of the shape
    if (displayM.showEdges == true)
        glBegin(GL_LINE_LOOP);
    else
        glBegin(GL_TRIANGLE_FAN);

    for (int i = 0; i < nbFaces; ++i)
    {
        glVertex3f((cos(i * 2.f * PI / nbFaces) * SCALE / SCREEN_WIDTH), 0.0f, (sin(i * 2.f * PI / nbFaces) * SCALE / SCREEN_HEIGHT));
    }
    glEnd();
}


void draw_tetrahedron(displayM& displayM)
{
    draw_shape(3, displayM);
}

void draw_pentahedral(displayM& displayM)
{
    draw_shape(4, displayM);
}

void draw_hexahedron(displayM& displayM)
{
    draw_shape(5, displayM);
}

void draw_heptahedron(displayM& displayM)
{
    draw_shape(6, displayM);
}

void draw_octahedron(displayM& displayM)
{
    draw_shape(7, displayM);
}

void draw_enneahedron(displayM& displayM)
{
    draw_shape(8, displayM);
}

void draw_sphere(displayM& displayM)
{
    GLfloat x, y, z, alpha, beta;
    GLfloat radius = 1.0f;
    int gradation = 32;

    for (alpha = 0.0; alpha < 2 * PI; alpha += PI/gradation)
    {
        if (displayM.showEdges == false)
            glBegin(GL_TRIANGLE_FAN);
        else
            glBegin(GL_LINE_LOOP);
        
        for (beta = 0.0; beta < 2.01 * PI; beta += PI/gradation)            
        {            
            x = radius*cos(beta)*sin(alpha);
            y = radius*sin(beta)*sin(alpha);
            z = radius*cos(alpha);
            glVertex3f(x, y, z);
            x = radius*cos(beta)*sin(alpha + PI/gradation);
            y = radius*sin(beta)*sin(alpha + PI/gradation);
            z = radius*cos(alpha + PI/gradation);            
            glVertex3f(x, y, z);            
        }        
        glEnd();
    }
}

void input(GLFWwindow* window, displayM& displayM)
{
    glfwPollEvents();

    select_shape(window, displayM);

    change_shape_color(window);

    show_edges(window, displayM);

    select_color_background(window, displayM);
}

void display(GLFWwindow* window, displayM& displayM)
{
    glPushMatrix();
    glTranslatef(0.f, 0.f, -3.f);


    displayM.rotation += 1;
    glRotatef(displayM.rotation, 1.f, 0.f, 1.f);

    display_color_background(displayM);

    display_shape(displayM);

    glPopMatrix();
}


void display_shape(displayM& displayM)
{
    int& SS = displayM.select_shape;
    if (SS == CIRCLE)
        draw_sphere(displayM);
    else if (SS == TRIHEDRAL)
        draw_trihedral(displayM);
    else if (SS == TETRAHEDRON)
        draw_tetrahedron(displayM);
    else if (SS == PENTAHEDRAL)
        draw_pentahedral(displayM);
    else if (SS == HEXAHEDRON)
        draw_hexahedron(displayM);
    else if (SS == HEPTAHEDRON)
        draw_heptahedron(displayM);
    else if (SS == OCTAHEDRON)
        draw_octahedron(displayM);
    else if (SS == ENNEAHEDRON)
        draw_enneahedron(displayM);
}

void select_shape(GLFWwindow* window, displayM& displayM)
{
    int& SS = displayM.select_shape;
    if (glfwGetKey(window, GLFW_KEY_0))
        SS = CIRCLE;
    else if (glfwGetKey(window, GLFW_KEY_3))
        SS = TRIHEDRAL;
    else if (glfwGetKey(window, GLFW_KEY_4))
        SS = TETRAHEDRON;
    else if (glfwGetKey(window, GLFW_KEY_5))
        SS = PENTAHEDRAL;
    else if (glfwGetKey(window, GLFW_KEY_6))
        SS = HEXAHEDRON;
    else if (glfwGetKey(window, GLFW_KEY_7))
        SS = HEPTAHEDRON;
    else if (glfwGetKey(window, GLFW_KEY_8))
        SS = OCTAHEDRON;
    else if (glfwGetKey(window, GLFW_KEY_9))
        SS = ENNEAHEDRON;
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

void display_color_background(displayM& displayM)
{
    if (displayM.color_back_ground == RED)
        glClearColor(1.f, 0, 0, 1.f);
    if (displayM.color_back_ground == BLUE)
        glClearColor(0, 1.f, 0, 1.f);
    if (displayM.color_back_ground == GREEN)
        glClearColor(0, 0, 1.f, 1.f);
}

void show_edges(GLFWwindow* window, displayM& displayM)
{
    bool minusPress = glfwGetKey(window, GLFW_KEY_MINUS);

	if (!displayM.keyPressed && minusPress)
		displayM.showEdges = !displayM.showEdges;

	displayM.keyPressed = minusPress;
}