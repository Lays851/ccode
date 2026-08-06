#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void infection(char** grid, bool** maps, int i, int j, int maxRow, int maxCol)
{
    if (i < 0 || i >= maxRow || j < 0 || j >= maxCol) return;
    if (grid[i][j] != '1' || maps[i][j]) return;

    maps[i][j] = true;

    infection(grid, maps, i+1, j, maxRow, maxCol);
    infection(grid, maps, i-1, j, maxRow, maxCol);
    infection(grid, maps, i, j+1, maxRow, maxCol);
    infection(grid, maps, i, j-1, maxRow, maxCol);
}

int numIslands(char** grid, int gridSize, int* gridColSize) {
    int cols = *gridColSize;
    bool **maps = malloc(gridSize * sizeof(bool *));
    for (int i = 0; i < gridSize; i++)
        maps[i] = calloc(cols, sizeof(bool));

    int count = 0;

    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (grid[i][j] == '1' && !maps[i][j])
            {
                infection(grid, maps, i, j, gridSize, cols);
                count++;
            }
        }
    }

    for (int i = 0; i < gridSize; i++)
        free(maps[i]);
    free(maps);

    return count;
}