#include <iostream>
#include <queue>
#include <vector>
#include <stack>

#include "puzzle.h"
#include "A_heuristics.h"
#include "operators.h"

using namespace std;

void solvePuzzle(vector<vector<int> > puzzle, int algoritm);

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

    solvePuzzle(puzzle, algorithm);

}

void printPuzzle(vector<vector<int> > puzzle)    {

    for(int i = 0; i < 3; i++)  {
        for(int j = 0; j < 3; j++)  {
            cout << puzzle[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;
}

void traceSolution(node current)    {
    
    node copy = current;
    stack<node> path;
    path.push(copy);

    while(copy.p != NULL)   {
        copy = *copy.p;
        path.push(copy);
    }

    // out of loop means copy store the intitial state of puzzle
    cout << "Expanding state" << endl;
    printPuzzle(copy.puzzle);
    path.pop();

    while(!path.empty())  {
        int g = path.top().g_n;
        int h = path.top().h_n;

        cout << "The best state to expand with g(n) = " << g << " and h(n) = " << h << " is..." << endl;
        printPuzzle(path.top().puzzle);

        path.pop();
    }

}


bool repeatedState(node *current, vector<node> visited)   {
    for(long unsigned int i = 0; i < visited.size(); i++)   {
        if(current->puzzle == visited[i].puzzle) {
            return true;
        }
    }
    return false;
}

void solvePuzzle(vector<vector<int> > puzzle, int algorithm)   {

    int count = 0;                                                      // keeps track of the number of nodes expanded until solution is found
    int maxNodes = 0;                                                   // keeps track of the max number of nodes in the queue at any time
    int depth = 0;                                                      // keeps track of depth of search tree

    node initial(puzzle);
    visited.push_back(initial);                                         // puts initial state into search tree
    priority.push(initial);

    while(priority.size() > 0)  {

        node *current = new node(priority.top());                           // next node to expand is the node on the top of priority queue

        if(priority.top().puzzle == goalState)  {
            depth = current->g_n;

            traceSolution(priority.top());

            cout << endl << "Goal!!!" << endl;
            cout << "To solve this problem the search algorithm needed to expand a total of " << count << " nodes." << endl;
            cout << "The maximum number of nodes in the queue at any one time: " << maxNodes << "." << endl;
            cout << "The depth of the goal node was " << depth << "." << endl;
            
            break;
        }
        else    { 
            count++;                                                        // going to expand this node, so update count                         

            visited.push_back(priority.top());                              // already checked this node -> push into visited nodes
            if(priority.size() > maxNodes)  {                               // update max nodes in queue
                maxNodes = priority.size();
            }           
            priority.pop();         

            // create children nodes
            node *c1 = new node(moveDown(current->puzzle), current->g_n + 1);
            if(!repeatedState(c1, visited))   {                             // make sure node is not a repeated state

                if(algorithm == 2)  {
                    c1->h_n = misplacedTile(c1->puzzle);
                }
                if(algorithm == 3)  {
                    c1->h_n = euclideanDistance(c1->puzzle);
                }
                c1->f_n = c1->g_n + c1->h_n;

                current->child1 = c1;
                c1->p = current;
                priority.push(*c1);

            }

            node *c2 = new node(moveUp(current->puzzle), current->g_n + 1);
            if(!repeatedState(c2, visited))   {

                if(algorithm == 2)  {
                    c2->h_n = misplacedTile(c2->puzzle);
                }
                if(algorithm == 3)  {
                    c2->h_n = euclideanDistance(c2->puzzle);
                }
                c2->f_n = c2->g_n + c2->h_n;

                current->child2 = c2;
                c2->p = current;
                priority.push(*c2);
            }

            node *c3 = new node(moveRight(current->puzzle), current->g_n + 1);
            if(!repeatedState(c3, visited))   {

                if(algorithm == 2)  {
                    c3->h_n = misplacedTile(c3->puzzle);
                }
                if(algorithm == 3)  {
                    c3->h_n = euclideanDistance(c3->puzzle);
                }
                c3->f_n = c3->g_n + c3->h_n;

                current->child3 = c3;
                c3->p = current;
                priority.push(*c3);
            }
            

            node *c4 = new node(moveLeft(current->puzzle), current->g_n + 1);
            if(!repeatedState(c4, visited)) {

                if(algorithm == 2)  {
                    c4->h_n = misplacedTile(c4->puzzle);
                }
                if(algorithm == 3)  {
                    c4->h_n = euclideanDistance(c4->puzzle);
                }
                c4->f_n = c4->g_n + c4->h_n;

                current->child4 = c4;
                c4->p = current;
                priority.push(*c4);
            }
            

        }

    }

    
    
}