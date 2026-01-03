#pragma once
#include <vector>
#include "player.h"

class GlobalState
{
public:
    void init();
    void update(float dt);
    void draw();

    // Getters (εκφώνηση ?)
    Player* getPlayer() { return &player; }
    float getCanvasSize() const { return canvas_size; }
    float getTileSize() const { return tile_size; }
    int getGridSize() const { return grid_size; }
    bool isWalkable(int gx, int gy) const;


    // Grid
    int grid_size = 12;
    float canvas_size = 500.0f;
    float tile_size;

    // 0 = free, 1 = obstacle
    std::vector<std::vector<int>> grid;

    // Target tile
    int targetGX = -1;
    int targetGY = -1;

    //levels 
    int currentGrid = 0;
    static const int TOTAL_LEVELS = 3;
    bool gameOver = false;

    void loadGrid(int grid);
    bool isAtGoal() const;


private:
    Player player;
};

