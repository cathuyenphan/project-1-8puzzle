#ifndef PROBLEM_H_
#define PROBLEM_H_

#include "puzzle.h"
#include "operators.h"

#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

class Problem   {
    public:
        Problem(vector<int> values);
        void operator=(const Problem& puzzle);

        vector<vector<int> > initial_state{{1,0,3},{4,2,6},{7,5,8}};        // default values
        vector<vector<int> > goal_state{{1,2,3},{4,5,6},{7,8,0}};

        void solve(int algorithm);


    private:
        vector<node> visited;
        priority_queue <node, vector<node>, cheaperNode> priority;

        void traceSolution(node current, int, int, int);
        bool repeatedState(node *current, vector<node> vec);
        void printPuzzle(vector<vector<int> > puzzle);

        int misplacedTile(vector<vector<int> > puzzle);
        int euclideanDistance(vector<vector<int> > puzzle);


};

Problem::Problem(vector<int> values)    {

    int index = 0; 
    for(int i = 0; i < 3; i++)  {
        for(int j = 0; j < 3; j++)  {
            initial_state[i][j] = values[index];
            index++;
        }
    }

    node initial(initial_state);
    priority.push(initial);


}

void Problem::operator=(const Problem& puzzle)  {

    initial_state = puzzle.initial_state;
    goal_state = puzzle.goal_state;

}

bool Problem::repeatedState(node *current, vector<node> visited)   {
    for(long unsigned int i = 0; i < visited.size(); i++)   {
        if(current->puzzle == visited[i].puzzle) {
            return true;
        }
    }
    return false;
}

void Problem::printPuzzle(vector<vector<int> > puzzle)    {

    for(int i = 0; i < 3; i++)  {
        for(int j = 0; j < 3; j++)  {
            cout << puzzle[i][j] << " ";
        }
        cout << endl;
    }

}

void Problem::traceSolution(node current, int count, int maxNodes, int depth)    {
    
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
    cout << endl;
    path.pop();

    while(path.size() > 1)  {
        int g = path.top().g_n;
        int h = path.top().h_n;

        cout << "The best state to expand with g(n) = " << g << " and h(n) = " << h << " is..." << endl;
        printPuzzle(path.top().puzzle);
        cout << "Expanding this node..." << endl;
        cout << endl;

        path.pop();
    }

    cout << "Goal!!!" << endl << endl;
    cout << "To solve this problem the search algorithm needed to expand a total of " << count << " nodes." << endl;
    cout << "The maximum number of nodes in the queue at any one time: " << maxNodes << "." << endl;
    cout << "The depth of the goal node was " << depth << "." << endl;

}

void Problem::solve(int algorithm)  {
    int count = 0; 
    int maxNodes = 0; 
    int depth = 0;

    while(!priority.empty())  {
        node *current = new node(priority.top());     

        visited.push_back(priority.top());                              // already checked this node -> push into visited nodes

        if(priority.size() > maxNodes)  {                               // update max nodes in queue
            maxNodes = priority.size();
        }

        if(priority.top().puzzle == goal_state) {
            depth = current->g_n;
            if(maxNodes < priority.size())   {
                maxNodes = priority.size();
            }

            traceSolution(priority.top(), count, maxNodes, depth);
            break;          

        }        
        else    {
            count++;
            priority.pop();          

            // create children nodes
            node *c1 = new node(moveDown(current->puzzle), current->g_n + 1);
            if(!repeatedState(c1, visited))   {                                // make sure node is not a repeated state
                
                if(algorithm == 2)  {
                    c1->h_n = misplacedTile(c1->puzzle);
                }
                if(algorithm == 3)  {
                    c1->h_n = euclideanDistance(c1->puzzle);
                }
                c1->f_n = c1->g_n + c1->h_n;

                current->child1 = c1;
                c1->p = current;
                if(c1->puzzle == goal_state)    {
                    depth = c1->g_n;
                    traceSolution(*c1, count, maxNodes, depth);
                    break;
                }
                else    {
                    priority.push(*c1);
                }

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
                
                if(c2->puzzle == goal_state)    {
                    depth = c2->g_n;
                    traceSolution(*c2, count, maxNodes, depth);
                    break;
                }
                else    {
                    priority.push(*c2);
                }
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
                
                if(c3->puzzle == goal_state)    {
                    depth = c3->g_n;
                    traceSolution(*c3, count, maxNodes, depth);
                    break;
                }
                else    {
                    priority.push(*c3);
                }
            }
            

            node *c4 = new node(moveLeft(current->puzzle), current->g_n + 1);
            if(c4->puzzle == goal_state)    {

            }
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
                
                if(c4->puzzle == goal_state)    {
                    depth = c4->g_n;
                    traceSolution(*c4, count, maxNodes, depth);
                    break;
                }
                else    {
                    priority.push(*c4);
                }
            }
                       
        }
        

    }

}



#endif