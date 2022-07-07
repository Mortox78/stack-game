#include "primitives.h"
#include <cstdio>


void Reshape(displayM& displayM)
{
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.001, 1000);
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


void draw_sphere(displayM& displayM)
{
    GLfloat x, y, z, alpha, beta; // Storage for coordinates and angles
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

    manage_shape(window, displayM);

    show_edges(window, displayM);
}

void display(GLFWwindow* window, displayM& displayM)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
    glTranslatef(0.0f, 0.f, -4.f);

    manage_rotation(window, displayM);

    glGetFloatv(GL_MODELVIEW_MATRIX, displayM.rotmat);
    glScalef(displayM.scale, displayM.scale, displayM.scale);
    display_shape(displayM);

    glPopMatrix();
}


void display_shape(displayM& displayM)
{
    if (displayM.select_shape == SPHERE)
        draw_sphere(displayM);
    if (displayM.select_shape == CUBE)
        draw_cube(displayM);
    if (displayM.showReferential == true)
        draw_referential(displayM);
}

void manage_shape(GLFWwindow* window, displayM& displayM)
{
    if (glfwGetKey(window, GLFW_KEY_1))
        displayM.select_shape = SPHERE;
    if (glfwGetKey(window, GLFW_KEY_2))
        displayM.select_shape = CUBE;
    if (glfwGetKey(window, GLFW_KEY_3))
        displayM.showReferential = true;

    if (glfwGetKey(window, GLFW_KEY_KP_ADD))
    {
        displayM.scale += 0.01f;
    }    
    if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT))
    {
        displayM.scale -= 0.01f;
    }
}


void show_edges(GLFWwindow* window, displayM& displayM)
{
    bool ePress = glfwGetKey(window, GLFW_KEY_E);

	if (!displayM.keyPressed && ePress)
		displayM.showEdges = !displayM.showEdges;

	displayM.keyPressed = ePress;
}


void draw_cone()
{
    glBegin(GL_TRIANGLE_STRIP);

    glVertex3f(0.f, 0.1f, 0.f);

    for (int i = 0; i < 64; ++i)
    {
        glVertex3f((cos(i * 2.f * PI / 64) * 50 / SCREEN_WIDTH), 0.0f, (sin(i * 2.f * PI / 64) * 50 / SCREEN_HEIGHT));
        glVertex3f(0.f, 0.1f, 0.f);
    }

    glVertex3f((cos(0 * 2.f * PI / 64) * 50 / SCREEN_WIDTH), 0.0f, (sin(0 * 2.f * PI / 64) * 50 / SCREEN_HEIGHT));

    glEnd();

    // draw the bottom of the shape
    glBegin(GL_TRIANGLE_FAN);

    for (int i = 0; i < 64; ++i)
    {
        glVertex3f((cos(i * 2.f * PI / 64) * 50 / SCREEN_WIDTH), 0.0f, (sin(i * 2.f * PI / 64) * 50 / SCREEN_HEIGHT));
    }
    glEnd();
}

void draw_cube(displayM& displayM)
{
    if (displayM.showEdges == false)
        glBegin(GL_TRIANGLE_FAN);
    else
        glBegin(GL_LINE_LOOP);
    //bottom
    glColor3f(1.f, 1.f, 1.f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);

    // draw top
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(0.0f, 1.0f, 1.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);

    // draw faces
    glVertex3f(1.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(0.0f, 1.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);

    glEnd();
}

void draw_referential(displayM& displayM)
{
    glBegin(GL_LINE_LOOP);
    // X
    glColor3f(1.f, 0.f, 0.f);
    glVertex3f(0.0f, 0.0f, 0.0f);   
    glVertex3f(1.5f, 0.0f, 0.0f);

    // Y
    glColor3f(0.f, 1.f, 0.f);
    glVertex3f(0.0f, 0.0f, 0.0f);   
    glVertex3f(0.0f, 1.5f, 0.0f);

    // Z
    glColor3f(0.f, 0.f, 1.f);
    glVertex3f(0.0f, 0.0f, 0.0f);   
    glVertex3f(0.0f, 0.0f, 1.5f);
    glEnd();


    // X
    glPushMatrix();
    glColor3f(1.f, 0.f, 0.f);
    glTranslated(1.5f, 0.f, 0.f);
    glRotated(-90, 0.f, 0.f, 1.f);
    draw_cone();
    glPopMatrix();

    // Y
    glPushMatrix();
    glColor3f(0.f, 1.f, 0.f);
    glTranslated(0.f, 1.5f, 0.f);
    draw_cone();
    glPopMatrix();

    // Z
    glPushMatrix();
    glColor3f(0.f, 0.f, 1.f);
    glTranslated(0.f, 0.f, 1.5f);
    glRotated(90, 1.f, 0.f, 0.f);
    draw_cone();
    glColor3f(1.f, 1.f, 1.f);
    glPopMatrix();
}

void rotate_x(GLFWwindow* window,displayM& displayM)
{
	bool xPress = glfwGetKey(window, GLFW_KEY_X);

	if (!displayM.keyXPressed && xPress)
		displayM.rotateX = !displayM.rotateX;

	displayM.keyXPressed = xPress;
}

void rotate_y(GLFWwindow* window,displayM& displayM)
{
	bool yPress = glfwGetKey(window, GLFW_KEY_Y);

	if (!displayM.keyYPressed && yPress)
		displayM.rotateY = !displayM.rotateY;

	displayM.keyYPressed = yPress;
}

void rotate_z(GLFWwindow* window,displayM& displayM)
{
	bool zPress = glfwGetKey(window, GLFW_KEY_Z);

	if (!displayM.keyZPressed && zPress)
		displayM.rotateZ = !displayM.rotateZ;

	displayM.keyZPressed = zPress;
}

void manage_rotation(GLFWwindow* window, displayM& displayM)
{
    rotate_x(window, displayM);
    rotate_y(window, displayM);
    rotate_z(window, displayM);

    if (displayM.init == false)
    {
        glGetFloatv(GL_MODELVIEW_MATRIX, displayM.rotmat);
        displayM.init = true;
    }

    glLoadMatrixf(displayM.rotmat);
    if (displayM.rotateX == true)
        glRotatef(1, 1.f, 0.f, 0.f);
    if (displayM.rotateY == true)
        glRotatef(1, 0.f, 1.f, 0.f);
    if (displayM.rotateZ == true)
        glRotatef(1, 0.f, 0.f, 1.f);

}