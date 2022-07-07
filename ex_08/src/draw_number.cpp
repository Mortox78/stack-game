#include <iostream>
#include "../include/stack.h"
#include "../include/draw_number.h"
#include <SDL2/SDL.h>




void draw_zero()
{
    glBegin(GL_LINE_STRIP);
    glColor3f(1.f, 1.f, 1.f);
    glVertex3f(0.f,  0.f,  0.f);
    glVertex3f(0.5f, 0.f,  0.f);
    glVertex3f(0.5f, 1.f,  0.f);
    glVertex3f(0.f,  1.f,  0.f);
    glVertex3f(0.f,  0.f,  0.f);
    glEnd();
}

void draw_one()
{
    glBegin(GL_LINE_STRIP);
    glColor3f(1.f, 1.f, 1.f);
    glVertex3f(0.f,  0.f,  0.f);
    glVertex3f(0.f,  1.f,  0.f);
    glVertex3f(0.f,  0.f,  0.f);
    glEnd();
}

void draw_two()
{
    glBegin(GL_LINE_STRIP);
    glColor3f(1.f, 1.f, 1.f);
    glVertex3f(0.f,  0.f,  0.f);
    glVertex3f(0.5f,  0.f,  0.f);
    glVertex3f(0.5f,  0.5f,  0.f);
    glVertex3f(0.f,  0.5f,  0.f);
    glVertex3f(0.f,  1.f,  0.f);
    glVertex3f(0.5f,  1.f,  0.f);
    glVertex3f(0.f,  1.f,  0.f);
    glEnd();
}

void draw_three()
{
    glBegin(GL_LINE_STRIP);
    glColor3f(1.f, 1.f, 1.f);
    glVertex3f(0.5f,  0.f,  0.f);
    glVertex3f(0.f,  0.f,  0.f);
    glVertex3f(0.f,  0.5f,  0.f);
    glVertex3f(0.5f,  0.5f,  0.f);
    glVertex3f(0.f,  0.5f,  0.f);
    glVertex3f(0.f,  1.f,  0.f);
    glVertex3f(0.5f,  1.f,  0.f);
    glEnd();
}

void draw_four()
{
    glBegin(GL_LINE_STRIP);
    glColor3f(1.f, 1.f, 1.f);
    glVertex3f(0.f,  0.f,  0.f);
    glVertex3f(0.f,  1.f,  0.f);
    glVertex3f(0.5f,  0.3f,  0.f);
    glVertex3f(0.f,  0.3f,  0.f);
    glEnd();
}

void draw_five()
{
    glBegin(GL_LINE_STRIP);
    glColor3f(1.f, 1.f, 1.f);
    glVertex3f(0.5f,  0.f,  0.f);
    glVertex3f(0.f,   0.f,  0.f);
    glVertex3f(0.f,  0.5f,  0.f);
    glVertex3f(0.5f,   0.5f,  0.f);
    glVertex3f(0.5f,   1.f,  0.f);
    glVertex3f(0.f,   1.f,  0.f);
    glEnd();
}

void draw_six()
{
    glBegin(GL_LINE_STRIP);
    glColor3f(1.f, 1.f, 1.f);
    glVertex3f(0.f,  1.f,  0.f);
    glVertex3f(0.5f,  1.f,  0.f);
    glVertex3f(0.5f,  0.f,  0.f);
    glVertex3f(0.f,  0.f,  0.f);
    glVertex3f(0.f,  0.5f,  0.f);
    glVertex3f(0.5f,  0.5f,  0.f);
    glEnd();
}


void draw_seven()
{
    glBegin(GL_LINE_STRIP);
    glColor3f(1.f, 1.f, 1.f);
    glVertex3f(0.5f,  1.f,  0.f);
    glVertex3f(0.f,  1.f,  0.f);
    glVertex3f(0.5f,  0.f,  0.f);
    glEnd();
}

void draw_eight()
{
    glBegin(GL_LINE_STRIP);
    glColor3f(1.f, 1.f, 1.f);
    glVertex3f(0.f,  0.f,  0.f);
    glVertex3f(0.f,  1.f,  0.f);
    glVertex3f(0.5f,  1.f,  0.f);
    glVertex3f(0.5f,  0.f,  0.f);
    glVertex3f(0.f,  0.f,  0.f);
    glVertex3f(0.f,  0.5f,  0.f);
    glVertex3f(0.5f,  0.5f,  0.f);
    glEnd();
}

void draw_nine()
{
    glBegin(GL_LINE_STRIP);
    glColor3f(1.f, 1.f, 1.f);
    glVertex3f(0.5f,  0.f,  0.f);
    glVertex3f(0.f,  0.f,  0.f);
    glVertex3f(0.f,  1.f,  0.f);
    glVertex3f(0.5f,  1.f,  0.f);
    glVertex3f(0.5f,  0.5f,  0.f);
    glVertex3f(0.f,  0.5f,  0.f);
    glEnd();
}


void draw_number(int number)
{
    if (number == ZERO)
        draw_zero();
    else if (number == ONE)
        draw_one();
    else if (number == TWO)
        draw_two();
    else if (number == THREE)
        draw_three();
    else if (number == FOUR)
        draw_four();
    else if (number == FIVE)
        draw_five();
    else if (number == SIX)
        draw_six();
    else if (number == SEVEN)
        draw_seven();
    else if (number == EIGHT)
        draw_eight();
    else if (number == NINE)
        draw_nine();
}