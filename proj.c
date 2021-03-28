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
int tarefas;
int numusers;

/* Estrutura */
typedef struct{
    char desc[MAXDESC];  /*descricao*/
    char ativ[MAXATIV];  /*atividade*/
    int dur;     /*duracao da tarefa*/
    int timeexec;        /*tempo em que saiu da tarefa inicial*/
} Tarefa;



/* prototipos*/

int comando_t(Tarefa dis[]);
int comando_n();
int comando_u();



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
            comando_n();
        }
        else if(comando == 'u'){
            comando_u();
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

/* funcoes dos comandos */

int comando_t(Tarefa ids[]){
    int duracao, i;
    char descricao[MAXDESC], c;
    
    scanf("%d", &duracao);
    for(i = 0; (c = getchar()) != '\n' && c != EOF; i++ )
        descricao[i] = c;
    descricao[i] = '\0';

    for(i=0; i < tarefas; i++){
        if (strcmp(descricao, ids[i].desc) == 0){
            printf("duplicate description\n");
            return 0;
            }
    }
    if (tarefas == MAXTAREFAS){
        printf("too many tasks\n");
        return 0;
    }

    else{
        ids[tarefas].dur = duracao;
        strcpy(ids[tarefas].desc, descricao);
        tarefas++;
        printf("task %d\n", tarefas);
        return 0;
    }
}

int comando_n(){
    float duracao;
    int aux;

    scanf("%f", &duracao);
    aux = duracao;

    if(duracao < 0 || (duracao != aux)){
        printf("invalid time\n");
        return 0;
    }
    
    else{
    time += duracao;
    printf("%d\n", time);
    return 0;
    }
}

int comando_u(){
    char utilizadores[MAXUT][MAXSTR], str[MAXSTR], fim[] = "\n";
    int i, escreve = 0, comp;

    scanf("%s", str);
    comp = strlen(str);

    if(strcmp(str,fim) == 0){
        for(i=0; i < numusers; i++){
            printf("%s\n", utilizadores[i]);
        }
        return 0;
    }

    for(i=0; i < comp; i++){
        if(str[i] != ' ' && str[i] != '\t')
            escreve = 1;
    }

    if(escreve == 1){
        for(i=0; i < numusers; i++){
            if(strcmp(utilizadores[i],str) == 0){
                printf("user already exists\n");
                return 0;
            }
        }

        if(numusers == MAXUT){
            printf("too many users\n");
            return 0;
        }

        else{
            for(i=0; i < comp; i++){
                utilizadores[numusers][i] = str[i];
            }
            utilizadores[numusers][i] = '\0';
            numusers++;
            return 0;
        }
    }
    return 0;
}

/* Funcoes auxiliares */
