// ikinci sorunun cevabı, "heap_mi" fonksiyonu kalan kodlar bu fonksiyon nasıl kullanacağız göstermek için

#include <stdio.h>

struct dugum{
    int key;
};

struct heap{
    struct dugum *dizi;
    int kapasite;
    int eleman_sayisi;
};

struct heap *heap_olustur(int kapasite){
    struct heap *gecici;
    gecici=(struct heap*)malloc(sizeof(struct heap));
    if(!gecici){
        printf("Dinamik alan ayirma basarisiz... \n");
        exit(1);
    }
    gecici->dizi=(struct dugum*)malloc(kapasite*sizeof(struct dugum));
    if(!gecici->dizi){
       printf("Dinamik alan ayirma basarisiz... \n");
       exit(1);
    }
    gecici->kapasite=kapasite;
    gecici->eleman_sayisi=0;
    return gecici;
}

void initialize_heap(struct heap *heap,int eleman_sayisi, int aralik){
    int i,j;
    int yeni,cik;

    if(eleman_sayisi >heap->kapasite) {
        printf("Heap gerekli kapasiteye sahip degil... exit...\n");
        exit(1);
    }
    srand(time(NULL));

    heap->dizi[0].key=rand()%aralik;
    for(i=1; i<eleman_sayisi; i++){
        while(1){
            cik=1;
            yeni=rand()%aralik;
            for(j=0; j<i; j++){
                if(yeni==heap->dizi[j].key){
                    cik=0; break;
                }
            }
            if(cik==0) continue;
            heap->dizi[i].key=yeni;
            break;
        }
    }
    heap->eleman_sayisi=eleman_sayisi;
}


int heap_mi(struct heap* h){
    int i;
    if(h==NULL) return 1;

    for(i=0; i< h->eleman_sayisi/2; i++){
		int sag = 2*i+2;
		int sol = 2*i+1;
        if( (sag < h->eleman_sayisi && h->dizi[i].key < h->dizi[sol].key) ||  // sag cocugu var ve babasindan buyuk ise demek ki heap degil
           (sol < h->eleman_sayisi && h->dizi[i].key < h->dizi[sol].key))  // sol cocugu var ve babasindan buyuk ise demek ki heap degil
            return 0;
    }
    return 1;
}

int main(){
    struct heap * h = heap_olustur(10);
    initialize_heap(h,10,11);
    if(heap_mi(h)==1)
        printf("Heapt?r.");
    else
        printf("Heap de?il.");

    return 0;
}
