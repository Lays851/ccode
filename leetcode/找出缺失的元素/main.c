#include <stdio.h>

// int* findMissingElements(int* nums, int numsSize, int* returnSize) {
//     if (numsSize <= 0) {
//         *returnSize = 0;
//         return NULL;
//     }

//     int min = 0, max = 0;
//     int total;

//     for(int i=0; i<numsSize; i++)
//     {
//         if(nums[i] > max)
//             max = nums[0];

//         if(nums[i] < min)
//             min = nums[0];
//     }
    
//     total = max - min + 1;
//     int misscount = total - numsSize;
//     *returnSize = misscount;

//     if(misscount == 0)
//         return NULL;



//     int *result_arr = malloc(misscount * sizeof(int));
//     if(result_arr == NULL)
//     {
//         *returnSize = 0;
//         return NULL;
//     }

//     int pos = 0;
//     for(int i=min; i<max; i++)
//     {
//         bool tmp = false;
//         for(int j=0; j<numsSize; j++)
//         {
//             if(nums[j] = i)
//                 tmp = true;
//                 break;
//         }
//         if(tmp == false)
//             result_arr[pos++] = i;
//     }


//     return result_arr;
// }

// void moveZeroes(int* nums, int numsSize) {
//     int rear = numsSize-1;

//     for(int i=0; i<=rear; i++)
//     {
//         if(nums[i] == 0)
//         {
//             for(int j=i; j<rear; j++)
//             {
//                 nums[j] = nums[j+1];
//             }
//             nums[rear--] = 0;
//             i--;   // 左移后位置i来了新元素，回退重新检查
//         }
//     }
// }



int main(void)
{
    char *s = "abcdefg";
    printf("%s", s+1);

    return 0;
}