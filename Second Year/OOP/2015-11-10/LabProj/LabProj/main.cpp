#include <iostream>
#include <string>

using namespace std;

class Person{
private:
    string fName, lName, adres;
    int TC_ID_NO;
public:
    Person(string, string, string, int);
    void set_fName(string);
    void set_lName(string);
    void set_adres(string);
    void set_TC_ID_NO(int);
    void print();
};


void Person::set_fName(string input){

    fName = input;
}


void Person::set_lName(string input){
    lName = input;
}


void Person::set_adres(string input){
    adres = input;
}

void Person::set_TC_ID_NO(int input){
    TC_ID_NO = input;
}

Person::Person(string a, string s, string adres, int tc){
    set_fName(a);
    set_lName(s);
    set_adres(adres);
    set_TC_ID_NO(tc);
}

void Person::print(){
    cout<<"First Name :\t"<<fName<<endl;
    cout<<"Last Name  :\t"<<lName<<endl;
    cout<<"Address    :\t"<<adres<<endl;
    cout<<"TC Number  :\t"<<TC_ID_NO<<endl;
}

class Student : Person{
    string school;
public:
    Student(string, string, string, int, string);
    void set_School(string);
    void print();

};

void Student::set_School(string sc){
    school = sc;
}
Student::Student(string a, string s, string adres, int no, string sch) :
    Person(a,s,adres,no){
    set_School(sch);
}
void Student::print(){
    Person::print();
    cout<<"School     :\t"<<school<<endl;
}
int main()
{

    Student s1("Amer", "Sawan", "Canakkale", 99769, "COMU");
    s1.print();cout << "Hello world!" << endl;
    return 0;
}
