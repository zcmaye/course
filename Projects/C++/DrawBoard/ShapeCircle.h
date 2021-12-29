#pragma once
#include"ShapeRect.h"
class ShapeCircle : public ShapeRect
{
public:
	ShapeCircle(int x1, int y1, int x2, int y2);
	ShapeCircle();
	void draw()override;
};

