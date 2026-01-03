#pragma once
#include "gameobject.h"
#include <vector>
#include <utility>

class Player : public GameObject
{
public:
    void init() override;
    void update(float dt) override;
    void draw() override;

    void setPath(const std::vector<std::pair<int, int>>& p);
    const std::vector<std::pair<int, int>>& getPath() const { return path; }

    int getGX() const { return gx; }
    int getGY() const { return gy; }

    void setGridPosition(int x, int y);
    


private:
    int gx = 0;
    int gy = 0;

    std::vector<std::pair<int, int>> path;
    int pathIndex = 0;

    float moveTimer = 0.0f;
    float moveDelay = 1.0f;
};
