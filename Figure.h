#ifndef Figure_h
#define Figure_h
#include "Point.h"
#include "List.h"

class Figure
{
public:
    char Symbol;
    int Row;
    int Column;
    bool isWhite;
    virtual void Step(List<List<Figure>>* allFigures, int newRow, int newColumn);
    Figure(char symbol, Point coords, bool isWhite);
    Figure(char symbol, Point coords);
    Figure();
    template<class T>
    T* CastTo()
    {
        return static_cast<T*>(this);
    }
};
#endif

