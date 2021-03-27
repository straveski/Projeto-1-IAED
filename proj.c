/*        PROJETO IAED        /
/ Realizado por Diogo Falcao ist199199  /

/ Bibliotecas /
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/ Constantes /
#define MAXDESC 50
#define MAXSTR 20
#define MAXTAREFAS 10000
#define MAXATIV 10
#define MAXUT 50

/ Variaveis globais /
global time;
global tarefas;

/ Estrutura /
typedef struct{
    char desc[MAXDESC];  /descricao/
    char ativ[MAXATIV];  /atividade/
    int duracao = 0;         /duracao da tarefa/
    int timeexec;        / tempo em que saiu da tarefa inicial/
} Tarefa;

/ prototipos /






/ main fuction */

int main(){
    Tarefa ids[MAXTAREFAS];






    return 0;
}
