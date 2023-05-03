#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "jury_list.h"

#define MAX_BUFFER 255

void create(tJuryName juryName, tNumVotes totalVoters, tListJ *listaJ);
/*
Objetivo: Crea una lista de jurado, con su nombre, sus contadores de votos a cero y su lista de participantes
Entrada: El nombre del jurado (tipo tJuryName), los votantes totales (tipo tNumVotes) y una lista (tipo tListJ).
Salida: La confirmación de que se ha creado correctamente el nuevo elemento, o en su defecto,
        la confirmación de que no se ha podido crear.
Precondiciones: -
Postcondiciones: -
*/

void new(tJuryName juryName, tParticipantName participantName, tEUParticipant Eur, tListJ *listaJ);
/*
Objetivo: Crea un nuevo país en la lista de participantes de un jurado, con su nombre,
          contador de votos a cero y localización.
Entrada: Un jurado (tJuryName), nombre de país (tipo tParticipantName), un booleano (tipo tEUParticipant) y la lista (tListJ).
Salida:  La confirmación de que se ha creado correctamente el nuevo elemento, o en su defecto,
         la confirmación de que no se ha podido crear o que el jurado no existe.
Precondiciones: -
Postcondiciones: -
*/

void vote(tJuryName juryName, tParticipantName participantName, tListJ *listaJ);
/*
Objetivo:  Añadir un voto al participante que se indique, además de añadirlo a los votos válidos/nulos del jurado.
Entrada:   Un nombre de país (tipo tParticipantName), un nombre de jurado (tipo tJuryName) y la lista(tipo tListJ).
Salida:    La confirmación de que se ha votado, o en su defecto,
           la confirmación de que se ha añadido un voto nulo a la votación, que no se ha encontrado el participante
           en la lista o que el jurado no existe.
Precondiciones: -
Postcondiciones: -
*/

void discualify(tParticipantName participantName, tListJ *listaJ);
/*
Objetivo: Descalificar a un país de la votación, eliminandolo de la lista y convirtiendo todos sus votos a nulos.
Entrada:  Un nombre de país (tipo tParticipantName) y la lista de jurados (tipo tListJ).
Salida:   La confirmación de que se ha descalificado al país introducido, o en su defecto,
          (si el país no estaba en la lista) un error de descalificación.
Precondiciones: -
Postcondiciones: -
*/

void Remove(tListJ *listaJ);
/*
Objetivo: Borrar todos los jurados que no tengan votos en sus datos.
Entrada:  Una lista de jurados (tipo tListJ).
Salida:   La confirmación de que se ha borrado un jurado en caso de que se cumplan los requisitos
          del objetivo.
Precondiciones: -
Postcondiciones: -
*/

void stats(tListJ *listaJ);
/*
Objetivo: Muestra todos los paises de la lista de cada jurado, su número de votos y porcentaje sobre votos válidos;
          número de votos nulos y número de votos totales sobre los votantes de cada jurado, además de su porcentaje. Este proceso
          se realiza para cada jurado de la lista.
Entrada:  Una lista de jurados (tipo tListJ)
Salida:   Todos los datos que se requiere mostrar, o error en caso de que no se puedan mostrar estadisticas.
Precondiciones: -
Postcondiciones: -
*/

void winners(tListJ *listaJ);
/*
Objetivo: Se mostrará el ganador de la votación de cada jurado por cada localización (eu/non-eu).
Entrada: Una lista de jurados (tipo tListJ).
Salida:  Los datos del objetivo, o error en caso de que no se pueda ejecutar correctamente la función.
Precondiciones: -
Postcondiciones: -
*/

tEUParticipant conversorBool(char *Eur);
/*
Objetivo: Convierte el parametro introducido al programa (eu/non-eu) a tipo tEUParticipant
Entrada: Un elemento char
Salida: Devuelve true en caso de que el parametro introducido sea "eu" o false en caso contrario
Precondiciones: Recibe "eu" o "non-eu"
Postcondiciones: -
*/

tNumVotes conversorInt(char *votes);
/*
Objetivo: Convierte una cadena de caracteres en un tipo tNumVotes
Entrada: Un elemento char
Salida: Devuelve un tNumVotes con el número que hubiese en la cadena.
Precondiciones: La cadena de caracteres es un número
Postcondiciones: -
*/

void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, tListJ *lJ) {
    printf("********************\n");
    switch (command) {
        case 'C':
            printf("%s %c: jury %s totalvoters %s\n", commandNumber, command, param1, param2);
            create(param1, conversorInt(param2), lJ);
            break;
        case 'N':
            printf("%s %c: jury %s participant %s location %s\n", commandNumber, command, param1, param2, param3);
            new(param1, param2, conversorBool(param3), lJ);
            break;
        case 'V':
            printf("%s %c: jury %s participant %s\n", commandNumber, command, param1, param2);
            vote(param1, param2, lJ);
            break;
        case 'D':
            printf("%s %c: participant %s\n", commandNumber, command, param1);
            discualify(param1, lJ);
            break;
        case 'S':
            printf("%s %c:\n",commandNumber, command);
            stats(lJ);

            break;
        case 'R':
            printf("%s %c:\n",commandNumber, command);
            Remove(lJ);
            break;
        case 'W':
            printf("%s %c:\n",commandNumber, command);
            winners(lJ);
            break;
        default:
            break;
    }
}

void readTasks(char *filename) {

    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2, *param3;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];
    tListJ lj;
    createEmptyListJ(&lj);
    f = fopen(filename, "r");

    if (f != NULL) {

        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, param3, &lj);
        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}


int main(int nargs, char **args) {

    char *file_name = "create.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
#ifdef INPUT_FILE
        file_name = INPUT_FILE;
#endif
    }

    readTasks(file_name);

    return 0;
}

void create(tJuryName juryName, tNumVotes totalVoters, tListJ *listaJ){

    tItemJ jury; // Crea un objeto del tipo tItemJ que representa un jurado
    strcpy(jury.juryName, juryName); // Copia el nombre del jurado recibido en el campo juryName del objeto jury
    jury.totalVoters = totalVoters, jury.validVotes = 0, jury.nullVotes = 0; // Asigna valores a los campos del objeto jury
    createEmptyListP(&jury.participantList); // Crea una lista vacía de participantes para el objeto jury

    // Verifica si el jurado ya existe en la lista y si no existe, lo agrega a la lista y muestra un mensaje de éxito por pantalla
    if(findItemJ(juryName, *listaJ) == NULLJ && insertItemJ(jury, listaJ)) {
        printf("* Create: jury %s totalvoters %d\n", juryName, totalVoters);
    } else {
        printf("+ Error: Create not possible\n"); // Muestra un mensaje de error si el jurado ya existe en la lista
    }
}


void new(tJuryName juryName, tParticipantName participantName,tEUParticipant Eur, tListJ *listaJ) {
    tPosJ p = findItemJ(juryName, *listaJ);
// Luego, obtenemos el elemento del jurado que encontramos
    tItemJ aux = getItemJ(p, *listaJ);

// Si encontramos el jurado y el participante no está en la lista de participantes de ese jurado
    if (p != NULLJ && findItemP(participantName, aux.participantList) == NULLP) {
        // Creamos un nuevo elemento para el participante
        tItemP votante;
        strcpy(votante.participantName, participantName);
        votante.numVotes = 0;
        votante.EUParticipant = Eur;

        // Insertamos el nuevo participante en la lista de participantes del jurado
        if (insertItemP(votante, &aux.participantList)) {
            // Imprimimos un mensaje de éxito y actualizamos el elemento del jurado en la lista de jurados
            printf("* New: jury %s participant %s location %s\n", aux.juryName,
                   votante.participantName,
                   votante.EUParticipant == true ? "eu" : "non-eu");
            updateItemJ(aux, p, listaJ);
        } else {
            // Si hubo un error al insertar el participante, imprimimos un mensaje de error
            printf("+ Error: New not possible");
        }
    } else {
        // Si no se encontró el jurado o el participante ya está en la lista de participantes del jurado, imprimimos un mensaje de error
        printf("+ Error: New not possible\n");
    }
}

void vote(tJuryName juryName, tParticipantName participantName, tListJ *listaJ){
    // Buscamos el jurado en la lista
    tPosJ p = findItemJ(juryName, *listaJ);
    // Obtenemos el elemento del jurado encontrado
    tItemJ auxJ = getItemJ(p, *listaJ);

    // Si encontramos el jurado, procedemos
    if(p!=NULLJ){
        // Buscamos al participante en la lista de participantes del jurado
        tPosP auxP = findItemP(participantName,auxJ.participantList);

        // Si encontramos al participante, procedemos
        if(auxP!=NULLP){
            // Obtenemos al votante
            tItemP votante = getItemP(auxP, auxJ.participantList);
            // Incrementamos en 1 el número de votos del participante
            votante.numVotes++;
            // Incrementamos en 1 el número de votos válidos del jurado
            auxJ.validVotes++;

            // Actualizamos la información del votante en la lista
            updateItemP(votante, auxP, &auxJ.participantList);
            // Actualizamos la información del jurado en la lista
            updateItemJ(auxJ, p, listaJ);

            // Imprimimos la información del voto realizado
            printf("* Vote: jury %s participant %s location %s numvotes %d\n",
                   auxJ.juryName,votante.participantName, votante.EUParticipant == true ? "eu" : "non-eu", votante.numVotes);
        }else {
            // Si no encontramos al participante, imprimimos un mensaje de error y se considera un voto nulo
            printf("+ Error: Vote not possible. Participant %s not found in jury %s. NULLVOTE\n", participantName,auxJ.juryName);
            auxJ.nullVotes++;
            updateItemJ(auxJ, p, listaJ);
        }
    }else printf("+ Error: Vote not possible\n");
}



void discualify(tParticipantName participantName, tListJ *listaJ){
// Buscamos el primer elemento de la lista de jurados
    tPosJ i;
    if(!isEmptyListJ(*listaJ)) {
        i = firstJ(*listaJ);
        tItemJ auxJ = getItemJ(i, *listaJ);
        // Recorremos todos los elementos de la lista de jurados
        while (i!= NULLJ && i <= lastJ(*listaJ)) {
            // Buscamos el participante en la lista de participantes del miembro del jurado actual
            tPosP p = findItemP(participantName, auxJ.participantList);

            if (p != NULLP) {
                // Si encontramos el participante, lo descalificamos y actualizamos el miembro del jurado
                tItemP votante = getItemP(p, auxJ.participantList);
                auxJ.validVotes -= votante.numVotes;
                auxJ.nullVotes += votante.numVotes;
                deleteAtPositionP(p, &auxJ.participantList);
                updateItemJ(auxJ, i, listaJ);
                printf("Jury %s\nParticipant %s disqualified\n\n",auxJ.juryName, participantName);
            }
            else {
                // Si no encontramos el participante, imprimimos un mensaje de error
                printf("Jury %s\nNo participant %s\n\n",auxJ.juryName, participantName);
            }

            // Avanzamos al siguiente elemento de la lista de jurados
            i = nextJ(i, *listaJ);
            if (i != NULLJ) {
                auxJ = getItemJ(i, *listaJ);
            }
        }
    }
    else {
        // Si la lista de jurados está vacía, imprimimos un mensaje de error
        printf("+ Error: Disqualify not possible\n");
    }

}

void stats(tListJ *listaJ){
    tPosJ i;
// Verificar si la lista está vacía
    if(!isEmptyListJ(*listaJ)) {
        i = firstJ(*listaJ);
        tItemJ auxJ = getItemJ(i, *listaJ);
        while (i!=NULLJ &&i<= lastJ(*listaJ)) {
// Mostrar el nombre del jurado actual
            printf("Jury %s\n",auxJ.juryName);
            tPosP p = firstP(auxJ.participantList);
// Verificar si la lista de participantes está vacía
            if(isEmptyListP(auxJ.participantList)) {
                printf("No participants\n");
            }
            else {
                tItemP auxP = getItemP(p, auxJ.participantList);
                while (p != NULLP){
// Mostrar el nombre del participante actual y su ubicación (EU o no EU)
                    printf("Participant %s location %s numvotes %d ", auxP.participantName,
                           auxP.EUParticipant == true ? "eu" : "non-eu",
                           auxP.numVotes);
// Verificar si hay votos válidos en el jurado actual
                    if (auxJ.validVotes == 0)
                        printf("(0.00%%)\n");
                    else
// Mostrar el porcentaje de votos recibidos por el participante actual
                        printf("(%.2f%%)\n", ((float)auxP.numVotes / (float)auxJ.validVotes) * 100.00);
                    p = nextP(p, auxJ.participantList);
                    if (p!=NULLP) auxP = getItemP(p,auxJ.participantList);
                }
            }
// Mostrar el número de votos nulos del jurado actual
            printf("Nullvotes %d\n", auxJ.nullVotes);
// Mostrar el número de votos válidos y el porcentaje de participación en el jurado actual
            printf("Participation: %d votes from %d voters (%.2f%%)\n\n",auxJ.validVotes+auxJ.nullVotes,
                   auxJ.totalVoters, ((float)(auxJ.validVotes+auxJ.nullVotes) / (float)auxJ.totalVoters ) *100.00);
            i= nextJ(i,*listaJ);
            if (i!=NULLJ) auxJ = getItemJ(i, *listaJ);
        }
    }else printf("+ Error: Stats not possible\n");

}

void Remove(tListJ *listaJ){
    tPosJ i; // Variable para iterar sobre la lista de jurados
    if(!isEmptyListJ(*listaJ)) { // Si la lista de jurados no está vacía
        i= firstJ(*listaJ); // Asignamos la posición del primer jurado
        tItemJ aux = getItemJ(i,*listaJ); // Obtenemos el primer jurado
        while (i!=NULLJ && i<= lastJ(*listaJ)) { // Mientras no lleguemos al final de la lista
            if(aux.validVotes+aux.nullVotes==0){ // Si el jurado no ha emitido votos válidos ni nulos
                printf("* Remove: jury %s\n", aux.juryName); // Imprimimos el mensaje de eliminación
                for (tPosP p= aux.participantList; p->next!=NULLP ; p= aux.participantList) { // Iteramos sobre la lista de participantes del jurado
                    deleteAtPositionP(p, &aux.participantList); // Eliminamos el participante actual
                }
                deleteAtPositionJ(i,listaJ); // Eliminamos el jurado actual
            } else i = nextJ(i,*listaJ); // Si el jurado ha emitido votos válidos o nulos, pasamos al siguiente jurado
            if (i!=NULLJ) aux = getItemJ(i,*listaJ); // Si no hemos llegado al final de la lista, obtenemos el siguiente jurado
        }
    }else printf("+ Error: Remove not possible\n"); // Si la lista de jurados está vacía, imprimimos un mensaje de error
}


void winners(tListJ *listaJ){
    if(!isEmptyListJ(*listaJ)) {  // Verifica que la lista de jurados no esté vacía
        tPosJ i= firstJ(*listaJ);  // Obtiene la primera posición de la lista de jurados
        tItemJ auxJ = getItemJ(i, *listaJ);  // Obtiene el primer elemento de la lista de jurados
        while (i !=NULLJ && i<= lastJ(*listaJ)) {  // Itera sobre la lista de jurados mientras la posición actual no sea nula y no se haya llegado al último elemento
            printf("Jury %s\n", auxJ.juryName);  // Imprime el nombre del jurado actual
            if (!isEmptyListP(auxJ.participantList)) {  // Verifica que la lista de participantes del jurado actual no esté vacía
                tItemP eur, noeur;  // Define dos variables para guardar al participante ganador de cada categoría
                bool empateEur = true, empateNoEur = true;  // Define variables booleanas para indicar si hay empate en cada categoría
                tPosP p = firstP(auxJ.participantList);  // Obtiene la primera posición de la lista de participantes del jurado actual
                tPosP a = p, b = p;  // Define dos variables para iterar sobre los participantes de cada categoría
                tItemP auxA, auxB;  // Define dos variables auxiliares para guardar los participantes de cada categoría
                for (bool aux = true; aux == true && nextP(a, auxJ.participantList) != NULLP; a = nextP(a, auxJ.participantList)) {  // Itera sobre los participantes de la categoría EU mientras la posición actual no sea nula y no se haya llegado al último elemento
                    auxA = getItemP(a,auxJ.participantList);  // Obtiene el participante actual

                    if (auxA.EUParticipant) {  // Verifica si el participante actual es de la categoría EU
                        eur = auxA;  // Si lo es, lo define como el primer ganador potencial
                        aux = false;  // Y detiene la iteración
                    }
                }
                for (bool aux = true; aux == true && nextP(b, auxJ.participantList) !=NULLP; b = nextP(b, auxJ.participantList)) {  // Itera sobre los participantes de la categoría no EU mientras la posición actual no sea nula y no se haya llegado al último elemento
                    auxB = getItemP(b,auxJ.participantList);  // Obtiene el participante actual

                    if (auxB.EUParticipant) {  // Verifica si el participante actual es de la categoría no EU
                        noeur = auxB;  // Si lo es, lo define como el primer ganador potencial
                        aux = false;  // Y detiene la iteración
                    }
                }
                for (; p != NULLP; p = nextP(p, auxJ.participantList)) {
                    tItemP auxP = getItemP(p, auxJ.participantList);  // Obtiene el participante actual

                    // Comprueba si el participante actual es de la UE y si su número de votos es mayor o igual que el del ganador actual de la UE
                    if (auxP.EUParticipant && auxP.numVotes >= eur.numVotes) {
                        empateEur = false;
                        // Comprueba si el participante actual es diferente al ganador actual de la UE y tiene la misma cantidad de votos que el ganador
                        if (strcmp(auxP.participantName, eur.participantName) != 0 && auxP.numVotes == eur.numVotes) {
                            empateEur = true;
                        }
                        // Actualiza el ganador de la UE
                        eur = auxP;
                    }
                    // Comprueba si el participante actual no es de la UE y si su número de votos es mayor o igual que el del ganador actual fuera de la UE
                    if (!auxP.EUParticipant && auxP.numVotes >= noeur.numVotes) {
                        empateNoEur = false;
                        // Comprueba si el participante actual es diferente al ganador actual fuera de la UE y tiene la misma cantidad de votos que el ganador
                        if (strcmp(auxP.participantName, noeur.participantName) != 0 && auxP.numVotes == noeur.numVotes) {
                            empateNoEur = true;
                        }
                        // Actualiza el ganador fuera de la UE
                        noeur = auxP;
                    }
                }
                // Si no hay empate en la categoría de participantes europeos, se imprime el nombre y número de votos del ganador
                if (!empateEur) printf("Location eu: Participant %s numvotes %d\n", eur.participantName, eur.numVotes);
                // De lo contrario, se imprime que no hay ganador
                else printf("Location eu: No winner\n");
                // Si no hay empate en la categoría de participantes no europeos, se imprime el nombre y número de votos del ganador
                if (!empateNoEur)
                    printf("Location non-eu: Participant %s numvotes %d\n\n", noeur.participantName, noeur.numVotes);
                // De lo contrario, se imprime que no hay ganador
                else printf("Location non-eu: No winner\n\n");

            } else printf("Location eu: No winner\nLocation non-eu: No winner\n\n");
            // Se avanza al siguiente elemento de la lista de jurados
            i = nextJ(i, *listaJ);
            // Si hay más elementos, se obtiene la información del siguiente jurado
            if (i!=NULLJ) auxJ = getItemJ(i, *listaJ);
        }
    }else printf("+ Error: Winners not possible");
}




tEUParticipant conversorBool(char *Eur){
    if(strcmp(Eur,"eu")==0)
        return true;
    else
        return false;
}

tNumVotes conversorInt(char *votes){
    int num = (int)atof(votes);
    return num;
}
