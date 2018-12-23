#ifndef LINKER_H
#define LINKER_H

#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>

using namespace std;

int hexToDec(std::string str){

        int address;

        std::stringstream stream;
        stream << str;
        stream >> std::hex >> address;

        return address;
    }

int stringToDec(std::string str){

        int output;

        std::stringstream stream;
        stream << str;
        stream >> output;

        return output;
}

    int hexStringToDec(string str){
        int output;
        stringstream stream;
        stream <<hex<<str;
        stream >> output;

        return output;
    }

    string intToHexString(int input){

        std::stringstream ss;
        ss<<std::hex<<input;
        return ss.str();
    }

int readFile(vector<vector<string>> &code){

        std::ifstream inFile("in.txt");
        std::string temp;
        std::string tempNoSpace="";
        int i=0;

        while (std::getline(inFile, temp)){

            for(int j=0;j<temp.size();j++){

                if(temp[j] != ' ' && temp[j] != '\t' && temp[j] != '\n' && temp[j] != '\0'){

                    tempNoSpace+=temp[j];

                }else{
                    code[i].push_back(tempNoSpace);
                    tempNoSpace.clear();
                }

            }

            code[i++].push_back(tempNoSpace);
            tempNoSpace.clear();
        }
        inFile.close();
        return i;
    }

void readESTAB(vector<vector<string>> &estab){
        std::ifstream inFile("ESTAB.txt");
        std::string temp;
        std::string tempNoSpace="";
        int i=0;

        while (std::getline(inFile, temp)){

            for(int j=0;j<temp.size();j++){

                if(temp[j] != ' ' && temp[j] != '\t' && temp[j] != '\n' && temp[j] != '\0'){

                    tempNoSpace+=temp[j];

                }else{
                    estab[i].push_back(tempNoSpace);
                    tempNoSpace.clear();
                }

            }

            estab[i++].push_back(tempNoSpace);
            tempNoSpace.clear();
        }
}

void extractObjectCode(vector<int>&objectCode, vector<vector<string>> code,int lines,vector<int>&address,vector<int>startAddresses){
    int progAddr=0;
    int temp=0;
    int k = 0;
    for(int i=0; i<lines ; i++){
            if(code[i][0]=="H"){
                progAddr=hexStringToDec(code[i][2]);
                progAddr=startAddresses[0+k];
                k++;
                cout<<progAddr<<endl;
            }else if (code[i][0]=="T"){
                    cout<<"found"<<endl;
                    temp=hexStringToDec(code[i][1]) + progAddr; //get starting address of text record
                for(int j=2 ; j<code[i].size() ; j++){
                    if(code[i][j].size()== 6){
                        //objectCode.insert(pair<int,int>(temp,hexStringToDec(code[i][j])));
                        objectCode.push_back(hexStringToDec(code[i][j]));
                        address.push_back((temp));
                        temp+=3;
                    }else if(code[i][j].size()== 8){
                        //objectCode.insert(pair<int,int>(temp,hexStringToDec(code[i][j])));
                        objectCode.push_back(hexStringToDec(code[i][j]));
                        address.push_back((temp));
                        temp+=4;
                    }

                }
            }

        }
}

void getStartAddresses(vector<vector<string>> estab,vector<int>&startAddresses){

    for(int i=0 ; i<estab.size() ; i++){
        if(estab[i].size() == 3){
            startAddresses.push_back(hexStringToDec(estab[i][1]));
        }
    }

}

void getESTABvalues(vector<vector<string>> estab,map<string,string>&estabValues){

    for(int i=0 ; i<estab.size() ; i++){
        if(estab[i].size() == 2){
            estabValues.insert(pair<string,string>(estab[i][0],estab[i][1]));
        }
    }
}

void extractModification(vector<vector<string>> code,int lines,vector<int>&modifyAddress,vector<int>&modifyObjectCode,vector<int>startAddresses,map<string,string>estabValues){
    int progAddr=0;
    int temp=0;
    int k = 0;
    for(int i=0; i<lines ; i++){
            if(code[i][0]=="H"){
                progAddr=hexStringToDec(code[i][2]);
                progAddr=startAddresses[0+k];
                k++;
            }else if (code[i][0]=="M"){
                if(code[i][2] == "05"){
                    modifyAddress.push_back(hexStringToDec(code[i][1]) - 1);
                    modifyObjectCode.push_back(hexStringToDec(estabValues.find()->second));
                }

            }

        }
}

#endif //
