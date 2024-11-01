#include <iostream>
#include <queue>
#include <vector>
#include <stack>

#include "puzzle.h"
#include "problem.h"
#include "A_heuristics.h"
#include "operators.h"

using namespace std;

int chooseAlgorithm();

int main()  {

    int input = 0;
    vector<int> values = {1,0,3,4,2,6,7,5,8};

    cout << "Welcome to 862283047 8-puzzle solver." << endl;
    cout << "Type \"1\" to use a default puzzle, or \"2\" to enter your own puzzle." << endl;
    cin >> input;

    if(input == 1)  {                           
        
        Problem puzzle = Problem(values);
        int option = chooseAlgorithm();
        puzzle.solve(option);
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

        Problem puzzle = Problem(values);
        int option = chooseAlgorithm();
        puzzle.solve(option);

    }

    return 0;
}

int chooseAlgorithm()  {
    int algorithm; 

    cout << "Choose algorithm:" << endl;
    cout << "1 for Uniform Cost Algorithm" << endl;
    cout << "2 for A* Algorithm with Misplaced Tile Heuristic" << endl;
    cout << "3 for A* Algorithm with Euclidean Distance Heuristic" << endl;

    cin >> algorithm; 
    return algorithm;
}


