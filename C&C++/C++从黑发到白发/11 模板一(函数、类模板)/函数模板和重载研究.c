#include<iostream>
using namespace std;

void showMax(int a, int c)
{
	cout << a << "  " << c << endl;
}
template<typename T>
void showMax(T a, T c)
{
	cout << a << "  " << c << endl;
}
template<typename T>
void showMax(T a, T b,T c)
{
	cout << a << "  " << b<<"  "<<c << endl;
}
int main()
{
	int a = 1;
	int b = 2;
	showMax(a, b); //当函数模板和普通函数都符合调用时,优先选择普通函数
	showMax<>(a, b); //若显示使用函数模板,则使用<> 类型列表

	showMax(3.0, 4.0); //如果 函数模板产生更好的匹配 使用函数模板

	showMax(5.0, 6.0, 7.0); //重载

	showMax('a', 100);  //调用普通函数 可以隐式类型转换 

	while (1);
	return 0;
}