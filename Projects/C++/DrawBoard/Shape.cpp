#include "Shape.h"
#include<easyx.h>
Shape::Shape(Shape::ShapeType type)
	:m_type(type)
	,m_color(BLACK)
{
}

Shape::ShapeType Shape::type()
{
	return Shape::ShapeType(m_type);
}

void Shape::setColor(const Color& c)
{
	m_color = c;
}

Color Shape::getColor() const
{
	return m_color;
}

std::ostream& operator<<(std::ostream& os, const Shape& shp)
{
	shp.save(os);
	return os;
}

std::istream& operator>>(std::istream& is, Shape& shp)
{
	shp.read(is);
	return is;
}
