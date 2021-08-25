/**
 * @author: Lena
 * @desc: LinkList
 * @application: Visual Studio Code -1.58.2
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 300

typedef struct Joseph{
    int data;
    struct Joseph *next;
}Joseph;

void arrayImpl(int t, int f, int in){
    static int data[MAXSIZE] = {0};
    int out = 0;
    int i=0;
    int k=0;
    while(out != t-f){
        ++i;
        if (i>t){
            i = 1;
        }
        if(data[i] == 0){
            ++k;
            if(k==in){
                data[i] = 1;
                ++out;
                k = 0;
                printf("%d, ", i);
            }
        }
    }
}

void cycleListImpl(int t, int f, int in){
    Joseph *head = NULL;
    Joseph *p = NULL;
    Joseph *r = NULL;
    int out = 0;
    head = (Joseph*)malloc(sizeof(Joseph));
    if(head){
        head->data = 1;
        head->next = NULL;
        p = head;
        for (int i=1; i<t; i++){
            r = (Joseph*)malloc(sizeof(Joseph));
            r->data = i+1;
            r->next = NULL;
            p->next = r;
            p = r;
        }
        p->next = head;
        p = head;
        while(p->next != p && out<t-f){
            for (int i=1; i<in; i++){
                r = p;
                p = p->next;
            }
            printf("%d, ", p->data);
            r->next = p->next;
            p = p->next;
            out++;
        }
        if(f==0){
            printf("%d ", p->data);
        }
    }
}

int recursiveJoseph(int total, int k, int i){
    // return i==1? (total+k-1)%total: (recursiveJoseph(total-1,k,i-1)+k)%total;
    return i==1? (k-1)%total: (recursiveJoseph(total-1,k,i-1)+k)%total;
}

void recursiveImpl(int total, int final, int interval){
    for (int index=1; index<=total-final; index++)
        printf("%d, ", 1+recursiveJoseph(total,interval,index));
}

int main(int argc, char *argv[]){
    int total = 200;
    int final = 0;
    // 1, 2, 3, 4, ..., interval
    int interval = 4;

    arrayImpl(total, final, interval);
    // cycleListImpl(total, final, interval);
    // recursiveImpl(total, final, interval);
}