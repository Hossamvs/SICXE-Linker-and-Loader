#include<iostream>
#include<algorithm>
#include<string>
using namespace std;
int main(){
    vector<string> x;
    vector<string>y;
    y.push_back("hi");
    x.push_back("hi");
    x.push_back("no");
    if(find(x.begin(),x.end(),y[0]) != x.end())
        cout<<"hi"<<endl;
    else{
        cout<<"heea";
    }
    return 0;
}
