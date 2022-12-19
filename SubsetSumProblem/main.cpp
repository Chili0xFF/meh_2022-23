#include <iostream>
#include <vector>
#include <fstream>
#include <functional>
#include <map>
#include <chrono>
#include <cmath>

#include "tp_args.hpp"
#include "searchMethods.h"
#include "Problem.h"

using namespace std;

string method;
int target;
int iterations;
string link;
bool showTime;
bool showGraph;
bool showSolution;
bool showQuality;
bool showIterations;
bool showAmountCheck;
int annealTemp;
float p_cross;
float p_mutation;
int pSize;
int useElites;

string tempMethod;
std::function<double(int)> T = [](int k){return 1000.0/(k+1);};

map<string, function<double(int)>> tempMap = {
        {"divByK",[](int k){return 1000.0/(k+1);}},
        {"divByLogK",[](int k){return 1000.0/log(k);}},
        {"05PowK",[](int k){return (double)pow(0.5,k);}}
};

map<string, function<vector<int>(Problem,int,bool,bool,bool)>> methods = {
        {"brute_force", SolveBruteForce},
        {"random_probe", SolveRandomTry},
        {"hill_climb_det", SolveClimbing},
        {"hill_climb_rand", SolveRandomClimbing},
        {"tabu_search", SolveTabu},
        {"annealing",[](Problem p,int i,bool a, bool b, bool c){return SolveAnnealing(p,i,a,b,c,annealTemp,tempMap.at(tempMethod));}},
        {"genetic",[](Problem p,int i, bool a, bool b, bool c){return SolveGenetic(p,i,a,b,c,p_cross,p_mutation,pSize,useElites);}}
};

int main(int argc, char **argv) {
    using namespace tp::args;
    // Arguments handling
    auto help = arg(argc, argv, "help", false);
    link = arg(argc,argv,"link", std::string("..\\data.txt"), "Path to the input file");
    target = arg(argc,argv, "target", 100, "Target value of our subset");
    method = arg(argc, argv, "method", std::string("genetic"),"Opt. method. Available are: brute_force tabu_search ""random_probe hill_climb_det.");
    iterations = arg(argc, argv, "iterations", 1000, "Maximal number of iterations.");
    showTime = arg(argc, argv, "time", false, "Show time.");
    showGraph = arg(argc, argv, "graph", false, "Show graph.");
    showSolution = arg(argc, argv, "solution", false, "Show solution.");
    showQuality = arg(argc, argv, "quality", false, "Show quality of solution.");
    showIterations = arg(argc, argv, "usedIterations", false, "Show how many iterations passed.");
    showAmountCheck = arg(argc, argv, "checks", false, "Show how many how many times target function was used");
    annealTemp = arg(argc,argv, "temperature",10,"Sets temperature. Only used for -method anneal");
    tempMethod = arg(argc,argv, "tempMethod",std::string("divByK"),"Chooses temperature methods. Only used for -method anneal [divByK | divByLogK | 05PowK]");
    p_cross=arg(argc,argv, "pCrossover",0.5f,"Probability of crossover. Genetic only");
    p_mutation=arg(argc,argv, "pMutation",0.5f,"Probability of mutation. Genetic only");
    pSize=arg(argc,argv, "pSize",100,"Sets population size. Genetic only");
    useElites= arg(argc, argv, "elites", 0, "Determines amount of elites during genetic algorithm");
    if (help) {
        std::cout << "help screen.." << std::endl;
        args_info(std::cout);
        return 0;
    }

    vector<int> multiset;
    ifstream f(link);
    if (f.is_open()) {
        string line;
        while (getline(f, line)) {
            multiset.push_back(stoi(line));
        }
        f.close();
    }else {
        cout<<"error, failed to load file: ";
        cout<<link<<endl;
        return 0;
    }

    Problem problem(target,multiset);
    auto start = std::chrono::steady_clock::now();
    vector<int> result = methods.at(method)(problem, iterations, showIterations, showAmountCheck, showGraph);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;

    if(showTime)std::cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";
    if(showSolution){
        cout<<"Solution: ";
        try{
            cout<<"{"<<result.at(0);
            for(int j=1;j<result.size();j++){
                cout<<", "<<result.at(j);
            }

        }
        catch(out_of_range){
            cout<<"EMPTY";
        }
        cout<<"}\n";
    }
    if(showQuality)cout<<"How far from perfection: "<<problem.checkHowCorrect(result)<<endl;
    return 0;
}


