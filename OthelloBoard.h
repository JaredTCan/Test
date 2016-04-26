#ifndef OTHELLO_H
#define OTHELLO_H
#include <string>
#include <vector>
#include <iostream>
struct solveList
{
    int dx;
    int dy;
    int score;
    solveList* next;

    solveList(int x, int y, int s)
    {
        dx = x;
        dy = y;
        score =s;
    }
};
class OthelloBoard
{
    public:
        OthelloBoard();
        int getColorAt(int x, int y);
        void setColorAt(int x, int y, int color);
        void printBoard();
        void makeMove(int x, int y, int color);
        int scoreMove(int x, int y, int color);
        bool checkGame();
        int scoreGame();
        bool validMove(int x, int y, int color);
    private:
        bool validMove(int x, int y, int color, solveList* adj);
        int boardSize = 8;
        int boardArray [8][8];
};

#endif // OTHELLO

