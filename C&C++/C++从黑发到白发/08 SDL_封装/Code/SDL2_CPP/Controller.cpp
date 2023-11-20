#include"Controller.h"
Controller::Controller()
{
	//shapes.push_back(new Line(0, 0, 640, 480));
	//shapes.push_back(new Rect(0, 0, 50, 50));
	//shapes.push_back(new Ellipse(0, 0, 640, 480));
	//shapes.push_back(new Triangle(100, 0, 50, 50));
	//shapes.push_back(new Pentastar(150, 0, 50, 50));
	//shapes.push_back(new Pentagon(200, 0, 50, 50));
	readData("shapes.txt");
}

Controller::~Controller()
{
	FILE* fp = fopen("shapes.txt", "w");
	for (auto& s : shapes)
	{
		s->write(fp);
	}
	fclose(fp);
}

void Controller::readData(const std::string& path)
{
	FILE* fp = fopen(path.data(), "r");
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
		if (s)
			shapes.push_back(s);
	} while (!feof(fp));

	fclose(fp);
}

bool Controller::event(SDL_Event* ev)
{
	switch (ev->type)
	{
	case SDL_MOUSEBUTTONDOWN:
		mousePressEvent(&ev->button);
		break;
	case SDL_MOUSEBUTTONUP:
		mouseReleaseEvent(&ev->button);
		break;
	case SDL_MOUSEMOTION:
		mouseMoveEvent(&ev->motion);
		break;
	case SDL_MOUSEWHEEL:
		mouseWheelEvent(&ev->wheel);
		break;
	}
	return false;
}

void Controller::draw()
{
	Game::renderer->setDrawColor(255, 0, 0, 255);
	//renderer->drawLine(0, 0, 640, 480);
	//renderer->drawEllipse(50, 50, 100, 50);

	for (auto s : shapes)
	{
		s->draw();
	}

	if (isPressed)
	{
		SDL_Rect rect = { begPos.x,begPos.y,endPos.x - begPos.x,endPos.y - begPos.y };
		switch (shapeType)
		{
		case ST_Line:
			Game::renderer->drawLine(begPos.x, begPos.y, endPos.x, endPos.y);
			break;
		case ST_Rect:
			Game::renderer->drawRect(&rect);
			break;
		case ST_Ellipse:
			Game::renderer->drawEllipse(&rect);
			break;
		case ST_Triangle:
			Game::renderer->drawTriangle(&rect);
			break;
		case ST_Pentastar:
			Game::renderer->drawPentastar(&rect);
			break;
		case ST_Pentagon:
			Game::renderer->drawPentagon(&rect);
			break;
		case ST_Graffiti:
			graf.draw();
			break;
		}
	}
}
void Controller::mousePressEvent(SDL_MouseButtonEvent* ev)
{
	isPressed = true;
	begPos = endPos = { ev->x,ev->y };
	if (shapeType == ST_Graffiti)
	{
		graf.addPoint(begPos);
	}
	std::cout << __FUNCTION__ << std::endl;
}
void Controller::mouseReleaseEvent(SDL_MouseButtonEvent* ev)
{
	isPressed = false;
	switch (shapeType)
	{
	case ST_Line:
		shapes.push_back(new Line(begPos.x, begPos.y, endPos.x, endPos.y));
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
void Controller::mouseMoveEvent(SDL_MouseMotionEvent* ev)
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
void Controller::mouseWheelEvent(SDL_MouseWheelEvent* ev)
{
	shapeType = (shapeType+1) % Max_Shape;
	std::cout << shapeType << std::endl;
}

