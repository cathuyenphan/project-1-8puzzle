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

    int algorithm;
    cout << "choose algorithm" << endl;
    cin >> algorithm;

    node* initial = new node(puzzle);
    vector<node> children = expandNode(initial);
    for(int i = 0; i < children.size(); i++)    {
        cout << "child " << i << "'s: " << endl;

        if(algorithm == 2)  {
            cout << "state: " << endl;
            printPuzzle(children[i].puzzle);                                           // misplaced tile heuristic
            children[i].h_n = misplacedTile(children[i].puzzle);
            cout << "h(n) = " << children[i].h_n << " ";
        }
        if(algorithm == 3)  {       
            cout << "state: " << endl;
            printPuzzle(children[i].puzzle);                                      // euclidean distance heuristic
            children[i].h_n = euclideanDistance(children[i].puzzle);
            cout << "h(n) = " << children[i].h_n << " ";
        }

        children[i].f_n = children[i].g_n + children[i].h_n; 
        cout << "f(n) = " << children[i].f_n << " " << endl;                  
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
        c1->g_n++;
        children.push_back(*c1);
        
    }

    node* c2 = new node(moveUp(current->puzzle));
    if(c2->puzzle != current->puzzle)   {
        c2->g_n++;
        children.push_back(*c2);
    }

    node* c3 = new node(moveRight(current->puzzle));
    if(c3->puzzle != current->puzzle)   {
        c3->g_n++;
        children.push_back(*c3);
    }

    node* c4 = new node(moveLeft(current->puzzle));
    if(c4->puzzle != current->puzzle) {
        c4->g_n++;
        children.push_back(*c4);
    }

    return children;                            // returns set of children expanded from the current node

}

void solvePuzzle(vector<vector<int> > puzzle, int algorithm)   {

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
            vector<node> children = expandNode(current);

            for(int i = 0; i < children.size(); i++)    {
                if(algorithm == 2)  {                   // misplaced tile heuristic
                    children[i].h_n = misplacedTile(children[i].puzzle);
                }
                if(algorithm == 3)  {                   // euclidean distance heuristic
                    children[i].h_n = euclideanDistance(children[i].puzzle);
                }

                children[i].f_n = children[i].g_n + children[i].h_n;                     
            }

        }

    }
    
}