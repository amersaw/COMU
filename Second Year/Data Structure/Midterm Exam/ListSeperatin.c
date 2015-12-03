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
void Seperate(struct Node* list, struct Node **list1){
    if(list == NULL)
        return;
    struct Node* lastList = NULL, *lastList1 = NULL;
    if(list->next !=NULL){
        *list1=list->next;
        lastList1 = list->next;
    }
    if(lastList1 != NULL)
    {
        list->next = lastList1->next;
        lastList = lastList1->next;
    }
    int x = 1;//We'll start by adding to list1;
    while((lastList1 != NULL && lastList1->next !=NULL) || (lastList != NULL && lastList->next !=NULL)){
        if(x==1){ //will add to list1;
            lastList1->next = lastList->next;
            lastList1 = lastList->next;
            x=0;
        } else{ //will add to list
            lastList->next = lastList1->next;
            lastList = lastList1->next;
            x=1;
        }
    }
    if(lastList1 != NULL)
        lastList1->next = NULL;
    if(lastList != NULL)
        lastList->next = NULL;
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

    struct Node* List1=NULL;
    Seperate(List,&List1);
    printf("\n\n---After Seperation---\n");
    printf("List :\n");
    PrintList(List);
    printf("\nList1 :\n");
    PrintList(List1);
    return 0;
}

