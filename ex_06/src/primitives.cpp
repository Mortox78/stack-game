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
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.001, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}


void draw_sphere(displayM& displayM)
{
    GLfloat x, y, z, alpha, beta; // Storage for coordinates and angles
    GLfloat radius = 1.f;
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

    show_edges(window, displayM);
}

void display(GLFWwindow* window, displayM& displayM)
{
    manage_player_cam(window, displayM);

    draw_maze(displayM);
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
    if ( fread(header, 1, 54, file) !=54 ||  header[0]!='B' || header[1]!='M')
    {
    
        printf("Not a correct BMP file\n");
        return false;
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

void manage_player_cam(GLFWwindow* window, displayM& displayM)
{
    double cursorX, cursorY;
    glfwGetCursorPos(window, &cursorX, &cursorY);

    manage_player_cam_rotation(window, displayM);
    manage_player_cam_translation(window, displayM);

    glRotatef(displayM.playerCam.rotateCamX, 1.f, 0.f, 0.f);
    glRotatef(displayM.playerCam.rotateCamY + 180, 0.f, 1.f, 0.f);

    glTranslatef(-displayM.playerCam.posCamX, 0.0f,  -displayM.playerCam.posCamZ);

    glfwSetCursorPos(window, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}

void draw_maze(displayM& displayM)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, displayM.textures[0]);
    // set the maze in front of the player
    glRotatef(-90, 0.f, 1.f, 0.f);
    glTranslatef(0.f, 0.f, -1.5f);
    // drawing the floor
    for (int i = 0; i < 30; ++i)
    {
        for (int j = 0; j < 20; ++j)
        {
            glPushMatrix();
            glTranslatef(i, 0.0f, j);
            // draw a wall
            glTranslatef(0.f, -0.5f, 0.f);
            if (displayM.map[i * 20 + j] == '#')
            {
                glBindTexture(GL_TEXTURE_2D, displayM.textures[1]);
                draw_cube(displayM);
                glBindTexture(GL_TEXTURE_2D, displayM.textures[0]);
            }
            // draw the platform
            glTranslatef(0.f, -1.f, 0.f);
            draw_cube(displayM);
            glPopMatrix();
        }
    }
    glDisable(GL_TEXTURE_2D);
}

void init_map(displayM& displayM)
{
    displayM.map = {
        '#','0','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
        '#','0','#','0','0','0','#','0','#','#','#','#','#','0','#','#','#','#','#','#',
        '#','0','#','0','#','#','#','0','#','#','#','0','0','0','#','#','#','0','0','#',
        '#','0','#','0','#','#','#','0','#','#','#','0','#','#','#','#','0','0','#','#',
        '#','0','0','0','0','0','0','0','#','0','0','0','#','#','#','#','0','#','#','#',
        '#','#','#','0','#','0','#','0','#','#','#','0','0','0','0','0','0','0','#','#',
        '#','#','#','0','#','0','#','0','#','#','#','0','#','#','#','#','#','0','#','#',
        '#','0','0','0','0','0','#','0','#','#','#','0','#','#','0','#','#','0','#','#',
        '#','#','#','0','#','#','#','0','0','#','#','0','#','#','0','#','#','0','#','#',
        '#','#','#','0','#','#','#','#','0','#','0','0','0','0','0','#','#','0','#','#',
        '#','0','0','0','0','0','0','#','0','0','0','#','#','#','0','#','#','0','#','#',
        '#','0','#','#','#','#','0','#','#','#','0','#','#','#','0','#','#','0','#','#',
        '#','0','#','#','#','#','0','#','#','#','0','#','#','#','0','0','#','0','#','#',
        '#','0','#','#','#','#','0','#','#','#','#','#','#','#','#','#','#','0','#','#',
        '#','0','#','#','#','#','0','0','0','0','0','0','0','0','#','#','0','0','0','#',
        '#','0','#','#','#','#','#','0','#','#','#','#','#','0','0','#','0','#','0','#',
        '#','0','0','0','0','0','#','0','#','0','#','0','#','#','0','#','0','#','#','#',
        '#','#','#','#','#','0','#','0','#','0','#','0','0','0','0','0','0','0','0','#',
        '#','#','#','#','#','0','#','0','0','0','#','0','#','#','#','#','#','#','0','#',
        '#','0','0','0','#','0','#','0','#','#','#','0','#','#','0','0','0','#','0','#',
        '#','0','#','0','#','0','#','0','#','0','0','0','#','0','0','#','0','#','0','#',
        '#','0','#','0','0','0','#','0','#','0','#','0','#','#','0','#','0','#','0','#',
        '#','0','#','#','#','#','#','0','#','0','#','0','#','0','0','#','0','#','#','#',
        '#','0','0','#','#','#','#','0','#','0','0','0','#','#','#','#','0','0','0','#',
        '#','#','0','#','0','0','0','0','#','#','0','#','#','0','#','#','#','0','#','#',
        '#','#','#','#','0','#','#','#','#','#','0','#','#','0','#','#','#','0','#','#',
        '#','#','#','#','0','#','#','#','#','#','0','#','0','0','0','0','0','0','#','#',
        '#','#','#','#','0','#','#','#','#','#','0','#','#','0','#','#','#','0','#','#',
        '#','#','#','#','0','#','#','#','#','#','0','0','0','0','#','#','0','0','0','#',
        '#','#','#','#','0','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'
    };
}

void manage_player_cam_translation(GLFWwindow* window, displayM& displayM)
{
    double forward = 0, strafe = 0;

    if (glfwGetKey(window, GLFW_KEY_UP))
        forward   = 0.025;
    if (glfwGetKey(window, GLFW_KEY_DOWN))
        forward   = -0.025;
    if (glfwGetKey(window, GLFW_KEY_LEFT))
        strafe    = 0.025;
    if (glfwGetKey(window, GLFW_KEY_RIGHT))
        strafe    = -0.025;


    double angle = displayM.playerCam.rotateCamY * PI / 180.f;

    displayM.playerCam.posCamX += forward * -sin(angle);
    displayM.playerCam.posCamZ += forward * cos(angle);
    displayM.playerCam.posCamX += strafe  * cos(angle);
    displayM.playerCam.posCamZ += strafe  * sin(angle);
}

void manage_player_cam_rotation(GLFWwindow* window, displayM& displayM)
{
    double cursorX, cursorY;
    glfwGetCursorPos(window, &cursorX, &cursorY);

    t_vector moveCam;
    moveCam.x = cursorX - SCREEN_WIDTH  / 2;
    moveCam.y = cursorY - SCREEN_HEIGHT / 2;

    displayM.playerCam.rotateCamX += (moveCam.y * MOUSE_SENSITIVITY);
    displayM.playerCam.rotateCamY += (moveCam.x * MOUSE_SENSITIVITY);

    if (displayM.playerCam.rotateCamX > 89)
        displayM.playerCam.rotateCamX = 89;
    else if (displayM.playerCam.rotateCamX < -89)
        displayM.playerCam.rotateCamX = -89;
}