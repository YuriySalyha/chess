#ifndef Board_h
#define Board_h
#include "List.h"
#include "Figure.h"
#include <iostream>
#include <vector>


class Board{
private:
    const int CellSize = 3;
    const char BlackCellSymbol = '#';
    const char WhiteCellSymbol = ' ';
public:
    List<Point*> Kings;
    List<List<Figure*>> allFigures;
    //Player* player1;
    //Player* player2;
    void CreateFigures();
    void InitBoard();
    void RefreshBoard();
    bool Step(Point figureCoords, Point newCoords, bool isWhite);
    bool IsCheck(Point figureCoords, Point newCoords, 
        List<List<Figure*>> allFigures, bool isWhite, List<Point*> Kings);
    bool IsСheckmate();
    char checkInput(char sign);
    void pawnConvert(char sign, Point coords);
    ~Board()
    {
        std::cout << "Destructed\n";
    }
    void startGame();
    std::vector<char> letters = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' };
    std::vector<char> figLetters = { 'C', 'B', 'Q', 'H' };
};
#endif