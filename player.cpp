#include "player.h"
#include "graphics.h"
#include "globalstate.h"
#include "config.h"
#include <string>

extern GlobalState gs;

void Player::init()
{
    gx = 1;
    gy = 1;

    path.clear();
    pathIndex = 0;
    moveTimer = 0.0f;
}

void Player::setPath(const std::vector<std::pair<int, int>>& p)
{
    path = p;
    pathIndex = 0;
    moveTimer = 0.0f;

}

void Player::setGridPosition(int x, int y) {
    gx = x;
    gy = y;
    path.clear();
    pathIndex = 0;
}

void Player::update(float dt)
{
    dt *= 0.001f;
    
    if (path.empty() || pathIndex >= (int)path.size())
        return;

    moveTimer += dt;

    while (moveTimer >= moveDelay && pathIndex < (int)path.size())
    {
        gx = path[pathIndex].first;
        gy = path[pathIndex].second;
        pathIndex++;
        moveTimer -= moveDelay;
    }

}

void Player::draw()
{
    graphics::Brush br;

    br.fill_opacity = 1.0f;
    br.outline_opacity = 0.0f;
    br.fill_color[0] = 1.0f;
    br.fill_color[1] = 1.0f;
    br.fill_color[2] = 1.0f;

    br.texture = std::string(ASSET_PATH) + "gio_kay.png";

    float tile = gs.getTileSize();

    float x = gx * tile + tile / 2.0f;
    float y = gy * tile + tile / 2.0f;

    graphics::drawRect(x, y, tile *0.8f, tile*0.8f, br);
}
