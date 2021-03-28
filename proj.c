/*        PROJETO IAED        */
/* Realizado por Diogo Falcao ist199199  */

/* Bibliotecas */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* Constantes */
#define MAXDESC 50
#define MAXSTR 20
#define MAXTAREFAS 10000
#define MAXATIV 10
#define MAXUT 50

/* Variaveis globais */
int time;
int tarefas = 0;

/* Estrutura */
typedef struct{
    char desc[MAXDESC];  /*descricao*/
    char ativ[MAXATIV];  /*atividade*/
    int dur;     /*duracao da tarefa*/
    int timeexec;        /*tempo em que saiu da tarefa inicial*/
} Tarefa;



/* prototipos*/

void comando_t(Tarefa dis[]);



/* main fuction */

int main(){
    Tarefa ids[MAXTAREFAS];
    char comando;
    do {
        comando = getchar();
        if(comando == 't'){
            comando_t(ids);
        }
        else if(comando == 'l'){
        }
        else if(comando == 'n'){
        }
        else if(comando == 'u'){
        }
        else if(comando == 'm'){
        }
        else if(comando == 'd'){
        }
        else if(comando == 'a'){
        }

    } while(comando != 'q');

    return 0;
}

void comando_t(Tarefa ids[]){
    int duracao, i;
    char descricao[MAXDESC];
    
    scanf("%d %s", &duracao, descricao);
    
    for(i=0; i < tarefas-1; i++){
        if (strcmp(descricao, ids[i].desc) == 0){
            printf("duplicate description");
            break;}
    }
    if (tarefas == MAXTAREFAS)
        printf("too many tasks");

    else{
        ids[tarefas].dur = duracao;
        strcpy(ids[tarefas].desc, descricao);
        tarefas++;
        printf("task %d\n", tarefas);
    }
}
