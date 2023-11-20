#include<iostream>
using namespace std;
/*	vptr
https://blog.csdn.net/qq_28584889/article/details/88756022
*/
class Base {
public:
	virtual void f() { cout << "Base::f" << endl; }
	virtual void g() { cout << "Base::g" << endl; }
	virtual void h() { cout << "Base::h" << endl; }
};
typedef void(*Fun)(void);

int main()
{
	Base t;
	Base t1;
	Fun fc=(Fun)*(int*)(*(int*)&t);
	fc();

	Fun fc1 = (Fun) * ((int*)(*(int*)&t)+4);
	fc1();

	return 0;
}
