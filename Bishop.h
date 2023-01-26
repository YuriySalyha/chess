#ifndef Bishop_h
#define Bishop_h

#include "Figure.h"
#include "Point.h" 

class Bishop : public Figure
{
public:
	Bishop(Point coords, bool isWhite);
	Bishop();
	bool ifCanGo(Point figureCoords, Point newCoords,
		List<List<Figure*>> allFigures, bool isWhite, List<Point*> Kings);
};

#endif