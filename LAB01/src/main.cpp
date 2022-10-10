#include <iostream>
#include <fstream>
#include "json.hpp"

int main(){
    using json = nlohmann::json;
    using namespace std;
    std::ifstream f("data\\data.json");
    json data = json::parse(f);
    cout<<data<<endl;
    return 0;
}