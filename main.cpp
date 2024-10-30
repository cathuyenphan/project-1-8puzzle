#include <iostream>
#include <queue>
#include <vector>
#include <stack>

#include "puzzle.h"
#include "A_heuristics.h"
#include "operators.h"

using namespace std;

int main()  {

    // default puzzle values
    vector<int> values = {1,0,3,4,2,6,7,5,8};

    int input = 0;

    cout << "Welcome to 862283047 8-puzzle solver." << endl;
    cout << "Type \"1\" to use a default puzzle, or \"2\" to enter your own puzzle." << endl;
    cin >> input;

    vector<vector<int>> puzzle;

    int index = 0; 

    if(input == 1)  {                           
        for(int i = 0; i < 3; i++)  {               // put default values into puzzle
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

        for(int i = 0; i < 3; i++)  {               // put user values into puzzle
            for(int j = 0; j < 3; j++)  {
                puzzle[i][j] = values[index];
                index++;
            }
        }


    }

    cout << "Enter your choice of algorithm:" << endl;
    cout << "1 for Uniform Cost Search" << endl;
    cout << "2 for A* with the Misplaced Tile heuristic" << endl;
    cout << "3 for A* with the Euclidean distance heuristic" << endl;

    cin >> input;


}
