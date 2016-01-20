#include <stdio.h>
int hash(char * tc,int onun_kuvveti){
	
	//Hata cunku TC numaranin uzunlugu 11 degil, onun icin hemen cikiyoruz (return -1);
	if(tc[11] != '\0') return -1; 
	
	int sonuc = 0,i; 
	
	// 0'den başlıyoruz alacağımız haneler kadar
	for(i=0;i<onun_kuvveti;i++){ 
	
		//simdiki_hane alirken biz sondan basliyoruz, 
		//biliyoruz ki TC numara her zaman 11 hane 
		//Boylece i=0 iken son hane alabilmek icin 11. hane almamiz lazim (10 indexli olan)  => 10-0 = 10
		//Ayni sekilde i=1 iken 10. hane aliyoruz (9 indexli olan) => 10-1 = 9
		char simdiki_hane = tc[10-i];
		
		//Elimizde bir hane var "0","9" arasinda bir rakam, onu int'e çevirmemiz lazım
		//Burda ne yaptık açıklaması : 	http://goo.gl/mmVbjV
		int simdiki_hane_int = simdiki_hane - '0';
		
		//Soru'ya göre biz her zaman aldığımız sayı sonuna ekleyeceğiz
		//bunu yapabilmek için şimdiye kadar ulaştığımız sayıyı 10 ile çarpıyoruz ve ona elde ettiğimiz sayı ekliyoruz
		//ornek: 	Sonuc = 123  ve simdiki_hane_int=4 ise
		//			ilk önce sonuc'u 10 ile çarıyoruz yani 123*10=1230 ve ona simdiki_hane_int ekliyoruz 1230+4 = 1234
		sonuc = sonuc * 10 + simdiki_hane_int;
	}
	return sonuc;
}

int main(){
	int res = hash("01234567891",3);
	printf("%d",res);
	return 0;
}
