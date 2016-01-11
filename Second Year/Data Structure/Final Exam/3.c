// ikinci sorunun cevabı, "kardes_bul" fonksiyonu kalan kodlar bu fonksiyon nasıl kullanacağız göstermek için

#include <stdio.h>
#include <stdlib.h>



struct dugum {
    int icerik;
    struct dugum *sol;
    struct dugum *sag;
};



struct dugum* kardes_bul(struct dugum* root, struct dugum* d){
    if(root == NULL) return 0;
    if(root == d) return NULL; // kök'ün kardeşi olmaz
    if(root->sag == d) return root->sol;
    if(root->sol == d) return root->sag;
    struct dugum * sagSonuc = kardes_bul(root->sag,d);
    struct dugum * solSonuc = kardes_bul(root->sol,d);

    //return sagSonuc==NULL?solSonuc:sagSonuc;

    if(sagSonuc == NULL)
        return solSonuc;
    else
        return sagSonuc;
}


struct dugum* dugum_olustur(int icerik){
    struct dugum *d = (struct dugum*)malloc(sizeof(struct dugum));
    if(d==NULL){
        printf("Heapte gerekli yer ayrilamadi... exit ...\n");
        exit(1);
    }
    d->icerik = icerik; (*d).icerik=icerik;
    d->sol=d->sag=NULL;
    return d;
}


void ekle(struct dugum **kok,int icerik){
    if(*kok == NULL){

        *kok = dugum_olustur(icerik);
        return;
    }

    if(icerik > (*kok)->icerik){
        ekle(&((*kok)->sag),icerik);
        return;
    }
    else {
        ekle(&((*kok)->sol),icerik);
        return;
    }

}

void print(struct dugum* kok){
    if(kok == NULL) return;
    print(kok->sol);
    printf("%d ",kok->icerik);
    print(kok->sag);
}

int main(int argc, char** argv) {
    struct dugum *agac = NULL;


    ekle(&agac,100);
    ekle(&agac,50);
    ekle(&agac,140);
    ekle(&agac,300);
    ekle(&agac,130);
    print(agac);

    struct dugum *kardes = kardes_bul(agac,agac);
    if(kardes == NULL)
        printf("\nNULLLL");
    else
        printf("\n%d", kardes->icerik);

    return (EXIT_SUCCESS);
}

