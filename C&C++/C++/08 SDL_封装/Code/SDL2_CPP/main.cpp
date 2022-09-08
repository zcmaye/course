#include"Window.h"
#include<iostream>
#include<vector>
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
	Shape() :Shape(0, 0,-1) {}
	Shape(int xPos, int yPos,int type)
		:x(xPos), y(yPos)
		,type(type)
	{}
	virtual void draw() = 0;
	virtual void write(FILE* fp)
	{
		fprintf(fp, "%d (%d,%d) ",type, x, y);
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
		:Shape(x1, y1,ST_Line), x2(x2), y2(y2)
	{

	}
	void draw()override
	{
		Window::renderer->drawLine(x, y, x2, y2);
	}
	 void write(FILE* fp)override
	{
		 Shape::write(fp);
		 fprintf(fp, "(%d,%d)",  x2, y2);
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
		:Shape(x, y,ST_Rect), w(w), h(h)
	{

	}
	void draw()override
	{
		SDL_Rect rect = { x,y,w,h };
		Window::renderer->drawRect(& rect);
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
	Ellipse():Ellipse(0,0,0,0) {}
	Ellipse(int x, int y, int w, int h)
		:Rect(x, y,w,h)
	{
		type = ST_Ellipse;
	}
	void draw()override
	{
		SDL_Rect rect = { x,y,w,h };
		Window::renderer->drawEllipse(&rect);
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
		Window::renderer->drawTriangle(x, y, w, h);
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
		Window::renderer->drawPentastar(x, y, w, h);
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
		Window::renderer->drawPentagon(x, y, w, h);
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
		Window::renderer->drawLines(points.data(), points.size());
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
			if (ret !=-1)
			{
				s->addPoint(point);
				while (*p++ != ' ' && *p);
			}
		} while (ret!=-1);
		return s;
	}
	}
	return nullptr;
}
class MyWindow :public Window
{
	std::vector<Shape*> shapes;
	SDL_Point begPos{ 0 };
	SDL_Point endPos{ 0 };
	bool isPressed = false;
	int shapeType = ST_Graffiti;
	Graffiti graf;
public:
	using Window::Window;
	~MyWindow()
	{
		FILE* fp = fopen("shapes.txt", "w");
		for (auto& s : shapes)
		{
			s->write(fp);
		}
		fclose(fp);
	}
	void init()
	{
		//shapes.push_back(new Line(0, 0, 640, 480));
		//shapes.push_back(new Rect(0, 0, 50, 50));
		//shapes.push_back(new Ellipse(50, 0, 50, 50));
		//shapes.push_back(new Triangle(100, 0, 50, 50));
		//shapes.push_back(new Pentastar(150, 0, 50, 50));
		//shapes.push_back(new Pentagon(200, 0, 50, 50));
		readData("shapes.txt");
	}
	void readData(const std::string& path)
	{
		FILE* fp = fopen(path.data(),"r");
		if (!fp)
		{
			std::cout << "readData failed" << std::endl;
			return;
		}

		char str[1024] = { 0 };
		do
		{
			fgets(str, 1024, fp);
			auto s = Shape::shapeFromString(str);
			if(s)
				shapes.push_back(s);
		} while (!feof(fp));

		fclose(fp);
	}
	void paintEvent(SDL_Event* ev)override
	{
		renderer->setDrawColor(255, 0, 0, 255);
		//renderer->drawLine(0, 0, 640, 480);
		//renderer->drawEllipse(50, 50, 100, 50);

		for(auto s:shapes)
		{
			s->draw();
		}

		if (isPressed)
		{
			SDL_Rect rect = { begPos.x,begPos.y,endPos.x - begPos.x,endPos.y - begPos.y };
			switch (shapeType)
			{
			case ST_Line:
				renderer->drawLine(begPos.x, begPos.y, endPos.x, endPos.y);
				break;
			case ST_Rect:
				renderer->drawRect(& rect);
				break;
			case ST_Ellipse:
				renderer->drawEllipse(&rect);
				break;
			case ST_Triangle:
				renderer->drawTriangle(&rect);
				break;
			case ST_Pentastar:
				renderer->drawPentastar(&rect);
				break;
			case ST_Pentagon:
				renderer->drawPentagon(&rect);
				break;
			case ST_Graffiti:
				graf.draw();
				break;
			}
		}
	}
	void updateEvent(SDL_Event* ev)override
	{

	}
	void mousePressEvent(SDL_MouseButtonEvent* ev)override
	{
		isPressed = true;
		begPos = endPos = { ev->x,ev->y };
		if (shapeType == ST_Graffiti)
		{
			graf.addPoint(begPos);
		}
		std::cout << __FUNCTION__ << std::endl;
	}
	void mouseReleaseEvent(SDL_MouseButtonEvent* ev)override
	{
		isPressed = false;
		switch (shapeType)
		{
		case ST_Line:
			shapes.push_back(new Line(begPos.x,begPos.y,endPos.x,endPos.y));
			break;
		case ST_Rect:
			shapes.push_back(new Rect(begPos.x, begPos.y, endPos.x - begPos.x, endPos.y - begPos.y));
			break;
		case ST_Ellipse:
			shapes.push_back(new Ellipse(begPos.x, begPos.y, endPos.x - begPos.x, endPos.y - begPos.y));
			break;
		case ST_Triangle:
			shapes.push_back(new Triangle(begPos.x, begPos.y, endPos.x - begPos.x, endPos.y - begPos.y));
			break;
		case ST_Pentastar:
			shapes.push_back(new Pentastar(begPos.x, begPos.y, endPos.x - begPos.x, endPos.y - begPos.y));
			break;
		case ST_Pentagon:
			shapes.push_back(new Pentagon(begPos.x, begPos.y, endPos.x - begPos.x, endPos.y - begPos.y));
			break;
		case ST_Graffiti:
			if (graf.count() > 2)
			{
				shapes.push_back(new Graffiti(graf));
			}
			graf.clear();
			break;
		}

		std::cout << __FUNCTION__ << std::endl;
	}
	void mouseMoveEvent(SDL_MouseMotionEvent* ev)override
	{
		if (isPressed)
		{
			endPos = { ev->x,ev->y };
			if (shapeType == ST_Graffiti)
			{
				graf.addPoint(endPos);
			}
		}
		std::cout << __FUNCTION__ << std::endl;
	}
	void mouseWheelEvent(SDL_MouseWheelEvent* ev)override
	{
		shapeType++;
		std::cout << shapeType << std::endl;
	}
};


int main(int argc, char* argv[])
{
	MyWindow w("sdl", 640, 480);
	w.init();

	return w.exec();
}
