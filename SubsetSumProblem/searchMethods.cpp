//
// Created by s23049 on 28.11.2022.
//

#include <random>
#include <algorithm>
#include "searchMethods.h"

typedef std::mersenne_twister_engine<uint_fast32_t,
        32,624,397,31,0x9908b0df,11,0xffffffff,7,0x9d2c5680,15,0xefc60000,18,1812433253>
        mt19937;
mt19937 mt1(time(nullptr));

int iterationsChecked=0;

vector<int> SolveTabu(Problem problem, int iterations, bool details, bool showHwoManyIterations, bool showHowManyChecked, bool showProgress) {
    int tabSize = 1000;
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
    problem.checked.push_back(binaryZeroes);
    vector<int> bestNeighbour=binaryZeroes;
    for(int i=0;i<iterations;i++, iterationsChecked++){
        //Generate neighbours
        vector<vector<int>> neighbours=findNeighbour(bestNeighbour);
        bestNeighbour={};
        for (vector<int> bour : neighbours) {
            if(find(problem.checked.begin(),problem.checked.end(),bour)==problem.checked.end()){
                if(problem.checkHowCorrect(bour)< problem.checkHowCorrect(bestNeighbour))bestNeighbour=bour;
            }
        }
        if(problem.checkHowCorrect(bestNeighbour)<problem.checkHowCorrect(bestSolution))bestSolution=bestNeighbour;
        problem.checked.push_back(bestNeighbour);
        if(problem.checked.size()>tabSize){
            problem.checked.erase(problem.checked.begin());
        }
        if(showProgress){
            cout << i << " " << problem.checkHowCorrect(problem.checked.back()) << " " << problem.checkHowCorrect(bestSolution) << endl;
        }
    }
    if(showHwoManyIterations)cout<<iterationsChecked<<endl;
    if(showHowManyChecked)cout<<problem.HowManyTimesChecked<<endl;
    return bestSolution;
}
vector<int> SolveRandomClimbing(Problem problem, int iterations, bool details, bool showHwoManyIterations, bool showHowManyChecked, bool showProgress) {
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
        //BinaryZeros = Random binary subset
        //best solution = max
        //
        tempResult = translate(problem.multiset,neighbours.at(0));
        if(problem.checkHowCorrect(tempResult)==0){
            //cout<<"FOUND SUBSET!"<<endl;
            if(showHwoManyIterations)cout<<iterationsChecked<<endl;
            if(showHowManyChecked)cout<<problem.HowManyTimesChecked<<endl;
            return tempResult;
        }
        int randomIndex = mt1()%neighbours.size();
        tempResult= translate(problem.multiset,neighbours.at(randomIndex));
        if(problem.checkHowCorrect(tempResult)==0){
            //cout<<"FOUND SUBSET!"<<endl;
            if(showHwoManyIterations)cout<<iterationsChecked<<endl;
            if(showHowManyChecked)cout<<problem.HowManyTimesChecked<<endl;
            return tempResult;
        }
        if(problem.checkHowCorrect(bestSolution)>problem.checkHowCorrect(tempResult)){
            bestSolution = tempResult;
            binaryZeroes=neighbours.at(randomIndex);
        }
        if(showProgress){
            cout << i << " " << problem.checkHowCorrect(problem.checked.back()) << " " << problem.checkHowCorrect(bestSolution) << endl;
        }
    }
    if(showHwoManyIterations)cout<<iterationsChecked<<endl;
    if(showHowManyChecked)cout<<problem.HowManyTimesChecked<<endl;
    return bestSolution;
}
vector<int> SolveBruteForce(Problem problem, int iterations, bool details, bool showHwoManyIterations, bool showHowManyChecked, bool showProgress){
    vector<int> multiset = problem.multiset;
    vector<int> tempResult;
    vector<int> bestSolution = multiset;
    int bestCost = problem.checkHowCorrect(bestSolution);
    int k=0;
    for(int i=1;i<=problem.multiset.size();i++)        //Ilość liczb w subsecie
    {
        //sort(multiset.begin(),multiset.end());
        do{

            tempResult.clear();
            for(int j=0;j<i;j++){
                tempResult.push_back(multiset.at(j));
            }

            if(find(problem.checked.begin(), problem.checked.end(), tempResult)==problem.checked.end()){
                int cost = problem.checkHowCorrect(tempResult);
                if(details){
                    cout<<"Subset: ";
                    cout<<"{"<<tempResult.at(0);
                    for(int j=1;j<tempResult.size();j++){
                        cout<<", "<<tempResult.at(j);
                    }
                    cout<<"}";
                    cout<<" HowFar: "<<cost<<"\n";
                }
                if(cost==0){
                    if(showHwoManyIterations)cout<<iterationsChecked<<endl;
                    if(showHowManyChecked)cout<<problem.HowManyTimesChecked<<endl;
                    return tempResult;
                }else if(cost<bestCost){
                    bestSolution=tempResult;
                    bestCost=cost;
                }
                problem.checked.push_back(tempResult);
            }
            k++;
            iterationsChecked++;
        }while(std::next_permutation(multiset.begin(),multiset.end())&&k<iterations);
    }
    cout<<"No subset found"<<endl;
    cout<<"Best solution: ";
    cout<<"{"<<bestSolution.at(0);
    for(int j=1;j<bestSolution.size();j++){
        cout<<", "<<bestSolution.at(j);
    }
    cout<<"}";
    int cost = problem.checkHowCorrect(bestSolution);
    cout<<" HowFar: "<<cost<<"\n";
    if(showHwoManyIterations)cout<<iterationsChecked<<endl;
    if(showHowManyChecked)cout<<problem.HowManyTimesChecked<<endl;
    return bestSolution;
}
vector<int> SolveClimbing(Problem problem, int iterations, bool details, bool showHwoManyIterations, bool showHowManyChecked, bool showProgress) {
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
        //BinaryZeros = Random binary subset
        //best solution = max
        //
        tempResult = translate(problem.multiset,neighbours.at(0));
        if(problem.checkHowCorrect(tempResult)==0){
            cout<<"FOUND SUBSET!"<<endl;
            if(showHwoManyIterations)cout<<iterationsChecked<<endl;
            if(showHowManyChecked)cout<<problem.HowManyTimesChecked<<endl;
            return tempResult;
        }
        for(int j=1;j<neighbours.size();j++){
            tempResult = translate(problem.multiset,neighbours.at(j));
            if(problem.checkHowCorrect(tempResult)==0){
                cout<<"FOUND SUBSET!"<<endl;
                if(showHwoManyIterations)cout<<iterationsChecked<<endl;
                if(showHowManyChecked)cout<<problem.HowManyTimesChecked<<endl;
                return tempResult;
            }
            if(problem.checkHowCorrect(bestSolution)>problem.checkHowCorrect(tempResult)){
                bestSolution = tempResult;
                binaryZeroes=neighbours.at(j);
            }
        }
        cout<<"Subset: ";
        cout<<"{"<<bestSolution.at(0);
        for(int j=1;j<bestSolution.size();j++){
            cout<<", "<<bestSolution.at(j);
        }
        cout<<"}";
        int cost = problem.checkHowCorrect(bestSolution);
        cout<<" HowFar: "<<cost<<"\n";

    }
    cout<<"No subset found"<<endl;
    cout<<"Best solution: ";
    cout<<"{"<<bestSolution.at(0);
    for(int j=1;j<bestSolution.size();j++){
        cout<<", "<<bestSolution.at(j);
    }
    cout<<"}";
    int cost = problem.checkHowCorrect(bestSolution);
    cout<<" HowFar: "<<cost<<"\n";
    if(showHwoManyIterations)cout<<iterationsChecked<<endl;
    if(showHowManyChecked)cout<<problem.HowManyTimesChecked<<endl;
    return bestSolution;
}
vector<int> SolveRandomTry(Problem problem, int iterations, bool details, bool showHwoManyIterations, bool showHowManyChecked, bool showProgress) {
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
        cout<<"Subset: ";
        cout<<"{"<<tempResult.at(0);
        for(int j=1;j<tempResult.size();j++){
            cout<<", "<<tempResult.at(j);
        }
        cout<<"}";
        int cost = problem.checkHowCorrect(tempResult);
        cout<<" HowFar: "<<cost<<"\n";
        if(cost==0){
            cout<<"FOUND CORRECT SUBSET!";
            if(showHwoManyIterations)cout<<iterationsChecked<<endl;
            if(showHowManyChecked)cout<<problem.HowManyTimesChecked<<endl;
            return tempResult;
        }else if(cost<bestCost){
            bestSolution=tempResult;
            bestCost=cost;
        }
    }
    cout<<"No subset found"<<endl;
    cout<<"Best solution: ";
    cout<<"{"<<bestSolution.at(0);
    for(int j=1;j<bestSolution.size();j++){
        cout<<", "<<bestSolution.at(j);
    }
    cout<<"}";
    int cost = problem.checkHowCorrect(bestSolution);
    cout<<" HowFar: "<<cost<<"\n";
    if(showHwoManyIterations)cout<<iterationsChecked<<endl;
    if(showHowManyChecked)cout<<problem.HowManyTimesChecked<<endl;
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
        vector<int> changedBinary = binary;
        int changedIndex = mt1()%binary.size();
        changedBinary.at(changedIndex)+=1;
        changedBinary.at(changedIndex)%=2;
        neighbours.push_back(changedBinary);
    }
    return neighbours;
}
