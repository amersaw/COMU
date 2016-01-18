#include <stdio.h>
#include <stdlib.h>



struct dugum {
    int icerik;
    struct dugum *sol;
    struct dugum *sag;
};


int BST_mi(struct dugum* agac){
    if(agac==NULL) return 1;
    int sag_agac_bst_mi = BST_mi(agac->sag);
    int sol_agac_bst_mi = BST_mi(agac->sol);

    int sag_taraftan_daha_kucuk_mu = 1;
    if(agac->sag !=NULL && agac->icerik > agac->sag->icerik)
        sag_taraftan_daha_kucuk_mu = 0;

    int sol_taraftan_daha_buyuk_mu = 1;
    if(agac->sol !=NULL && agac->icerik < agac->sol->icerik)
        sol_taraftan_daha_buyuk_mu= 0;

    if( sol_taraftan_daha_buyuk_mu == 1//simdiki dugum soldaki'den daha buyuk ve
        && sol_taraftan_daha_buyuk_mu == 1 //simdiki dugum sagdaka'den daha kucuk ve
        && sag_agac_bst_mi == 1                      // sagdaki agac ta s?k?nt? yok
        && sol_agac_bst_mi == 1)                     // ve soldaki agac ta s?k?nt? yok ise demek ki yanlislik yok
        return 1; // yukaritaki sartlar hepsini dogru ise demek ki evet bir ikili arama agactir
    else        // yukaridaki sartilar herhangi birisi buzuk ise demek ki yanlislik var demekk ki agac degil
        return 0;
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


    printf("\n\n\nNormal durum    : %d\n",BST_mi(agac)); // Burda kesin BST olmasi lazim, cunku ona gore olusturduk

    //simdi bu agac bozduralim :
    agac->icerik = 0; // bu sekilde agaci bozduk cunku kok dugumu en kucuk dugum oldu
    printf("Bozduktan Sonra : %d\n\n",BST_mi(agac));

    return (EXIT_SUCCESS);
}

