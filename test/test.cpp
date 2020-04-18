#include <iostream>
#include "func.h"
using namespace std;

int main(){
    string a = "ab";
    string b = "acdb";
    
    const int i = 1;

    // copy, top-level const is ignored
    int j = i;
    const int* const p1 = &j;
    j = 2;
    cout<<"The value of j is: "<<j<<endl;

    // copy, low-level const cannot be ignored
    // top-level const is ignored
    const int *p2 = p1;

    if(isPredecessor(a, b)) cout<<"Yes"<<endl;
    else cout<<"No"<<endl;
    return 0;
}