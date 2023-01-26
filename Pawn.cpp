#include "Pawn.h"
#include "Board.h"
#include "iostream"
#include "Element.h"

Pawn::Pawn(Point coords, bool isWhite) : Figure('P', coords, isWhite)
{

}

Pawn::Pawn()
{

}

bool Pawn::isKingSafe(Point figureCoords, Point newCoords,
	List<List<Figure*>> allFigures, bool isWhite, List<Point*> Kings)
{
	int signForHorizontal;
	int signForVertical;
	if (figureCoords.a == newCoords.a) {
		if (abs(Kings[isWhite]->a - figureCoords.a) == abs(Kings[isWhite]->b - figureCoords.b)) {
			int a = figureCoords.a;
			int b = figureCoords.b;
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
			while (allFigures[a][b]->Symbol == ' ' && 
				((a >= 0 && a < 8) && (b >= 0 && b < 8)))
			{
				a -= signForVertical; 
				b -= signForHorizontal;
			}
			if (allFigures[a][b]->Symbol != 'K') {
				return true;
			}
			a = figureCoords.a;
			b = figureCoords.b;
			while (allFigures[a][b]->Symbol == ' ' && ((a >= 0 && a < 8) && (b >= 0 && b < 8)))
			{
				a += signForVertical;
				b += signForHorizontal;
			}
			if (allFigures[a][b]->isWhite != isWhite &&
				(allFigures[a][b]->Symbol == 'Q' || allFigures[a][b]->Symbol == 'B')) {
				return false;
			}
		}
	}
	if (newCoords.b - figureCoords.b == 1
		|| newCoords.b - figureCoords.b == -1) {
		int a = figureCoords.a;
		int b = figureCoords.b;
		if (Kings[isWhite]->b == figureCoords.b) {

			if (Kings[isWhite]->b > figureCoords.b) {
				signForHorizontal = -1;
			}
			else
			{
				signForHorizontal = 1;
			}
			while (allFigures[a][b]->Symbol == ' ' && (b >= 0 && b < 8))
			{
				b -= signForHorizontal;
			}
			if (allFigures[a][b]->Symbol != 'K') {
				return true;
			}
			for (int i = figureCoords.b; i < 8 || i >= 0; i += signForHorizontal)
			{
				if (allFigures[a][b]->Symbol != ' ') {
					if (allFigures[a][b]->Symbol == 'Q' || allFigures[a][b]->Symbol == 'C') {
						return false;
					}
					break;
				}
			}
		}
		else
		{
			if (newCoords.b - figureCoords.b == 1 && figureCoords.b > Kings[isWhite]->b)
			{
				return true;
			}
			if (newCoords.b - figureCoords.b == -1 && figureCoords.b < Kings[isWhite]->b)
			{
				return true;
			}
			if (figureCoords.a > Kings[isWhite]->a) {
				signForVertical = 1;
			}
			else
			{
				signForVertical = -1;
			}
			while (allFigures[a][b]->Symbol == ' ' && ((a >= 0 && a < 8) && (b >= 0 && b < 8)))
			{
				a += signForVertical;
				b += signForHorizontal;
			}
		}
	}

	return true;
}

void Pawn::pawnConvertation(Point newCoords, 
	List<List<Figure*>> allFigures, bool isWhite)
{
	if (isWhite && newCoords.a != 0) {
		return;
	}
	if (!isWhite && newCoords.a != 7) {
		return;
	}

	char f;
	while (true)
	{
		std::cout << "Choose figure to convert\n";
		std::cin >> f;
		if (f == 'C' || f == 'B' || f == 'H' || f == 'Q')
		{
			return;
		}
		std::cout << "Wrong coordinate\n";
	}
}

bool Pawn::ifCanGo(Point figureCoords, Point newCoords,
	List<List<Figure*>> allFigures, bool isWhite, List<Point*> Kings)
{
	if (!isKingSafe(figureCoords, newCoords, allFigures, isWhite, Kings)) {
		return false;
	}


	if (figureCoords.a == 1 || figureCoords.a == 6) {
		if (abs(newCoords.a - figureCoords.a) == 2 && allFigures[newCoords.a][newCoords.b]->Symbol == ' ') {
			return true;
		}
	}
	int output;
	switch (isWhite)
	{
	case false: output = 1; break;
	case true: output = -1; break;
	}
	if(newCoords.a - figureCoords.a != output) {
		std::cout << "Wrong coordinate";
		return false;
	}
	// FIX HERE
	//if(!(newCoords.b == figureCoords.b 
	//	|| newCoords.b - figureCoords.b == 1 
	//	|| newCoords.b - figureCoords.b == -1))
	//{
	//	std::cout << "Wrong coordinate";
	//	return false;
	//}
	if (newCoords.b == figureCoords.b &&
		allFigures[newCoords.a][newCoords.b]->Symbol == ' ')
	{
		pawnConvertation(newCoords, allFigures, isWhite);
		return true;
	}
	if (abs(newCoords.b - figureCoords.b) == 1 
		&& allFigures[newCoords.a][newCoords.b]->Symbol != ' ')
	{
		if (allFigures[newCoords.a][newCoords.b]->isWhite != isWhite) {
			pawnConvertation(newCoords, allFigures, isWhite);
			return true;
		}
	}
	std::cout << "Wrong coordinate";
	return false;
}