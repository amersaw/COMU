#include<iostream>
using namespace std;
class tmp{
    static int nesnelerSayisi;
public:
    void sifirla(){
        nesnelerSayisi = 0;
    }
    tmp(){
        cout<<"Constructor Cagirildi. nesnelerin sayisi :"<<++nesnelerSayisi<<endl;
    }
    ~tmp(){
        cout<<"Deconstructor Cagirildi. nesnelerin sayisi :"<<--nesnelerSayisi<<endl;
    }
};

int tmp::nesnelerSayisi;
int main(){

    {
        cout<<"Blok 1 basladi."<<endl;
        tmp a,b,c;
        cout<<"Blok 1 bitti"<<endl;
        {
            cout<<"Blok 2 basladi."<<endl;
            tmp d,e;
            cout<<"Blok 2 bitti"<<endl;
        }

    }
    return 0;
}
