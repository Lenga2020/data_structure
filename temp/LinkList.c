/**
 * @author: Lena
 * @desc: LinkList
 * @application: Visual Studio Code -1.58.2
 * ps: all of the link list has head node
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define pf_S "%d"
typedef int Element;

typedef struct LinkList{
    Element data;
    struct LinkList *next;
}LinkList, Node;

typedef struct Data_POS{
    int status;
    int pos;
}lena;

LinkList *createNode(){
    Node *node = NULL;
    node = (LinkList *)malloc(sizeof(LinkList));
    if (node){
        node->next = NULL;
        return node;
    }else{
        printf("create node error! \n");
        return NULL;
    }
}

/**
 * @return -1: link list is NULL
 * @return  0: link list is empty
 * @return  1: there are some datas in LinkList
 */
int isEmpty(LinkList *list){
    if(list){
        return list->next?1:0;
    }else{
        return -1;
    }
}

void destory(LinkList *list){
    if (isEmpty(list)!=-1){
        Node *node;
        while(list){
            node = list;
            list = list->next;
            free(node);
        }
    }else{
        printf("destory node error! \n");
    }
}

void clear(LinkList *list){
    if (isEmpty(list)==1){
        destory(list->next);
        list->next = NULL;
    }else{
        printf("clear node error! \n");
    }
}

int getLen(LinkList *list){
    int len = isEmpty(list);
    LinkList *demo = list;
    if(len == 1){
        len = -1;
        while(demo){
            ++len;
            demo = demo->next;
        }
    }
    free(demo);
    return len;
}

// pos not index
Node *getNode(LinkList *list, int pos){
    if(isEmpty(list) != -1){
        int num = 0;
        Node *demo = list;
        while(demo && num<pos){
            demo = demo->next;
            ++num;
        }
        if(demo && num==pos){
            return demo;
        }
    }
    return NULL;
}

void insert(LinkList *list, int pos, Element data){
    if (isEmpty(list)!=-1 && pos>0){
        Node *node = getNode(list, pos-1);
        if(node){
            Node *node2 = createNode();
            node2->data = data;
            node2->next = node->next;
            node->next = node2;
            return;
        }
    }
    printf("error insert!\n");
}

void headInsert(LinkList *list, Element data){
    if(isEmpty(list)!=-1){
        Node *node = createNode();
        node->data = data;
        if (list->next){
            node->next = list->next;
            list->next = node;
        }else{
            node->next = NULL;
            list->next = node;
        }
    }
}

void tailInsertDemo(Node *list, Element *data, int len){
    if(list){
        LinkList *tail = list;
        int i = 0;
        for (i=0; i<len; i++){
            // core from
            Node *node = createNode();
            node->data = data[i];
            node->next = NULL;
            tail->next = node;
            tail = node;
            // core end
        }
    }
}

void delete(LinkList *list, int pos){
    if(isEmpty(list)==1){
        Node *node = getNode(list, pos-1);
        if(node){
            Node *node2 = node->next;
            if(node2){
                node->next = node2->next;
                free(node2);
                return;
            }
        }
    }
    printf("error at delete!\n");
}

void display(LinkList *list){
    if(isEmpty(list) == 1){
        LinkList *temp = list->next;
        printf("LinkList(%d): ", getLen(list));
        do{
            printf(pf_S" ", temp->data);
            temp = temp->next;
        } while (temp);
        printf("\n");
    }else{
        printf("Linklist is null or empty");
    }
}

lena getPosByData(LinkList *list, Element data){
    lena res;
    res.status = 0;
    if(isEmpty(list)==1){
        int num = 1;
        LinkList *demo = list;
        demo = demo->next;
        while(demo){
            if(data == demo->data){
                res.status = 1;
                res.pos = num;
                break;
            }
            ++num;
            demo = demo->next;
        }
    }
    return res;
}

void helpOne(LinkList *list){
    srand((unsigned)time(NULL));
    int len = 6 + rand()%12;
    int temp;
    Element data[18];
    for(int i=0; i<len; i++){
        temp = rand()%100;
        data[i] = temp;
        printf("%d ", data[i]);
        // printf("%d ", temp);
        // insert(list,1,temp);
        // headInsert(list, temp);
    }
    tailInsertDemo(list, data, len);
    printf("\n");
}

void test01(){
    LinkList *list = createNode();
    helpOne(list);
    display(list);
    insert(list,708, 999);
}

int main(int argc, char *argv[]){
    test01();
    return 0;
}