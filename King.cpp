#include "King.h"
#include <cmath>
#include <iostream>
King::King(Point coords, bool isWhite) : Figure('K', coords, isWhite)
{

}

King::King()
{
}

bool King::ifDirectСheck(Point kingCoords, List<List<Figure*>> allFigures, bool isWhite, int xDirection, int yDirection)
{
	int a = kingCoords.a + yDirection;
	int b = kingCoords.b + xDirection;

	bool isStraight;

	if (xDirection == 0 || yDirection == 0)
	{
		isStraight = true;
	}
	else
	{
		isStraight = false;
	}

	while ((a >= 0 && a < 8) && (b >= 0 && b < 8))
	{
		if (allFigures[a][b]->Symbol != ' ') {
			if (allFigures[a][b]->isWhite != isWhite) {
				if (isStraight && (allFigures[a][b]->Symbol == 'Q' || allFigures[a][b]->Symbol == 'C')) {
					return true;
				}
				if (!isStraight) {
					if (allFigures[a][b]->Symbol == 'Q' || allFigures[a][b]->Symbol == 'B') {
						return true;
					}
				}
			}
			return false;
		}
		a += yDirection;
		b += xDirection;
	}
	return false;
}

bool King::ifCanGo(Point figureCoords, Point newCoords,
	List<List<Figure*>> allFigures, bool isWhite, List<Point*> Kings, bool fromKingMethode)
{
	if (fromKingMethode) {
		bool var = !isWhite;
		if ((abs(figureCoords.a - newCoords.a) > 1 &&
			abs(figureCoords.b - newCoords.b) > 1)) {
			return false;
		}
		if (allFigures[newCoords.a][newCoords.b]->Symbol != ' ') {
			if (allFigures[newCoords.a][newCoords.b]->isWhite == isWhite)
			{
				return false;
			}
		}
		if ((abs(Kings[var]->a - newCoords.a) < 2 &&
			abs(Kings[var]->b - newCoords.b) < 2)) {
			return false;
		}
	}

	int pawnDirection;
	if (isWhite == true) {
		pawnDirection = -1;
	}
	else
	{
		pawnDirection = 1;
	}

	if (newCoords.b != 0)
	{
		
		if (allFigures[newCoords.a + pawnDirection][newCoords.b - 1]->Symbol == 'P' &&
			isWhite != allFigures[newCoords.a + pawnDirection][newCoords.b - 1]->isWhite)
		{
			return false;
		}
	}
	if (newCoords.b != 7)
	{
		if (allFigures[newCoords.a + pawnDirection][newCoords.b + 1]->Symbol == 'P' &&
			isWhite != allFigures[newCoords.a + pawnDirection][newCoords.b + 1]->isWhite)
		{
			return false;
		}
	}


	for (int i = 0; i < possibleHorse.size(); i++) 
	{
		if (newCoords.a + possibleHorse[i].first > 7 || newCoords.a + possibleHorse[i].first < 0)
		{
			continue;
		}
		if (newCoords.b + possibleHorse[i].second > 7 || newCoords.b + possibleHorse[i].second < 0)
		{
			continue;
		}
		if (allFigures[newCoords.a + possibleHorse[i].first][newCoords.b + possibleHorse[i].second]->Symbol == 'H'
			&& allFigures[newCoords.a + possibleHorse[i].first][newCoords.b + possibleHorse[i].second]->isWhite != isWhite) {
			return false;
		}
	}


	for (int i = 0; i < possibleDirections.size(); i++)
	{
		if (ifDirectСheck(newCoords, allFigures, isWhite, possibleDirections[i].first, possibleDirections[i].second))
		{
			return false;
		}
	}
	return true;
}

bool King::KingsSafety(Point figureCoords, Point newCoords,
	List<List<Figure*>> allFigures, bool isWhite, List<Point*> Kings)
{
	int a = figureCoords.a;
	int b = figureCoords.b;
	int signForHorizontal;
	int signForVertical;
	int i;
	
	if (Kings[isWhite]->a == figureCoords.a || Kings[isWhite]->b == figureCoords.b) {
		if (Kings[isWhite]->b > figureCoords.b) {
			signForHorizontal = -1;
			i = figureCoords.b;
		}
		else if (Kings[isWhite]->a == figureCoords.a)
		{
			signForHorizontal = 1;
			i = figureCoords.b;
		}
		if (Kings[isWhite]->a > figureCoords.a) {
			signForHorizontal = -1;
			i = figureCoords.a;
		}
		else if (Kings[isWhite]->b == figureCoords.b)
		{
			signForHorizontal = 1;
			i = figureCoords.a;
		}
		i -= signForHorizontal;
		for (i; i < 8 && i >= 0; i -= signForHorizontal)
		{
			if (Kings[isWhite]->a == figureCoords.a) {
				b = i;
			}
			else
			{
				a = i;
			}
			if (a == newCoords.a && b == newCoords.b) {
				return true;
			}
			if (allFigures[a][b]->Symbol != ' ') {
				if (allFigures[a][b]->Symbol != 'K') {
					return true;
				}
				if (allFigures[a][b]->Symbol == 'K' && allFigures[a][b]->isWhite != isWhite) {
					return true;
				}
				break;
			}
		}
		if (Kings[isWhite]->b > figureCoords.b) {
			i = figureCoords.b;
		}
		else if(Kings[isWhite]->a == figureCoords.a)
		{
			i = figureCoords.b;
		}
		if (Kings[isWhite]->a > figureCoords.a) {
			i = figureCoords.a;
		}
		else if (Kings[isWhite]->b == figureCoords.b)
		{
			i = figureCoords.a;
		}
		i += signForHorizontal;
		for (i; i < 8 && i >= 0; i += signForHorizontal)
		{
			if (Kings[isWhite]->a == figureCoords.a) {
				b = i;
			}
			else
			{
				a = i;
			}
			if (a == newCoords.a && b == newCoords.b) {
				return true;
			}
			if (allFigures[a][b]->Symbol != ' ') {
				if(allFigures[a][b]->isWhite == isWhite) 
				{
					return true;
				}
				if (allFigures[a][b]->Symbol == 'Q' || allFigures[a][b]->Symbol == 'C')
				{
					return false;
				}
				break;
			}
		}
	}
	else if (Kings[isWhite]->a != figureCoords.a || Kings[isWhite]->b != figureCoords.b) {
		a = figureCoords.a;
		b = figureCoords.b;
		if (figureCoords.a > Kings[isWhite]->a) {
			signForVertical = 1;
		}
		else
		{
			signForVertical = -1;
		}
		if (figureCoords.b > Kings[isWhite]->b)
		{
			signForHorizontal = +1;
		}
		else
		{
			signForHorizontal = -1;
		}
		a -= signForVertical;
		b -= signForHorizontal;
		while (((a >= 0 && a < 8) && (b >= 0 && b < 8)) && allFigures[a][b]->Symbol == ' ')
		{
			a -= signForVertical;
			b -= signForHorizontal;
			if (a == newCoords.a && b == newCoords.b) {
				return true;
			}
		}
		if((a < 0 || a >= 8) || (b < 0 || b >= 8))
		{
			return true;
		}
		if (allFigures[a][b]->Symbol != 'K') {
			return true;
		}
		if (allFigures[a][b]->isWhite != isWhite) {
			return true;
		}

		a = figureCoords.a + signForVertical;
		b = figureCoords.b + signForHorizontal;
		while (allFigures[a][b]->Symbol == ' ' && ((a >= 0 && a < 8) && (b >= 0 && b < 8)))
		{
			a += signForVertical;
			b += signForHorizontal;
			if (a == newCoords.a && b == newCoords.b) {
				return true;
			}
		}
		if (allFigures[a][b]->isWhite == isWhite) {
			return true;
		}
		if (allFigures[a][b]->Symbol == 'Q' ||
			allFigures[a][b]->Symbol == 'B')
		{
			return false;
		}
		return true;
	}
	return true;
}
