#ifndef A_HEURISTICS_H_
#define A_HEURISTICS_H_

#include "puzzle.h"
#include "problem.h"
#include <iostream>
#include <vector>

using namespace std;


int Problem::misplacedTile(vector<vector<int> > puzzle)  {            

    int count = 0;
    for(int i = 0; i < 3; i++)  {
        for(int j = 0; j < 3; j++)  {
            if(puzzle[i][j] == 0)   {                   // not counting the blank space
                continue;
            }
            if(puzzle[i][j] != goal_state[i][j]) {
                count++;
            }
        }
    }

    return count;       // the number of misplaced tiles
}

int Problem::euclideanDistance(vector<vector<int> > puzzle)  {

    double distance = 0; 
    double temp = 0;

    int tile; 
    int x, y;

    for(int i = 0; i < 3; i++)  {
        for(int j = 0; j < 3; j++)  {
            tile = puzzle[i][j];

            if(tile != 0)   {                               // find where tile is supposed to be 
                x = (tile - 1) / 3;
                y = (tile - 1) % 3;

                temp = sqrt(pow(i - x, 2) + pow(j - y, 2));
                distance += (temp);
            }   
        }
    }
        
    return round(distance);                                 // round to nearest whole number
}


#endif
