#include "grid.h"
#include "graphics.h"
#include "globalstate.h"
#include "config.h"

void drawGrid(const GlobalState& gs)
{
    float ts = gs.getTileSize();
    int gsSize = gs.getGridSize();

    for (int y = 0; y < gsSize; y++) {
        for (int x = 0; x < gsSize; x++) {
            float cx = x * ts + ts / 2.0f;
            float cy = y * ts + ts / 2.0f;

            graphics::Brush br;

            if (x == 0 || x == gsSize - 1 || y == 0 || y == gsSize - 1) {
                br.outline_opacity = 0.0f;
                br.fill_opacity = 1.0f;
                br.texture = std::string(ASSET_PATH) + "sinboy.png";
                graphics::drawRect(cx, cy, ts, ts, br);
            }
            else if (gs.grid[y][x] == 1) {
                br.outline_opacity = 0.0f;
                br.fill_opacity = 1.0f;
                br.texture = std::string(ASSET_PATH) + "ypo.png";
                graphics::drawRect(cx, cy, ts, ts, br);
            }
            else {
                br.outline_opacity = 1.0f;
                br.fill_opacity = 1.0f;
                br.fill_color[0] = 1.0f;
                br.fill_color[1] = 1.0f;
                br.fill_color[2] = 1.0f;
                br.outline_color[0] = 0.0f;
                br.outline_color[1] = 0.0f;
                br.outline_color[2] = 0.0f;
                graphics::drawRect(cx, cy, ts, ts, br);
            }

            if (x == gs.targetGX && y == gs.targetGY) {
                graphics::Brush targetBr;
                targetBr.fill_opacity = 1.0f;
                targetBr.outline_opacity = 0.0f;
                targetBr.texture = std::string(ASSET_PATH) + "aristotelis.png";
                graphics::drawRect(cx, cy, ts, ts, targetBr);
            }
        }
    }
}


