#include<iostream>
#include<string.h>
using namespace std;

class Date{
    int gun, ay, yil;

public:
    Date(int, int, int);
    void date_ata(int, int, int);
    friend ostream operator<<(ostream&, const Date&);
};


Date::Date(int g =0, int a= 0, int y=0){
        gun=g;ay=a;yil=y;
}

void Date::date_ata(int g =0, int a= 0, int y=0){
        gun=g;ay=a;yil=y;
}

ostream operator<<(ostream & out, const Date &d){
    out<<d.gun<<d.ay<<d.yil<<endl;
    return out;
}

class Ogrenci{
    char* adi;
    char* soyadi;
    Date dgun;
public:
    Ogrenci(char*, char*, Date);
    void adi_ata(char* a);
    void soyadi_ata(char* );
    friend ostream & operator << (ostream&, const Ogrenci &);
};

Ogrenci::Ogrenci(char* a, char* s, Date d){
    adi = new char[strlen(a)+1];
    strcpy (adi,a);

    soyadi = new char[strlen(s)+1];
    strcpy(soyadi,s);

    dgun = d;
}

void Ogrenci::adi_ata(char* a){
    adi = new char[strlen(a)+1];
    strcpy (adi,a);
}
void Ogrenci::soyadi_ata(char* s){
    soyadi = new char[strlen(s)+1];
    strcpy(soyadi,s);
}
ostream & operator << (ostream& out, const Ogrenci & o){
    out<<"Ogrenci Bilgileri :"<<endl;
    out<<"Adi:"<<o.adi<<endl;
    out<<"Soyadi:"<<o.soyadi<<endl;
    out<<"Dogun Gunu:"<<o.dgun<<endl;
    return out;
}

int main(){
    Date d(15,8,1993);
    Ogrenci o("Amer", "Sawan",d);
    cout<<o;
    return 0;
}
