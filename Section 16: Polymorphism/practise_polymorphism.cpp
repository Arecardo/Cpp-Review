/*  - Practise_Polymorphism.cpp
    -
    - This is the source code for Practice Student Excecise #12
    - 
    - Author: Xinrun Zhang
    - Date: April 7, 2020
*/

#include <iostream>
using namespace std;

class Shape{
    public:
        virtual float area()=0;
        virtual float perimeter()=0;
};

class Rectangle: public Shape{
    public:
        Rectangle(float l=1, float b=1){
            length = l;
            breadth = b;
        }

        float area(){ return length * breadth;}
        float perimeter(){ return 2*(length + breadth);}

    private:
        float length;
        float breadth;
};

class Circle: public Shape{
    public:
        Circle(float r=1){
            radius = r;
        }

        float area(){ return pi*radius*radius;}
        float perimeter(){ return 2*pi*radius;}
        
    private:
        float radius;
        const float pi = 3.14;
};

int main(){
    // initial base shape pointer to derived rectangle
    Shape *p = new Rectangle(4.1, 3.2);
    cout<<"Hello, Rectangle!"<<endl;
    cout<<"The area of the rectangle: "<<p->area()<<endl;
    cout<<"The perimeter of the rectangle: "<<p->perimeter()<<endl;

    // change pointer to a new derived circle
    p = new Circle(3.0);
    cout<<endl;
    cout<<"Hello, Circle!"<<endl;
    cout<<"The area of the circle: "<<p->area()<<endl;
    cout<<"The perimeter of the circle: "<<p->perimeter()<<endl;

    return 0;
}