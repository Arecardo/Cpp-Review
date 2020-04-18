#include <iostream>
#include <string>

bool isPredecessor(std::string t, std::string word){
        // initial
        for(int i=0; i<t.size(); i++){
            if(t[i] != word[i]){
                t.insert(t.begin()+i,word[i]);
                std::cout<<"t now is: "<<t<<std::endl;
                if(t != word) return false;
                else return true;
            }
        }
        t.insert(t.end(), *(word.end()-1));
        return t == word;
}