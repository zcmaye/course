#pragma once
#include"Shape.h"
class ShapeRect :public Shape
{
public:
	ShapeRect();
	ShapeRect(int x1,int y1,int x2,int y2, Shape::ShapeType type = Shape::ShapeRect);
	void draw() override;
	void setLeftTop(int x, int y);
	void setRightBottom(int x, int y) ;

	std::string save(std::ostream& out)const override;
	std::string read(std::istream& in) override;
protected:
	int m_x1;
	int m_y1;
	int m_x2;
	int m_y2;
};

