#include <stdio.h>
#include <stdlib.h>

int n;
// left:左侧剩余待入栈车厢,stack:栈数组,top:栈顶,right:右侧已出序列,pos:右侧当前长度
void dfs(int left[], int stack[], int top, int right[], int pos, int left_len) {
    if(left_len == 0 && top == 0) { // 全部转移完成，输出结果
        for(int i=0; i<n; i++) printf("%d ", right[i]);
        printf("\n");
        return;
    }
    // 分支1：左侧还有车厢，将最左边车厢入栈
    if(left_len > 0) {
        stack[top+1] = left[0];
        int new_left[left_len-1];
        for(int i=1; i<left_len; i++) new_left[i-1] = left[i];
        dfs(new_left, stack, top+1, right, pos, left_len-1);
    }
    // 分支2：栈非空，栈顶出栈到右侧
    if(top > 0) {
        right[pos] = stack[top];
        dfs(left, stack, top-1, right, pos+1, left_len);
    }
}

int main() {
    printf("输入车厢数量N：");
    scanf("%d", &n);
    int left[n], stack[n], right[n];
    for(int i=0; i<n; i++) left[i] = i+1;
    printf("所有可能的右侧排列：\n");
    dfs(left, stack, 0, right, 0, n);
    return 0;
}