#include <iostream>
#include<cstring>
using namespace std;

class Kenar{
    int x1,y1,x2,y2;
public:
    Kenar(int a,int b, int c, int d){
        x1=a;
        y1=b;
        x2=c;
        y2=d;
    }
    void print(){
        cout<<"("<<x1<<","<<y1<<") ("<<x2<<","<<y2<<")\t";
    }

};
class Cokgen{
public:
    Kenar k1;
    Cokgen(Kenar k):k1(k){ //burda parametreden k1'e bilgiler aktarmak icin yapici baslatici kullandik
    }
    virtual void yazdir(){//Burda dikkat edilmesi lazim, virtual olarak tanimladik
        k1.print();
    }
};
class Ucgen:public Cokgen{
    Kenar k2,k3;
public:
    Ucgen(Kenar a, Kenar b,Kenar c):Cokgen(a),k2(b),k3(c){
    }
    void yazdir(){
        k1.print();
        k2.print();
        k3.print();
        cout<<endl;
    }
};



class Besgen:public Cokgen{
    Kenar k2,k3,k4,k5;
public:
    Besgen(Kenar a, Kenar b,Kenar c,Kenar d, Kenar e):Cokgen(a),k2(b),k3(c),k4(d),k5(e){
    }
    void yazdir(){
        k1.print();
        k2.print();
        k3.print();
        k4.print();
        k5.print();
        cout<<endl;
    }
};

void goster(Cokgen *obj){
    obj->yazdir();
}

int main(){
    Kenar x (1,2,3,4),y(5,6,7,8),z(0,1,5,7);
    Besgen *a = new Besgen (x,y,z,x,y);
    Ucgen *b = new Ucgen(z,x,y);
    goster(a);  // ayni fonksiyon bir defa besgen ile cagiriyoruz
    goster(b);  // ve bazen ucgen ile cagiriyoruz
                // ama her birisi kendi print fonksiyonu cagiriyor,
                // cunku temel sinifta print fonksiyonu VIRTUAL olarak tanimladik

    return 0;
}
