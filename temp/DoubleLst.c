/**
 * @author: Lena
 * @desc: LinkList
 * @application: Visual Studio Code -1.58.2
 */
#include <stdlib.h>
#include <stdio.h>

typedef int Element;

typedef struct DoubleList{
    struct DoubleList *pre;
    Element data;
    struct DoubleList *next;
}DoubleList, Node;

DoubleList *instance(){
    DoubleList *list = (DoubleList *)malloc(sizeof(DoubleList));
    list->pre = list;
    list->data = -1;
    list->next = list;
    return list;
}

int isEmpty(DoubleList *list){
    if (list){
        return list->next==list?0:1;
    }else{
        return -1;
    }
}

Node *createNode(Element data){
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    return node;
}

Node *getNodeByPosition(DoubleList *list, int pos){
    if (isEmpty(list) != -1 && pos>=0){
        int index = 0;
        Node *temp = list;
        while(temp != list && ++index<=pos-1){
            temp = temp->next;
            if (index == pos-1){
                break;
            }
        }
        return temp;
    }else{
        return NULL;
    }
}

void Insert(DoubleList *list, int pos, Element data){
    Node *node1 = getNodeByPosition(list, pos-1);
    if(node1){
        Node *node2 = createNode(data);
        node2->next = node1->next;
        node1->next->pre = node2;
        node1->next = node2;
        node2->pre = node1;
    }else{
        printf("Error Insert!\n");
    }
}

void delete(DoubleList *list, int pos){
    if (isEmpty(list)==1 && pos>0){
        Node *node = getNodeByPosition(list, pos);
        if (node && node->data != -1){
            node->pre->next = node->next;
            node->next->pre = node->pre;
            free(node);
        }
    }
}

void counterDisplay(DoubleList *list){
    if (isEmpty(list) == 1){
        Node *node = list->next;
        printf("DoubleList: ");
        while (node != list){
            printf("%d ", node->data);
            node = node->next;
        }
        printf("\b.\n");
    }
}

void orderDisplay(DoubleList *list){
    if (isEmpty(list) == 1){
        Node *node = list->pre;
        printf("DoubleList: ");
        while (node != list){
            printf("%d ", node->data);
            node = node->pre;
        }
        printf("\b.\n");
    }
}

void test(){
    DoubleList *list = instance();
    Insert(list,1,1);
    Insert(list,2,2);
    Insert(list,3,3);
    Insert(list,4,4);
    Insert(list,5,5);
    Insert(list,6,6);
    Insert(list,4,9);
    counterDisplay(list);
    delete(list,190);
    counterDisplay(list);
}

int main(int argc, char *argv[]){
    test();
    return 0;
}