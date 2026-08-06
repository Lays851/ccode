#include <string.h>

void setZeroes(int** matrix, int matrixSize, int* matrixColSize) {
    int cols = *matrixColSize;
    int row_flag[matrixSize], col_flag[cols];
    memset(row_flag, 0, sizeof(row_flag));
    memset(col_flag, 0, sizeof(col_flag));

    /* 第一趟：标记哪些行、列需要清零 */
    for(int i=0; i<matrixSize; i++)
    {
        for(int j=0; j<cols; j++)
        {
            if(matrix[i][j] == 0)
            {
                row_flag[i] = 1;
                col_flag[j] = 1;
            }
        }
    }

    /* 第二趟：按标记清零 */
    for(int i=0; i<matrixSize; i++)
    {
        for(int j=0; j<cols; j++)
        {
            if(row_flag[i] || col_flag[j])
                matrix[i][j] = 0;
        }
    }
}