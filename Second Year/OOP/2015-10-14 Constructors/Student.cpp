#include<iostream>
#include<string.h>

using namespace std;


class Date{
    int gun,ay,yil;
public:
    Date(int g=0, int a=0, int y=0){
        gun=g;
        ay=a;
        yil=y;
    }
    void print(){
        cout<<gun<<"/"<<ay<<"/"<<yil<<endl;
    }
};
class Ogrenci{
    char * adi,*soyadi;
    Date dgunu;
public:
    Ogrenci(char *, char *, Date);
    void print();
};
Ogrenci::Ogrenci(char * a, char *s, Date d){
    adi = new char[strlen(a) + 1]; // +1 cunku her string sonunda bir bitirme harf var '\0'
    strcpy(adi,a);

    soyadi = new char[strlen(s) + 1];
    strcpy(soyadi,s);

    dgunu = d;
}

void Ogrenci::print(){
    cout<<"Ogrencinin adi :\t"<<adi<<endl;
    cout<<"Ogrencinin Soyadi :\t"<<soyadi<<endl;
    cout<<"Ogrencinin Dogum tarihi :\t";
    dgunu.print();
}
int main(){

    Date *d = new Date(15,8,1993);
    Ogrenci *o1 = new Ogrenci("Amer", "Sawan", *d);
    o1->print();
    return 0;
}
