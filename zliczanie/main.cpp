#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

string link = R"(..\..\SubsetSumProblem\testRandom_maxTarget=50149_randomTarget=23857.txt)";
string target = R"(..\..\SubsetSumProblem\target.txt)";
int main() {
    ifstream f(link);
    int suma=0;
    vector<int> multiset;
    if (f.is_open()) {
        string line;
        while (getline(f, line)) {
            suma+= stoi(line);
            multiset.push_back(stoi(line));
        }
        f.close();
    }else {
        cout<<"error, failed to load file: ";
        cout<<link<<endl;
        return 0;
    }
    ifstream f_target(target);
    vector<int> target_set;
    if (f_target.is_open()) {
        string line;
        while (getline(f_target, line)) {
            target_set.push_back(stoi(line));
        }
        f.close();
    }else {
        cout<<"error, failed to load file: ";
        cout<<target<<endl;
        return 0;
    }
    int target_suma=0;
    for(int i=0;i<target_set.size();i++){
        if(target_set.at(i)==1){
            target_suma+=multiset.at(i);
        }
    }
    cout<<"target: "<<target_suma;
return 0;
}
//