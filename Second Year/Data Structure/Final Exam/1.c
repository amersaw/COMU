#include <stdio.h>
int hash(char * tc,int onun_kuvveti){
	if(tc[11] != '\0') return -1; //Hata cunku TC numaranin uzunlugu 11 degil
	int sonuc = 0,i;
	for(i=0;i<onun_kuvveti;i++){
		char simdiki_hane = tc[10-i];
		int simdiki_hane_int = simdiki_hane - '0' ;
		sonuc = sonuc * 10 + simdiki_hane_int;
	}
	return sonuc;
}

int main(){
	int res = hash("01234567891",3);
	printf("%d",res);
	return 0;
}
