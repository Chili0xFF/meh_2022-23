#include <random>
#include <algorithm>
#include <map>
#include "searchMethods.h"

typedef std::mersenne_twister_engine<uint_fast32_t,
        32,624,397,31,0x9908b0df,11,0xffffffff,7,0x9d2c5680,15,0xefc60000,18,1812433253>
        mt19937;
mt19937 mt1(time(nullptr));

int iterationsChecked=0;

vector<int> SolveTabu(Problem problem, int iterations, bool showHwoManyIterations, bool showHowManyChecked, bool showProgress) {
    int tabSize = 1000;
    vector<int> binaryZeroes = problem.binaryResult;
    vector<int> bestSolution = {};
    //Generate size
    std::uniform_int_distribution<int> int_distr(0, problem.multiset.size()-1);
    int size = int_distr(mt1)+1;
    //Generate numbers;
    for(int j=0;j<size;j++) {
        int indexToOne = mt1() % (problem.multiset.size());                           //generating a random subset
        if (binaryZeroes.at(indexToOne) == 0)binaryZeroes.at(indexToOne) = 1;
        else j--;
    }
    problem.checked.push_back(binaryZeroes);
    vector<int> bestNeighbour=binaryZeroes;
    for(int i=0;i<iterations;i++, iterationsChecked++){
        //Generate neighbours
        vector<vector<int>> neighbours=findNeighbour(bestNeighbour);
        bestNeighbour= neighbours.at(0);
        for (vector<int> bour : neighbours) {

            if(find(problem.checked.begin(),problem.checked.end(),bour)==problem.checked.end()){
                vector<int> TranslatedBour= translate(problem.multiset,bour);
                if(problem.checkHowCorrect(TranslatedBour)< problem.checkHowCorrect(translate(problem.multiset,bestNeighbour)))bestNeighbour=bour;
            }
        }
        vector<int> trBN = translate(problem.multiset, bestNeighbour);
        if(problem.checkHowCorrect(trBN)<problem.checkHowCorrect(bestSolution))bestSolution=trBN;
        problem.checked.push_back(bestNeighbour);
        if(problem.checked.size()>tabSize){
            problem.checked.erase(problem.checked.begin());
        }
        if(showProgress)printZb(iterationsChecked,problem,bestSolution,trBN);
        int cost = problem.checkHowCorrect(bestSolution);
        if(cost==0){
            if(showHwoManyIterations)cout<<"Iterations: "<<iterationsChecked<<endl;
            if(showHowManyChecked)cout<<"Times Checked: "<<problem.HowManyTimesChecked<<endl;
            return bestSolution;
        }
    }
    if(showHwoManyIterations)cout<<"Iterations: "<<iterationsChecked<<endl;
    if(showHowManyChecked)cout<<"Times Checked: "<<problem.HowManyTimesChecked<<endl;
    return bestSolution;
}
vector<int> SolveRandomClimbing(Problem problem, int iterations, bool showHwoManyIterations, bool showHowManyChecked, bool showProgress) {
    vector<int> binaryZeroes = problem.binaryResult;
    vector<int> bestSolution = problem.multiset;
    //Generate size
    std::uniform_int_distribution<int> int_distr(0, problem.multiset.size()-1);
    int size = int_distr(mt1)+1;
    //Generate numbers;
    for(int j=0;j<size;j++) {
        int indexToOne = mt1() % (problem.multiset.size());                           //generating a random subset
        if (binaryZeroes.at(indexToOne) == 0)binaryZeroes.at(indexToOne) = 1;
        else j--;
    }

    for(int i=0;i<iterations;i++,iterationsChecked++){
        vector<vector<int>> neighbours = findNeighbour(binaryZeroes);                       //Generating vector filled with new binary forms
        vector<int> tempResult;
        tempResult = translate(problem.multiset,neighbours.at(0));
        if(problem.checkHowCorrect(tempResult)==0){
            if(showHwoManyIterations)cout<<"Iterations: "<<iterationsChecked<<endl;
            if(showHowManyChecked)cout<<"Times Checked: "<<problem.HowManyTimesChecked<<endl;
            return tempResult;
        }
        int randomIndex = mt1()%neighbours.size();
        tempResult= translate(problem.multiset,neighbours.at(randomIndex));
        if(problem.checkHowCorrect(tempResult)==0){
            if(showHwoManyIterations)cout<<"Iterations: "<<iterationsChecked<<endl;
            if(showHowManyChecked)cout<<"Times Checked: "<<problem.HowManyTimesChecked<<endl;
            return tempResult;
        }
        if(problem.checkHowCorrect(bestSolution)>problem.checkHowCorrect(tempResult)){
            bestSolution = tempResult;
            binaryZeroes=neighbours.at(randomIndex);
        }
        if(showProgress)printZb(iterationsChecked,problem,bestSolution,tempResult);
    }
    if(showHwoManyIterations)cout<<"Iterations: "<<iterationsChecked<<endl;
    if(showHowManyChecked)cout<<"Times Checked: "<<problem.HowManyTimesChecked<<endl;
    return bestSolution;
}
vector<int> SolveBruteForce(Problem problem, int iterations, bool showHwoManyIterations, bool showHowManyChecked, bool showProgress){
    vector<int> multiset = problem.multiset;
    vector<int> tempResult;
    vector<int> bestSolution = {};
    int bestCost = problem.checkHowCorrect(bestSolution);
    vector<int> binaryZeroes;
    int cost;
    binaryZeroes.reserve(problem.multiset.size());
    for (int i = 0; i < problem.multiset.size()&&iterationsChecked<iterations; ++i) {
        binaryZeroes.clear();
        for(int j=0;j<problem.multiset.size()-i;j++){
            binaryZeroes.push_back(0);
        }
        for(int j=0;j<i;j++){
            binaryZeroes.push_back(1);
        }
        do{
            tempResult = translate(problem.multiset,binaryZeroes);
            cost = problem.checkHowCorrect(tempResult);
            if(cost<bestCost){
                bestSolution=tempResult;
                bestCost=cost;
            }
            if(cost==0){
                break;
            }
            iterationsChecked++;
            if(showProgress)printZb(iterationsChecked,problem,bestSolution,tempResult);
        }while(std::next_permutation(binaryZeroes.begin(),binaryZeroes.end())&&iterationsChecked<iterations);
    }

    if(showHwoManyIterations)cout<<"Iterations: "<<iterationsChecked<<endl;
    if(showHowManyChecked)cout<<"Times Checked: "<<problem.HowManyTimesChecked<<endl;
    return bestSolution;
}
vector<int> SolveClimbing(Problem problem, int iterations, bool showHwoManyIterations, bool showHowManyChecked, bool showProgress) {
    vector<int> binaryZeroes = problem.binaryResult;
    vector<int> bestSolution = problem.multiset;
    //Generate size
    std::uniform_int_distribution<int> int_distr(0, problem.multiset.size()-1);
    int size = int_distr(mt1)+1;
    //Generate numbers;
    for(int j=0;j<size;j++) {
        int indexToOne = mt1() % (problem.multiset.size());                           //generating a random subset
        if (binaryZeroes.at(indexToOne) == 0)binaryZeroes.at(indexToOne) = 1;
        else j--;
    }

    for(int i=0;i<iterations;i++,iterationsChecked++){
        vector<vector<int>> neighbours = findNeighbour(binaryZeroes);                       //Generating vector filled with new binary forms
        vector<int> tempResult;
        tempResult = translate(problem.multiset,neighbours.at(0));
        if(problem.checkHowCorrect(tempResult)==0){
            if(showHwoManyIterations)cout<<"Iterations: "<<iterationsChecked<<endl;
            if(showHowManyChecked)cout<<"Times Checked: "<<problem.HowManyTimesChecked<<endl;
            return tempResult;
        }
        for(int j=1;j<neighbours.size();j++){
            tempResult = translate(problem.multiset,neighbours.at(j));
            if(problem.checkHowCorrect(tempResult)==0){
                if(showHwoManyIterations)cout<<"Iterations: "<<iterationsChecked<<endl;
                if(showHowManyChecked)cout<<"Times Checked: "<<problem.HowManyTimesChecked<<endl;
                return tempResult;
            }
            if(problem.checkHowCorrect(bestSolution)>problem.checkHowCorrect(tempResult)){
                bestSolution = tempResult;
                binaryZeroes=neighbours.at(j);
            }
        }
        if(showProgress)printZb(iterationsChecked,problem,bestSolution,tempResult);
    }
    if(showHwoManyIterations)cout<<"Iterations: "<<iterationsChecked<<endl;
    if(showHowManyChecked)cout<<"Times Checked: "<<problem.HowManyTimesChecked<<endl;
    return bestSolution;
}
vector<int> SolveRandomTry(Problem problem, int iterations, bool showHwoManyIterations, bool showHowManyChecked, bool showProgress) {
    vector<int> binaryZeroes = problem.binaryResult;
    vector<int> bestSolution = problem.multiset;
    int bestCost = problem.checkHowCorrect(bestSolution);
    for(int i=0;i<iterations;i++,iterationsChecked++){
        binaryZeroes = problem.binaryResult;
        //Generate size
        std::uniform_int_distribution<int> int_distr(0, problem.multiset.size()-1);
        int size = int_distr(mt1)+1;
        //Generate numbers;
        for(int j=0;j<size;j++){
            int indexToOne = mt1()%(problem.multiset.size());
            if(binaryZeroes.at(indexToOne)==0)binaryZeroes.at(indexToOne)=1;
            else j--;
        }
        vector<int> tempResult = translate(problem.multiset,binaryZeroes);
        int cost = problem.checkHowCorrect(tempResult);
        if(cost==0){
            if(showHwoManyIterations)cout<<"Iterations: "<<iterationsChecked<<endl;
            if(showHowManyChecked)cout<<"Times Checked: "<<problem.HowManyTimesChecked<<endl;
            return tempResult;
        }else if(cost<bestCost){
            bestSolution=tempResult;
            bestCost=cost;
        }
        if(showProgress)printZb(iterationsChecked,problem,bestSolution,tempResult);
    }
    if(showHwoManyIterations)cout<<"Iterations: "<<iterationsChecked<<endl;
    if(showHowManyChecked)cout<<"Times Checked: "<<problem.HowManyTimesChecked<<endl;
    return bestSolution;
}
vector<int> SolveAnnealing(Problem problem, int iterations, bool showHwoManyIterations, bool showHowManyChecked, bool showProgress, int temp, std::function<double(int)> T) {
    vector<int> binaryZeroes = problem.binaryResult;
    vector<int> bestSolution = problem.multiset;
    std::uniform_int_distribution<int> rndNgb(0, binaryZeroes.size()-1);
    std::uniform_real_distribution<float> uk(0.0,1.0);
    //Generate size
    std::uniform_int_distribution<int> int_distr(0, problem.multiset.size()-1);
    int size = int_distr(mt1)+1;
    //Generate numbers;
    for(int j=0;j<size;j++){
        int indexToOne = mt1()%(problem.multiset.size());
        if(binaryZeroes.at(indexToOne)==0)binaryZeroes.at(indexToOne)=1;
        else j--;
    }
    vector<int> tempResult = translate(problem.multiset,binaryZeroes);
    bestSolution = tempResult;
    //Annealing
    for(int k=1;k<iterations+1&&problem.checkHowCorrect(bestSolution)!=0;k++,iterationsChecked++){
        if(showProgress)printZb(iterationsChecked,problem,bestSolution,tempResult);
        vector<vector<int>> neighbours = findNeighbour(binaryZeroes);
        vector<int> randomNeighbour = neighbours.at(rndNgb(mt1));
        vector<int> tranlRandNeighw = translate(problem.multiset,randomNeighbour);
        if(problem.checkHowCorrect(tranlRandNeighw)<problem.checkHowCorrect(tempResult)){
            tempResult=tranlRandNeighw;
            binaryZeroes=randomNeighbour;
            if(problem.checkHowCorrect(tempResult)<problem.checkHowCorrect(bestSolution)){
                bestSolution=tempResult;
            }
        }
        else if(uk(mt1)< exp(-1*((abs(problem.checkHowCorrect(tranlRandNeighw)-problem.checkHowCorrect(tempResult)))/T(k)))){
            tempResult=tranlRandNeighw;
            binaryZeroes=randomNeighbour;
            }
    }
    if(showHwoManyIterations)cout<<"Iterations: "<<iterationsChecked<<endl;
    if(showHowManyChecked)cout<<"Times Checked: "<<problem.HowManyTimesChecked<<endl;
    return bestSolution;
}

vector<int> translate(vector<int> multiset, vector<int> binaryZeroes) {
    vector<int> Result;
    for (int j = 0; j < binaryZeroes.size(); ++j) {
        if(binaryZeroes.at(j)==1){
            Result.push_back(multiset.at(j));
        }
    }
    return Result;
}

vector<vector<int>> findNeighbour(const vector<int>& binary) {
    vector<vector<int>> neighbours;

    for(int i=0;i<binary.size();i++){
        vector<int> changedBinary=binary;
        changedBinary.at(i)=1-changedBinary.at(i);
        neighbours.push_back(changedBinary);
    }
    return neighbours;
}

vector<int> randomNeighbour(const vector<int>& binary){
    vector<vector<int>> neighbours = findNeighbour(binary);
    std::uniform_int_distribution<int> rndNgb(0, neighbours.size()-1);
    return neighbours.at(rndNgb(mt1));
}

void printZb(int iteration,Problem problem, vector<int> bestSolutionSoFar, vector<int> tempSolution){
    cout << iteration << "\t" << problem.checkHowCorrect(bestSolutionSoFar) << "\t" << problem.checkHowCorrect(tempSolution) << endl;
}