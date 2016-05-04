
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
            while(!board->validMove(x,y,BLACK)){
                cout<<"Invalid Move"<<endl;
                cout<<"Or type x=9 y=9 to give up"<<endl;
                cout<<"enter x pos"<<endl;
                int x;
                cin >> x;
                cout<<"enter y pos"<<endl;
                int y;
                cin >> y;
                if(x==9 && y==9){
                    cout<<"you lose"<<endl;
                    return 0;
                }
            }
        }

        board->printBoard();
        cout<<"AI's Turn"<<endl;
        cout<<"Thinking..."<<endl;
        AITurn(board);
        cout<<"Done, press enter to continue"<<endl;
        cin.ignore();
        cin.get();

    }
    board->printBoard();
    int result = board->scoreGame();
    if(result < 0)
    {
        cout<<"You Win!!"<<endl;
        return 0;
    }
    if(result == 0)
    {
        cout<<"Tie"<<endl;
        return 0;
    }
    if(result > 0)
    {
        cout<<"you lose"<<endl;
        return 0;
    }
}
