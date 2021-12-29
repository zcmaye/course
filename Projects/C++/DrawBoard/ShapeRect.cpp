#include "ShapeRect.h"
#include<easyx.h>
#include<sstream>
#include<iostream>
ShapeRect::ShapeRect()
	:ShapeRect(0,0,0,0)
{
}

ShapeRect::ShapeRect(int x1, int y1, int x2, int y2, Shape::ShapeType type)
	: Shape(type)
	,m_x1(x1),m_y1(y1),m_x2(x2),m_y2(y2)
{

}

void ShapeRect::draw()
{
	setlinecolor(m_color);
	rectangle(m_x1, m_y1, m_x2, m_y2);
}

void ShapeRect::setLeftTop(int x, int y)
{
	m_x1 = x;
	m_y1 = y;
}

void ShapeRect::setRightBottom(int x, int y)
{
	m_x2 = x;
	m_y2 = y;
}

std::string ShapeRect::save(std::ostream& out) const
{
	out <<std::dec<< m_type << " " << m_x1 << " " << m_y1 << " " << m_x2 << " " << m_y2 << " " << std::hex << m_color;
	return std::string();
}

std::string ShapeRect::read(std::istream& in)
{
	in >> m_x1 >> m_y1 >> m_x2 >> m_y2 >> std::hex >> m_color;
	return std::string();
}
