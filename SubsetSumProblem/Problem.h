//
// Created by s23049 on 28.11.2022.
//
#include <iostream>
#include <vector>
#include <numeric>

#ifndef SUBSETSUMPROBLEM_PROBLEM_H
#define SUBSETSUMPROBLEM_PROBLEM_H
class Problem{
public:
    std::vector<int> multiset;
    std::vector<int> binaryResult;
    std::vector<std::vector<int>> checked;
    int targetValue;
    int HowManyTimesChecked=0;
    void zero() {
        for(int j=0;j<this->multiset.size();j++){
            this->binaryResult.push_back(0);
        }
    }

    Problem(int target, std::vector<int> set){
        this->targetValue=target;
        this->multiset=set;
        zero();
    };
    void showMultiset(){
        std::cout<<"{"<<this->multiset.at(0);
        for(int i=1;i<this->multiset.size();i++){
            std::cout<<", "<<this->multiset.at(i);
        }
        std::cout<<"}\n";
    };
    int checkHowCorrect(std::vector<int> subset){
        HowManyTimesChecked++;
        int result=std::accumulate(subset.begin(),subset.end(),0);  //Funkcja kosztu
        int differenceFromZero = result-targetValue;
        return abs(differenceFromZero);
    };
};
#endif //SUBSETSUMPROBLEM_PROBLEM_H
