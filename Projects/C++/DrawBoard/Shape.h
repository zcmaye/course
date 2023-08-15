#pragma once
#include<string>
#include<istream>

using Color = unsigned int;
struct Point
{
	Point(int x, int y) :x(x), y(y) {};
	Point() :Point(0, 0) {};
	bool operator!=(const Point& pos) const
	{
		return (x != pos.x || y != pos.y);
	}

	bool operator==(const Point& pos) const
	{
		return (x == pos.y && y == pos.y);
	}
	int x;
	int y;
};

class Shape
{
public:
	enum ShapeType
	{
		ShapeNone,
		ShapeLine,
		ShapeGraffiti,		//涂鸦
		ShapeRect,			//矩形
		ShapeCircle,		//圆形
		ShapeMax,
	};
public:
	Shape(Shape::ShapeType type);
	virtual ~Shape() {};
	virtual void draw() = 0;
	Shape::ShapeType type();
	virtual std::string save(std::ostream&out)const = 0;
	virtual std::string read(std::istream&in) = 0;
	void setColor(const Color& c);
	Color getColor() const;
public:
	friend std::ostream& operator<<(std::ostream& os, const Shape& shp);
	friend std::istream& operator>>(std::istream& is, Shape& shp);
protected:
	int m_type;		//形状类型
	Color m_color;	//颜色
};

