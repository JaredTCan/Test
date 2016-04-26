/*Jared
 */

#include<iostream>
#include "OthelloBoard.h"

using namespace std;

static int EMPTY = 0;
static int BLACK = 1;
static int WHITE = 2;

void AITurn(OthelloBoard* board)
{
    solveList *aiList = NULL;
    for(int y = 0; y < 8; y++)
    {
        for(int x = 0; x < 8; x++)
        {
            solveList*ptr = new solveList(x,y,board->scoreMove(x,y,WHITE));
            ptr->next = aiList;
            aiList = ptr;
        }
    }
    solveList *top = aiList;
    while(aiList!=NULL)
    {
        if(top->score < aiList->score)
        {
            top = aiList;
        }
        aiList = aiList->next;
    }
    board->makeMove(top->dx,top->dy,WHITE);
}

int main(int argv, char* argc[])
{
    OthelloBoard *board = new OthelloBoard();
    //board->printBoard();

    while(board->checkGame())
    {
        board->printBoard();
        cout<<"Player's turn"<<endl;
        cout<<"enter x pos"<<endl;
        int x;
        cin >> x;
        cout<<"enter y pos"<<endl;
        int y;
        cin >> y;

        if(board->validMove(x,y,BLACK))
        {
            board->makeMove(x,y,BLACK);
        }
        else
        {
            cout<<"Invalid Move"<<endl;
        }

        board->printBoard();
        cout<<"AI's Turn"<<endl;
        cout<<"Thinking..."<<endl;
        AITurn(board);
        cout<<"Done, press enter to continue"<<endl;

    }
    board->printBoard();
    int result = board->scoreGame();
    if(result < 0)
    {
        cout<<"You Win!!"<<endl;
    }
    if(result = 0)
    {
        cout<<"Tie"<<endl;
    }
    if(result > 0)
    {
        cout<<"you lose"<<endl;
    }
}
