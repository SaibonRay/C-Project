#include "graphics.h"
#include "globalstate.h"
#include "config.h"
#include "iostream"
using namespace std;

GlobalState gs;

void update(float dt)
{
    gs.update(dt);
}

void draw()
{
    gs.draw();
}

int main()
{
    graphics::createWindow(500, 500, "Gio Kay Ahh Game");

    graphics::playMusic(std::string(ASSET_PATH) + "ost.mp3", 0.05f, true, 0);

    gs.init();

    graphics::setUpdateFunction(update);
    graphics::setDrawFunction(draw);

    graphics::startMessageLoop();
    return 0;
}
