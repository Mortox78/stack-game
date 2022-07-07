#include <iostream>
#include "../include/stack.h"
#include "../include/draw_number.h"
#include <SDL2/SDL.h>


void game::Reshape()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.001, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cam.camX, cam.camY, cam.camZ, cam.eyeX, cam.eyeY, cam.eyeZ, 0.f, 1.f, 0.f);
}

void block::draw_shape()
{
    glPushMatrix();
    glTranslatef(x, y, z);
    glColor3f(R, G, B);
    // bottom
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f,     0.0f, 0.0f);
    glVertex3f(length,   0.0f, 0.0f);
    glVertex3f(length,   0.0f, width);
    glVertex3f(0.0f,     0.0f, width);
    glVertex3f(0.0f,     0.0f, 0.0f);
    glEnd();

    // top
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f,     BLOCK_HEIGHT, 0.0f);
    glVertex3f(length,   BLOCK_HEIGHT, 0.0f);
    glVertex3f(length,   BLOCK_HEIGHT, width);
    glVertex3f(0.0f,     BLOCK_HEIGHT, width);
    glVertex3f(0.0f,     BLOCK_HEIGHT, 0.0f);
    glEnd();


    // first face
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f,          0.0f);
    glVertex3f(0.0f, 0.0f,          width);
    glVertex3f(0.0f, BLOCK_HEIGHT,  width);
    glVertex3f(0.0f, BLOCK_HEIGHT,  0.0f);
    glVertex3f(0.0f, 0.0f,          0.0f);
    glEnd();

    // second face
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f,     0.0f,          0.0f);
    glVertex3f(0.0f,     BLOCK_HEIGHT,  0.0f);
    glVertex3f(length,   BLOCK_HEIGHT,  0.0f);
    glVertex3f(length,   0.0f,          0.0f);
    glVertex3f(0.0f,     0.0f,          0.0f);
    glEnd();

    // third face
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(length, 0.0f,          0.0f);
    glVertex3f(length, BLOCK_HEIGHT,  0.0f);
    glVertex3f(length, BLOCK_HEIGHT,  width);
    glVertex3f(length, 0.0f,          width);
    glVertex3f(length, 0.0f,          0.0f);
    glVertex3f(0.0f,   0.0f,          0.0f);
    glEnd();

    // fourth face
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f,     0.0f,          width);
    glVertex3f(0.0f,     BLOCK_HEIGHT,  width);
    glVertex3f(length,   BLOCK_HEIGHT,  width);
    glVertex3f(length,   0.0f,          width);
    glVertex3f(0.0f,     0.0f,          width);

    glEnd();
    glPopMatrix();
}

block::block(unsigned int sizeBlockList, block& block, int& axis)
{
    if (axis == X_AXIS)
    {
        x = 1.f;
        z = block.z;
    }
    else if (axis == Z_AXIS)
    {
        x = block.x;
        z = 1.f;
    }
    y = sizeBlockList * BLOCK_HEIGHT;

    width  = block.width;
    length = block.length;

    forward    = false;
    backward   = true;
    ableToMove = true;

    change_block_color(R, G, B);
}

void block::move(game& game)
{
    if (!ableToMove)
        return;


    if (forward)
    {
        if (game.axis_movement == X_AXIS)
        {
            x += 0.001f * game.deltaTime;
        }
        else if (game.axis_movement == Z_AXIS)
        {
            z += 0.001f * game.deltaTime;
        }
    }
    else if (backward)
    {
        if (game.axis_movement == X_AXIS)
        {
            x -= 0.001f * game.deltaTime;
        }
        else if (game.axis_movement == Z_AXIS)
        {
            z -= 0.001f * game.deltaTime;
        }
    }
    if (x > 1.f || z > 1.f)
    {
        forward  = false;
        backward = true;
    }
    else if (x < -1.f || z < -1.f)
    {
        forward  = true;
        backward = false;
    }
}


void game::add_block_to_blockList()
{
    if (canAddBlock)
    {
        // last block can't move anymore
        blockList.back().ableToMove = false;
        // reshape the current moving block
        int i = blockList.size();
        
        // try to stack the block on tower's top, if it fails, game over
        if (stack_block_x_axis(blockList[i - 2], blockList[i - 1]) == false
        ||  stack_block_z_axis(blockList[i - 2], blockList[i - 1]) == false)
        {
            running = false;
            blockList.pop_back();
            return;
        }

        // get a random axis between x and z
        srand(SDL_GetTicks());
        axis_movement = rand() % 2;
        // add a new block (the new block that will move)
        block newBlock(blockList.size(), blockList.back(), axis_movement);
        blockList.push_back(newBlock);
        canAddBlock = false;
        moveCamera = true;
        score += 1;
    }
}


game::game()
{
    init_blockList_and_camera();

    spaceKeyPressed   = false;
    canAddBlock       = false;
    running           = true;
    moveCamera        = false;
    restart           = false;
    gameOverCamPlaced = false;
    score             = 0;
}

void game::input()
{
    bool spacePress = glfwGetKey(window, GLFW_KEY_SPACE);

	if (!spaceKeyPressed && spacePress)
		canAddBlock = !canAddBlock;
    if (!spaceKeyPressed && spacePress && running == false)
    {
        restart = true;
    }
	spaceKeyPressed = spacePress;

    if (spaceKeyPressed && restart == true)
    {
        blockList.clear();
        init_blockList_and_camera();
        running      = true;
        canAddBlock  = false;
        restart      = false;
        score        = 0;
    }
    else if (canAddBlock && running)
    {
        add_block_to_blockList();
    }
}

block::block()
{
    x = 0.f;
    y = 0.f;
    z = 0.f;

    width  = 1.f;
    length = 1.f;

    forward    = false;
    backward   = false;
    ableToMove = false;

    R = 1.f;
    G = 1.f;
    B = 1.f;
}

void block::change_block_color(float& R, float& G, float& B)
{
    srand(SDL_GetTicks());

    R = (float)rand()/(float)(RAND_MAX);
    G = (float)rand()/(float)(RAND_MAX);
    B = (float)rand()/(float)(RAND_MAX);

    glColor3f(R, G, B);
}

// Reshape the new block added to the tower, and return if it's game over or not
bool game::stack_block_x_axis(block& bottomBlock, block& topBlock)
{
    if (topBlock.x + topBlock.length < bottomBlock.x || bottomBlock.x + bottomBlock.length < topBlock.x)
    {
        return false;
    }
    if (bottomBlock.x < topBlock.x && topBlock.x + topBlock.length > bottomBlock.x + bottomBlock.length)
    {
        topBlock.length -= (topBlock.x - bottomBlock.x);
    }
    else if (bottomBlock.x > topBlock.x && topBlock.x + topBlock.length < bottomBlock.x + bottomBlock.length)
    {
        topBlock.length -= (bottomBlock.x - topBlock.x);
        topBlock.x = bottomBlock.x;
    }
    
    return true;
}

bool game::stack_block_z_axis(block& bottomBlock, block& topBlock)
{
    if (topBlock.z + topBlock.width < bottomBlock.z || bottomBlock.z + bottomBlock.width < topBlock.z)
    {
        return false;
    }
    if (bottomBlock.z < topBlock.z && topBlock.z + topBlock.width > bottomBlock.z + bottomBlock.width)
    {
        topBlock.width -= (topBlock.z - bottomBlock.z);
    }
    else if (bottomBlock.z > topBlock.z && topBlock.z + topBlock.width < bottomBlock.z + bottomBlock.width)
    {
        topBlock.width -= (bottomBlock.z - topBlock.z);
        topBlock.z = bottomBlock.z;
    }
    
    return true;
}


void game::manage_camera()
{
    if (moveCamera)
    {
        cam.eyeY += 0.001 * deltaTime;
        cam.camY += 0.001 * deltaTime;
        
        // + 0.6f because the game starts with 2 blocks (2 * 0.2) + 0.6 == 1.f (the pos of cameraY)
        if (cam.camY >= blockList.size() * BLOCK_HEIGHT + 0.6f)
        {
            moveCamera = false;
        }
    }
    if (!running)
    {
        game_over_camera_movement();
    }

    // it will translate the tower to 0.0.0
    glTranslatef(-0.5f, 0.f, -0.5f);
}

void game::init_blockList_and_camera()
{
    axis_movement = rand() % 2;
    block bottomBlock;
    blockList.push_back(bottomBlock);
    block newBlock(blockList.size(), blockList.back(), axis_movement);
    blockList.push_back(newBlock);

    cam = {-1.f, 1.f, -1.f, 0.5f, 0.f, 0.5f};
    angleRotateTowerGameOver = 0;
}


void game::game_over_camera_movement()
{
    int towerSize = blockList.size();

    if (cam.camY > ((towerSize * BLOCK_HEIGHT) / 2) + 1.f) 
    {
        cam.camY -= 0.002 * deltaTime;
        cam.eyeY -= 0.001 * deltaTime;
        cam.camX -= 0.003 * deltaTime;
        cam.camZ -= 0.003 * deltaTime;
    }
    else
    {
        glRotatef(angleRotateTowerGameOver, 0.f, 1.f, 0.f);
        angleRotateTowerGameOver += (0.1f * deltaTime);
    }
}


void game::display_score()
{
    glPushMatrix();
    glTranslatef(0.f, cam.camY, 3.f);
    int nbBlocks = score;

    for (int i = 10; i < 1000; i *= 10)
    {
        int numberToDraw = nbBlocks % 10;
        draw_number(numberToDraw);
        glTranslatef(1.f, 0.f, 0.f);
        if (score >= i)
        {
            nbBlocks =  score / i;
        }
        else
        {
            break;
        }
    }

    glPopMatrix();
}
