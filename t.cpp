#include<iostream>
#include<algorithm>
#include<string>
#include<map>
using namespace std;
int main(){
    map<char,int>mymap;
    char x = 'f';
    mymap['a']=150;
    mymap['b']=100;
    mymap['c']=200;
    mymap['b']+=250;
    mymap[x] = 500;
    if(mymap.find('?')!=mymap.end()){
        cout<<"aaaaaaa"<<endl;
    }
    cout<<mymap['f']<<endl;
    return 0;
}
