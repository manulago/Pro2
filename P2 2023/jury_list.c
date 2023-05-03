/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Manuel Lago Tielas               LOGIN 1: m.lago.tielas
 * AUTHOR 2: Carmelo Alejandro García Almeida LOGIN 2: carmelo.garcia
 * GROUP: 4.4
 * DATE: 12 / 04 / 23
 */

#include "jury_list.h"
#include "participant_list.h"
#include <string.h>
#include <string.h>

void createEmptyListJ(tListJ *L){
    L->LastPos=NULLJ;/* Creamos una lista vacia igualando el tPosJ LastPos a NULLJ */
}
bool isEmptyListJ(tListJ L){
    return (L.LastPos==NULLJ);/*Comprobamos si la lista esta vacia comparando Lastpos con NULLJ*/
}
tPosJ firstJ(tListJ L){
    return 0; /*devolvemos la primera posicion de la lista */
}
tPosJ lastJ(tListJ L){
    return L.LastPos;/* Devolvemos el valor de LastPos, es decir la ultima posicion*/
}
tPosJ previousJ(tPosJ p,tListJ L){
    if (p== firstJ(L)){/*si la posicion dada es la primera devolvemos NULLJ*/
        return NULLJ;
    }
    else
        return --p;/*devolvemos la posicion p-1*/
}
tPosJ nextJ(tPosJ p, tListJ L){
    if (p== lastJ(L))/*si la posicion dada es la ultima devolvemos NULLJ*/
        return NULLJ;
    else
        return ++p;/*devolvemos la posicion p+1*/
}
tItemJ getItemJ(tPosJ p, tListJ L){
    return L.data[p];/* devuelve los datos en la posicion dada p*/
}
void updateItemJ(tItemJ d, tPosJ p,tListJ *L){
    L->data[p]=d;/*igualamos los datos de la posicion p a los nuevos datos d*/
}
tPosJ findItemJ(tJuryName d,tListJ L){
    tPosJ p;
    if (L.LastPos==NULLJ)
        return NULLJ;/*si la lista esta vacia devuelve NULLJ*/
    else{
        for (p = firstJ(L); (p<=L.LastPos)&&(strcmp(d,L.data[p].juryName)!=0); p++);/*mientras p sea distinto de la ultima posicion avanza desde la primera hasta la ultima*/
        if (strcmp(L.data[p].juryName, d) != 0) /*comparo el juryName de la posicion p con el parcicipante que queremos encontrar*/
            return NULLJ;
        else
            return p;
    }
}
bool insertItemJ(tItemJ d, tListJ *L){
    tPosJ i;
    if(L->LastPos==Max-1){   //Comprobar si el array está lleno
        return false;
    }else{
        if(isEmptyListJ(*L)||strcmp(d.juryName, L->data[L->LastPos].juryName)>0){
            L->LastPos++;
            L->data[L->LastPos]=d;
        }else{
            L->LastPos++;

            for(i=L->LastPos;i>0 && strcmp(d.juryName,L->data[i-1].juryName)<0;i--){
                L->data[i]=L->data[i-1];
            }
            L->data[i]=d;
        }
        return true;
    }
}
void deleteAtPositionJ(tPosJ p, tListJ *L){
    tPosJ i;
    L->LastPos--;/*reducimos la lista una posicion*/
    for ( i = p; i <=L->LastPos ; i++)/*desde la posicion a eliminar recorremos la lista hasta la ultima posicion sustituyendo los datos de la posicion en la que estamos por los de la posicion siguiente*/
        L->data[i]=L->data[i+1];
}

