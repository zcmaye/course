#include "Controller.h"
#include<easyx.h>
#include<fstream>
#include<iostream>
#include<sstream>

std::string readLine(std::fstream& f)
{
	std::string res;
	char ch = ' ';
	std::streamsize len;
	while (ch != '\n')
	{
		len = f.readsome(&ch, 1);
		if (len == 0)
			break;
		res += ch;
	}
	return res;
}

void Controller::run()
{
	readFile("./test.txt");

	ExMessage msg;
	while (true)
	{
		if (peekmessage(&msg))
			event(msg);

		for (auto shape : m_shapes)
		{
			shape->draw();
		}
	}
}

void Controller::readFile(const char* filename)
{
	std::fstream f;
	f.open(filename, std::ios::in);
	if (f.is_open())
	{
		while (!f.eof())
		{
			int type = 0;
			f >> type;

			Shape* shape = nullptr;
			switch (type)
			{
			case Shape::ShapeType::ShapeLine:
			{
				shape = new ShapeLine;
				break;
			}
			case Shape::ShapeRect:
			{
				shape = new ShapeRect;
				break;
			}
			case Shape::ShapeGraffiti:
			{
				shape = new ShapeGraffiti;
				break;
			}
			case Shape::ShapeCircle:
			{
				shape = new ShapeCircle;
				break;
			}
			default:
				return;
				break;
			}
			std::stringstream stream(readLine(f), std::ios::in);
			stream >> *shape;
			m_shapes.push_back(shape);
			shape = nullptr;
		}
	}
}

void Controller::event(const ExMessage& msg)
{
	switch (msg.message)
	{
	case WM_LBUTTONDOWN:
		mousePressEvent(msg.x, msg.y);
		break;
	case WM_LBUTTONUP:
		mouseReleaseEvent(msg.x, msg.y);
		break;
	case WM_MOUSEMOVE:
		mouseMoveEvent(msg.x, msg.y);
		break;
	case WM_MOUSEWHEEL:
		mouseWheelEvent(msg.wheel);
		break;
	case WM_RBUTTONDOWN:
		std::fstream f;
		f.open("./test.txt", std::ios::out);
		if (f.is_open())
		{
			for (auto sh : m_shapes)
			{
				f << *sh << std::endl;
			}
		}
		break;
	}
}

void Controller::mousePressEvent(int x, int y)
{
	m_isPress = true;
	m_prePos = m_begPos = Point(x, y);
}

void Controller::mouseReleaseEvent(int x, int y)
{
	m_isPress = false;
	
	switch (m_curType)
	{
	case Shape::ShapeType::ShapeLine:
		m_shapes.push_back(new ShapeLine(m_begPos.x, m_begPos.y, x, y));
		break;
	case Shape::ShapeRect:
		m_shapes.push_back(new ShapeRect(m_begPos.x, m_begPos.y, x, y));
		break;
	case Shape::ShapeGraffiti:
		m_shapes.push_back(new ShapeGraffiti(m_graf));
		m_graf.clear();
		break;
	case Shape::ShapeCircle:
		m_shapes.push_back(new ShapeCircle(m_begPos.x, m_begPos.y, x, y));
		break;
	default:
		break;
	}
	m_shapes.back()->setColor(m_curColor);
}

void Controller::mouseMoveEvent(int x, int y)
{
	setlinecolor(m_curColor);
	setlinestyle(PS_SOLID, 3);
	if (m_isPress)
	{	
		int	oldmode = getrop2();
		setrop2(R2_NOTXORPEN);

		switch (m_curType)
		{
		case Shape::ShapeType::ShapeLine:
			line(m_begPos.x, m_begPos.y, m_prePos.x, m_prePos.y);
			line(m_begPos.x, m_begPos.y, x, y);
			break;
		case Shape::ShapeRect:
			rectangle(m_begPos.x, m_begPos.y, m_prePos.x, m_prePos.y);
			rectangle(m_begPos.x, m_begPos.y, x, y);
			break;
		case Shape::ShapeGraffiti:
			m_graf.draw();
			m_graf.addPoint(x, y);
			break;
		case Shape::ShapeCircle:
			ellipse(m_begPos.x, m_begPos.y, m_prePos.x, m_prePos.y);
			ellipse(m_begPos.x, m_begPos.y, x, y);
			break;
		default:
			break;
		}

		m_prePos = Point(x, y);
		setrop2(oldmode);
	}
}

void Controller::mouseWheelEvent(int angle)
{
	m_curType = Shape::ShapeType((m_curType + 1) % Shape::ShapeMax);
	m_curColor = RGB(rand() % 256, rand() % 256,rand() % 256);
}


