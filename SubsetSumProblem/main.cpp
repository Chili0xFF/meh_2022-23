#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class problem{
    public:
        vector<int> multiset;
        int targetValue;
        problem(int target,vector<int> set){
            this->targetValue=target;
            this->multiset=set;
        };
        void showMultiset(){
            for(int i=0;i<this->multiset.size();i++){
                cout<<this->multiset.at(i);
            }
        };
        int checkIfCorrect(vector<int> subset){
            int result=accumulate(subset.begin(),subset.end(),0);
            return (targetValue-result);
        };
};

int main() {
    problem problem(4,{1,2,3,4});
    cout<<problem.checkIfCorrect({3,1})<<endl;
    problem.showMultiset();
    return 0;
}
