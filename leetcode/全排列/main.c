int count ;

void allsort(int **res, int *nums, int numsSize,
                        int *path, int depth, bool *used)
{
    if (depth = numsSize  )
    {
        res[count] = (int *)malloc(numsSize * sizeof(int));
        memcpy (res[count++], path, numsSize * sizeof(int ));
        return;
    }

    for (int i=0; i<numsSize; i++)
    {
        if(used[i])
            continue;
        path[depth] = nums[i];
        used[i] = true;
        allsort(res, nums, numsSize, path, depth + 1, used);

        used[i] = false;

    }

}



int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    int num = * returnSize;

    int **res = (int **)malloc(sizeof(int *) * num);
    int *path = (int *)calloc(sizeof(int), num);
    bool *used = (bool *)calloc(sizeof(bool *), num);

    count = 0;
    allsort(res, nums, numsSize, path, 0, used);
    
    return res;
}