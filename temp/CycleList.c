/**
 * @author: Lena
 * @desc: LinearList
 * @application: Visual Studio Code -1.58.2
 * ps: all of the link list has head node
 */

#include <stdlib.h>
#include <stdio.h>

#define pf_s "%d"
typedef int Element;

typedef struct CycleList{
    Element data;
    struct CycleList *next;
}CycleList, Node;

CycleList *instance(){
    CycleList *list = (CycleList*)malloc(sizeof(CycleList));
    if(list){
        list->next = list;
        return list;
    }else{
        return NULL;
    }
}

int isEmpty(CycleList *list){
    if(list){
        return list==list->next?0:1;
    }else{
        return -1;
    }
}

void destory(CycleList *list){
    if(isEmpty(list)!=-1){
        Node *node = list->next;
        list->next = NULL;
        list = node;
        while(list){
            node = node->next;
            free(list);
            list = node;
        }
    }
}

void headInsert(CycleList *list, Element data){
    if (isEmpty(list) != -1){
        Node *node = (Node*)malloc(sizeof(Node));
        node->data = data;
        node->next = list->next;
        list->next = node;
    }
}

void tailInsert(CycleList *list, Element data){
    if (isEmpty(list)!=-1){
        Node *temp = list;
        Node *node = (Node*)malloc(sizeof(CycleList));
        node->data = data;
        while(temp->next != list)
            temp = temp->next;
        temp->next = node;
        node->next = list;
    }
}

void delete(CycleList *list, int pos){
    if (isEmpty(list)==1){
        int index = 0;
        Node *node = list->next;
        Node *preNode = list;
        while(node!=list && ++index<=pos){
            if (index == pos){
                preNode->next = node->next;
                free(node);
                printf("OK! \n");
                break;
            }
            preNode = node;
            node = node->next;
        }
    }
}

// list1 + list2 = list3
CycleList* AddCycleList(CycleList *list1, CycleList *list2){
    if (isEmpty(list1)==1 && isEmpty(list2)){
        CycleList *list3 = instance();
        CycleList *temp1 = list1;
        CycleList *temp2 = list2;

        while(temp1->next != list1){
            tailInsert(list3, temp1->next->data);
            temp1 = temp1->next;
        }
        while(temp2->next != list2){
            tailInsert(list3, temp2->next->data);
            temp2 = temp2->next;
        }
        return list3;
    }
    return NULL;
}

void display(CycleList *list){
    if (isEmpty(list) == 1){
        Node *node = list->next;
        printf("CycleList: ");
        while(node!=list){
            printf(pf_s, node->data);
            node = node->next;
            if (node != list){
                printf(", ");
            }else{
                printf(".\n");
            }
        }
    }
}

void test(){
    CycleList *list = instance();
    tailInsert(list,1);
    tailInsert(list,2);
    tailInsert(list,3);
    tailInsert(list,4);
    tailInsert(list,5);
    display(list);
    CycleList *list2 = instance();
    tailInsert(list2,11);
    tailInsert(list2,12);
    tailInsert(list2,13);
    tailInsert(list2,14);
    tailInsert(list2,15);
    display(list2);
    
    display(AddCycleList(list2, list));
}

int main(int argc, char *argv[]){
    test();
    return 0;
}