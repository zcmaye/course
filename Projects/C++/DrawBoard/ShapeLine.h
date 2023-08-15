#pragma once
#include"ShapeRect.h"
class ShapeLine : public ShapeRect
{
public:
	ShapeLine(int x1, int y1, int x2, int y2);
	ShapeLine();
	void draw()override;
};

