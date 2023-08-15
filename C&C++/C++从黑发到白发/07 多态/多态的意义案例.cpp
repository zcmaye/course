#include<iostream>
using namespace std;
/*案例：打印  矩形 和 圆形
矩形： x(横坐标)， y(纵坐标)，length(长度)， wid(宽度)
圆形： x(横坐标)， y(纵坐标)， r(半径)
思路：
矩形 和 圆形 都有 共同的元素：x(横坐标)， y(纵坐标)
那么可以把x， y抽取出来 定义出一个 形状类作为父类，形状类中 包含这两个属性。
定义一个 矩形类，继承 形状类。在自己类中扩展 length(长度)， wid(宽度)属性
定义一个 圆形类，继承 形状类。在自己类中扩展 r(半径) 属性
写一个测试类，定义相应的方法 来实现功能。*/
class Shape
{
public:
	Shape(int x=0,int y=0)
	{
		this->m_x = x;
		this->m_y = y;
	}
	int getX()
	{
		return m_x;
	}
	int getY()
	{
		return m_y;
	}
	void setX(int x)
	{
		this->m_x = x;
	}
	void setY(int y)
	{
		this->m_y = y;
	}
	virtual void show()
	{
		cout<<"我是形状类，坐标为(" << m_x << "," << m_y << ")";
	}
protected:
	int m_x;
	int m_y;
};
//矩形类，宽度，高度
class Rect :public Shape
{
public:
	Rect(int x=0,int y=0,int length = 0, int width = 0) :m_len(length), m_wid(width),Shape(x,y)
	{
	}
	void show()
	{
		cout << "我是矩形，我的坐标是("<<m_x<<","<<m_y<<"),长度和宽度是("<<m_len<<","<<m_wid<<")" << endl;
	}
protected:
private:
	int m_wid;	//宽度
	int m_len;	//长度
};
//矩形类，宽度，高度
class Circle :public Shape
{
public:
	Circle(int x = 0, int y = 0, int r=0) :m_r(r), Shape(x, y)
	{
	}
	void show()
	{
		cout << "我是圆形，我的坐标是(" << m_x << "," << m_y << "),半径是(" << m_r << ")" << endl;
	}
protected:
private:
	int m_r;//半径
};
//等边三角形
class Trilateral : public Shape
{
public:
	void show()
	{
		cout << "我是等边三角形" << endl;
	}
private:

};
void show(Shape *shape)
{
	shape->show();
}
void show(Shape& shape)
{
	shape.show();
}
int main()
{
	/*Shape *base = new Rect(20, 50, 60, 30);
	base->show();
	delete base;
	base = new Circle(20, 20, 50);
	base->show();*/

	Rect r;
	show(r);

	Circle c;
	show(c);

	Trilateral t;
	show(t);

	return 0;
}