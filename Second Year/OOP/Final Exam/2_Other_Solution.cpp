#include <iostream>
#include<list>
#include<algorithm>
using namespace std;

int A[]= {3,5,6,20,28,4,32} ;
int main(){
    list<int> st=list<int>(A,A+7);//Bu en uygun yapici kullandik, ilk parametre liste basi, ikinci parametre listenin son elamandan bir daha sonra eleman (son eleman :st+6)
    list<int>::iterator it; 
    it = st.end(); 
    while(it!=st.begin()){ 
        it--;
        cout<<*it<<endl;// simdiki elemanin degeri yazdiriyoruz
    }
    cout<<"Arama yapacaksiniz elemani giriniz :";
    int ara;
    cin>>ara;//kullancidan hangi eleman arayacagiz aliyoruz
    list<int>::iterator arama_sonuc = find(st.begin(),st.end(),ara);    // yeni isaretci tanimliyoruz ve find algoritmasi cagiriyoruz
                                                                        // Find Algoritmasi ilk parametre : listenin basi
                                                                        // ikinci parametre listenin son elemanin sonraki eleman
                                                                        // ucuncu parametre arama yapmak istedegim eleman
    if(arama_sonuc == st.end()){ // eger buldugumuz sonuc son elemanin sonraki eleman ayni ise, demek ki listede yok
        cout<<"Listede DEGIL"<<endl;
    } else {  // degil ise demek ki listede var
        cout<<"Bulundu"<<endl;;
    }


    return 0;
}
