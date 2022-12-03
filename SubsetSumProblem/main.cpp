#include <iostream>
#include <vector>
#include <fstream>
#include <functional>
#include <map>
#include <chrono>

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

int main(int argc, char **argv) {
    using namespace tp::args;
    // Arguments handling
    auto help = arg(argc, argv, "help", false);
    link = arg(argc,argv,"link", std::string("No file given"), "Path to the input file");
    target = arg(argc,argv, "target", 100, "Target value of our subset");
    method = arg(argc, argv, "method", std::string("tabu_search"),"Opt. method. Available are: brute_force tabu_search ""random_probe hill_climb_det.");
    iterations = arg(argc, argv, "iterations", 100, "Maximal number of iterations.");
    showTime = arg(argc, argv, "time", false, "Show time.");
    showGraph = arg(argc, argv, "graph", false, "Show graph.");
    showSolution = arg(argc, argv, "solution", false, "Show solution.");
    showQuality = arg(argc, argv, "quality", false, "Show quality of solution.");
    showIterations = arg(argc, argv, "usedIterations", false, "Show how many iterations passed.");
    showAmountCheck = arg(argc, argv, "checks", false, "Show how many how many times target function was used");

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

    map<string, function<vector<int>(Problem,int,bool,bool,bool)>> methods = {
            {"brute_force", SolveBruteForce},
            {"random_probe", SolveRandomTry},
            {"hill_climb_det", SolveClimbing},
            {"hill_climb_rand", SolveRandomClimbing},
            {"tabu_search", SolveTabu},
    };

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