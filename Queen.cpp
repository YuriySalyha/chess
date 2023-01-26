#include "Queen.h"

Queen::Queen(Point coords, bool isWhite) : Figure('Q', coords, isWhite)
{

}

Queen::Queen()
{
}

bool Queen::ifCanGo(Point figureCoords, Point newCoords,
	List<List<Figure*>> allFigures, bool isWhite, List<Point*> Kings)
{
	Bishop b;
	Castle c;
	if (figureCoords.a == newCoords.a || figureCoords.b == newCoords.b) {
		if (c.ifCanGo(figureCoords, newCoords, allFigures, isWhite, Kings)) {
			return true;
		}
	}
	else if (b.ifCanGo(figureCoords, newCoords, allFigures, isWhite, Kings))
	{
		return true;
	}
	return false;
}