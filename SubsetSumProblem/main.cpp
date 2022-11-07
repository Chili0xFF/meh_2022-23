#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>

typedef std::mersenne_twister_engine<uint_fast32_t,
        32,624,397,31,0x9908b0df,11,0xffffffff,7,0x9d2c5680,15,0xefc60000,18,1812433253>
        mt19937;
mt19937 mt1(time(nullptr));

using namespace std;

class Problem{
    public:
        vector<int> multiset;
        vector<int> binaryResult;
        vector<vector<int>> checked;
        int targetValue;

    void zero() {
        for(int j=0;j<this->multiset.size();j++){
            this->binaryResult.push_back(0);
        }
    }

    Problem(int target, vector<int> set){
            this->targetValue=target;
            this->multiset=set;
            zero();
        };
        void showMultiset(){
            cout<<"{"<<this->multiset.at(0);
            for(int i=1;i<this->multiset.size();i++){
                cout<<", "<<this->multiset.at(i);
            }
            cout<<"}\n";
        };
        int checkHowCorrect(vector<int> subset){
            int result=accumulate(subset.begin(),subset.end(),0);  //Funkcja kosztu
            int differenceFromZero = result-targetValue;
            return abs(differenceFromZero);
        };
};


vector<int> SolveRandomTry(Problem problem, int iterations=1000);

vector<int> SolveClimbing(Problem problem, int iterations=1000);

vector<int> SolveBruteForce(Problem problem);

int main() {
    Problem problem(60,{2,4,8,16,2,4,8,16,2,4,8,16});
    //problem.showMultiset();
    //SolveBruteForce(problem);
    SolveRandomTry(problem,10);
    //SolveClimbing(problem);
    return 0;
}

vector<int> SolveBruteForce(Problem problem){
    vector<int> multiset = problem.multiset;
    vector<int> tempResult;
    vector<int> bestSolution = multiset;
    for(int i=1;i<=problem.multiset.size();i++)        //Ilość liczb w subsecie
    {
        //sort(multiset.begin(),multiset.end());
        do{
            tempResult.clear();
            for(int j=0;j<i;j++){
                tempResult.push_back(multiset.at(j));
            }

            if(find(problem.checked.begin(), problem.checked.end(), tempResult)==problem.checked.end()){
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
                    return tempResult;
                }else if(cost<problem.checkHowCorrect(bestSolution)){
                    bestSolution=tempResult;
                }
                problem.checked.push_back(tempResult);
            }


        }while(next_permutation(multiset.begin(),multiset.end()));
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
    return bestSolution;
}

vector<int> SolveClimbing(Problem problem, int iterations) {
    vector<int> binaryZeroes = problem.binaryResult;
    vector<int> bestSolution = problem.multiset;
    for(int i=0;i<iterations;i++){
        
    }
    return {0};
}

vector<int> SolveRandomTry(Problem problem, int iterations) {
    vector<int> binaryZeroes = problem.binaryResult;
    vector<int> bestSolution = problem.multiset;
    for(int i=0;i<iterations;i++){
        binaryZeroes = problem.binaryResult;
        //Generate size
        int size = (mt1()%(problem.multiset.size()-1))+1;
        //Generate numbers;
        for(int j=0;j<size;j++){
            int indexToOne = mt1()%(problem.multiset.size());
            if(binaryZeroes.at(indexToOne)==0)binaryZeroes.at(indexToOne)=1;
            else j--;
        }
        vector<int> tempResult;
        for (int j = 0; j < binaryZeroes.size(); ++j) {
            if(binaryZeroes.at(j)==1){
                tempResult.push_back(problem.multiset.at(j));
            }
        }
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
            return tempResult;
        }else if(cost<problem.checkHowCorrect(bestSolution)){
            bestSolution=tempResult;
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
    return bestSolution;
}
