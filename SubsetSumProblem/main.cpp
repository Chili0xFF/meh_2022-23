#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>

using namespace std;

class Problem{
    public:
        vector<int> multiset;
        vector<vector<int>> checked;
        int targetValue;
        Problem(int target,vector<int> set){
            this->targetValue=target;
            this->multiset=set;
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



vector<int> SolveBruteForce(Problem problem){
    vector<int> multiset = problem.multiset;
    vector<int> tempResult;
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
                cout<<"}\n";
                int cost = problem.checkHowCorrect(tempResult);
                //cout<<"Koszt: "<<cost<<endl;
                if(cost==0){
                    cout<<"FOUND CORRECT SUBSET!";
                    return tempResult;
                }
                problem.checked.push_back(tempResult);
            }


        }while(next_permutation(multiset.begin(),multiset.end()));
    }
    return problem.multiset;
}

int main() {
    Problem problem(14,{1,2,3,3,4,5,6,7,8,1,2});
    //cout<<"Odleglosc wyniku od celu: "<<problem.checkHowCorrect({3,1})<<endl;
    problem.showMultiset();
    //vector<int> vector;
    SolveBruteForce(problem);
    return 0;
}
