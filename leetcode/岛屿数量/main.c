/* 岛屿数量
给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。
岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。
此外，你可以假设该网格的四条边均被水包围。
示例 1：
输入：
grid = [
  ['1','1','1','1','0'],
  ['1','1','0','1','0'],
  ['1','1','0','0','0'],
  ['0','0','0','0','0']
]
输出：
1
示例 2：
输入：
grid = [
  ['1','1','0','0','0'],
  ['1','1','0','0','0'],
  ['0','0','1','0','0'],
  ['0','0','0','1','1']
]
输出：
3
*/


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