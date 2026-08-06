#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "main.c"

int main() {
    // 用例1: 标准1个岛
    char r0[] = "11110";
    char r1[] = "11010";
    char r2[] = "11000";
    char r3[] = "00000";
    char *g1[] = {r0, r1, r2, r3};
    int c1 = 5;
    printf("用例1: %d (应为1)\n", numIslands(g1, 4, &c1));

    // 用例2: 3个岛
    char a0[] = "11000";
    char a1[] = "11000";
    char a2[] = "00100";
    char a3_[] = "00011";
    char *g2[] = {a0, a1, a2, a3_};
    int c2 = 5;
    printf("用例2: %d (应为3)\n", numIslands(g2, 4, &c2));

    // 用例3: 单个格子
    char b0[] = "1";
    char *g3[] = {b0};
    int c3 = 1;
    printf("用例3: %d (应为1)\n", numIslands(g3, 1, &c3));

    // 用例4: 全0
    char d0[] = "000";
    char d1[] = "000";
    char *g4[] = {d0, d1};
    int c4 = 3;
    printf("用例4: %d (应为0)\n", numIslands(g4, 2, &c4));

    return 0;
}
