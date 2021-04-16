/*        PROJETO IAED        */
/* Realizado por Diogo Falcao ist199199  */

/* Bibliotecas */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* Constantes */
#define MAXDESC 51
#define MAXSTR 21
#define MAXTAREFAS 10000
#define MAXATIV 10
#define MAXUT 50

#define ERRO_DESC_DUPLICADA "duplicate description\n"
#define ERRO_MUITAS_TAREFAS "too many tasks\n"
#define ERRO_DESC_INV "invalid duration\n"
#define ERRO_TEMPO "invalid time\n"
#define ERRO_USER_EXISTE "user already exists\n"
#define ERRO_MUITOS_USERS "too many users\n"
#define ERRO_ATIV_DUP "duplicate activity\n"
#define ERRO_INVALID_DESC "invalid description\n"
#define ERRO_MUITAS_ATIV "too many activities\n"
#define ERRO_TASK_N_EXISTE "no such task\n"
#define ERRO_TASK_JA_COMECOU "task already started\n"
#define ERRO_USER_N_EXISTE "no such user\n"
#define ERRO_ATIV_N_EXISTE "no such activity\n"

/* Variaveis globais */
int time; /*Controlar o tempo */
int tarefas; /*Controla o numero de tarefas*/
int numusers; /*Controla o numero de utilizadores */
int atividades = 3; /*Controla o numero de atividades */
/*Vetor que contem as strings das atividades existentes*/
char ativ[MAXATIV][MAXSTR] = {"TO DO","IN PROGRESS", "DONE"};
/*Vetor  que contem as strings dos nomes dos utilizadores*/
char utilizadores[MAXUT][MAXSTR];
int aux[MAXTAREFAS];


/* Estruturas */
typedef struct{
    char desc[MAXDESC];  /*descricao*/
    char atv[MAXSTR];  /*atividade*/
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
void ordena(int a[],Tarefa ids[], int left, int right, int flag);
void merge(int vec[], Tarefa ids[], int left, int m, int right, int flag);

/* main fuction--- Esta funcao vai tratar dos comandos dados de input pelo
 utilizador ate que este utilize o comando q para acabar o programa*/
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

/*Esta funcao vai adicionar uma nova tarefa ao sistema*/
int comando_t(Tarefa ids[]){
    int duracao, i, size;
    char descricao[MAXDESC], c;
    /*Tratamento do input*/
    scanf("%d", &duracao);
    for(i = 0; (c = getchar()) != '\n' && c != EOF; i++ )
        descricao[i] = c;
    descricao[i] = '\0';
    size = strlen(descricao);
    el_espacos_inicio(descricao, size);
    /*Tratamento dos erros*/
    for(i=0; i < tarefas; i++){
        if (strcmp(descricao, ids[i].desc) == 0){
            printf(ERRO_DESC_DUPLICADA);
            return 0;
            }
    }
    if (tarefas == MAXTAREFAS){
        printf(ERRO_MUITAS_TAREFAS);
        return 0;
    }
    if(duracao <= 0){
        printf(ERRO_DESC_INV);
        return 0;
    }
    /*adiciona a tarefa a estrutura dos ids das tarefas*/
    else{
        ids[tarefas].dur = duracao;
        ids[tarefas].timeexec = 0;
        strcpy(ids[tarefas].atv, ativ[0]);
        strcpy(ids[tarefas].desc, descricao);
        tarefas++; /*incrementa as tarefas globalmente*/
        printf("task %d\n", tarefas);
        return 0;
    }
}
/*Esta funcao avanca o tempo do sistema*/
int comando_n(){
    float duracao;
    int aux;
    /*Tratamento do input*/
    scanf("%f", &duracao);
    aux = duracao;
    /*Tratamento dos erros*/
    if(duracao < 0 || (duracao != aux)){
        printf(ERRO_TEMPO);
        return 0;
    }
    
    else{
    time += duracao; /*Incrementa o tempo globalmente*/
    printf("%d\n", time);
    return 0;
    }
}
/*Esta funcao adiciona um utiizador ou lista todos os utilizadores*/
int comando_u(){
    char strnome[MAXSTR], c;
    int i;
    /*Tratamento do input*/
    for(i=0 ;(c = getchar()) != '\n';){
        if(c != ' '){
            strnome[i] = c;
            i++;
        }
    }
    strnome[i] = '\0';
    /*Verificar se e para listar todos os utilizadores*/
    if(strnome[0] == '\0'){
        for(i=0; i < numusers; i++){
            printf("%s\n", utilizadores[i]);
        }
        return 0;
    }
    else{
        /*Tratamento dos erros*/
        for(i=0; i < numusers; i++){
            if(strcmp(utilizadores[i],strnome) == 0){
                printf(ERRO_USER_EXISTE);
                return 0;
            }
        }
        if(numusers == MAXUT){
            printf(ERRO_MUITOS_USERS);
            return 0;
        }
        else{
            strcpy(utilizadores[numusers], strnome);
            numusers++;
            return 0;
        }
    }
    return 0;
}
/*Esta funcao adiciona uma atividade ou lista todas as atividades*/
int comando_a(){
    int i, compaux, comp;
    char string[MAXSTR],c;
    /*Tratamento do input*/
    for(i=0; (c=getchar()) != '\n';i++){
        string[i] = c;
    }
    string[i]= '\0';
    /*Tamanho e retira o espaco do inicio */
    compaux = strlen(string);
    el_espacos_inicio(string, compaux);
    comp = strlen(string);

    /*Caso do input sem atividade */
    if(string[0] == '\0'){
        for(i=0; i < atividades; i++)
            puts(ativ[i]);
        return 0;
    }
    /*Tratamento dos erros*/
    for(i=0; i < atividades; i++){
        if(strcmp(ativ[i],string) == 0){
            printf(ERRO_ATIV_DUP);
            return 0;
        }
    }
    for(i=0; i<comp; i++){
        if (string[i] >= 'a' && string[i] <= 'z'){
            printf(ERRO_INVALID_DESC);
            return 0;
        }
    }
    if(atividades+1 > MAXATIV){
        printf(ERRO_MUITAS_ATIV);
        return 0;
    }
    /*Adiciona a nova atividade ao vetor de strings*/
    else{
        strcpy(ativ[atividades], string);
        atividades++; /*incrementa globalmente o numero de atividades*/
        return 0;
    }
}
/*Esta funcao vai listar as atividades*/
int comando_l(Tarefa ids[]){
    int idinput[MAXTAREFAS] = {0}, quantidade_ids = 0, i = 0, t, flag = 0;
    int ids_ord[MAXTAREFAS];
    char c;
    /*tratamento do input*/
    /*flag = 0 --> estamos num espaco*/
    /*flag = 1 --> estamos a ler um numero*/
    /*flag = -1 --> numero negativo*/
    while(( c = getchar()) != '\n'){
        if (flag == 1){
            if (c != ' ')
                idinput[i] = (idinput[i]*10) + (c - '0');
            else{
                i++;
                flag = 0;
            }
        }
        else if(c >= '1' && c <= '9'){
            if (flag == -1){
                idinput[i] += (c - '0')*flag;
                flag = 1; 
            }
            else{
                flag = 1;
                idinput[i] += c - '0'; 
            }
        }
        else if(c == '-'){
            flag = -1;
        }
    }
    for(i = 0; idinput[i] != 0; i++)
        quantidade_ids++;
    /*Lista todas as tarefas*/
    if (quantidade_ids == 0){
        for(i=0;i<tarefas; i++){
            ids_ord[i] = i+1;
        }
        ordena(ids_ord, ids, 0, tarefas-1, 0);
        for(i=0; i < tarefas; i++)
            printf("%d %s #%d %s\n",ids_ord[i], ids[ids_ord[i]-1].atv,\
            ids[ids_ord[i]-1].dur, ids[ids_ord[i]-1].desc);
        return 0;
    }
    else{ 
        for(i=0; i < quantidade_ids; i++){
            /*Tratamento dos erros*/
            if (idinput[i] > tarefas || idinput[i] <= 0)
                printf("%d: no such task\n", idinput[i]);
            /*Lista as tarefas que recebeu de input*/
            else{
            t = idinput[i];
            printf("%d %s #%d %s\n",t,ids[t-1].atv,ids[t-1].dur,ids[t-1].desc);
            }
        }
        return 0;
    }
}
/*Esta funcao move uma tarefa de uma atividade para outra*/
int comando_m(Tarefa ids[]){
    int i, id, flag = 0, gasto, slack;
    char atividade[MAXSTR], utilizador[MAXSTR];
    /*Tratamento do input*/
    scanf("%d %s %[^\n]", &id, utilizador, atividade);

    /*Tratamento dos erros*/
    if(id > tarefas || id <= 0){
        printf(ERRO_TASK_N_EXISTE);
        return 0;
    }
    if(strcmp(atividade,ativ[0]) == 0){
        if(strcmp(ids[id-1].atv, ativ[0]) != 0){
            printf(ERRO_TASK_JA_COMECOU);
            return 0;
        }
    }
    /*flag = 0 --> nao encontrou o utilizador*/
    for(i=0; i < numusers; i++){
        if(strcmp(utilizador, utilizadores[i]) == 0)
            flag = 1;
    }
    if(flag==0){
        printf(ERRO_USER_N_EXISTE);
        return 0;
    }
    /*Se passou, a flag esta  a 1, entao:
    flag = 1 --> encontramos a atividade
    flag = 0 --> nao encontramos a atividade*/
    for(i=0; i<atividades; i++){
        if(strcmp(atividade, ativ[i]) == 0)
            flag = 0;
    }
    if (flag == 1){
        printf(ERRO_ATIV_N_EXISTE);
        return 0;
    }
    /*Se movermos a atividade para DONE*/
    if(strcmp(atividade, ativ[2]) == 0){
        if(strcmp(ids[id-1].atv,ativ[0])==0)
            gasto = 0;
        else
            gasto = time - ids[id-1].timeexec;
        slack = gasto - ids[id-1].dur;
        strcpy(ids[id-1].atv, atividade);
        printf("duration=%d slack=%d\n", gasto, slack);
        return 0;
    }
    /*Se a tarefa ainda nao tinha sido iniciada, vamos iniciar*/
    else if(ids[id-1].timeexec == 0){
        strcpy(ids[id-1].atv, atividade);
        ids[id-1].timeexec = time;
        return 0;
    }
    /*Se ja tiver sido iniciada e nao for movida para DONE*/
    else{
        strcpy(ids[id-1].atv, atividade);
        return 0;
    }
}
/*Esta funcao lista todas as tarefas que estejam numa dada atividade*/
int comando_d(Tarefa ids[]){
    int i,j=0, flag = 0, compaux, ids_ativ[MAXTAREFAS];
    char atividade[MAXSTR], c;
    /*Tratamento do input*/
    for(i=0;(c=getchar()) != '\n';i++){
        atividade[i] = c;
    }
    atividade[i] = '\0';
    compaux = strlen(atividade);
    el_espacos_inicio(atividade, compaux);

    /* Tratamento dos erros*/
    for(i = 0; i < atividades; i++){
        if(strcmp(atividade, ativ[i]) == 0)
            flag = 1;
    }
    if (flag == 0){
        printf(ERRO_ATIV_N_EXISTE);
        return 0;
    }

    for(i = 0; i < tarefas; i++){
        if(strcmp(ids[i].atv,atividade) == 0){
            ids_ativ[j] = i+1;
            j++;
        }
    }
    /*vai ordenar as tarefas dessa atividade*/
    ordena(ids_ativ, ids,0, j-1, 0);
    ordena(ids_ativ, ids, 0, j-1, 1);
    /*output*/
    for(i=0; i < j; i++)
        printf("%d %d %s\n", ids_ativ[i], ids[ids_ativ[i]-1].timeexec,\
         ids[ids_ativ[i]-1].desc);
    
    return 0;
}
/* Funcoes auxiliares */

/*Esta funcao vai retirar os espacos do inicio de uma string*/
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

/*flag = 0 ---> ordenacao alfabetica
flag = 1 ---> ordenacao tempos de exec*/
void ordena(int a[],Tarefa ids[], int left, int right, int flag){
    int m = (right + left)/2;
    if (right <= left)
        return;
    ordena(a,ids,left, m, flag);
    ordena(a,ids, m+1, right, flag);
    merge(a,ids, left, m, right, flag);
}

void merge(int vec[], Tarefa ids[], int left, int m, int right, int flag){
    int i, j, k;
    for (i = m + 1; i > left; i--)
        aux[i-1] = vec[i-1];
    for (j = m; j < right; j++)
        aux[right + m - j] = vec[j+1];
    if (flag == 1){
        for (k = left; k <= right; k++){
            if ((ids[aux[j]-1].timeexec < ids[aux[i]-1].timeexec) || i == m + 1)
                vec[k] = aux[j--];
            else
                vec[k] = aux[i++];
        }
    }
    else{
        for (k = left; k <= right; k++){
            if (strcmp(ids[aux[j]-1].desc,ids[aux[i]-1].desc)< 0 || i == m + 1)
                vec[k] = aux[j--];
            else
                vec[k] = aux[i++];
        }
    }   
}
