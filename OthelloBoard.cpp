/* Jared C
 * E = 0
 * B = 1
 * W = 2
 */

#include "OthelloBoard.h"
#include <iostream>
#include <queue>

using namespace std;

static int EMPTY = 0;
static int BLACK = 1;
static int WHITE = 2;

OthelloBoard::OthelloBoard()
{
    int middle = boardSize/2;
    boardArray[middle][middle]    = WHITE;
    boardArray[middle-1][middle-1]= WHITE;
    boardArray[middle-1][middle]  = BLACK;
    boardArray[middle][middle-1]  = BLACK;
}

void OthelloBoard::printBoard()
{
    for(int y = 0; y < boardSize; y++)
    {
        for(int c = 0; c<boardSize; c++)
        {
            cout<<"|---";
        }
        cout<<"|"<<endl;
        for(int x=0; x < boardSize; x++)
        {
            cout<<"| ";
            if(boardArray[x][y]==EMPTY)
            {
                cout<<"  ";
            }
            else if(boardArray[x][y]==BLACK)
            {
                cout<<"B ";
            }
            else
            {
                cout<<"W ";
            }
        }
        cout<<"|"<<endl;
    }
    for(int c = 0; c<boardSize; c++)
    {
        cout<"|---";
    }
    cout<<"|"<<endl;
}

int OthelloBoard::getColorAt(int x, int y)
{
    if(x < boardSize && y < boardSize)
    {
        return boardArray[x][y];
    }
    cout<<"Improper coordinates"<<endl;
    return -1;
}

void OthelloBoard::setColorAt(int x, int y, int color)
{
    if(x < boardSize && y < boardSize)
    {
        boardArray[x][y] = color;
        return;
    }
    cout<<"Improper coordinates"<<endl;
}

bool OthelloBoard::validMove(int x, int y, int color)
{
    solveList *adj = new solveList(0,0,0);
    return validMove(x,y,color,adj);
}
bool OthelloBoard::validMove(int x, int y, int color, solveList* adj)
{
    //cout<<"Valid Move"<<endl;
    int opp;
    if(color == BLACK)
    {
        opp = WHITE;
    }
    else
    {
        opp = BLACK;
    }


    if(boardArray[x][y] != EMPTY)
    {
        return false;
    }

    queue<int> xQueue;
    queue<int> yQueue;
    bool hasAdjColor = false;
    for(int c = -1; c < 2; c++)
    {
        if(y+c > -1 && y+c < boardSize)
        {
            for(int d = -1; d < 2; d++)
            {
                if(x+d > -1 && x+d < boardSize)
                {
                    if(boardArray[x+d][y+c] == opp)
                    {
                        hasAdjColor = true;
                        xQueue.push(d);
                        yQueue.push(c);
                    }
                }
            }
        }
    }
    if(!hasAdjColor)
    {
        return false;
    }

    bool isValid = false;
    //cout<<xQueue.size()<<endl;
    while(!xQueue.empty())
    {
        int tx = x;
        int ty = y;
        int dx = xQueue.front();
        int dy = yQueue.front();
        xQueue.pop();
        yQueue.pop();

        tx+=dx;
        ty+=dy;
        int score = 0;
        //cout<<dx<<" "<<dy<<endl;
        while((tx > -1 && tx < boardSize)&&(ty>-1&&ty<boardSize))
        {
            if(boardArray[tx][ty] == color)
            {
                solveList* ptr = new solveList(dx, dy, score);
                adj->next = ptr;
                //cout<<"WTF?"<<endl;
                adj = adj->next;
                isValid = true;
                adj->next = NULL;

                break;
            }
            if(boardArray[tx][ty] == EMPTY)
            {
                break;
            }
            score++;
            tx+=dx;
            ty+=dy;
            //cout<<"here?"<<endl;
        }
    }
    return isValid;
}


int OthelloBoard::scoreMove(int x, int y, int color)
{
    solveList* adj = new solveList(0,0,0);
    int n = 0;
    if(validMove(x,y,color,adj))
    {
        while(adj != NULL)
        {

            //cout<<adj->dx<<" "<<adj->dy<<endl;
            //cout<<adj->score<<endl;
            n += adj->score;
            adj = adj->next;
        }
    }
    else
    {
        return 0;
    }
    return n;
}

void OthelloBoard::makeMove(int x, int y, int color)
{
    solveList* adj = new solveList(0,0,0);
    if(validMove(x,y,color,adj))
    {
        //cout<<"/validMove"<<endl;
        setColorAt(x,y,color);
        while(adj->next != NULL)
        {
            adj = adj->next;
            for(int c = 1; c <= adj->score; c++)
            {
                setColorAt(x+(adj->dx * c), y+(adj->dy * c), color);
            }
        }
    }
}

bool OthelloBoard::checkGame()
{
    for(int y = 0; y < boardSize; y++)
    {
        for(int x = 0; x < boardSize; x++)
        {
            if(boardArray[x][y] == EMPTY)
            {
                return true;
            }
        }
    }
    return false;
}

int OthelloBoard::scoreGame()
{
    int score = 0;
    int bScore = 0;
    int wScore = 0;
    for(int y = 0; y < boardSize; y++)
    {
        for(int x = 0; x < boardSize; x++)
        {
            if(boardArray[x][y] == WHITE)
            {
                score++;
                wScore++;
            }
            if(boardArray[x][y] == BLACK)
            {
                score--;
                bScore++;
            }
        }
    }
    cout<<"Black: "<<bScore<<endl;
    cout<<"White: "<<wScore<<endl;
    return score;
}
