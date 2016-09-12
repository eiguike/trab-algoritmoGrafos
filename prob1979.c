// Ângela Rodrigues Ferreira
// Henrique Teruo Eihara
// Hitalo Siqueira


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRETO 2
#define CINZA 1
#define BRANCO 0
#define NULO -1
#define MAX 6000

typedef struct NO{
  int v;
  struct NO *prox;
}no;
typedef no* lista;

int cor[MAX], pred[MAX], d[MAX], f[MAX], peso[MAX], tempo, elementos, topSort[MAX];

void iniciaLista(lista *pl);
void insereInicio(lista *pl, int vertice);
void insereFim(lista *pl, int vertice);
void liberaLista(lista *pl);
void imprimeLista(lista *pl);
void removeInicio(lista *pl, int *vertice);
void buscaLargura(lista listaAdj[], int n);
void DFS(lista listaAdj[], int n);
void DFS_AUX(lista listaAdj[], no *aux, int u);

int main(int argc, char** argv) {

  char x,y; 
  int N, M, C, i, j, k, u, v;
  char string[500];
  char * token;
  
  /*Reads number vertices */
  fgets(string, sizeof(string), stdin);
  sscanf(string, "%d", &N);
  //printf("%d\n", N); 
  

  
  while(N != 0){
    lista listaAdj[N];

    for(i=0;i<N;i++){
      iniciaLista(&listaAdj[i]);
    }
    
    for (k=0; k < N; k++) {
      /* Reads vertex */
      fgets(string, sizeof(string), stdin);
      sscanf(string, "%d", &i);
      //printf("%d\n", i); 
      
      /* Reads list of vertices adjacent to vertex i */
      fgets(string, sizeof(string), stdin);
      token = strtok(string," "); 
      while (token != NULL){
  j = atoi(token);
  //printf("%d ", j);
  insereFim(&listaAdj[i - 1], j - 1);
  insereFim(&listaAdj[j - 1], i - 1);
  token = strtok(NULL," ");
      }
      //printf("\n", j);
    }
    
    /* Debug -- Writes graph matrix */ 
    /* for (i=0; i < N; i++){
      for (j=0; j < N; j++)
  printf("%d ", graph[i][j]);
      printf("\n");
      } */
    
    buscaLargura(listaAdj, N);
 
    for(i=0;i<N;i++){
        liberaLista(&listaAdj[i]);
    }

    /* Reads number of vertices. */
    fgets(string, sizeof(string), stdin);
    sscanf(string, "%d", &N);
    //printf("%d\n", N);
    
    
  } 
}

void iniciaLista(lista *pl){
  *pl = NULL;
}

void insereInicio(lista *pl, int vertice){
  no *novoNo;
  novoNo = (no*) malloc(sizeof(no));

  novoNo->v = vertice;
  novoNo->prox = *pl;

  *pl = novoNo;
}

void insereFim(lista *pl, int vertice){
  no *novoNo, *aux;
  
  if(*pl == NULL){
    novoNo = (no*) malloc(sizeof(no));
    novoNo->v = vertice;
    novoNo->prox = NULL;
    
    *pl = novoNo;

  }else{
    aux = *pl;
    insereFim(&(aux->prox), vertice);
  }
}

void liberaLista(lista *pl){
  no *aux;
  
  aux = *pl;
  if(*pl != NULL){
    if(aux->prox != NULL){
      liberaLista(&(aux->prox));
    }
  }
  free(*pl);
  *pl = NULL;
}

void imprimeLista(lista *pl){
  no *aux;
  
  aux = *pl;
  if(aux == NULL){  
    return;
  }else{
    printf("%d ", aux->v);
    imprimeLista(&(aux->prox));
  }
}

void removeInicio(lista *pl, int *vertice){
  no *aux;

  aux = *pl;
  if(aux == NULL){  
    return;
  }else{
    *pl = aux->prox;
    *vertice = aux->v;
    free(aux);
  }
}

void DFS(lista listaAdj[], int n){
  int i, pesoAux[n], tempoMax;
  no *aux;

  for(i=0;i<n;i++){
    cor[i] = BRANCO;
    pred[i] = NULO;
    d[i] = NULO;
    f[i] = NULO;
  }
  tempo = 0;

  for(i=0;i<n;i++){
    if(cor[i] == BRANCO){
      DFS_AUX(listaAdj, aux, i);
    }
  }
  for(i=0;i<n;i++){
    pesoAux[i] = peso[i];
  }

  for(i=0;i<n;i++){
    aux = listaAdj[topSort[i]];
    while(aux != NULL){
      if(pesoAux[aux->v] < pesoAux[topSort[i]] + peso[aux->v]){
        pesoAux[aux->v] = pesoAux[topSort[i]] + peso[aux->v];
      }
      aux = aux->prox;
    }
  }

  tempoMax = 0;
  for(i=0;i<n;i++){
    if(tempoMax < pesoAux[i]){
      tempoMax = pesoAux[i];
    }
  }
  printf("%d\n",tempoMax);
}

void DFS_AUX(lista listaAdj[], no *aux, int u){

  cor[u] = CINZA;
  d[u] = tempo;
  tempo++;

  aux = listaAdj[u];

  while(aux != NULL){
    if(cor[aux->v] == BRANCO){
      pred[aux->v] = u;
      DFS_AUX(listaAdj, aux, aux->v);
    }
    aux = aux->prox;
  }
  cor[u] = PRETO;
  f[u] = tempo;

  topSort[elementos] = u;
  elementos--;
  tempo++;
}

void buscaLargura(lista listaAdj[], int n){
    lista q;
    int vertice, max, i, dist[n], cor[n], pred[n];
    no *aux;
 
    for(i=0;i<n;i++){
        dist[i] = n + 1;
        cor[i] = BRANCO;
        pred[i] = n + 1;
    }
 
    dist[0] = 0;
    cor[0] = CINZA;
    pred[0] = NULO;
 
    iniciaLista(&q);
    insereFim(&q, 0);
 
    while(q != NULL){
        removeInicio(&q, &vertice);
        aux = listaAdj[vertice];
 
        while(aux != NULL){
            if(cor[aux->v] == BRANCO){
                cor[aux->v] = CINZA;
                dist[aux->v] = dist[vertice] + 1;
                pred[aux->v] = vertice;
                insereFim(&q, aux->v);
            }
             
            cor[vertice] = PRETO;
            aux = aux->prox;
        }   
    }

    for(i=0;i<n;i++){
      printf("%d ", cor[i]);
    }
    printf("\n");

    for(i=0;i<n;i++){
      printf("%d ", pred[i]);
    }
    printf("\n");

    for(i=0;i<n;i++){
      printf("%d ", cor[i]);
    }
    printf("\n");

}