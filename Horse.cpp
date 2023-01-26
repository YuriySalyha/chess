#include "Horse.h"
#include "King.h"

Horse::Horse(Point coords, bool isWhite) : Figure('H', coords, isWhite)
{

}

Horse::Horse()
{
}

bool Horse::ifCanGo(Point figureCoords, Point newCoords,
	List<List<Figure*>> allFigures, bool isWhite, List<Point*> Kings) {
	if (abs((figureCoords.a + 1) - (newCoords.a + 1)) == 1)
	{
		if (abs((figureCoords.b + 1) - (newCoords.b + 1)) != 2)
		{
			return false;
		}
	}
	else if (abs((1 + figureCoords.a) - (1 + newCoords.a)) == 2)
	{
		if (abs((figureCoords.b + 1) - (newCoords.b + 1)) != 1)
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	if (allFigures[newCoords.a][newCoords.b]->Symbol != ' ') {
		if (allFigures[newCoords.a][newCoords.b]->isWhite == isWhite) {
			return false;
		}
	}
	King king;
	if (king.KingsSafety(figureCoords, newCoords, allFigures, isWhite, Kings)) {
		return true;
	}
	return false;
}
