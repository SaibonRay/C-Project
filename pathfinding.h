#pragma once
#include <vector>
#include <utility>

std::vector<std::pair<int, int>> findPathAStar(
    const std::vector<std::vector<int>>& grid,
    int gridSize,
    int sx, int sy,
    int tx, int ty
);

