#include "ShapeCircle.h"
#include<easyx.h>
ShapeCircle::ShapeCircle(int x1, int y1, int x2, int y2)
	:ShapeRect(x1,y1,x2,y2,Shape::ShapeCircle)
{
}
ShapeCircle::ShapeCircle()
	: ShapeRect(0,0,0,0)
{
}
void ShapeCircle::draw()
{
	setlinecolor(m_color);
	ellipse(m_x1, m_y1, m_x2, m_y2);
}
