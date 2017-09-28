#include <stdio.h>
#include <stdlib.h>

#define COUNT_TIMES 10

int count;

int fib(int n, int *mem)
{
    // 如果没有缓存结果则进行计算，并把结果加入到缓存中
    if (mem[n] == -1)
    {
        mem[n] = fib(n - 1, mem) + fib(n - 2, mem);
        // 统计计算次数
        count++;
    }
    // 返回缓存结果
    return mem[n];
}

int main()
{
    int i, j, *mem;
    for (i = 0; i < COUNT_TIMES; i++)
    {
        // 申请一块内存来缓存结果
        mem = (int *)malloc(sizeof(int) * COUNT_TIMES);
        // 初始化其中的结果
        mem[0] = mem[1] = 1;
        for (j = 2; j < COUNT_TIMES; j++)
            mem[j] = -1;
        
        // 调用计算
        printf("n %d 结果 %2d 计算次数 %d\\n", i, fib(i, mem), count);
        
        count = 0; // 计算次数清零
        free(mem); // 释放用来缓存的内存
    }
}
