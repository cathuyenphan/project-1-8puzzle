#ifndef PUZZLE_H_
#define PUZZLE_H_

#include <iostream>
#include <vector>

using namespace std;


struct node  {

    node *p = NULL;                             // parent node
    node *child1 = NULL;                        // branching factor = 4, so each parent can have at most 4 children
    node *child2 = NULL;
    node *child3 = NULL;
    node *child4 = NULL;

    int costToNode = 0;                         // g(n)
    int distanceToGoal = 0;                     // h(n)
    int total = 0;                              // F(n) = g(n) + h(n)

    vector<vector<int>> puzzle;
    node(vector<vector<int>> cur)   {           // if parameter is entire puzzle (initial state)

        puzzle = cur;      
        costToNode = 0; 
        distanceToGoal = 0;

    }
    node(const node &newpuzzle) {               // if parameter is a node
        puzzle = newpuzzle.puzzle;

        costToNode = newpuzzle.costToNode;
        distanceToGoal = newpuzzle.distanceToGoal;
        total = newpuzzle.total;

        p = newpuzzle.p;
        child1 = newpuzzle.child1;
        child2 = newpuzzle.child2;
        child3 = newpuzzle.child3;
        child4 = newpuzzle.child4;

    }

    


};

struct cheaperNode  {
};

#endif
