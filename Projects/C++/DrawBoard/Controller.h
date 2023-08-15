#pragma once
#include<easyx.h>
#include"ShapeRect.h"
#include"ShapeGraffiti.h"
#include"ShapeLine.h"
#include"ShapeCircle.h"
#include<vector>
struct ExMessage;

class Controller
{
public:
	void run();
	void readFile(const char* filename);
	void event(const ExMessage& msg);
protected:
	void mousePressEvent(int x, int y);
	void mouseReleaseEvent(int x, int y);
	void mouseMoveEvent(int x, int y);
	void mouseWheelEvent(int val);
private:
	bool m_isPress = false;	//左键是否按下
	Point m_begPos;			//鼠标点击时的坐标
	Point m_prePos;			//上次的结束坐标
	ShapeGraffiti m_graf;
	Color m_curColor = RED;

	Shape::ShapeType m_curType = Shape::ShapeLine;	//当前绘制的形状
	std::vector<Shape*> m_shapes;
};

