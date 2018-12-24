#include<iostream>
#include<algorithm>
#include<string>
#include<map>
#include<sstream>
using namespace std;

    int hexStringToDec(string str){
        int output;
        stringstream stream;
        stream <<hex<<str;
        stream >> output;

        return output;
    }

int main(){
    string x = "ffffff";
    string y = "ffffff";
    int temp = hexStringToDec(x);
    int temp2 = hexStringToDec(y);
    int z = temp - temp2 +1;
    cout <<z<<endl;
    return 0;
}
