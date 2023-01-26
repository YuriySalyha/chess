#include "Bishop.h"
#include "King.h"
Bishop::Bishop(Point coords, bool isWhite) : Figure('B', coords, isWhite)
{
	
}

Bishop::Bishop()
{

}

bool Bishop::ifCanGo(Point figureCoords, Point newCoords,
	List<List<Figure*>> allFigures, bool isWhite, List<Point*> Kings) {
	int signForHorizontal;
	int signForVertical;
	int a = figureCoords.a;
	int b = figureCoords.b;
	if (figureCoords.a > newCoords.a) {
		signForVertical = -1;
	}
	else
	{
		signForVertical = 1;
	}
	if (figureCoords.b > newCoords.b)
	{
		signForHorizontal = -1;
	}
	else
	{
		signForHorizontal = 1;
	}
	while ((a != newCoords.a - signForVertical || b != newCoords.b - signForHorizontal) 
		&& ((a >= 0 && a < 8) && (b >= 0 && b < 8)))
	{
		if (a == newCoords.a - signForVertical || b == newCoords.b - signForHorizontal)
		{
			return false;
		}
		a += signForVertical;
		b += signForHorizontal;
		if (allFigures[a][b]->Symbol != ' ')
		{
			return false;
		}

	}
	if ((a < 0 || a > 7) || (b < 0 && b > 7)) 
	{
		return false;
	}
	if (allFigures[newCoords.a][newCoords.b]->Symbol != ' ')
	{
		if (allFigures[newCoords.a][newCoords.b]->isWhite == isWhite)
		{
			return false;
		}
	}
	King king;
	if (king.KingsSafety(figureCoords, newCoords, allFigures, isWhite, Kings)) {
		return true;
	}
	return false;
}