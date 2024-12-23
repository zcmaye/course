## 01.互不相同且无重复数字的三位数

**题目：**有 **1、2、3、4** 四个数字，能组成多少个互不相同且无重复数字的三位数？都是多少？

**程序分析：**可填在百位、十位、个位的数字都是 **1、2、3、4**，组成所有的排列后再去掉不满足条件的排列。

```c
int main()
{
	for (int i = 1; i < 5; i++) { // 以下为三重循环
		for (int j = 1; j < 5; j++) {
			for (int k = 1; k < 5; k++) { // 确保i、j、k三位互不相同
				if (i != k && i != j && j != k) {
					printf("%d,%d,%d\n", i, j, k);
				}
			}
		}
	}
	return 0;
}
```

## 02.企业发放的奖金根据利润提成

**题目：**企业发放的奖金根据利润提成。

- 利润(i)低于或等于10万元时，奖金可提10%；
- 利润高于10万元，低于20万元时，低于10万元的部分按10%提成，高于10万元的部分，可提成7.5%；
- 20万到40万之间时，高于20万元的部分，可提成5%；
- 40万到60万之间时高于40万元的部分，可提成3%；
- 60万到100万之间时，高于60万元的部分，可提成1.5%；
- 高于100万元时，超过100万元的部分按1%提成。

从键盘输入当月利润i，求应发放奖金总数？

**程序分析：**请利用数轴来分界，定位。注意定义时需把奖金定义成双精度浮点(double)型。

```c
int main()
{
    double profit,bonus;
    printf("请输入利润(万元):");
    scanf("%lf", &profit);

    if (profit <= 10) {
        bonus = profit * 0.1;
    }
    else if (profit < 20) {
		bonus = 10 * 0.1 + (profit - 10) * 0.075;
    }
    else if (profit < 40) {
		bonus = 10 * 0.1 + 10 * 0.075 + (profit - 20) * 0.05;
    }
    else if (profit < 60) {
		bonus = 10 * 0.1 + 10 * 0.075 + 20 * 0.05 + (profit - 40) * 0.03;
    }
    else if (profit < 100) {
		bonus = 10 * 0.1 + 10 * 0.075 + 20 * 0.05 + 20*0.03 +
            (profit - 60) * 0.015;
    }
    else {
		bonus = 10 * 0.1 + 10 * 0.075 + 20 * 0.05 + 20 * 0.03 +
			40 * 0.01 + (profit - 100) * 0.01;
    }

    printf("提成(万元):%lf\n", bonus);
 
    return 0;
}
```

## 03.完全平方数

**题目：**一个整数，它加上100后是一个完全平方数，再加上168又是一个完全平方数，请问该数是多少？

**程序分析：**假设该数为 x。

1、则：`x + 100 = m^2`, `x + 100 + 168 = n^2`

2、将上述两个等式相减，可得到`n^2 - m^2 = 168`；根据平方差公式`a^2 - b^2 = (a + b)(a - b)`，这里令`a = n`，`b = m`，则有`(n + m)(n - m) = 168`

3、接下来我们需要找出满足`(n + m)(n - m) = 168`的整数`n`和`m`，进而求出`x`。

```c
int main()
{
	for (int m = 0; m < 1000; m++)
	{
		for (int n = m + 1; n < 1000; n++)
		{
			if ((n + m) * (n - m) == 168)
			{
				int x = m * m - 100;
				printf("%d ", x);
			}
		}
	}
	return 0;
}
```



## 04.某天是这一年的第几天

**题目：**输入某年某月某日，判断这一天是这一年的第几天？

**程序分析：**以3月5日为例，应该先把前两个月的加起来，然后再加上5天即本年的第几天，特殊情况，闰年且输入月份大于3时需考虑多加一天。

```c
#include <stdio.h>
#include <stdbool.h>
const int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

bool isLeapYear(int year)
{
	return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}
int main()
{
	int year, month, day;
	printf("输入年 月 日:");
	scanf("%d %d %d", &year, &month, &day);

	int days = 0;
	//计算month之前的总天数
	for (int i = 0; i < month - 1; i++) {
		days += daysInMonth[i];
	}
	//计算闰年
	if (isLeapYear(year) && month > 2) {
		days += 1;
	}
	//加上当前月得天数
	days += day;
	printf("这是这一年的第 %d 天。\n", days);
	return 0;
}
```



## 05.把三个数由小到大输出

**题目：**输入三个整数 x、y、z，请把这三个数由小到大输出。

**程序分析：**我们想办法把最小的数放到 x 上，先将 x 与 y 进行比较，如果 x>y 则将 x 与 y 的值进行交换，然后再用 x 与 z 进行比较，如果 x>z 则将 x 与 z 的值进行交换，这样能使 x 最小。

```c
#include <stdio.h>
#include <stdbool.h>

void swap(int* p1, int* p2)
{
	int tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

int main()
{
	int x, y, z;
	printf("输入x y z:");
	scanf("%d %d %d", &x, &y, &z);

	//x最大
	if (x > y && x > z) {
		//z与x交换
		swap(&x, &z);

		if (x > y) {
			swap(&x, &y);
		}
	}
	//y最大
	else if (y > x && y > z) {
		//z与y交换
		swap(&y, &z);

		if (x > y) {
			swap(&x, &y);
		}
	}

	printf("%d %d %d", x, y, z);
	return 0;
}
```

## 06.九九乘法表

**题目：**输出 **9\*9** 口诀。

**程序分析：**分行与列考虑，共 9 行 9 列，i 控制行，j 控制列。

```c
int main()
{
	for (int i = 1; i < 10; i++) {
		for (int j = 1; j <= i; j++) {
			printf("%2d*%2d=%2d ", i, j, i * j);
		}
		printf("\n");
	}
	return 0;
}
```



## 07.斐波拉契数列

**题目：**古典问题（兔子生崽）：有一对兔子，从出生后第3个月起每个月都生一对兔子，小兔子长到第三个月后每个月又生一对兔子，假如兔子都不死，问每个月的兔子总数为多少？（输出前40个月即可）

**程序分析：**兔子的规律为数列1,1,2,3,5,8,13,21....，即下个月是上两个月之和（从第三个月开始）。

```c
#include <stdio.h>

int main()
{
    int a = 1, b = 1;
    printf("%12d%12d", a, b); // 输出前两项
 
	for (int i = 3; i <= 40; i++)
    {
        int temp = a + b; // 计算下一项
        printf("%12d", temp); // 输出下一项
 
        a = b; // 更新a
        b = temp; // 更新b

        if (i % 4 == 0)
            printf("\n");
    }
 
    return 0;
}
```

## 08.素数

**题目：**判断 101 到 200 之间的素数。

**程序分析：**判断素数的方法：用一个数分别去除 2 到 sqrt(这个数)，如果能被整除，则表明此数不是素数，反之是素数。

## 09.物品装包

**题目：**n个物品，已知每个物品的重量，书包的承重固定，每个书包最多放两个物品，可以放一个物品或者两个物品。显然总重量要求总不超过书包承重，假设每个物品的重量都不超过书包承重，问最少需要几个书包?

**输入：**第一行包含两个正整数n(0<n<=10000)和m(0<m<=2000000000)，表示物品个数和书包的承重。接下来n行，每行一个正整数，表示每个物品的重量。重量不超过1000000000，并且每个物品的重量不超过m。

**输出：**输出一行，一个整数表示最少需要的书包个数。

```c
#include <stdio.h>

void bubbleSort(int* arr, size_t size) {
	for (int i = 0; i < size-1; i++) {
		for (int k = 0; k < size - i - 1; k++) {
			if (arr[k] > arr[k + 1]) {
				int tmp = arr[k];
				arr[k] = arr[k + 1];
				arr[k + 1] = tmp;
			}
		}
	}
}

int main()
{
	int n, m;
	int arr[10000];
	int bagCount = 0;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%d", arr + i);
	}
	bubbleSort(arr, n);
	for (int i = 0; i < n; ) {
		//两个物品超过书包承重
		if (arr[i] + arr[i + 1] > m) {
			bagCount++;
			i++;
		}
		//两个物品未超过书包承重
		else {
			bagCount++;
			i+=2;
		}
		if (i == n - 1)
		{
			bagCount++;
			break;
		}
	}
	printf("%d", bagCount);

	return 0;
}
```

