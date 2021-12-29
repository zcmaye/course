#include "ShapeGraffiti.h"
#include<easyx.h>
ShapeGraffiti::ShapeGraffiti()
	:Shape(Shape::ShapeType::ShapeGraffiti)
{
}

void ShapeGraffiti::draw()
{
	setlinecolor(m_color);
	//如果小于2个点，先不绘制
	if (m_points.size() < 2)
	{
		return;
	}
	for (int i = 0; i < m_points.size()-1; i++)
	{
		line(m_points[i].x, m_points[i].y, m_points[i + 1].x, m_points[i + 1].y);
	}
}

void ShapeGraffiti::addPoint(int x, int y)
{
	m_points.push_back({ x, y });
}

void ShapeGraffiti::addPoint(const Point& pos)
{
	m_points.push_back(pos);
}

void ShapeGraffiti::clear()
{
	m_points.clear();
}

std::string ShapeGraffiti::save(std::ostream& out) const
{
	out <<std::dec<< m_type<<" "<<m_points.size();
	for (size_t i = 0; i < m_points.size(); i++)
	{
		out << " " << m_points[i].x << "," << m_points[i].y;
	}
	out << " " << std::hex << m_color;
	return std::string();
}

std::string ShapeGraffiti::read(std::istream& in)
{
	int cnt = 0;	//涂鸦点的数量
	char skip = 0;	//把逗号读取掉
	in >> cnt;
	m_points.reserve(cnt);
	for (size_t i = 0; i < cnt; i++)
	{
		Point pos;
		in >> pos.x >>skip>> pos.y;
		m_points.push_back(pos);
	}
	in >>std::hex>> m_color;
	return std::string();
}
