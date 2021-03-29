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
int atividades = 3;
char ativ[MAXATIV][MAXSTR] = {"TO DO","IN PROGRESS", "DONE"};

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
int comando_a();
void el_espacos_inicio(char str[], int size);


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
            comando_a();
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
    char utilizadores[MAXUT][MAXSTR], str[MAXSTR], c;
    int i, comp;

    for(i=0 ;(c = getchar()) != '\n';){
        if(c != ' '){
            str[i] = c;
            i++;
        }
    }
    str[i] = '\0';
    comp = strlen(str);

    if(str[0] == '\0'){
        for(i=0; i < numusers; i++){
            printf("%s\n", utilizadores[i]);
        }
        return 0;
    }

    else{
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

int comando_a(){
    char str[MAXSTR];
    int i, compaux, comp;
    scanf("%[^\n]", str);
    compaux = strlen(str);
    el_espacos_inicio(str, compaux);
    comp = strlen(str);

    if(str[0] == '\0'){
        for(i=0; i < atividades; i++)
            puts(ativ[i]);
        return 0;
    }

    for(i=0; i<comp; i++){
        if (str[i] >= 'a' && str[i] <= 'z'){
            printf("invalid description\n");
            return 0;
        }
    }

    for(i=0; i < atividades; i++){
        if(strcmp(ativ[i],str) == 0){
            printf("duplicate activity\n");
            return 0;
        }
    }

    if(atividades+1 >= MAXATIV){
        printf("too many activities\n");
        return 0;
    }

    else{
        strcpy(ativ[atividades], str);
        puts(ativ[atividades]);
        atividades++;
        return 0;
    }
}
/* Funcoes auxiliares */

void el_espacos_inicio(char str[], int size){
    int i1,i2 = 0, firstspace = 0;
    for(i1=0; i1< size; i1++){
        if( str[i1] != ' ')
            firstspace = 1;
        if (firstspace ==1){
            str[i2] = str[i1];
            i2++;
        }
    }
    str[i2] = '\0';
}



























