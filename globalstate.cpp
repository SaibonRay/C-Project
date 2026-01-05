#include "globalstate.h"
#include "graphics.h"
#include "grid.h"
#include "pathfinding.h"
#include "config.h"
#include "iostream"
using namespace std;
#include <string>

void GlobalState::init()
{
    tile_size = canvas_size / grid_size;
    currentGrid = 0;
    loadGrid(currentGrid);
}

void GlobalState::loadGrid(int level)
{
    currentGrid= level;

    if (level == 0)
    {
        grid = {
        {1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,1,0,0,0,0,0,0,1},
        {1,0,1,0,1,0,1,1,1,1,0,1},
        {1,0,1,0,0,0,0,0,0,1,0,1},
        {1,0,1,1,1,1,1,1,0,1,0,1},
        {1,0,0,0,0,0,0,1,0,0,0,1},
        {1,1,1,1,1,1,0,1,1,1,0,1},
        {1,0,0,0,0,0,0,0,0,1,0,1},
        {1,0,1,1,1,1,1,1,0,1,0,1},
        {1,0,0,0,0,0,0,1,0,0,0,1},
        {1,0,1,1,1,1,0,0,0,1,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1}
        };
    }
    else if (level == 1)
    {
        grid = {
            {1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,1,0,0,0,0,1},
            {1,0,1,1,1,0,1,0,1,1,0,1},
            {1,0,0,0,1,0,0,0,1,0,0,1},
            {1,1,1,0,1,1,1,0,1,0,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,1,1,1,1,1,1,1,1,0,1},
            {1,0,0,0,0,0,0,0,0,1,0,1},
            {1,0,1,1,1,1,1,1,0,1,0,1},
            {1,0,0,0,0,0,0,1,0,0,0,1},
            {1,0,0,0,1,1,0,0,0,1,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1}
        };
    }
    else if (level == 2)
    {
        grid = {
            {1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,1,0,0,0,0,0,1},
            {1,1,1,1,0,1,0,1,1,1,0,1},
            {1,0,0,1,0,0,0,1,0,0,0,1},
            {1,0,0,1,1,1,0,1,0,1,0,1},
            {1,0,0,0,0,0,0,1,0,1,0,1},
            {1,0,1,1,1,1,1,1,0,1,0,1},
            {1,0,0,0,0,0,0,0,0,1,0,1},
            {1,0,1,1,1,1,1,1,0,1,0,1},
            {1,0,0,0,0,0,0,1,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1}
        };
    }

    player.init();
    player.setGridPosition(1, 1);


    targetGX = -1;
    targetGY = -1;

    soundPlayed = false;

    levelCompleted = false;
    levelTimer = 0.0f;
}

bool GlobalState::isWalkable(int gx, int gy) const
{
    if (gx < 0 || gy < 0 || gx >= grid_size || gy >= grid_size)
        return false;

    return grid[gy][gx] == 0 || grid[gy][gx] == 2;
}

bool GlobalState::isAtGoal() const
{
    return player.getGX() == targetGX && player.getGY() == targetGY;
}


void GlobalState::update(float dt)
{
    graphics::MouseState ms;
    graphics::getMouseState(ms);

    if (ms.button_left_pressed && player.getPath().empty())
    {
        int targetX = ms.cur_pos_x / tile_size;
        int targetY = ms.cur_pos_y / tile_size;

        if (isWalkable(targetX, targetY)) {
            targetGX = targetX;
            targetGY = targetY;
        }

        if (!isWalkable(targetX, targetY)) {
            graphics::playSound(std::string(ASSET_PATH) + "den_eimai_bro.mp3", 0.5f, false);           
        }
        auto path = findPathAStar(
            grid,
            grid_size,
            player.getGX(),
            player.getGY(),
            targetX,
            targetY
        );

        if (!path.empty())
        {
            player.setPath(path);
        }
    }

    player.update(dt);

    if (!soundPlayed && player.getGX() == targetGX && player.getGY() == targetGY) {

        if (currentGrid == 0) {
            graphics::playSound(std::string(ASSET_PATH) + "aristotelis_bro.mp3", 0.5f, false);
            
        }
        else if (currentGrid == 1) {
            graphics::playSound(std::string(ASSET_PATH) + "megas_alexandros_type_c.mp3", 0.5f, false);
        }
        else if (currentGrid == 2) {
            graphics::playSound(std::string(ASSET_PATH) + "nootropia_read_a_book.mp3", 0.5f, false);
        }
        soundPlayed = true;
    }

    if (isAtGoal())
    {
        if (currentGrid < 2)
            loadGrid(currentGrid + 1);
    }
}

void GlobalState::draw()
{
    drawGrid(*this);
    player.draw();
    
    graphics::Brush br;
    br.outline_opacity = 0.0f;
    br.fill_opacity = 1.0f;

    if (currentGrid == 0)
    {
        br.texture = std::string(ASSET_PATH) + "level1.png";
    }
    else if (currentGrid == 1)
    {
        br.texture = std::string(ASSET_PATH) + "level2.png";
    }
    else if (currentGrid == 2)
    {
        br.texture = std::string(ASSET_PATH) + "level3.png";
    }

    graphics::drawRect(250, 20, 248, 45, br);

        
    
}
