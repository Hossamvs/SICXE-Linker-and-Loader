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
    map<string,int>estabValues;
    vector<int>objectCode;
    vector<int>address;
    vector<int>modifyAddress;
    vector<int>modifyObjectCode;
    vector<int>startAddresses;
    vector<string>operation;
    map<string,int>linkedAddresses;
    int lines = readFile(code);
    getStartAddresses(code,startAddresses, lines);
    getESTABvalues(code,estabValues,startAddresses,lines);
    extractObjectCode(objectCode,code,lines,address,startAddresses);
    extractModification(code,lines,modifyAddress,modifyObjectCode,startAddresses,estabValues,operation);
    cout<<address.size()<<" sizes " <<modifyAddress.size()<< " Operations "<<objectCode.size()<<endl;
    try{
        linkingAddresses(modifyAddress,modifyObjectCode,address,objectCode,linkedAddresses,operation);
    }
    catch(const std::exception &exc){
        std::cerr << exc.what();
    }
    printMap(linkedAddresses);
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

//    for( std::map<string,int>::const_iterator it = estabValues.begin(); it != estabValues.end(); ++it )
//    {
//      string value = it->first;
//      int key = it->second;
//      cout<<value<<"\t"<<key<<endl;
//
//    }

    for(int i=0; i<address.size(); i++){
        cout<<intToHexString(address[i])<<" |  "<<intToHexString(objectCode[i])<<endl;
    }

    for(int i=0; i<modifyAddress.size(); i++){
        cout<<intToHexString(modifyAddress[i])<<" |  "<<intToHexString(modifyObjectCode[i])<<" | " <<operation[i]<<endl;
    }

//    for(int i=0 ; i<linkedAddresses.size(); i++){
//        cout<<linkedAddresses[i]<<endl;
//    }

    for( std::map<string,int>::const_iterator it = linkedAddresses.begin(); it != linkedAddresses.end(); ++it )
    {
      string value = it->first;
      int key = it->second;
      cout<<value<<"\t"<<intToHexString(key)<<endl;
    }


    return 0;
}
