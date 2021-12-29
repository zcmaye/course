#include "ShapeLine.h"
#include<easyx.h>
ShapeLine::ShapeLine(int x1, int y1, int x2, int y2)
	:ShapeRect(x1,y1,x2,y2,Shape::ShapeLine)
{
}
ShapeLine::ShapeLine()
	: ShapeLine(0, 0, 0, 0)
{
}
void ShapeLine::draw()
{
	setlinecolor(m_color);
	line(m_x1, m_y1, m_x2, m_y2);
}
