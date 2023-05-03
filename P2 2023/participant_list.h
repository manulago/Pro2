/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Manuel Lago Tielas               LOGIN 1: m.lago.tielas
 * AUTHOR 2: Carmelo Alejandro García Almeida LOGIN 2: carmelo.garcia
 * GROUP: 4.4
 * DATE: 12 / 04 / 23
 */
#ifndef PARTICIPANT_LIST_H
#define PARTICIPANT_LIST_H

#include "types.h"
#include <stdbool.h>

#define NULLP NULL
typedef struct tItemP {
    tParticipantName participantName;
    tNumVotes numVotes;
    tEUParticipant EUParticipant;
}tItemP;

typedef struct tnode* tPosP;
struct tnode{
    tItemP data;
    tPosP next;
}; typedef tPosP tListP;

void createEmptyListP(tListP *L);
// OBJETIVO: Crea una lista vacia
// ENTRADA: Lista a crear
// SALIDA: Lista creada y vacia
// POSTCONDICION:Que se haya inicializado la lista

bool isEmptyListP(tListP L);
// OBJETIVO:comprobar si la lista esta vacia
// ENTRADA:la lista a comprobar
// SALIDA:booleano true o false

tPosP firstP(tListP L);
// OBJETIVO: localizar el primer elemento de la lista
// ENTRADA: La lista de la que queremos obtener el primer elemento
// SALIDA: la primera posicion de la lista
// PRECONDICION: que la lista no este vacia

tPosP lastP(tListP L);
// OBJETIVO: localizar el ultimo elemento de la lista
// ENTRADA: La lista de la que queremos obtener el ultimo elemento
// SALIDA: la ultima posicion de la lista
// PRECONDICION: que la lista no este vacia

tPosP nextP(tPosP p,tListP l);
// OBJETIVO: devuelve la posicion siguiente a la del elemento indicado
// ENTRADA: La lista y la posicion de la que queremos obtener la posicion siguiente
// SALIDA: la posicion posterior a la dada
// PRECONDICION: la posicion indicada es una posicion valida de la lista

tPosP previousP(tPosP p,tListP L);
// OBJETIVO: devuelve la posicion anterior a la del elemento indicado
// ENTRADA: La lista y la posicion de la que queremos obtener la posicion anterior
// SALIDA: la posicion anterior a la dada
// PRECONDICION: la posicion indicada es una posicion valida de la lista

bool createNodeP(tPosP *p);
// OBJETIVO: crea un nuevo nodo en la lista
// ENTRADA: la posicion donde creamos el nodo
// SALIDA: devuelve true si se ha creado el nodo

bool insertItemP(tItemP d, tListP *L);
// OBJETIVO: insertar un nuevo elemento en la lista
// ENTRADA: el elemento a insertar, su posicion y la lista (si la posicion es LNULL se añade al final de la lista)
// SALIDA:devuelve el valor True o False, en caso de que haya insertado el elemento o en caso contrario
// PRECONDICION: la posicion indicada es una posicion valida de la lista
// POSTCONDICION: las posiciones de los elementos posteriores a la del elemento insertado se pueden ver modificadas

void deleteAtPositionP(tPosP p, tListP *L);
// OBJETIVO: eliminar un elemento de la lista
// ENTRADA: la posicion a eliminar y la lista
// SALIDA: no devuelve ningun valor, simplemente elimina
// PRECONDICION: la posicion indicada es una posicion valida de la lista
// POSTCONDICION: las posiciones de los elementos posteriores a la del elemento eliminado se pueden ver modificadas

tItemP getItemP(tPosP p,tListP L);
// OBJETIVO: devuelve el contenido del elemento de la lista que ocupa la posicion indicada
// ENTRADA: la posicion de la que queremos obtener el contenido y la lista
// SALIDA: el tItemL de la posicion dada
// PRECONDICION: la posicion indicada es una posicion valida de la lista

void updateItemP(tItemP d, tPosP p,tListP *L);
// OBJETIVO: modifica el contenido del elemento situado en la posicion indicada
// ENTRADA: el contenido nuevo con el que vamos a sustituir el anterior, la posicion y la lista
// SALIDA: no hay salida, simplemente se actualiza la lista
// PRECONDICION: la posicion indicada es una posicion valida de la lista
// POSTCONDICION:el orden de los elementos de la lista no se ve modificado

tPosP findItemP(tParticipantName d, tListP L);
// OBJETIVO: devuelve la posicion del primer elemento cuyo identificador coincide con el dado
// ENTRADA: el identificador del elemento a buscar y la lista
// SALIDA: la posicion del primer elemento que coincida con el identificador(o LNULL si no existe)

tPosP findPositionP(tListP L, tItemP d);
#endif
