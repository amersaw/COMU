#include<stdlib.h>
//#include<iostream>
struct Node{
    int value;
    struct Node* next;
};
struct Node* CreateNode(int v){
    struct Node* retVal = (struct Node*)malloc(sizeof(struct Node));
    retVal->value = v;
    retVal->next = NULL;
    return retVal;
}

void AddToEnd(struct Node** list, int val){
    if(*list == NULL){
        *list= CreateNode(val);
    }else{
        struct Node* current = *list;
        while(current->next!=NULL){
            current = current->next;
        }
        current->next = CreateNode(val);
    }

}

void PrintList(struct Node* list){
    struct Node* current = list;
    while(current!=NULL){
        printf("%d\t",current->value);
        current=current->next;
    }
}

/***************************Cevap Burda********************************/
void Count(struct Node * list, int * even, int* odd){

    *even = 0;
    *odd = 0;
    struct Node * current = list;
    while(current != NULL){

        if(current->value %2 == 0)//Cift
            *even = *even +1;
        else
            *odd = *odd +1 ;
        current = current->next;
    }
}
/**********************************************************************/

int main(){

    struct Node* List = NULL;
    AddToEnd(&List,1);
    AddToEnd(&List,2);
    AddToEnd(&List,3);
    AddToEnd(&List,4);
    AddToEnd(&List,5);
    AddToEnd(&List,6);
    AddToEnd(&List,7);
    AddToEnd(&List,8);
    AddToEnd(&List,9);


    printf("\nFull List :\n");
    PrintList(List);
    int even, odd;
    Count(List,&even,&odd);

    printf("\nEven : %d\nOdd : %d\n",even,odd);
    return 0;
}

