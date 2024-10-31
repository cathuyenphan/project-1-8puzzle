#ifndef OPERATORS_H_
#define OPERATORS_H_

#include "puzzle.h"
#include <iostream>
#include <vector>

using namespace std;

vector<int> findBlank(vector<vector<int> > state) {
  // find the blank tile on puzzle
  vector<int> coordinates{};

  for(int i = 0; i < 3; i++)  {
    for(int j = 0; j < 3; j++)  {
      if(state[i][j] == 0)  {
        coordinates.push_back(i);
        coordinates.push_back(j);
      }
    }
  }

  return coordinates;

}

vector<vector<int> > swap(vector<vector<int> > state, int x, int y, int i, int j)  {
  //swap two nodes
  int temp;
  temp = state[x][y];
  state[x][y] = state[i][j];
  state[i][j] = temp;

  return state;

};

vector<vector<int> > moveDown(vector<vector<int> > puzzle)  {
  // move tile down
  vector<int> blank = findBlank(puzzle);                              // get coordinates of the blank space
  if(blank[0] == 0) {
    return puzzle;                                                    // can't move tile down if the blank is on top row
  }
  else  {
    int tile_row = blank[0] - 1;
    return swap(puzzle, blank[0], blank[1], tile_row, blank[1]);      // swap values of 0 and tile on top.
  }


};

vector<vector<int> > moveUp(vector<vector<int> > puzzle)  {
  //move tile up
  vector<int> blank = findBlank(puzzle);

  if(blank[0] == 2) {
    return puzzle;                                                    // can't move tile up if blank is on bottom row
  }
  else  {
    int tile_row = blank[0] + 1;
    return swap(puzzle, blank[0], blank[1], tile_row, blank[1]);
  }
};

vector<vector<int> > moveRight(vector<vector<int> > puzzle)  {
  // move tile right
  vector<int> blank = findBlank(puzzle);

  if(blank[1] == 0) {
    return puzzle;                                                      // can't move tile right if the blank is on the left-most column
  }
  else  {
    int tile_column = blank[1] - 1;
    return swap(puzzle, blank[0], blank[1], blank[0], tile_column);
  }
};

vector<vector<int> > moveLeft(vector<vector<int> > puzzle)  {
  // move tile left
  vector<int> blank = findBlank(puzzle);
  if(blank[1] == 2) {
    return puzzle;
  }
  else  {
    int tile_column = blank[1] + 1;
    return swap(puzzle, blank[0], blank[1], blank[0], tile_column);
  }
  
};

#endif
