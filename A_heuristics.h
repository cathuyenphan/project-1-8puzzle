#ifndef A_HEURISTICS_H_
#define A_HEURISTICS_H_

#include "puzzle.h"
#include <iostream>
#include <vector>

using namespace std;

const vector<vector<int>> goalState = {{1,2,3},{4,5,6},{7,8,9}};

int misplacedTile(vector<vector<int>> puzzle)  {

    int count = 0;
    for(int i = 0; i < 3; i++)  {
        for(int j = 0; j < 3; j++)  {
            if(puzzle[i][j] != goalState[i][j]) {
                count++;
            }
        }
    }

    return count;       // the number of misplaced tiles
}

int euclideanDistance(vector<vector<int>> puzzle)  {

    int distance = 0; 
    float temp = 0;

    int misplaced = 0;      // number that is misplaced
    int a, b;               // coordinates of misplaced node
    int x, y;               // coordinates of goal node


    for(int i = 0; i < 3; i++)  {
        for(int j = 0; j < 3; j++)  {
            if(puzzle[i][j] == 0)   {                              // don't need to find euclidean distance of the blank space
                continue;
            }

            if(puzzle[i][j] != goalState[i][j]) {                  // find and get coordinates of the misplaced node
                misplaced = puzzle[i][j];
                a = i;
                b = j;

                for(int m = 0; m < 3; m++)  {                       // get coordinates of the goal node
                    for(int n = 0; n < 3; n++)  {
                        if(misplaced == goalState[m][n])    {
                            x = m;
                            y = n;
                        }
                    }
                }

                temp = pow((a - x), 2) + pow((b - y), 2);
                distance += sqrt(temp);
                
            }
        }
    }

    return distance;

}

#endif
