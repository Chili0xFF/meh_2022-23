#include <iostream>
#include <fstream>
#include "json.hpp"

int main(int argc, char **argv){
    using json = nlohmann::json;
    using namespace std;
    std::ifstream f(argv[1]);
    json data = json::parse(f);
    cout<<data<<endl;

    string text = data.at("text");
    int textHeight = data.at("h");// / 2;
    int textWidth = data.at("w");//-text.length();
    int inBetween = (textWidth - text.length() - 2);
    int emptyLines=0;
    bool flagEmptyLines=false,flagExtraEmptyLine=false,flagBreakingLines=false;
    if(textHeight-3<0) {
        cout << "error, height must be >3 ";
        return 0;
    }else if(textHeight>0){
        flagEmptyLines=true;
        if(textHeight%2==0)flagExtraEmptyLine=true;
        emptyLines=textHeight/2-1;
    }
    int amountOfLinesNeeded=0;
    if(textWidth<text.length()){
        flagBreakingLines=true;
        amountOfLinesNeeded=text.length()/textWidth;
    }
    int a[amountOfLinesNeeded];


    for(int i=0;i<textWidth;i++) cout<<"#";     //TopBorder

    if(flagEmptyLines) {
        for (int i = 0; i < emptyLines; i++) {
            cout << "\n#";
            for (int j = 0; j < textWidth-2; j++)cout << " ";   //EmptyLines if apply
            cout << "#";
        }
    }
    if(flagExtraEmptyLine){
        cout << "\n#";
        for (int j = 0; j < textWidth-2; j++)cout << " ";       //ExtraLine if the emount of empty lines is not even
        cout << "#";
    }
    cout<<"\n#";
    for(int i=0; i < inBetween / 2; i++)cout << " ";
    if(text.length()%2!=0)cout<<" ";
    cout<<text;                                             //TheRealLine
    for(int i=0; i < inBetween / 2; i++)cout << " ";
    cout<<"#";

    if(flagEmptyLines) {
        for (int i = 0; i < emptyLines; i++) {
            cout << "\n#";
            for (int j = 0; j < textWidth-2; j++)cout << " ";   //EmptyLines if apply
            cout << "#";
        }
    }
    cout<<"\n";
    for(int i=0;i<textWidth;i++) cout<<"#";                 //BottomLine
    return 0;
}