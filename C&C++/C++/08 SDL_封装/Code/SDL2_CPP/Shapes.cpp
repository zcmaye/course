#include"Shapes.h"
Shape* Shape::shapeFromString(const std::string& str)
{
	int type = -1;
	int ret = sscanf(str.data(), "%d", &type);
	//跳过类型
	const char* p = str.data();
	while (*p++ != ' ');

	switch (type)
	{
	case ST_Line:
	{
		auto s = new Line();
		ret = sscanf(p, "(%d,%d) (%d,%d)\n", &s->x, &s->y, &s->x2, &s->y2);
		return s;
	}
	case ST_Rect:
	{
		auto s = new Rect();
		ret = sscanf(p, "(%d,%d) (%d,%d)\n", &s->x, &s->y, &s->w, &s->h);
		return s;
	}
	case ST_Ellipse:
	{
		auto s = new Ellipse();
		ret = sscanf(p, "(%d,%d) (%d,%d)\n", &s->x, &s->y, &s->w, &s->h);
		return s;
	}
	case ST_Triangle:
	{
		auto s = new Triangle();
		ret = sscanf(p, "(%d,%d) (%d,%d)\n", &s->x, &s->y, &s->w, &s->h);
		return s;
	}
	case ST_Pentastar:
	{
		auto s = new Pentastar();
		ret = sscanf(p, "(%d,%d) (%d,%d)\n", &s->x, &s->y, &s->w, &s->h);
		return s;
	}
	case ST_Pentagon:
	{
		auto s = new Pentagon();
		ret = sscanf(p, "(%d,%d) (%d,%d)\n", &s->x, &s->y, &s->w, &s->h);
		return s;
	}
	case ST_Graffiti:
	{
		auto s = new Graffiti();
		SDL_Point point;
		do
		{
			ret = sscanf(p, "(%d,%d)", &point.x, &point.y);
			if (ret != -1)
			{
				s->addPoint(point);
				while (*p++ != ' ' && *p);
			}
		} while (ret != -1);
		return s;
	}
	}
	return nullptr;
}