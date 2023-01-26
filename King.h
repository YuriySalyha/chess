#ifndef King_h
#define King_h

#include "Figure.h"
#include "Point.h" 
#include <vector>

class King : public Figure
{
public:
	King(Point coords, bool isWhite);
	King();
	std::vector<std::pair<int, int>> possibleHorse = { {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, -2}, {-1, 2} };
	std::vector<std::pair<int, int>> possibleDirections = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1}, {1, 0}, {-1, 0}, {0, -1}, {0, 1} };
	bool ifDirectСheck(Point newCoords, List<List<Figure*>> allFigures, bool isWhite, int xDirection, int yDirection);
	bool ifCanGo(Point figureCoords, Point newCoords,
		List<List<Figure*>> allFigures, bool isWhite, List<Point*> Kings, bool fromKingMethode = true);
	bool KingsSafety(Point figureCoords, Point newCoords,
		List<List<Figure*>> allFigures, bool isWhite, List<Point*> Kings);
};

#endif