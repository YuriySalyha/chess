#include "Figure.h"

Figure::Figure(char symbol, Point coords, bool isWhite)
{
    Symbol = symbol;
    Row = coords.a;
    Column = coords.b;
    this->isWhite = isWhite;
}
Figure::Figure(char symbol, Point coords)
{
    Symbol = symbol;
}
Figure::Figure()
{

}
void Figure::Step(List<List<Figure>>* allFigures, int newRow, int newColumn)
{

}
