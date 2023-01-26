#ifndef Pawn_h
#define Pawn_h

#include "Figure.h" 
#include "Point.h" 
class Pawn : public Figure
{
public:

	Pawn(Point coords, bool isWhite);
	Pawn();


	void pawnConvertation(Point newCoords,
		List<List<Figure*>> allFigures, bool isWhite);


	bool isKingSafe(Point figureCoords, Point newCoords, 
		List<List<Figure*>> allFigures,
		bool isWhite, List<Point*> Kings);


	bool ifCanGo(Point figureCoords, Point newCoords, 
		List<List<Figure*>> allFigures, bool isWhite,
		List<Point*> Kings);
};

#endif // !Pawn_h