#include <iostream>
using namespace std;

class Test2;

class Test{
    public: 
        Test(int n=10){
            a = n;
        }

        friend int getA(); // friend function
        friend Test2; // friend class

    private:
        int a = 0;    
};

int getA(){
    Test t(5);
    return t.a;
}

class Test2{
    public:
        Test b;

        void fun(){
            cout<<"friend class: "<<b.a<<endl;
        }
};

int fun(){
    cout<<"This is fun!"<<endl;
    return 0;
}

int main(){
    cout<<"Hello~"<<endl;
    int t = getA();
    cout<< "friend function: "<<t<<endl;

    fun();

    Test2 kk;
    kk.fun();

    return 0;
}