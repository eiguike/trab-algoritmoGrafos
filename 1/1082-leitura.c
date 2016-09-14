// Primeira Trabalho - Algoritmo em Grafos 2016/2
// Ângela Rodrigues Ferreira
// Henrique Teruo Eihara
// Hitalo Siqueira
// https://www.urionlinejudge.com.br/judge/en/problems/view/1082

#include <stdio.h>

#define MAXN 30

#define WHITE 0
#define GRAY 1
#define BLACK 2
#define INFINITE -1
#define ZERO 0

#define TRUE 1
#define FALSE 0

typedef struct{
  int begin;
  int end;
  int queue[MAXN];
}QUEUE;

int is_queue_empty(QUEUE *q){
  return q->begin == q->end ? TRUE : FALSE;
}

int remove_queue(QUEUE * q){
  int aux = q->queue[q->begin];
  //printf("%c,", aux+97);
  q->begin+=1;

  return aux;
}

void insert_queue(QUEUE * q, int value){
  q->queue[q->end] = value;
  q->end+=1;
}

int sort_queue(QUEUE *q){
  int i, j, aux;
  for(i = (q->end) -1; i >= 1; i--){
    for(j = 0; j < i; j++){
      if(q->queue[j] > q->queue[j+1]){
        aux = q->queue[j];
        q->queue[j] = q->queue[j+1];
        q->queue[j+1] = aux;
      }
    }
  }
}

void print_queue(QUEUE * q){
  int i;

  for(i=0; i<(q->end); i++)
    printf("%c,", q->queue[i]);
}

// Variables necessary to use BFS
int color[27];
int dist[27];
int pred[27];

void initialize_vector(int * vector, int value, int N){
  int i;
  for(i=0; i < N; i++)
    vector[i] = value;
}

void initialize_queue(QUEUE * q, int N){
  q->end = 0;
  q->begin = 0;
  initialize_vector(q->queue, ZERO, N);
}

int BFS(int graph[MAXN][MAXN], int root, int N){
  QUEUE q, vertices;
  int u, i, i2;


  initialize_queue(&q, N);
  initialize_queue(&vertices, N);

  dist[root] = ZERO;
  color[root] = GRAY;
  pred[root] = ZERO;

  insert_queue(&q, root);
  while(!is_queue_empty(&q)){
    u = remove_queue(&q);
    insert_queue(&vertices, u+97);

    for(i=0; i < N; i++){
      // it is adjacent
      if(graph[u][i] > 0){
        if(color[i] == WHITE){
          dist[i] = dist[u] + 1;
          pred[i] = u;
          color[i] = GRAY;
          insert_queue(&q, i);
        }
      }
    }
    color[u] = BLACK;
  }

  sort_queue(&vertices);
  print_queue(&vertices);

}

int main(int argc, char** argv) {

  char x,y;
  int N, M, C, i, j, k, u, v;
  int graph[MAXN][MAXN];

  /*Reads number of cases */
  scanf("%d", &C);

  for (k=0; k < C;k++){
    initialize_vector(color, WHITE, N);
    initialize_vector(dist, INFINITE, N);
    initialize_vector(pred, ZERO, N);

    /* Reads input. */
    scanf("%d %d", &N, &M);
    /* printf("%d %d\n", N, M); */

    /* Initialize graph matrix */
    for (i=0; i < N; i++)
      for (j=0; j < N; j++)
        graph[i][j] = 0;

    /* Reads graph */
    for (i=0; i < M; i++){
      /* edge u v */
      scanf(" %c", &x);
      scanf(" %c", &y);
      u = x - 'a';
      v = y - 'a';
      graph[u][v] = graph[v][u] = 1;
    }

    /* Debug -- Writes graph matrix
       for (i=0; i < N; i++){
       for (j=0; j < N; j++)
       printf("%d ", graph[i][j]);
       printf("\n");
       } */

    printf("Case #%d:\n",k+1);

    int total = 0;
    for (i = 0; i < N; i++){
      if (color[i] == WHITE){
        BFS(graph, i, N);
        printf("\n");
        total++;
      }
    }
    printf("%d connected components\n\n", total);
  }
}
