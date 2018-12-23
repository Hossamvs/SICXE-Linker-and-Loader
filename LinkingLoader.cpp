#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "Linker.h"
using namespace std;

int main(){
    vector<vector<string>> code(1000);
    vector<vector<string>> estab(500);
    map<string,string>estabValues;
    vector<int>objectCode;
    vector<int>address;
    vector<int>modifyAddress;
    vector<int>modifyObjectCode;
    vector<int>startAddresses;

    int lines = readFile(code);
    readESTAB(estab);
    getStartAddresses(estab,startAddresses);
    getESTABvalues(estab,estabValues);
    extractObjectCode(objectCode,code,lines,address,startAddresses);
    //extractModification(code,lines,modifyAddress,modifyObjectCode)
    //cout<<code[0][1][0]<<endl;

/*Debugging */
//    for(int i=0; i<code.size() ; i++)
//        for(int j = 0 ; j< code[i].size() ; j++)
//            cout<<code[i][j]<<endl;

//    for(int i=0; i<estab.size() ; i++)
//        for(int j = 0 ; j< estab[i].size() ; j++)
//            cout<<estab[i][j]<<endl;

//    for( std::map<int,int>::const_iterator it = objectCode.begin(); it != objectCode.end(); ++it )
//    {
//      int value = it->first;
//      int key = it->second;
//      cout<<value<<"\t"<<key<<endl;
//
//    }

//    for( std::map<string,string>::const_iterator it = estabValues.begin(); it != estabValues.end(); ++it )
//    {
//      string value = it->first;
//      string key = it->second;
//      cout<<value<<"\t"<<key<<endl;
//
//    }

//    for(int i=0; i<address.size(); i++){
//        cout<<address[i]<<" |  "<<objectCode[i]<<endl;
//    }
    return 0;
}
