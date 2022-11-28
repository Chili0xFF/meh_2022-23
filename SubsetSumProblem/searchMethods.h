//
// Created by s23049 on 28.11.2022.
//

#ifndef SUBSETSUMPROBLEM_SEARCHMETHODS_H
#define SUBSETSUMPROBLEM_SEARCHMETHODS_H

using namespace std;

#include <vector>
#include "Problem.h"

vector<int> SolveRandomTry(Problem problem, int iterations=1000, bool details=false, bool showHwoManyIterations=false, bool showHowManyChecked=false, bool showProgress=false);
vector<int> SolveClimbing(Problem problem, int iterations=1000, bool details=false, bool showHwoManyIterations=false, bool showHowManyChecked=false, bool showProgress=false);
vector<int> SolveRandomClimbing(Problem problem, int iterations=1000, bool details=false, bool showHwoManyIterations=false, bool showHowManyChecked=false, bool showProgress=false);
vector<int> SolveBruteForce(Problem problem, int iterations=0, bool details=false, bool showHwoManyIterations=false, bool showHowManyChecked=false, bool showProgress=false);
vector<int> SolveTabu(Problem problem, int iterations, bool details=false, bool showHwoManyIterations=false, bool showHowManyChecked=false, bool showProgress=false);
vector<vector<int>> findNeighbour(const vector<int>& vector1);
vector<int> translate(vector<int> vector1, vector<int> vector2);
#endif //SUBSETSUMPROBLEM_SEARCHMETHODS_H