#ifndef Castle_h
#define Castle_h

#include "Figure.h"
#include "Point.h" 

class Castle : public Figure
{
public:
	Castle();
	Castle(Point coords, bool isWhite);
	bool ifCanGo(Point coords, Point newCoords,
		List<List<Figure*>> allFigures, bool isWhite, List<Point*> Kings);
};

#endif
