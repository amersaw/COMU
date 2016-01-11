//bu sorunun cevabı, "sirali_mi" fonksiyonu sadece, kalan kodlar bu fonksiyon nasıl kullanacağız göstermek için
#include <stdio.h>

struct node{
    int key;
    struct node* next;
};

int sirali_mi(struct node* bas){
    if(bas == NULL) return 1;// liste bos ise sirali olarak kabul ediyoruz
    if(bas->next == NULL) return 1;// listede tek elemen varsa sirali olarak kabul ediyoruz
    int onceki = bas->key; //onceki eleman ilk eleman
    struct node* simdiki = bas->next; //ikinci elemandan basliyoruz (listede kesin 1'den fazla elemanlar var)
    while(simdiki!=NULL){ //listenin sonuna ulasmaya kadar
        if(simdiki->key > onceki) //eger simdiki eleman onceki elemanden daha buyuk ise demek ki sirali degil demek ki return 0;
            return 0;
        onceki = simdiki->key; //sonraki elemana geciyoruz
        simdiki=simdiki->next; //sonraki elemana geciyoruz
    }
    return 1; // listenin sonuna kadar ulastiysak ve hala cikmadik demek ki liste sirali demek ki return 1;
}

struct node* create_node(int key){
    struct node *retVal = (struct node*)malloc(sizeof(struct node));
    if(retVal == NULL)
        exit(-1);
    retVal->key=key;
    retVal->next = NULL;
};

void sonuna_ekle(struct node**head, int key){
    if(*head == NULL) {
        *head = create_node(key);
        return;
    }
    struct node* current = *head;
    while(current->next != NULL)
        current = current->next;
    current->next = create_node(key);
}

void print(struct node * head){
    while(head!= NULL){
        printf("%d\t",head->key);
        head = head->next;
    }
    printf("\n");
}

int main(){
    struct node* list=NULL;
    sonuna_ekle(&list,10);
    sonuna_ekle(&list,5);
    sonuna_ekle(&list,3);
    sonuna_ekle(&list,2);
    sonuna_ekle(&list,1);
    print(list);
    printf("%d",sirali_mi(list));
    return 0;
}
