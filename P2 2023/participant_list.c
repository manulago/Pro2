/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Manuel Lago Tielas               LOGIN 1: m.lago.tielas
 * AUTHOR 2: Carmelo Alejandro García Almeida LOGIN 2: carmelo.garcia
 * GROUP: 4.4
 * DATE: 12 / 04 / 23
 */

#include "participant_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void createEmptyListP(tListP *L){
    *L = NULLP;
}

bool isEmptyListP(tListP L){
    return(L == NULLP);
}

tPosP firstP(tListP L){
    return L;
}

tPosP nextP(tPosP p, tListP L){
    return p->next;
}

tPosP previousP(tPosP p,tListP L){
    tPosP q;
    if (p==firstP(L)) {
        return NULLP;
    }
    else {
        for (q = L;q->next!=p;q=q->next);
        return q;
    }
}

bool createNodeP(tPosP *p){
    *p = malloc(sizeof(struct tnode));
    return *p !=NULL;
}

bool insertItemP(tItemP d, tListP *L){
    tPosP q,p;
    if(!createNodeP(&q)){
        return false;
    }else{
        q->data=d;
        q->next=NULLP;
        if(*L==NULLP){
            *L=q;
        }else if(strcmp(d.participantName, (*L)->data.participantName)<0){
            q->next=*L;
            *L=q;
        }else{
            p=findPositionP(*L,d);
            q->next = p->next;
            p->next=q;
        }
    }
}

tPosP lastP(tListP L){
    tPosP p;
    for (p = L;p->next != NULLP ; p = p->next);
    return p;
}

void deleteAtPositionP(tPosP p, tListP *L){
    tPosP q;
    if (p==*L)
        *L = (*L)->next;
    else if(p->next == NULLP){
        for (q= *L; q->next != p; q = q->next);
        q->next =NULLP;
    }
    else{
        q = p->next;
        p->data = q->data;
        p->next = q->next;
        p=q;
    }
    free(p);
}

tItemP getItemP(tPosP p,tListP L){
    return p->data;
}

void updateItemP(tItemP d, tPosP p,tListP *L){
    p->data=d;
}

tPosP findItemP(tParticipantName d, tListP L){
    tPosP p;
    if(isEmptyListP(L)){
        return NULLP;
    }else{
        for(p=L;(p!=NULLP)&&(strcmp(p->data.participantName, d)<0);p=p->next);
        if(p!=NULLP&& strcmp(p->data.participantName, d)==0){
            return p;
        }else{
            return NULLP;
        }
    }
}



tPosP findPositionP(tListP L, tItemP d){
    tPosP p;
    p=L;
    while((p->next!=NULLP)&& strcmp(p->next->data.participantName, d.participantName)<0){
        p=p->next;
    }return p;
}