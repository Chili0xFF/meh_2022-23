//
// Created by s23049 on 28.11.2022.
//

#ifndef SUBSETSUMPROBLEM_SEARCHMETHODS_H
#define SUBSETSUMPROBLEM_SEARCHMETHODS_H

using namespace std;

using chromosome_t = vector<int>;
using population_t = vector<chromosome_t>;

#include <vector>
#include "Problem.h"

vector<int> SolveRandomTry(Problem problem, int iterations=1000, bool showHwoManyIterations=false, bool showHowManyChecked=false, bool showProgress=false);
vector<int> SolveClimbing(Problem problem, int iterations=1000, bool showHwoManyIterations=false, bool showHowManyChecked=false, bool showProgress=false);
vector<int> SolveRandomClimbing(Problem problem, int iterations=1000, bool showHwoManyIterations=false, bool showHowManyChecked=false, bool showProgress=false);
vector<int> SolveBruteForce(Problem problem, int iterations=0, bool showHwoManyIterations=false, bool showHowManyChecked=false, bool showProgress=false);
vector<int> SolveTabu(Problem problem, int iterations, bool showHwoManyIterations=false, bool showHowManyChecked=false, bool showProgress=false);
vector<int> SolveAnnealing(Problem problem, int i, bool a, bool b, bool c, int temperature, std::function<double(int)> T = [](int k){return 1000.0/(k+1);});
vector<int> SolveGenetic(Problem problem, int iterations, bool showHwoManyIterations, bool showHowManyChecked, bool showProgress, float p_crossover, float p_mutation, int populationSize);
chromosome_t mutation(chromosome_t preMutation, float p_mutation);
vector<vector<int>> crossover1p(chromosome_t p1, chromosome_t p2);
vector<vector<int>> findNeighbour(const vector<int>& vector1);
vector<int> translate(vector<int> vector1, vector<int> vector2);
vector<int> randomNeighbour(const vector<int>& binary);
chromosome_t generateRandomSolution(int size);
population_t populate(int populationSize,int chromosomeSize);

float fitness(Problem p, chromosome_t a);
void printZb(int iteration, Problem problem, vector<int> vector1, vector<int> vector2);
#endif //SUBSETSUMPROBLEM_SEARCHMETHODS_H
