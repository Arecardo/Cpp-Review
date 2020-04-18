#include <iostream>
#include "func.h"
using namespace std;

int main(){
    string a = "ab";
    string b = "acdb";

    if(isPredecessor(a, b)) cout<<"Yes"<<endl;
    else cout<<"No"<<endl;
    return 0;
}