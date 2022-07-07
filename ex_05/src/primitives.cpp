#include "primitives.h"
#include <cstdio>
#include <iostream>

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <math.h>


void Reshape(displayM& displayM)
{
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect = 720.f / 1280.f;
    gluOrtho2D(-1, 1, -aspect, aspect);
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
    GLfloat radius = 0.5f;
    int gradation = 32;

    for (alpha = 0.0; alpha < 2 * PI; alpha += PI/gradation)
    {
        if (displayM.showEdges == false)
            glBegin(GL_TRIANGLE_FAN);
        else
            glBegin(GL_LINE_LOOP);
        
        glColor3f(1.f, 1.f, 1.f);
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

    select_texture(window, displayM);


    manage_shape(window, displayM);

    show_edges(window, displayM);
}

void display(GLFWwindow* window, displayM& displayM)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    manage_the_way(window, displayM);
    draw_the_way(displayM);

    glTranslatef(displayM.vecMove.x, displayM.vecMove.y, 0.0f);

    rotate_x(window, displayM);
    rotate_y(window, displayM);
    rotate_z(window, displayM);
    glScalef(displayM.scale, displayM.scale, displayM.scale);

    if (displayM.wayFinished)
    {
        manage_shape_movement(displayM);
        display_shape(displayM);
    }
}


void display_shape(displayM& displayM)
{
    if (displayM.select_shape == SPHERE)
        draw_sphere(displayM);
    if (displayM.select_shape == CUBE)
    {
        glEnable(GL_TEXTURE_2D);
        draw_cube(displayM);
        glDisable(GL_TEXTURE_2D);
    }
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
        displayM.scale += 0.02f;
    }    
    if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT))
    {
        displayM.scale -= 0.02f;
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
    glPushMatrix();
    glScalef(0.5f, 0.5f, 0.5f);
    // bottom
    if (displayM.showEdges == false)
        glBegin(GL_TRIANGLE_FAN);
    else
        glBegin(GL_LINE_LOOP);


    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glEnd();

    // top
    if (displayM.showEdges == false)
        glBegin(GL_TRIANGLE_FAN);
    else
        glBegin(GL_LINE_LOOP);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.0f, 1.0f, 1.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glEnd();


    // first face
    if (displayM.showEdges == false)
        glBegin(GL_TRIANGLE_FAN);
    else
        glBegin(GL_LINE_LOOP);

    glVertex3f(0.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glEnd();

    // second face
    if (displayM.showEdges == false)
        glBegin(GL_TRIANGLE_FAN);
    else
        glBegin(GL_LINE_LOOP);

    glVertex3f(0.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glEnd();

    // third face
    if (displayM.showEdges == false)
        glBegin(GL_TRIANGLE_FAN);
    else
        glBegin(GL_LINE_LOOP);

    glVertex3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glEnd();

    // fourth face
    if (displayM.showEdges == false)
        glBegin(GL_TRIANGLE_FAN);
    else
        glBegin(GL_LINE_LOOP);

    glVertex3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);

    glEnd();
    glPopMatrix();
}

void draw_referential(displayM& displayM)
{
    glBegin(GL_LINE_LOOP);
    // draw line ref
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


    // draw cones
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
    glRotatef(displayM.rotationX, 1.f, 0.f, 0.f);

	bool xPress = glfwGetKey(window, GLFW_KEY_X);

	if (!displayM.keyXPressed && xPress)
		displayM.canRotateX = !displayM.canRotateX;

	displayM.keyXPressed = xPress;

    if (displayM.canRotateX)
    {
        displayM.rotationX += 1;
    }
}

void rotate_y(GLFWwindow* window,displayM& displayM)
{
    glRotatef(displayM.rotationY, 0.f, 1.f, 0.f);
	bool yPress = glfwGetKey(window, GLFW_KEY_Y);

	if (!displayM.keyYPressed && yPress)
		displayM.canRotateY = !displayM.canRotateY;

	displayM.keyYPressed = yPress;
    if (displayM.canRotateY)
    {
        displayM.rotationY += 1;
    }
}

void rotate_z(GLFWwindow* window,displayM& displayM)
{
    glRotatef(displayM.rotationZ, 0.f, 0.f, 1.f);
	bool zPress = glfwGetKey(window, GLFW_KEY_Z);

	if (!displayM.keyZPressed && zPress)
		displayM.canRotateZ = !displayM.canRotateZ;

	displayM.keyZPressed = zPress;
    if (displayM.canRotateZ)
    {
        displayM.rotationZ += 1;
    }
}

void draw_the_way(displayM& displayM)
{
    glBegin(GL_LINE_LOOP);
    glColor3f(1.f, 1.f, 1.f);
    for (unsigned int i = 0; i < displayM.pointList.size(); ++i)
    {
        glVertex3f(displayM.pointList[i].x, displayM.pointList[i].y, 0.f);
    }

    glEnd();
}

void manage_the_way(GLFWwindow* window, displayM& displayM)
{
    bool leftClickDown  = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    bool rightClickDown = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);

    t_point newPoint;

    glfwGetCursorPos(window, &newPoint.x, &newPoint.y);

    if (newPoint.x < 0 || newPoint.x > 1280 || newPoint.y < 0 || newPoint.y > 720)
        return;

    float aspect = 720.f / 1280.f;
    newPoint.x = ((newPoint.x / 1280.f) - 0.5) * 2.f;
    newPoint.y = ((newPoint.y / 720.f) - 0.5) * 2.f * -aspect;

    if (leftClickDown)
    {
        if (displayM.wayFinished)
        {
            displayM.pointList.clear();
            displayM.wayFinished = false;
            displayM.indexMovement = 0;
        }

        displayM.pointList.push_back(newPoint);
    }
    else if (rightClickDown && displayM.wayFinished == false)
    {
        displayM.wayFinished = true;
        displayM.pointList.push_back(newPoint);
        displayM.vecMove = {displayM.pointList[0].x, displayM.pointList[0].y};
    }
}


void manage_shape_movement(displayM& displayM)
{
    if (displayM.wayFinished == false)
        return;

    unsigned int i = displayM.indexMovement;
    t_vector vecMovement = {displayM.pointList[i].x - displayM.vecMove.x,
                            displayM.pointList[i].y - displayM.vecMove.y};

    vecMovement = unitaryVector(vecMovement);

    displayM.vecMove.x += vecMovement.x * 0.01f;
    displayM.vecMove.y += vecMovement.y * 0.01f;


    // E = "epsilon"
    float E = 0.01;

    if (displayM.vecMove.x <= displayM.pointList[i].x + E 
    &&  displayM.vecMove.x >= displayM.pointList[i].x - E
    &&  displayM.vecMove.y <= displayM.pointList[i].y + E
    &&  displayM.vecMove.y >= displayM.pointList[i].y - E) 
    {
        displayM.indexMovement += 1;
    }
    if (displayM.indexMovement == displayM.pointList.size())
    {
        displayM.indexMovement = 0;
    }
}

t_vector unitaryVector(t_vector vector)
{
    t_vector unitaryVector;

    float length = calculateLengthOfVector(vector);
    
    if (length != 0)
    {
        unitaryVector.x = vector.x / length;
        unitaryVector.y = vector.y / length;
    }

    return unitaryVector;
}

float calculateLengthOfVector(t_vector vector)
{
    return sqrt(pow(vector.x, 2) + pow(vector.y, 2));
}

t_vector get_vector_from_points(t_point firstPoint, t_point secondPoint)
{
	t_vector vector;
    vector.x = secondPoint.x - firstPoint.x;
    vector.y = secondPoint.y - firstPoint.x;

	return vector;
}

GLuint loadBMP(const char* fileName)
{
    // Data read from the header of the BMP file
    unsigned char header[54]; // Each BMP file begins by a 54-bytes header
    unsigned int dataPos;     // Position in the file where the actual data begins
    unsigned int width, height;
    unsigned int imageSize;   // = width*height*3
    // Actual RGB data
    unsigned char * data;

    FILE * file = fopen(fileName,"rb");
    if (!file)
    {
        printf("Image could not be opened\n");
        return 0;
    }

    // If not 54 bytes read : problem || If the benning of our header doesn't begin with "BM"
    if ( fread(header, 1, 54, file) != 54 ||  header[0]!='B' || header[1]!='M')
    {
        printf("Not a correct BMP file\n");
        return 0;
    }

    // Read ints from the byte array
    dataPos    = *(int*)&(header[0x0A]);
    imageSize  = *(int*)&(header[0x22]);
    width      = *(int*)&(header[0x12]);
    height     = *(int*)&(header[0x16]);

    // Some BMP files are misformatted, guess missing information
    if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
    if (dataPos==0)      dataPos=54; // The BMP header is done that way

    // Create a buffer
    data = new unsigned char [imageSize];

    // Read the actual data from the file into the buffer
    fread(data,1,imageSize,file);

    //Everything is in memory now, the file can be closed
    fclose(file);

    // Create one OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    return textureID;
}

void select_texture(GLFWwindow* window, displayM& displayM)
{
    if (glfwGetKey(window, GLFW_KEY_A))
        glBindTexture(GL_TEXTURE_2D, displayM.textures[0]);
    if (glfwGetKey(window, GLFW_KEY_B))
        glBindTexture(GL_TEXTURE_2D, displayM.textures[1]);
    if (glfwGetKey(window, GLFW_KEY_C))
        glBindTexture(GL_TEXTURE_2D, displayM.textures[2]);
}