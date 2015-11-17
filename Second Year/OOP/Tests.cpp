#include <iostream>
#include <stdlib.h>
using namespace std;
class MyClass{
private:
    static int membersCount;

public:
    int value;
    MyClass(const MyClass &);
    MyClass();
    ~MyClass();
    MyClass operator=(const MyClass &);
    MyClass operator=(int);
    void * operator new (size_t s);
    MyClass operator ++();
    MyClass operator ++(int); //POST
    friend ostream & operator <<(ostream&, const MyClass &);
};
ostream & operator <<(ostream& os, const MyClass & obj){
    os<<obj.value<<endl;
}
MyClass MyClass::operator ++(int x){
    value++;
    cout<<"Post ++ operator called"<<endl;
    return *this;
}
MyClass MyClass::operator ++(){
    value++;
    cout<<"Pre ++ operator called"<<endl;
    return *this;
}
void * MyClass::operator new (size_t s){
    void * p = malloc(s);

    cout<<"new operator called"<<endl;
    return p;
}
MyClass MyClass::operator=(int a){
    this->value = a;
}
MyClass MyClass::operator=(const MyClass & obj){
    value= obj.value;
    cout<<"Operator = Called."<<"Members Count : "<<membersCount<<endl;
    return *this;
}
MyClass::MyClass(const MyClass & obj){  //Copy Constructor
    value = obj.value;
    membersCount++;
    cout<<"COPY constructor Called.\t"<<"Members Count : "<<membersCount<<endl;
}
MyClass::MyClass(){  //Constructor
    value=0;
    membersCount++;
    cout<<"Constructor Called.\t"<<"Members Count : "<<membersCount<<endl;
}

MyClass::~MyClass(){    //Deconstructure
    membersCount--;
    cout<<"Deconstructor Called.\t"<<"Members Count : "<<membersCount<<endl;
}
void PrintMyClass(MyClass x){
    cout<<"The value of this MyClass object is :#"<<x.value<<"#\n";
}

int MyClass::membersCount = 0;
int main()
{
    {
        MyClass a;
        a.value = 10;
        cout<<a;
        MyClass b;

        b=a;

        ++a;
        a++;
    }
    return 0;
}
