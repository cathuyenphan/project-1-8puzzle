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

    int g_n = 0;                                // g(n)
    int h_n = 0;                                // h(n)
    int f_n = 0;                                // F(n) = g(n) + h(n)

    vector<vector<int> > puzzle;
    node(vector<vector<int> > cur)   {           // initial state node

        puzzle = cur;      
        g_n = 0; 
        h_n = 0;

    }
    node(const node &newpuzzle) {               // for expanding node
        puzzle = newpuzzle.puzzle;

        g_n = newpuzzle.g_n;
        h_n = newpuzzle.h_n;
        f_n = newpuzzle.f_n;

        p = newpuzzle.p;
        child1 = newpuzzle.child1;
        child2 = newpuzzle.child2;
        child3 = newpuzzle.child3;
        child4 = newpuzzle.child4;

    }

    node(vector<vector<int> > newpuzzle, int costToNode)   {
        puzzle = newpuzzle;

        g_n = costToNode;
        h_n = 0;
        f_n = g_n + h_n;

    }

    void operator=(const node &current)  {                  // overloaded assignment for deep copy
        puzzle = current.puzzle;
        g_n = current.g_n;
        h_n = current.h_n;
        f_n = current.f_n;

        p = current.p; 
        child1 = current.child1;
        child2 = current.child2;
        child3 = current.child3;
        child4 = current.child4;

    }

    


};

struct cheaperNode  {

    bool operator()(const node& c1, const node& c2) {
        if(c1.f_n > c2.f_n) {                           // makes sure priority_heap keeps smallest f_n values at the top
            return true;
        }
        return false;
    }
};

#endif
