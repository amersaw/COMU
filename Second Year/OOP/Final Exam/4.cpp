#include <iostream>
#include<cstring>
using namespace std;

class String{
    char* contents;
    int size;
public:
    String(char* input);
    friend ostream& operator<<(ostream&, String);
    ~String();

};
String::String(char* input){//yapici
    size = strlen(input);
    if(size>10) // eger aldigimiz string'in uzunlugu 10'dan daha uzun ise hata firlatacagiz
        throw "Hata Oldu, Verilen string 10 karakterden fazla olmaz"; //hata firlatiyoruz ve yapicidan cikiyoruz (devam etmeyecegiz return gibi)
    //hata olmadiginda burdan devam edecegiz
    contents = new char [size+1];//aldigimiz string boyut kadariyla arti bir son harf icin (\0)
    strcpy(contents,input);
}

ostream& operator<<(ostream& os, String obj){//cout ile kullanabilmek icin
    os<<obj.contents;
    return os;
}
String::~String(){ //yokedici
    if(contents != NULL)
        delete[] contents;
}
int main(){
    try{
        String str="Pranioma tomatona arabyamakana ghalia";//burda biliyoruz ki hata olacak ama try-catch icinde oldugu icin hemen catch bloğuna gidecek
    }
    catch(const char* ex){ //char* tipinden bir hata attiliginda burda gelecegiz, ve bu hatanin içerdekleri ex içinde olacak
        cout<<ex; //aldığımız hata içerdekleri ekrene yazdırıyoruz.
    }
    return 0;
}
