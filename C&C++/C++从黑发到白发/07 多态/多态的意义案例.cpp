#include<iostream>
using namespace std;
/*��������ӡ  ���� �� Բ��
���Σ� x(������)�� y(������)��length(����)�� wid(���)
Բ�Σ� x(������)�� y(������)�� r(�뾶)
˼·��
���� �� Բ�� ���� ��ͬ��Ԫ�أ�x(������)�� y(������)
��ô���԰�x�� y��ȡ���� �����һ�� ��״����Ϊ���࣬��״���� �������������ԡ�
����һ�� �����࣬�̳� ��״�ࡣ���Լ�������չ length(����)�� wid(���)����
����һ�� Բ���࣬�̳� ��״�ࡣ���Լ�������չ r(�뾶) ����
дһ�������࣬������Ӧ�ķ��� ��ʵ�ֹ��ܡ�*/
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
		cout<<"������״�࣬����Ϊ(" << m_x << "," << m_y << ")";
	}
protected:
	int m_x;
	int m_y;
};
//�����࣬��ȣ��߶�
class Rect :public Shape
{
public:
	Rect(int x=0,int y=0,int length = 0, int width = 0) :m_len(length), m_wid(width),Shape(x,y)
	{
	}
	void show()
	{
		cout << "���Ǿ��Σ��ҵ�������("<<m_x<<","<<m_y<<"),���ȺͿ����("<<m_len<<","<<m_wid<<")" << endl;
	}
protected:
private:
	int m_wid;	//���
	int m_len;	//����
};
//�����࣬��ȣ��߶�
class Circle :public Shape
{
public:
	Circle(int x = 0, int y = 0, int r=0) :m_r(r), Shape(x, y)
	{
	}
	void show()
	{
		cout << "����Բ�Σ��ҵ�������(" << m_x << "," << m_y << "),�뾶��(" << m_r << ")" << endl;
	}
protected:
private:
	int m_r;//�뾶
};
//�ȱ�������
class Trilateral : public Shape
{
public:
	void show()
	{
		cout << "���ǵȱ�������" << endl;
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