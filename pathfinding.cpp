#include "pathfinding.h"
#include <algorithm>
#include <cmath>

struct Node
{
    int x, y;
    int g, h;
    Node* parent;

    int f() const { return g + h; }
};

static int heuristic(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}

static bool isWalkable(
    const std::vector<std::vector<int>>& grid,
    int x, int y,
    int gridSize
)
{
    if (x < 0 || y < 0 || x >= gridSize || y >= gridSize)
        return false;
    return grid[y][x] == 0;
}

std::vector<std::pair<int, int>> findPathAStar(
    const std::vector<std::vector<int>>& grid,
    int gridSize,
    int sx, int sy,
    int tx, int ty
)
{
    std::vector<std::pair<int, int>> path;

    if (!isWalkable(grid, tx, ty, gridSize))
        return path;

    std::vector<Node*> open;
    std::vector<Node*> closed;

    Node* start = new Node{ sx, sy, 0, heuristic(sx, sy, tx, ty), nullptr };
    open.push_back(start);

    Node* targetNode = nullptr;

    while (!open.empty())
    {
        int best = 0;
        for (int i = 1; i < open.size(); i++)
            if (open[i]->f() < open[best]->f())
                best = i;

        Node* current = open[best];
        open.erase(open.begin() + best);
        closed.push_back(current);

        if (current->x == tx && current->y == ty)
        {
            targetNode = current;
            break;
        }

        const int dirs[4][2] = {
            {1,0}, {-1,0}, {0,1}, {0,-1}
        };

        for (auto& d : dirs)
        {
            int nx = current->x + d[0];
            int ny = current->y + d[1];

            if (!isWalkable(grid, nx, ny, gridSize))
                continue;

            bool inClosed = false;
            for (auto c : closed)
                if (c->x == nx && c->y == ny)
                    inClosed = true;

            if (inClosed)
                continue;

            int newG = current->g + 1;

            Node* successor = nullptr;
            for (auto o : open)
                if (o->x == nx && o->y == ny)
                    successor = o;

            if (!successor)
            {
                successor = new Node{
                    nx, ny,
                    newG,
                    heuristic(nx, ny, tx, ty),
                    current
                };
                open.push_back(successor);
            }
            else if (newG < successor->g)
            {
                successor->g = newG;
                successor->parent = current;
            }
        }
    }

    while (targetNode && targetNode->parent)
    {
        path.push_back({ targetNode->x, targetNode->y });
        targetNode = targetNode->parent;
    }

    std::reverse(path.begin(), path.end());
    return path;
}
