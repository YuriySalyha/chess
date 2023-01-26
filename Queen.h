#ifndef Queen_h
#define Queen_h

#include "Figure.h"
#include "Point.h" 
#include "Bishop.h"
#include "Castle.h"

class Queen : public Figure
{
public:
	Queen(Point coords, bool isWhite);
	Queen();
	bool ifCanGo(Point figureCoords, Point newCoords,
		List<List<Figure*>> allFigures, bool isWhite, List<Point*> Kings);
};

#endif