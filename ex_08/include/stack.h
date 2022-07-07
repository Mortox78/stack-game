#ifndef _STACK_H_
#define _STACK_H_

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define BLOCK_HEIGHT 0.1f

#include <vector>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <GL/gl.h>

class game;

class block
{
    public:
    block();
    block(unsigned int sizeBlockList, block& block, int& axis);
    ~block(){}
    float  x;
    float  y;
    float  z;

    float R;
    float G;
    float B;

    float  width;
    float  length;

    bool forward;
    bool backward;
    bool ableToMove;

    void draw_shape();
    void move(game& game);
    void change_block_color(float& R, float& G, float& B);
};

enum
{
    X_AXIS,
    Z_AXIS,
};

struct camera
{
    float camX;
    float camY;
    float camZ;
    float eyeX;
    float eyeY;
    float eyeZ;
};

class game
{
    public:
    game();
    ~game(){}

    GLFWwindow* window;
    std::vector<block> blockList;

    bool spaceKeyPressed;
    bool canAddBlock;
    bool running;
    bool moveCamera;
    bool restart;
    bool gameOverCamPlaced;

    int axis_movement;
    int angleRotateTowerGameOver;
    int score;

    float deltaTime;


    camera cam;

    void add_block_to_blockList();
    void input();
    void Reshape();
    void manage_camera();
    bool stack_block_x_axis(block& bottomBlock, block& topBlock);
    bool stack_block_z_axis(block& bottomBlock, block& topBlock);
    void init_blockList_and_camera();
    void game_over_camera_movement();
    void display_score();

};


#endif