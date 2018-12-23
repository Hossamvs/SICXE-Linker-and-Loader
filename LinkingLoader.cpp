#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "Linker.h"
using namespace std;

int main(){
    vector<vector<string>> code(1000);
    vector<vector<int>> estab(500);
    vector<string>objectCode;
    vector<string>address;

    int lines = readFile(code);
    extractObjectCode(objectCode,code,lines,address);
    //cout<<code[0][1][0]<<endl;

/*Debugging */
//    for(int i=0; i<code.size() ; i++)
//        for(int j = 0 ; j< code[i].size() ; j++)
//            cout<<code[i][j]<<endl;

//    for( std::map<int,int>::const_iterator it = objectCode.begin(); it != objectCode.end(); ++it )
//    {
//      int value = it->first;
//      int key = it->second;
//      cout<<value<<"\t"<<key<<endl;
//
//    }
    for(int i=0; i<address.size(); i++){
        cout<<address[i]<<" |  "<<objectCode[i]<<endl;
    }
    return 0;
}
