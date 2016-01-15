#include <iostream>
#include<list>
#include<algorithm>
using namespace std;

template<class T> //herhangi toplama islem tanimlanmis tip kabul eder
double hesapla (T* matris, int size){
    double cift = 0, tek=0;
    for(int i=1;i<=size;i++){
        T eleman = matris[i-1]; //simdiki eleman aliyoruz, burda i-1 aldik cunku 1'den basladik sifirdan degil
        if(i%2==0){//cift indexli
            cift+=eleman*eleman; // simdiki elemanin karesi (cift)'e ekliyoruz
        }else{ //tek indexli
            tek+=eleman*eleman*eleman; // simdiki elemanin kupu (tek)'e ekliyoruz
        }
    }
    return tek/cift; //Soru dogru anladiysam boyle olmasi lazim ya da cift/tek olabilir
}

int main(){
    int a[]={5,8,4,3,9,12};
    double b[]={12.4, 14.5, 16.12, 23.18, 21.2, 22.44, 55.33, 66.20, 77.66 ,78.0};

    cout<<hesapla(a,6)<<endl;
    cout<<hesapla(b,10)<<endl;
    return 0;
}
