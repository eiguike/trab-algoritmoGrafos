// Ângela Rodrigues Ferreira
// Henrique Teruo Eihara
// Hitalo Siqueira

#include <stdio.h>
#include <stdlib.h>

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

int cor[MAX], pred[MAX], d[MAX], f[MAX], peso[MAX], tempo, elementos, topSort[MAX], achou = 0;
int flag = 0;

void iniciaLista(lista *pl);
void insereInicio(lista *pl, int vertice);
void insereFim(lista *pl, int vertice);
void liberaLista(lista *pl);
void imprimeLista(lista *pl);
void removeInicio(lista *pl, int *vertice);
int DFS(lista listaAdj[], int n, int start);
void DFS_AUX(lista listaAdj[], no *aux, int u);

int main(int argc, char** argv) {

  int N, M, V, W, P, i, k;
  lista listaAdj[MAX];

  scanf("%d %d", &N, &M);

  // n = vertex
  // m = edges
  while(N != 0 || M != 0){
    flag = 0;

    for(i=0;i<N;i++){
      iniciaLista(&listaAdj[i]);
    }

    for (k=0; k < M; k++) {
      scanf("%d %d %d", &V, &W, &P);

      insereFim(&listaAdj[V-1], W - 1);
      if(P == 2)
        insereFim(&listaAdj[W-1], V - 1);
    }

    for(i=0; i<N; i++){
      if(DFS(listaAdj, N, i) == 0){
        printf("0\n");
        break;
        flag = -1;
      }else
        flag = 0;
    }

    if(flag == 0)
      printf("1\n");

//    for(i=0;i<N;i++){
//      liberaLista(&listaAdj[i]);
//    }

    scanf("%d %d", &N, &M);
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

int DFS(lista listaAdj[], int n, int start){
  int i;
  no *aux = NULL;

  for(i=0;i<n;i++){
    cor[i] = BRANCO;
    pred[i] = NULO;
    d[i] = NULO;
    f[i] = NULO;
  }
  DFS_AUX(listaAdj, aux, start);
  flag++;

  for(i=0 ;i<n;i++){
    if(cor[i] == BRANCO){
        return 0;
    }
  }
  return 1;
}

void DFS_AUX(lista listaAdj[], no *aux, int u){
  cor[u] = CINZA;
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
}
