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

void extractObjectCode(vector<int>&objectCode, vector<vector<string>> code,int lines,vector<int>&address,vector<int>startAddresses){
    int progAddr=0;
    int temp=0;
    int k = 0;
    for(int i=0; i<lines ; i++){
            if(code[i][0]=="H"){
                progAddr=hexStringToDec(code[i][2]);
                progAddr=startAddresses[0+k];
                k++;
                cout<<intToHexString(progAddr)<<endl;
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

void getStartAddresses(vector<vector<string>> code,vector<int>&startAddresses,int lines){//start addresses of programs
    int loadAddress= 16384; //LOAD ADDRESS AS IF PROVIDED FROM THE OS 4000
    int temp=loadAddress;
    int temp2=0;
    for(int i=0 ; i<lines ; i++){
        if(code[i][0] == "H"){
           startAddresses.push_back( loadAddress+ temp2 );
           temp2+=hexStringToDec(code[i][3]);
        }
    }
}

void getESTABvalues(vector<vector<string>> code,map<string,int>&estabValues,vector<int>startAddresses, int lines){
    int progLength =0;
    int k=0;
    for(int i=0 ; i<lines ; i++){
           if(code[i][0] == "H"){
                progLength=startAddresses[0+k];
                estabValues.insert(pair<string,int>(code[i][1],progLength));
                k++;
            }else if(code[i][0] == "D"){
                for(int j=1 ; j<(code[i].size() -1) ; j+=2){
                    //int temp = code[i].size()-1;
                    estabValues.insert(pair<string,int>(code[i][j],hexStringToDec(code[i][j+1]) + progLength));
                }
            }

    }
}

void extractModification(vector<vector<string>> code,int lines,vector<int>&modifyAddress,vector<int>&modifyObjectCode,vector<int>startAddresses,map<string,int>estabValues,vector<string>&operation){
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
                    modifyAddress.push_back(hexStringToDec(code[i][1])+progAddr - 1);
                    //cout<<estabValues.find(code[i][3].substr(1,code[i][3].size()-1))->second<<endl;
                    //cout<<"aaaaaaa "<<code[i][3].substr(0,1)<<endl;
                    operation.push_back(code[i][3].substr(0,1));
                    modifyObjectCode.push_back((estabValues.find(code[i][3].substr(1,code[i][3].size()-1))->second));
                }else if(code[i][2] == "06"){
                    modifyAddress.push_back(hexStringToDec(code[i][1])+progAddr);
                    //cout<<estabValues.find(code[i][3].substr(1,code[i][3].size()-1))->second<<endl;
                    operation.push_back(code[i][3].substr(0,1));
                    modifyObjectCode.push_back((estabValues.find(code[i][3].substr(1,code[i][3].size()-1))->second));
                }
            }

        }
}
void linkingAddresses(vector<vector<string>> code,int lines,vector<int>modifyAddress,vector<int>modifyObjectCode,vector<int>address,vector<int>objectCode,vector<string>&linkedAddresses,vector<string>operation){
    int k=0;
    int temp=0;
    int sum=0;
    for(int i=0 ; i < address.size() ; ++i){
        if(address[i]==modifyAddress[k]){
            if(operation[k] == "+"){
                if(objectCode[i]<= 16777215 && objectCode[i]>1048575){//between ffffff and fffff to get negative numbers
                    temp+= ~objectCode[i];
                    temp++;
                    temp+=modifyObjectCode[k];
                    }else{
                        temp+=o
                    }
                }else if(operation[k] == "-"){
                    if(objectCode[i]<= 16777215 && objectCode[i]>1048575)//between ffffff and fffff to get negative numbers
                    temp+= ~objectCode[i];
                    temp++;
                    temp+=modifyObjectCode[k];
                }
            k++;
            i--;
            cout<<"aaaaaaa "<<intToHexString(temp)<<endl;
            temp=0;
        }else{
            //linkedAddresses.push_back(intToHexString(objectCode[i]));//bug
        }
    }
}

#endif //
