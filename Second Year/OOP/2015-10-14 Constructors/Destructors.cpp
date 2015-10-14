//Nesne Dizilerini Başlatma
#include<iostream>
#include<cstdlib>
#include<string.h>

using namespace std;

class String{
    int size;
    char *contents;
public:
    String(const char*);
    void print();
    ~String();//Destructor
};

String::String(const char *in_data){
    cout<<"Constructor has been invoked"<<endl;
    size = strlen(in_data);
    contents = new char[size +1];
    strcpy(contents,in_data);
}

String::~String(){
    cout<<"Destructor has been invoked"<<endl;
    delete[] contents;
}

void String::print(){
    cout<<contents<<", Size:"<<size<<endl;
}

int main(){
    String string1("string 1");
    String string2("string 2");
    string1.print();
    string2.print();
    return 0;//Destructor is called twice
}
