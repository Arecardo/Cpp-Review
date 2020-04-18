#include <iostream>
#include <string>
using namespace std;

bool isPredecessor(string t, string word){
        // initial
        for(int i=0; i<t.size(); i++){
            if(t[i] != word[i]){
                t.insert(t.begin()+i,word[i]);
                cout<<"t now is: "<<t<<endl;
                if(t != word) return false;
                else return true;
            }
        }
        t.insert(t.end(), *(word.end()-1));
        return t == word;
}

int main(){
    string a = "ab";
    string b = "acb";

    if(isPredecessor(a, b)) cout<<"Yes"<<endl;
    else cout<<"No"<<endl;
    return 0;
}