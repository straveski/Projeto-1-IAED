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
char utilizadores[MAXUT][MAXSTR];

/* Estrutura */
typedef struct{
    char desc[MAXDESC];  /*descricao*/
    char ativ[MAXSTR];  /*atividade*/
    int dur;     /*duracao da tarefa*/
    int timeexec;        /*tempo em que saiu da tarefa inicial*/
} Tarefa;

/* prototipos*/

int comando_t(Tarefa ids[]);
int comando_l(Tarefa ids[]);
int comando_n();
int comando_u();
int comando_a();
int comando_m(Tarefa ids[]);
int comando_d(Tarefa ids[]);
void el_espacos_inicio(char str[], int size);
void ordena_alfabet(Tarefa ids[]);
void ordena(int vec[],Tarefa ids[], int size);

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
            comando_l(ids);
        }
        else if(comando == 'n'){
            comando_n();
        }
        else if(comando == 'u'){
            comando_u();
        }
        else if(comando == 'm'){
            comando_m(ids);
        }
        else if(comando == 'd'){
            comando_d(ids);
        }
        else if(comando == 'a'){
            comando_a();
        }
    } while(comando != 'q');

    return 0;
}

/* funcoes dos comandos */

int comando_t(Tarefa ids[]){
    int duracao, i, size;
    char descricao[MAXDESC], c;
    
    scanf("%d", &duracao);
    for(i = 0; (c = getchar()) != '\n' && c != EOF; i++ )
        descricao[i] = c;
    descricao[i] = '\0';
    size = strlen(descricao);
    el_espacos_inicio(descricao, size);

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
        ids[tarefas].timeexec = 0;
        strcpy(ids[tarefas].ativ, ativ[0]);
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
    char str[MAXSTR], c;
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
        atividades++;
        return 0;
    }
}

int comando_l(Tarefa ids[]){
    int idinput[MAXTAREFAS] = {0}, quantidade_ids = 0, i = 0, t, flag = 0;
    char c;

    while(( c = getchar()) != '\n'){
        if (flag == 1){
            if (c != ' ')
                idinput[i] = (idinput[i]*10) + (c - '0');
            else
                i++; 
        }
        else if(c >= '1' && c <= '9'){
            flag = 1;
            idinput[0] += c - '0'; 
        }
    }

    for(i = 0; idinput[i] != 0; i++)
        quantidade_ids++;
    
    if (quantidade_ids == 0){
        ordena_alfabet(ids);
        return 0;
    }
    
    else{
        for(i=0; i < quantidade_ids; i++){
            if (idinput[i] > tarefas){
                printf("%d: no such task\n", idinput[i]);
                return 0;
            }
        }
        for(i=0; i < quantidade_ids; i++){
            t = idinput[i];
            printf("%d %s #%d %s\n", t, ids[t-1].ativ, ids[t-1].dur, ids[t-1].desc);
        }
        return 0;
    }
}

int comando_m(Tarefa ids[]){
    int i, id, flag = 0, gasto, slack;
    char atividade[MAXSTR], utilizador[MAXSTR];
    scanf("%d %s %[^\n]", &id, utilizador, atividade);

    /*erros*/
    if(id > tarefas){
        printf("no such task\n");
        return 0;
    }
    if(strcmp(atividade,ativ[0]) == 0){
        printf("task already started\n");
        return 0;
    }
    for(i=0; i < numusers; i++){
        if(strcmp(utilizador, utilizadores[i]) == 0)
            flag = 1;
    }
    if(flag==0){
        printf("no such user\n");
        return 0;
    }
    for(i=0; i<atividades; i++){
        if(strcmp(atividade, ativ[i]) == 0)
            flag = 0;
    }

    if (flag == 1){
        printf("no such activity\n");
        return 0;
    }
    /* comando correto*/
    if(strcmp(atividade, ativ[2]) == 0){
        gasto = ids[id-1].timeexec - time;
        slack = gasto - ids[id-1].dur;
        printf("duration=%d slack=%d\n", gasto, slack);
        return 0;
    }

    else{
        strcpy(ids[id-1].ativ, atividade);
        ids[id-1].timeexec = time;
        return 0;
    }
}

int comando_d(Tarefa ids[]){
    int i,j=0, flag = 0, compaux, ids_ativ[MAXTAREFAS];
    char atividade[MAXSTR];
    scanf("%[^\n]", atividade);
    compaux = strlen(atividade);
    el_espacos_inicio(atividade, compaux);

    /*         erro       */
    for(i = 0; i < atividades; i++){
        if(strcmp(atividade, ativ[i]) == 0)
            flag = 1;
    }
    if (flag == 0){
        printf("no such activity");
        return 0;
    }
    /* funcao */
    /*Este ciclo vai percorrer todos os ids das tarefas e vai verificar quais tem a mesma ativiadade
    que a atividade dada como input, copiando esses ids para um vetor que vai seguidamente ser ordenado*/
    for(i = 0; i < tarefas; i++){
        if(strcmp(ids[i].ativ,atividade) == 0){
            ids_ativ[j] = i+1;
            j++;
        }
    }

    ordena(ids_ativ, ids, j);
    return 0;
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

void ordena_alfabet(Tarefa ids[]){
    char v1[MAXTAREFAS][MAXDESC], aux[MAXDESC]; 
    int i, k, v2[MAXTAREFAS] = {0}, aux2;

    for(i=0; i<tarefas;i++)
        v2[i] = i+1;

    for(i=0; i<tarefas; i++){
        strcpy(v1[i], ids[i].desc);
    }

    for(i=0; i < tarefas; i++){
        for(k = i+1; k < tarefas;k++){
            if(strcmp(v1[i],v1[k]) > 0){
                strcpy(aux,v1[k]);
                strcpy(v1[k], v1[i]);
                strcpy(v1[i], aux);
                aux2 = v2[k];
                v2[k] = v2[i];
                v2[i] = aux2;
            }
        }
    }

    for(i=0; i < tarefas; i++)
        printf("%d %s #%d %s\n",v2[i], ids[v2[i]-1].ativ, ids[v2[i]-1].dur, v1[i]);
}

void ordena(int vec[], Tarefa ids[], int size){
    int i, j, aux, fim = size;
    /* este ciclo vai ordenar os ids em relacao ao instante de inico atraves de um bubble sort e se 
    dois ids tiverem o mesmo instante de inico, vai ordena-los em relacao a descricao*/
    for(i=0; i < fim; i++){
        for(j= i+1; j < fim; j++){
            if(ids[vec[i]].timeexec > ids[vec[j]].timeexec){
                aux = vec[j];
                vec[j] = vec[i];
                vec[i] = aux;
            }
            else if(ids[vec[i]].timeexec == ids[vec[j]].timeexec){
                if(strcmp(ids[vec[i]].desc,ids[vec[j]].desc) > 0){
                    aux = vec[j];
                    vec[j] = vec[i];
                    vec[i] = aux;
                }
            }
        }
    }
    for(i=0; i < size; i++)
        printf("%d\n", vec[i]);

    for(i=0; i < size; i++)
        printf("%d %d %s\n", vec[i], ids[vec[i]-1].timeexec, ids[vec[i]-1].desc);
}