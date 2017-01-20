//Bu üçgen her eleman üsteki iki elemanların toplamı 
//Kenarlar her zaman 1 dır 
//Matris haliblnde yazsak  böyle olur 
//1
//1   1
//1   2   1
//1   3   3   1
//1   4   6    4   1
//1  5   10  10  5   1
//Buna dikkat edilirse her eleman üst satrindaki önceki sütun ve aynı sütun toplamı, koordinat olarak konuşsak 
//(ilk parametre satır olursa) :
//  pascal(i,j)=pascal(i-1,j-1) + pascal(i-1,j)
//Aynı zamanda dikkat edersek kenarlar her zaman 1 dır, kenarlar demek ki satır numarası sütun numarası aynı olunca (sağ kanat bir elemanı )  veya sütun numarası 0 olunca (sol kanat bir elemanı), bunlar isteyince hemen 1 dondurabiliriz, Pascal fonksiyon son hali böyle olur 

def pascal(i:Int, j:Int) :Int={
   if(i==0 || i==j) 1
   else pascal(i-1,j-1) + pascal(i-1,j)
} 


