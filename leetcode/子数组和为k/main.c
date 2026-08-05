int subarraySum(int* nums, int numsSize, int k) {
    int count = 0;
    int *maps = (int *)calloc(1001*20001*2, sizeof(int));

    int sum = 0;
    int *map = maps + 1001*20001*1 ;
    map[sum]++;

    for(int i=1; i<numsSize; i++)
    {
        sum += nums[i-1];
        if(map[sum-k] > 0)
        {
            count += map[sum - k];
        }
        map[sum]++;
    }

    free(maps);
    return count;
}