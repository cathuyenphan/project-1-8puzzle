#include <iostream>
#include <queue>
#include <vector>
#include <stack>

#include "puzzle.h"
#include "A_heuristics.h"
#include "operators.h"

using namespace std;

void printPuzzle(vector<vector<int> > puzzle);
void solvePuzzle(vector<vector<int> > puzzle, int algoritm);
vector<node> expandNode(node* cur);

vector<node> visited;
priority_queue <node, vector<node>, cheaperNode> priority; 

int main()  {

    // default puzzle values
    vector<int> values = {1,0,3,4,2,6,7,5,8}; 

    int input = 0;

    cout << "Welcome to 862283047 8-puzzle solver." << endl;
    cout << "Type \"1\" to use a default puzzle, or \"2\" to enter your own puzzle." << endl;
    cin >> input;

    vector<vector<int> > puzzle(3, vector<int>(3));

    int index = 0; 

    if(input == 1)  {                           
        index = 0; 

        for(int i = 0; i < 3; i++)  {
            for(int j = 0; j < 3; j++)  {
                puzzle[i][j] = values[index];
                index++;
            }
        }
    }
    if(input == 2)  {

        int index = 0;

        cout << "Enter your puzzle, use a zero to represent the blank" << endl;
        cout << "Enter the first row, use space or tabs between numbers" << endl;
        cin >> values[0] >> values[1] >> values[2];

        cout << "Enter the second row, use space or tabs between numbers" << endl;
        cin >> values[3] >> values[4] >> values[5];

        cout << "Enter the third row, use space or tabs between numbers" << endl;
        cin >> values[6] >> values[7] >> values[8];

        for(int i = 0; i < 3; i++)  {
            for(int j = 0; j < 3; j++)  {
                puzzle[i][j] = values[index];
                index++;
            }
        }

    }


    node* initial = new node(puzzle);
    vector<node> children = expandNode(initial);
    for(int i = 0; i < children.size(); i++)    {
        cout << "child node " << i << ":" << endl;
        printPuzzle(children[i].puzzle);
        cout << endl;
    }

}

void printPuzzle(vector<vector<int> > puzzle)    {

    for(int i = 0; i < 3; i++)  {
        for(int j = 0; j < 3; j++)  {
            cout << puzzle[i][j] << " ";
        }
        cout << endl;
    }
}

vector<node> expandNode(node* current)  {

    vector<node> children;

    node* c1 = new node(moveDown(current->puzzle));
    if(c1->puzzle != current->puzzle)   {                       // make sure shift changes the puzzle
        children.push_back(*c1);
        c1->costToNode++;
    }

    node* c2 = new node(moveUp(current->puzzle));
    if(c2->puzzle != current->puzzle)   {
        children.push_back(*c2);
        c2->costToNode++;
    }

    node* c3 = new node(moveRight(current->puzzle));
    if(c3->puzzle != current->puzzle)   {
        children.push_back(*c3);
        c3->costToNode++;
    }

    node* c4 = new node(moveLeft(current->puzzle));
    if(c4->puzzle != current->puzzle) {
        children.push_back(*c4);
        c4->costToNode++;
    }

    return children;                            // returns set of children expanded from the current node

}

void solvePuzzle(vector<vector<int> > puzzle, int algorthm)   {

    int count = 0;                              // keeps track of the number of nodes expanded until solution is found
    int maxNodes = 0;                           // keeps track of the max number of nodes in the queue at any time
    int depth = 0;                              // keeps track of depth of search tree

    node initial(puzzle);
    visited.push_back(initial);               // puts initial state into search tree
    priority.push(initial);

    while(priority.size() > 0)  {

        node *current = new node(priority.top());        // next node to expand is the node on the top of priority queue

        if(priority.top().puzzle == goalState)  {
            cout << "Goal!!!" << endl;
            // print final message here...
            break;
        }
        else    { 
            count++;                                    // going to expand this node, so update count                         

            visited.push_back(priority.top());          // already checked this node -> push into visited nodes
            if(priority.size() > maxNodes)  {           // update max nodes in queue
                maxNodes = priority.size();
            }           
            priority.pop();         

            // create children nodes



        }

    }
    
}