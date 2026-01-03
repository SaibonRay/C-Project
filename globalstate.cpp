#include "globalstate.h"
#include "graphics.h"
#include "grid.h"
#include "pathfinding.h"
#include "config.h"

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
            {1,0,0,0,1,1,0,0,0,1,2,1},
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
            {1,0,0,0,0,0,0,0,0,0,2,1},
            {1,1,1,1,1,1,1,1,1,1,1,1}
        };
    }

    player.init();
    player.setGridPosition(1, 1);
}

bool GlobalState::isWalkable(int gx, int gy) const
{
    if (gx < 0 || gy < 0 || gx >= grid_size || gy >= grid_size)
        return false;

    return grid[gy][gx] == 0 || grid[gy][gx] == 2;
}

bool GlobalState::isAtGoal() const
{
    return grid[player.getGY()][player.getGX()] == 2;
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
}
