#include "Board.h"
#include <iostream>
#include "Pawn.h"
#include "Castle.h"
#include "Horse.h"
#include "Empty.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

void Board::startGame()
{
    bool whiteTurn = true;
    Point figureCoords;
    Point newFigureCoords;
    char inputLetter;
    bool isPossibleCheckmate = false;
    InitBoard();
    while (true)
    {
        figureCoords.b = 10;
        newFigureCoords.b = 10;
        if (whiteTurn) {
            std::cout << "Its white turn!\n";
        }
        else
        {
            std::cout << "Its black turn!\n";
        }

        std::cout << "Enter a number: ";
        std::cin >> figureCoords.a;
        std::cout << "Enter a letter: ";
        std::cin >> inputLetter;

        figureCoords.a = abs(figureCoords.a - 8);
        for (int i = 0; i < letters.size(); i++)
        {
            if (inputLetter == letters[i]) {
                figureCoords.b = i;
                break;
            }
        }

        std::cout << "Enter a new number coordinate: ";
        std::cin >> newFigureCoords.a;
        std::cout << "Enter a new letter coordinate: ";
        std::cin >> inputLetter;

        newFigureCoords.a = abs(newFigureCoords.a - 8);
        for (int i = 0; i < letters.size(); i++)
        {
            if (inputLetter == letters[i]) {
                newFigureCoords.b = i;
                break;
            }
        }

        if (figureCoords.b == 10 || (figureCoords.a < 0 || figureCoords.a > 7)) {
            std::cout << "Wrong coordinate\n";
            continue;
        }
        if (newFigureCoords.b == 10 || (newFigureCoords.a < 0 || newFigureCoords.a > 7)) {
            std::cout << "Wrong coordinate\n";
            continue;
        }

        if (allFigures[figureCoords.a][figureCoords.b]->Symbol == ' ') {
            std::cout << "Wrong coordinate\n";
            continue;
        }
        if (allFigures[figureCoords.a][figureCoords.b]->isWhite == true)
        {
            std::cout << "white ";
        }
        if (allFigures[figureCoords.a][figureCoords.b]->isWhite == false) {
            std::cout << " black ";
        }
        if (allFigures[figureCoords.a][figureCoords.b]->isWhite != whiteTurn) {
            std::cout << "Wrong coordinate\n";
            continue;
        }


        if(Step(figureCoords, newFigureCoords, whiteTurn))
        {
            whiteTurn = abs(whiteTurn - 1);
            RefreshBoard();
        }
        else
        {
            std::cout<< "Wrong coordinate\n";
        }


        if (isPossibleCheckmate) {
            newFigureCoords.a = Kings[!whiteTurn]->a;
            newFigureCoords.b = Kings[!whiteTurn]->b;
            if (IsCheck(figureCoords, newFigureCoords, allFigures, !whiteTurn, Kings))
            {
                std::cout<< "Checkmate to ";
                switch (!whiteTurn)
                {
                case true: std::cout << "white\n"; break;
                case false: std::cout << "black\n"; break;
                }
                return;
            }
            else
            {
                isPossibleCheckmate = false;
            }
        }
        newFigureCoords.a = Kings[whiteTurn]->a;
        newFigureCoords.b = Kings[whiteTurn]->b;
        if (IsCheck(figureCoords, newFigureCoords, allFigures, whiteTurn, Kings)) {
            isPossibleCheckmate = true;
            std::cout << "Check to ";
            switch (whiteTurn)
            {
            case true: std::cout << "white\n"; break;
            case false: std::cout << "black\n"; break;
            }
        }
        std::cout << Kings[whiteTurn]->a << ", " << Kings[whiteTurn]->b << ", " << int(whiteTurn) << "\n";
        std::cout << Kings[!whiteTurn]->a << ", " << Kings[!whiteTurn]->b << ", " << int(!whiteTurn) << "\n";
    }
}

void Board::CreateFigures()
{
    List<Figure*> BlackMainFigures;
    BlackMainFigures.add(new Castle(Point(0, 0), false));
    BlackMainFigures.add(new Horse(Point(0, 1), false));
    BlackMainFigures.add(new Bishop(Point(0, 2), false));
    BlackMainFigures.add(new Queen(Point(0, 3), false));
    BlackMainFigures.add(new King(Point(0, 4), false));
    Kings.add(new Point(0, 4));
    BlackMainFigures.add(new Bishop(Point(0, 5), false));
    BlackMainFigures.add(new Horse(Point(0, 6), false));
    BlackMainFigures.add(new Castle(Point(0, 7), false));
    allFigures.add(BlackMainFigures);
    List<Figure*> BlackPawn;
    for (int i = 0; i < 8; i++) {
        Point topPowCoord(1, i);
        BlackPawn.add(new Pawn(topPowCoord, false));
    }
    allFigures.add(BlackPawn);
    for (int j = 2; j < 6; j++) {
        List<Figure*> emptyRow;
        for (int i = 0; i < 8; i++) {
            Point emptyCoord(j, i);
            emptyRow.add(new Empty(emptyCoord));
        }
        allFigures.add(emptyRow);
    }
    List<Figure*> WhitePawn;
    for (int i = 0; i < 8; i++) {
        Point topPowCoord(6, i);
        WhitePawn.add(new Pawn(topPowCoord, true));
    }
    allFigures.add(WhitePawn);
    List<Figure*> WhiteMainFigures;
    WhiteMainFigures.add(new Castle(Point(7, 0), true));
    WhiteMainFigures.add(new Horse(Point(7, 1), true));
    WhiteMainFigures.add(new Bishop(Point(7, 2), true));
    WhiteMainFigures.add(new Queen(Point(7, 3), true));
    WhiteMainFigures.add(new King(Point(7, 4), true));
    Kings.add(new Point(7, 4));
    WhiteMainFigures.add(new Bishop(Point(7, 5), true));
    WhiteMainFigures.add(new Horse(Point(7, 6), true));
    WhiteMainFigures.add(new Castle(Point(7, 7), true));
    allFigures.add(WhiteMainFigures);
}
void Board::InitBoard()
{
    CreateFigures();
    RefreshBoard();

}
void Board::RefreshBoard()
{
    int number = 8;
    std::cout << "\n ---------------------------------------------------------\n |    ";
    for (int i = 0; i < 8; i++)
    {
        std::cout << "  " << letters[i] << "   ";
    }
    std::cout << "   |\n";
    std::cout << " |   -------------------------------------------------   |\n";
    for (int row = 0; row < 8; row++)
    {
        for (int cellRow = 0; cellRow < CellSize; cellRow++)
        {
            std::cout << " | ";
            if (CellSize / 2 == cellRow)
            {
                std::cout << number << " |";
            }
            else
            {
                std::cout << "  |";
            }
            for (int column = 0; column < 8; column++)
            {
                for (int cellColumn = 0; cellColumn < CellSize; cellColumn++)
                {
                    char symbol = ((row + column) % 2 == 0)
                        ? WhiteCellSymbol : BlackCellSymbol;
                    if (CellSize / 2 == cellRow && CellSize / 2 == cellColumn)
                    {
                        if (row < allFigures.len() && allFigures[row][column]->Symbol != ' ')
                        {
                            std::cout << allFigures[row][column]->Symbol << " ";
                        }
                        else
                        {
                            std::cout << symbol << " ";

                        }
                    }
                    else {
                        if (column == 7 && cellColumn == 2) {
                            std::cout << symbol;
                        }
                        else
                        {
                            std::cout << symbol << " ";
                        }
                    }
                }
            }
            if (CellSize / 2 == cellRow)
            {
                std::cout << "| " << number;
                number--;
            }
            else
            {
                std::cout << "|  ";
            }
            std::cout << " |\n";
        }
    }
    std::cout << " |   -------------------------------------------------   |\n";
    std::cout << " |    ";
    for (int i = 0; i < 8; i++)
    {
        std::cout << "  " << letters[i] << "   ";
    }
    std::cout << "   |\n";
    std::cout << " ---------------------------------------------------------\n";
}

char Board::checkInput(char sign)
{
    for (int i = 0; i < figLetters.size(); i++)
    {
        if (sign == figLetters[i]) {
            return sign;
        }
    }
    return '*';
}

void Board::pawnConvert(char sign, Point coords)
{
    switch (sign)
    {
    case 'C': allFigures[coords.a][coords.b]->CastTo<Castle>()->Symbol = 'C'; break;
    case 'H': allFigures[coords.a][coords.b]->CastTo<Horse>()->Symbol = 'H'; break;
    case 'B': allFigures[coords.a][coords.b]->CastTo<Bishop>()->Symbol = 'B'; break;
    case 'Q': allFigures[coords.a][coords.b]->CastTo<Queen>()->Symbol = 'Q'; break;
    }
}

bool Board::Step(Point figureCoords, Point newCoords, bool isWhite)
{
    Pawn pawn;
    Castle castle;
    Horse horse;
    Bishop bishop;
    Queen queen;
    King king;
    switch (allFigures[figureCoords.a][figureCoords.b]->Symbol)
    {
    case 'P': 
        //allFigures[][]->CastTo<Pawn>().Step()
        if (pawn.ifCanGo(figureCoords, newCoords, allFigures, isWhite, Kings))
    {
        allFigures[newCoords.a][newCoords.b]->CastTo<Pawn>()->Symbol = 'P';
        allFigures[newCoords.a][newCoords.b]->CastTo<Pawn>()->isWhite = isWhite;
        allFigures[figureCoords.a][figureCoords.b]->CastTo<Empty>()->Symbol = ' ';
        //allFigures[figureCoords.a][figureCoords.b]->CastTo<Empty>()->isWhite = ' ';
        if ((newCoords.a == 0 && isWhite == true)
            ||( newCoords.a == 7 && isWhite == false))
        {
            char fig;
            do {
                std::cout << "Chose to what figure convert pawn: ";
                std::cin >> fig;
            } while (checkInput(fig) == '*');
            pawnConvert(fig, newCoords);
        }
        return true;
    }break;

    case 'C': if (castle.ifCanGo(figureCoords, newCoords, allFigures, isWhite, Kings))
    {
        allFigures[newCoords.a][newCoords.b]->CastTo<Castle>()->Symbol = 'C';
        allFigures[newCoords.a][newCoords.b]->CastTo<Castle>()->isWhite = isWhite;
        allFigures[figureCoords.a][figureCoords.b]->CastTo<Empty>()->Symbol = ' ';
        //allFigures[figureCoords.a][figureCoords.b]->CastTo<Empty>()->isWhite = ' ';
        return true;
    } break;

    case 'H': if (horse.ifCanGo(figureCoords, newCoords, allFigures, isWhite, Kings))
    {
        allFigures[newCoords.a][newCoords.b]->CastTo<Horse>()->Symbol = 'H';
        allFigures[newCoords.a][newCoords.b]->CastTo<Horse>()->isWhite = isWhite;
        allFigures[figureCoords.a][figureCoords.b]->CastTo<Empty>()->Symbol = ' ';
        //allFigures[figureCoords.a][figureCoords.b]->CastTo<Empty>()->isWhite = ' ';
        return true;
    } break;

    case 'B': if (bishop.ifCanGo(figureCoords, newCoords, allFigures, isWhite, Kings))
    {
        allFigures[newCoords.a][newCoords.b]->CastTo<Bishop>()->Symbol = 'B';
        allFigures[newCoords.a][newCoords.b]->CastTo<Bishop>()->isWhite = isWhite;
        allFigures[figureCoords.a][figureCoords.b]->CastTo<Empty>()->Symbol = ' ';
        //allFigures[figureCoords.a][figureCoords.b]->CastTo<Empty>()->isWhite = ' ';
        return true;
    } break;

    case 'Q': if (queen.ifCanGo(figureCoords, newCoords, allFigures, isWhite, Kings))
    {
        allFigures[newCoords.a][newCoords.b]->CastTo<Queen>()->Symbol = 'Q';
        allFigures[newCoords.a][newCoords.b]->CastTo<Queen>()->isWhite = isWhite;
        allFigures[figureCoords.a][figureCoords.b]->CastTo<Empty>()->Symbol = ' ';
        //allFigures[figureCoords.a][figureCoords.b]->CastTo<Empty>()->isWhite = ' ';
        return true;
    }break;

    case 'K': if (king.ifCanGo(figureCoords, newCoords, allFigures, isWhite, Kings))
    {
        allFigures[newCoords.a][newCoords.b]->CastTo<King>()->Symbol = 'K';
        allFigures[newCoords.a][newCoords.b]->CastTo<King>()->isWhite = isWhite;
        Kings[isWhite]->a = newCoords.a;
        Kings[isWhite]->b = newCoords.b;
        allFigures[figureCoords.a][figureCoords.b]->CastTo<Empty>()->Symbol = ' ';

        //allFigures[figureCoords.a][figureCoords.b]->CastTo<Empty>()->isWhite = ' ';
        return true;
    }break;
    }
    return false;
}

bool Board::IsCheck(Point figureCoords, Point newCoords, 
    List<List<Figure*>> allFigures, bool isWhite, List<Point*> Kings)
{
    King king;
    if (king.ifCanGo(figureCoords, newCoords, allFigures, 
        isWhite, Kings, false)) {
        return false;
    }
    return true;
}
bool Board::IsСheckmate()
{
    return false;
}