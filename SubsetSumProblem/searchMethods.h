//
// Created by s23049 on 28.11.2022.
//

#ifndef SUBSETSUMPROBLEM_SEARCHMETHODS_H
#define SUBSETSUMPROBLEM_SEARCHMETHODS_H

using namespace std;

#include <vector>
#include "Problem.h"

vector<int> SolveRandomTry(Problem problem, int iterations=1000, bool showHwoManyIterations=false, bool showHowManyChecked=false, bool showProgress=false);
vector<int> SolveClimbing(Problem problem, int iterations=1000, bool showHwoManyIterations=false, bool showHowManyChecked=false, bool showProgress=false);
vector<int> SolveRandomClimbing(Problem problem, int iterations=1000, bool showHwoManyIterations=false, bool showHowManyChecked=false, bool showProgress=false);
vector<int> SolveBruteForce(Problem problem, int iterations=0, bool showHwoManyIterations=false, bool showHowManyChecked=false, bool showProgress=false);
vector<int> SolveTabu(Problem problem, int iterations, bool showHwoManyIterations=false, bool showHowManyChecked=false, bool showProgress=false);
vector<int> SolveAnnealing(Problem problem, int i, bool a, bool b, bool c, int temperature, std::function<double(int)> T = [](int k){return 1000.0/(k+1);});
vector<vector<int>> findNeighbour(const vector<int>& vector1);
vector<int> translate(vector<int> vector1, vector<int> vector2);
vector<int> randomNeighbour(const vector<int>& binary);
void printZb(int iteration, Problem problem, vector<int> vector1, vector<int> vector2);
#endif //SUBSETSUMPROBLEM_SEARCHMETHODS_H
