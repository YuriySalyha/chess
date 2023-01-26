#ifndef Horse_h
#define Horse_h

#include "Figure.h"
#include "Point.h" 

class Horse : public Figure
{
public:
	Horse(Point coords, bool isWhite);
	Horse();
	bool ifCanGo(Point figureCoords, Point newCoords, 
		List<List<Figure*>> allFigures, bool isWhite, List<Point*> Kings);
};

#endif