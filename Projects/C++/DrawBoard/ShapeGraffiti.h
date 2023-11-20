#pragma once
#include"Shape.h"
#include<vector>
class ShapeGraffiti :public Shape
{
public:
	ShapeGraffiti();
	void draw()override;
	void addPoint(int x, int y);
	void addPoint(const Point&pos);
	void clear();

	std::string save(std::ostream& out)const override;
	std::string read(std::istream& in) override;

private:
	std::vector<Point> m_points;
};

