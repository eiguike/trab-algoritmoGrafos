// Ângela Rodrigues Ferreira
// Henrique Teruo Eihara
// Hitalo Siqueira

#include <stdio.h>
#include <stdlib.h>

#define MAX 60
#define INFINITO 10001

int matAdj[MAX][MAX];
int parent[MAX];

int kruskal(int R, int C);
int find(int i);
int uni(int i,int j);

int main () {
	int R, C, V, W, P;
	int i, j;


	scanf("%d %d", &R, &C);
	
	for(i = 0; i < R; i++){
		for(j = 0; j < R; j++){
			matAdj[i][j] = INFINITO;
		}
	}

	for(i = 0; i < C; i++){
		scanf("%d %d %d", &V, &W, &P);
		matAdj[V - 1][W - 1] = P;
		matAdj[W - 1][V - 1] = P;
	}

	printf("%d\n", kruskal(R, C));

	return 0;
}

int kruskal(int R, int C){
	int linha, coluna, custo = 0, i, j;
	int min = INFINITO;
	
	while(C--){
		for(i = 0; i < R; i++){
			for(j = 0; j < R; j++){
				if(matAdj[i][j] < min){
					min = matAdj[i][j];
					linha = i;
					coluna = j;
				}
			}
		}

		if(uni(find(linha + 1),find(coluna + 1))){
			custo += min;
		}

		matAdj[linha][coluna] = matAdj[coluna][linha] = INFINITO;
		min = INFINITO;
	} 

	return custo;
}

int find(int i) {
	while(parent[i]){	
		i = parent[i];
	}
	return i;
}

int uni(int i,int j) {
	if(i!=j){
		parent[j]=i;
		return 1;
	}
	return 0;
}