```cpp
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int cmp(const void* a, const void* b);

int main()
{
    int* x, * y;
    int size;
    int i;

    scanf("%d", &size);
    x = (int*)malloc(sizeof(int) * size);
    y = (int*)malloc(sizeof(int) * size);
    for (i = 0; i < size; ++i) {
        scanf("%d %d", x + i, y + i);
    }
    qsort((void*)x, size, sizeof(int), cmp);
    qsort((void*)y, size, sizeof(int), cmp);

    int min = 0;
    // write your code here
    /*找x中间点*/
    int x1 = *(x + (size / 2));
    for (int i = 0; i < size; i++)
    {
        min += abs(x1 - *(x + i));
    }
    int y1 = *(y + (size / 2));
    for (int i = 0; i < size; i++)
    {
        min += abs(y1 - *(y + i));
    }
    printf("%d\n", min);

    return 0;
}

int cmp(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;//升序排序
}

```

