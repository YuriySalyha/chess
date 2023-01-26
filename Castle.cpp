#include "Castle.h"
#include "King.h"

Castle::Castle(Point coords, bool isWhite) : Figure('C', coords, isWhite)
{

}

Castle::Castle()
{

}


bool Castle::ifCanGo(Point coords, Point newCoords,
	List<List<Figure*>> allFigures, bool isWhite, List<Point*> Kings)
{
	if (allFigures[newCoords.a][newCoords.b]->Symbol != ' ')
	{
		if (allFigures[newCoords.a][newCoords.b]->isWhite == isWhite) {
			return false;
		}
	}
	int from;
	int to;
	if (coords.a != newCoords.a)
	{
		to = newCoords.a + 1;
		from = coords.a + 1;
	}
	else
	{
		from = coords.b + 1;
		to = newCoords.b + 1;
	}
	// problem with from and to if one of them equal to zero
	int x = coords.b, y = coords.a;
	for (int i = 1; i < abs(from - to); i++) 
	{
		if (coords.a == newCoords.a) {
			if (from > to)
			{
				x--;
			}
			else
			{
				x++;
			}
		}
		else
		{
			if (from > to)
			{
				y--;
			}
			else
			{
				y++;
			}
		}
		if (allFigures[y][x]->Symbol != ' ')
		{

			return false;
		}
	}
	King king;
	if (king.KingsSafety(coords, newCoords, allFigures, isWhite, Kings)) {
		return true;
	}
	return false;
}
