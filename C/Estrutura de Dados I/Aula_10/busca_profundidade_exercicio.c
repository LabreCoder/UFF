#include <stdlib.h>
#include <stdio.h>

#define BRANCO 0
#define AMARELO 1
#define VERMELHO 2

/*
 * Esse código assume que o grafo é íntegro (não existem arestas para nós que não existem
 */

typedef struct vizinho {
	int id_vizinho;
	struct vizinho *prox;
}TVizinho;

typedef struct grafo{
	int id_vertice;
	TVizinho *prim_vizinho;
	struct grafo *prox;
}TGrafo;

TGrafo *inicializa(){
	return NULL;
}

void imprime(TGrafo *g){
	while(g != NULL){
		printf("Vértice %d\n", g->id_vertice);
		printf("Vizinhos: ");
		TVizinho *v = g->prim_vizinho;
		while(v != NULL){
			printf("%d ", v->id_vizinho);
			v = v->prox;
		}
		printf("\n\n");
		g = g->prox;
	}
}

void libera_vizinho(TVizinho *v){
	if(v != NULL) {
		libera_vizinho(v->prox);
		free(v);
	}
}

void libera(TGrafo *g){
	if(g != NULL){
		libera_vizinho(g->prim_vizinho);
		libera(g ->prox);
		free(g);
	}
}

TGrafo* busca_vertice(TGrafo* g, int x){
	while((g != NULL) && (g->id_vertice != x)) {
		g = g->prox;
	}
	return g;
}

TVizinho* busca_aresta(TGrafo *g, int v1, int v2){
	TGrafo *pv1 = busca_vertice(g,v1);
	TGrafo *pv2 = busca_vertice(g,v2);
	TVizinho *resp = NULL;
	//checa se ambos os vértices existem
	if((pv1 != NULL) && (pv2 != NULL)) {
		//percorre a lista de vizinhos de v1 procurando por v2
		resp = pv1->prim_vizinho;
		while ((resp != NULL) && (resp->id_vizinho != v2)) {
			resp = resp->prox;
		}
	}
	return resp;
}

TGrafo *insere_vertice(TGrafo *g, int x){
	TGrafo *p = busca_vertice(g, x);
	if(p == NULL){
		p = (TGrafo*) malloc(sizeof(TGrafo));
		p->id_vertice = x;
		p->prox = g;
		p->prim_vizinho = NULL;
		g = p;
	}
	return g;
}

void insere_um_sentido(TGrafo *g, int v1, int v2){
	TGrafo *p = busca_vertice(g, v1);
	TVizinho *nova = (TVizinho *) malloc(sizeof(TVizinho));
	nova->id_vizinho = v2;
	nova->prox = p->prim_vizinho;
	p->prim_vizinho = nova;
}

void insere_aresta(TGrafo *g, int v1, int v2){
	TVizinho *v = busca_aresta(g, v1, v2);
	if(v == NULL) {
		insere_um_sentido(g, v1, v2);
		insere_um_sentido(g, v2, v1);
	}
}

void retira_um_sentido(TGrafo *g, int v1, int v2){
	TGrafo *p = busca_vertice(g, v1);
	if(p != NULL) {
		TVizinho *ant = NULL;
		TVizinho *atual = p->prim_vizinho;
		while ((atual) && (atual->id_vizinho != v2)) {
			ant = atual;
			atual = atual->prox;
		}
		if (ant == NULL) //v2 era o primeiro nó da lista de vizinhos
			p->prim_vizinho = atual->prox;
		else
			ant->prox = atual->prox;
		free(atual);
	}
}

void retira_aresta(TGrafo *g ,int v1, int v2){
	TVizinho* v = busca_aresta(g,v1,v2);
	if(v != NULL) {
		retira_um_sentido(g, v1, v2);
		retira_um_sentido(g, v2, v1);
	}
}

TGrafo *retira_vertice(TGrafo *g, int v){
	TGrafo *p = g;
	TGrafo *ant = NULL;
	while((p != NULL) && (p->id_vertice != v)){
		ant = p;
		p = p->prox;
	}
	if(p != NULL) {
		while (p->prim_vizinho != NULL)
			retira_aresta(g, v, p->prim_vizinho->id_vizinho);
		if (ant == NULL)
			g = g->prox;
		else
			ant->prox = p->prox;
		free(p);
	}
	return g;
}

void visitaP(TGrafo *g, TGrafo* vert, int i, int *cor){

	cor[i] = AMARELO;
	printf("%d ", vert->id_vertice);
	TVizinho* v = vert->prim_vizinho;

	while(v != NULL){
		if(cor[v->id_vizinho] == BRANCO){
			visitaP(g, busca_vertice(g, v->id_vizinho), v->id_vizinho, cor);
		}
		v = v-> prox;
	}

	cor[i] = VERMELHO;
}


void profundidade(TGrafo *g, int nvertices){

	int cor[nvertices];
	TGrafo* vert = g;
	
	int i;
	for(i = 0; i < nvertices; i++){
		cor[i] = BRANCO;
	}
	for(i = 0; i < nvertices; i++){
		if(cor[i] == BRANCO){
			visitaP(g, vert, i, cor);
		}
		vert = vert->prox;
	}

}

int main(){
	TGrafo *g = inicializa();
	g = insere_vertice(g, 5);
	g = insere_vertice(g, 4);
	g = insere_vertice(g, 3);
	g = insere_vertice(g, 2);
	g = insere_vertice(g, 1);
	g = insere_vertice(g, 0);
	insere_um_sentido(g, 0, 2);
	insere_um_sentido(g, 0, 1);
	insere_um_sentido(g, 1, 3);
	insere_um_sentido(g, 2, 4);
	insere_um_sentido(g, 3, 5);
	insere_um_sentido(g, 4, 5);


	printf("Grafo: \n");
	imprime(g);

	printf("Profundidade: \n");
	profundidade(g, 6);
	printf("\n");

	libera(g);
}
