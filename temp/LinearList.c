/**
 * @author: Lena
 * @desc: LinearList
 * @application: Visual Studio Code -1.58.2
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAXSIZE 30
#define pf_s "%d"
typedef int Element;

typedef struct LinearList{
    Element data[MAXSIZE];
    int len;
}LinearList;

typedef struct Positions{
    int status;
    int final;
    int pos[MAXSIZE];
}pos;

LinearList *instance(){
    static LinearList *linearList = NULL;
    linearList = (LinearList*)malloc(sizeof(LinearList));
    if (linearList){
        linearList->len = 0;
        return linearList;
        // linearList->data = (Element*)malloc(sizeof(Element)*MAXSIZE);
        // return linearList->data?linearList:NULL;
    }
    return NULL;
}

/**
 * @return -1:  LinearList is NULL
 * @return  0:  LinearList is empty
 * @return  1:  There are some elements in LinearList
 */
int isEmpty(LinearList *list){
    if (list){
        return list->len>0?1:0;
    }else{
        return -1;
    }
}

void destory(LinearList *list){
    free(list);
}

void clear(LinearList *list){
    if(isEmpty(list) != -1)
        list->len = 0;
}

void display(LinearList *list){
    if (isEmpty(list) == 1){
        int len, i;
        len = list->len;
        printf("LinearList(%d): ", len);
        for (i=0; i<len; i++){
            printf(pf_s, list->data[i]);
            if (i < len-1){
                printf(", ");
            }else{
                printf(".\n");
            }
        }
    }
}

void insert(LinearList *list, int pos, Element data){
    if(isEmpty(list)!=-1 && pos>0 && pos<=MAXSIZE && list->len<MAXSIZE){
        int index, len;
        len = list->len;
        if (pos > len){
            list->data[len] = data;
        }else{
            for (index=len; index>=pos; index--){
                list->data[index] = list->data[index-1];
            }
            list->data[pos-1] = data;
        }
        ++list->len;
    }else{
        printf("error insert!\n");
    }
}

void delete(LinearList *list, int pos){
    if (isEmpty(list)==1 && pos>0 && pos<=list->len){
        int len, dindex;
        len = list->len;
        for(dindex = pos-1; dindex<len-1; dindex++){
            list->data[dindex] = list->data[dindex+1];
        }
        --list->len;
    }else{
        printf("error delete!\n");
    }
}

void update(LinearList *list, int pos, Element data){
    if (isEmpty(list)==1 && pos>0 && pos<=list->len){
        list->data[pos-1] = data;
    }else{
        printf("error update!\n");
    }
}

pos findPosition(LinearList *list, Element data){
    pos res;
    res.status = 0;
    if (isEmpty(list)==1){
        int len, i;
        res.final = 0;
        len = list->len;
        for (i=0; i<len; i++){
            if (list->data[i] == data){
                res.status = 1;
                res.pos[res.final] = i+1;
                res.final++;
            }
        }
    }
    return res;
}

void duplicateRemoval(LinearList *list){
    if (isEmpty(list)==1 && list->len>1){
        int len, i, j;
        Element dataTemp;
        len = list->len;
        for(i=0; i<len-1; i++){
            dataTemp = list->data[i];
            for (j=i+1; j<len; ){
                if (list->data[j] == dataTemp){
                    delete(list,j+1);
                    --len;
                }else{
                    ++j;
                }
            }
        }
    }else{
        printf("no need to remove\n");
    }
}

// the smallest is the first one
void sortQuick(LinearList *list){
    if (isEmpty(list)==1 && list->len>1){
        int len, i, j, change, valIndex;
        Element temp;
        len = list->len;
        for (i=0; i<len-1; i++){
            change = 0;
            temp = list->data[i];
            for (j=i+1; j<len; j++){
                if (temp > list->data[j]){
                    change = 1;
                    temp = list->data[j];
                    valIndex = j;
                }
            }
            if (change){
                list->data[valIndex] = list->data[i] + list->data[valIndex];
                list->data[i] = list->data[valIndex] - list->data[i];
                list->data[valIndex] = list->data[valIndex] - list->data[i];
            }
        }
    }
}

// the smallest is the first one
void sortBubbling(LinearList *list){
    if (isEmpty(list)==1 && list->len>1){
        int len, i, j, temp; 
        len = list->len;
        for(i=0; i<len-1; i++){
            for(j=0; j<len-1-i; j++){
                if (list->data[j] > list->data[j+1]){
                    list->data[j] += list->data[j+1];
                    list->data[j+1] = list->data[j] - list->data[j+1];
                    list->data[j] = list->data[j] - list->data[j+1];
                }
            }
        }
    }
}

// List1 plus List2 (list1 and list2 are undecreasing)
LinearList *listPlus(LinearList *list1, LinearList *list2){
    if (isEmpty(list1)==1 && isEmpty(list2)){
        LinearList *list3 = instance();
        int len1, len2, i, j, k;
        i = j = 0;
        k = 1;
        len1 = list1->len;
        len2 = list2->len;
        Element a1, b2;
        while((i<len1) && (j<len2)){
            a1 = list1->data[i];
            b2 = list2->data[j];
            if (a1>b2){
                j++;
                insert(list3,k++,b2);
            }else if(a1<b2){
                i++;
                insert(list3,k++,a1);
            }else{
                i++;
                j++;
                insert(list3,k++,a1);
            }
        }
        while(i<len1){
            insert(list3,k++,list1->data[i]);
            i++;
        }
        while(j<len2){
            insert(list3,k++,list2->data[j]);
            j++;
        }
        return list3;
    }
    return NULL;
}

// insert some datas
void helpOne(LinearList *list){
    printf("do you want to insert some datas(y/n)");
    char temp1;
    scanf("%c", &temp1);
    getchar();
    if ('y' == temp1){
        int i, len, temp2;
        srand((unsigned)time(NULL));
        len = 5 + rand()%10;
        for (i=0; i<len; i++){
            temp2 = rand()%100;
            printf("%d ", temp2);
            insert(list, 1, temp2);
        }
        printf("\n");
    }
}

void test01(){
    LinearList *list = instance();
    helpOne(list);
    display(list);
    sortBubbling(list);
    display(list);
}

void test02(){
    LinearList *list1 = instance();
    LinearList *list2 = instance();
    helpOne(list1);
    sortQuick(list1);
    duplicateRemoval(list1);
    helpOne(list2);
    sortBubbling(list2);
    duplicateRemoval(list2);
    LinearList *list3 = listPlus(list1, list2);
    display(list1);
    display(list2);
    display(list3);
}

int main(int argc, char *argv[]){
    test02();
    return 0;
}