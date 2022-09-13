#pragma once
#include<iostream>
#include<vector>
#include"Game.h"
#include"Renderer.h"
enum ShapeType
{
	ST_Line,
	ST_Rect,
	ST_Ellipse,
	ST_Triangle,
	ST_Pentastar,
	ST_Pentagon,
	ST_Graffiti,
	Max_Shape
};

class Shape
{
public:
	int x;
	int y;
	int type;
public:
	Shape() :Shape(0, 0, -1) {}
	Shape(int xPos, int yPos, int type)
		:x(xPos), y(yPos)
		, type(type)
	{}
	virtual void draw() = 0;
	virtual void write(FILE* fp)
	{
		fprintf(fp, "%d (%d,%d) ", type, x, y);
	}
	static Shape* shapeFromString(const std::string& str);
};
class Line :public Shape
{
public:
	int x2;
	int y2;
public:
	Line() {}
	Line(int x1, int y1, int x2, int y2)
		:Shape(x1, y1, ST_Line), x2(x2), y2(y2)
	{

	}
	void draw()override
	{
		Game::renderer->drawLine(x, y, x2, y2);
	}
	void write(FILE* fp)override
	{
		Shape::write(fp);
		fprintf(fp, "(%d,%d)", x2, y2);
		fputc('\n', fp);
	}
};
class Rect :public Shape
{
public:
	int w;
	int h;
public:
	Rect() {}
	Rect(int x, int y, int w, int h)
		:Shape(x, y, ST_Rect), w(w), h(h)
	{

	}
	void draw()override
	{
		SDL_Rect rect = { x,y,w,h };
		Game::renderer->drawRect(&rect);
	}
	void write(FILE* fp) override
	{
		Shape::write(fp);
		fprintf(fp, "(%d,%d)", w, h);
		fputc('\n', fp);
	}
};
class Ellipse :public Rect
{
public:
	Ellipse() :Ellipse(0, 0, 0, 0) {}
	Ellipse(int x, int y, int w, int h)
		:Rect(x, y, w, h)
	{
		type = ST_Ellipse;
	}
	void draw()override
	{
		SDL_Rect rect = { x,y,w,h };
		Game::renderer->drawEllipse(&rect);
	}
};
class Triangle :public Rect
{
public:
	Triangle() :Triangle(0, 0, 0, 0) {}
	Triangle(int x, int y, int w, int h)
		:Rect(x, y, w, h)
	{
		type = ST_Triangle;
	}
	void draw()override
	{
		Game::renderer->drawTriangle(x, y, w, h);
	}
};
class Pentastar :public Rect
{
public:
	Pentastar() :Pentastar(0, 0, 0, 0) {}
	Pentastar(int x, int y, int w, int h)
		:Rect(x, y, w, h)
	{
		type = ST_Pentastar;
	}
	void draw() override
	{
		Game::renderer->drawPentastar(x, y, w, h);
	}
};
class Pentagon :public Rect
{
public:
	Pentagon() :Pentagon(0, 0, 0, 0) {}
	Pentagon(int x, int y, int w, int h)
		:Rect(x, y, w, h)
	{
		type = ST_Pentagon;
	}
	void draw() override
	{
		Game::renderer->drawPentagon(x, y, w, h);
	}
};
class Graffiti : public Shape
{
	std::vector<SDL_Point> points;
public:
	Graffiti()
		:Shape(0, 0, ST_Graffiti)
	{

	}
	void addPoint(const SDL_Point& point)
	{
		points.push_back(point);
	}
	int count()
	{
		return points.size();
	}
	void clear()
	{
		points.clear();
	}
	void draw()override
	{
		Game::renderer->drawLines(points.data(), points.size());
	}
	void write(FILE* fp) override
	{
		fprintf(fp, "%d ", type);
		for (auto& p : points)
		{
			fprintf(fp, "(%d,%d) ", p.x, p.y);
		}
		fputc('\n', fp);
	}
};