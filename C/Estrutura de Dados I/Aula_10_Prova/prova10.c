#include <stdio.h>
#include <stdlib.h>
#define BRANCO 0
#define AMARELO 1
#define VERMELHO 2

typedef struct vizinho {
	int id_vizinho;
	struct vizinho *prox;
}TVizinho;

typedef struct grafo{
	int id_vertice;
	TVizinho *prim_vizinho;
	struct grafo *prox;
}TGrafo;

typedef struct lista {
	int info;
	struct lista* prox;
} TLista;

typedef struct fila {
	TLista *inicio;
	TLista *fim;
} TFila;

TFila *inicializa(void){
	TFila *f = (TFila *)malloc(sizeof(TFila));
	f->inicio = NULL;
	f->fim = NULL;
	return f;
}

int fila_vazia(TFila *f){
	if (f->inicio == NULL) {
		return 1;
	}
	else return 0;
}

void insere(TFila *f, int elem){
	TLista *novo = (TLista *)malloc(sizeof(TLista));
	novo->info = elem;
	novo->prox = NULL; //inserção no fim da fila
	if (!fila_vazia(f)){
		f->fim->prox = novo;
	}
	else{
		f->inicio = novo;
	}
	f->fim = novo; //elemento inserido é o novo fim da fila
}

/*
 * Remove elemento da fila e retorna info do elemento excluído
 */
int retira(TFila *f){
	if (fila_vazia(f)){
		exit(1);
	}
	int info = f->inicio->info;

	TLista *aux = f->inicio;
	f->inicio=f->inicio->prox;
	//se elemento removido era o único da fila
	//faz fim apontar para NULL também
	if (f->inicio == NULL) {
		f->fim = NULL;
	}
	free(aux);
	return info;
}

void libera(TFila *f){
	TLista *q, *p = f->inicio;
	while(p != NULL){
		q = p;
		p = p->prox;
		free(q);
	}
	free(f);
}

void imprime_grafo(TGrafo *g){
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

TGrafo *inicializa_grafo(){
	return NULL;
}

void libera_vizinhos(TVizinho *v){
	while(v != NULL){
		TVizinho *temp = v;
		v = v->prox;
		free(temp);
	}
}
void libera_grafo(TGrafo *g){
	while(g != NULL){
		libera_vizinhos(g->prim_vizinho);
		TGrafo *temp = g;
		g = g->prox;
		free(temp);
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
	if(v == NULL)
		insere_um_sentido(g, v1, v2);
		insere_um_sentido(g, v2, v1);
}
int quantidade_vertice(TGrafo *g){
	TGrafo *aux = g;
	int cont = 0;
	while (aux){
		cont += 1;
		aux = aux-> prox;
	}
	return cont;
}
int visitaL(TGrafo *g, TGrafo *vert, int v1, int v2, int *cor){
    cor[vert->id_vertice] = AMARELO;
    TFila *fila = inicializa();

    insere(fila, vert->id_vertice);

    int t = 0;

    while(fila->inicio){
        TGrafo* u = busca_vertice(g, retira(fila));
        printf("%d ", u->id_vertice);

        TVizinho *v = u->prim_vizinho;

        while(v){
            if (v2 == v->id_vizinho){ 
                t = 1;
            }

            if(cor[v->id_vizinho] == BRANCO){
                cor[v->id_vizinho] = AMARELO;
                insere(fila, v->id_vizinho);
            }

            v = v->prox;
        }
    }

    return t;
}


int existe_caminho(TGrafo *g, int v1, int v2){
    int tamanho = quantidade_vertice(g);
    int cor[tamanho];
    TGrafo *vert = g;
    printf("\n\nCaminhamento em largura: \n");
    int i;
    int t = 0;

    for (i = 0; i < tamanho; i++){
        cor[i] = BRANCO;
    }

    for (i = 0; i < tamanho; i++){
        if (cor[i] == BRANCO){
            if (vert->id_vertice == v1){
                t = visitaL(g, vert, v1, v2, cor);
            }
        }
        vert = vert->prox;
    }

    return t;
}
     

int main(void) {
	TGrafo *grafo;
	grafo = inicializa_grafo();
	grafo = insere_vertice(grafo, 9);
	grafo = insere_vertice(grafo, 8);
	grafo = insere_vertice(grafo, 7);
	grafo = insere_vertice(grafo, 6);
	grafo = insere_vertice(grafo, 5);
	grafo = insere_vertice(grafo, 4);
	grafo = insere_vertice(grafo, 3);
	grafo = insere_vertice(grafo, 2);
	grafo = insere_vertice(grafo, 1);
	grafo = insere_vertice(grafo, 0);
	insere_um_sentido(grafo, 0, 2);  
	insere_um_sentido(grafo, 0, 1);
	insere_um_sentido(grafo, 1, 3);
	insere_um_sentido(grafo, 3, 5);
	insere_um_sentido(grafo, 3, 2);	  
	insere_um_sentido(grafo, 2, 4);
	insere_um_sentido(grafo, 4, 9);
	insere_um_sentido(grafo, 4, 5);
	insere_um_sentido(grafo, 6, 0);
	insere_um_sentido(grafo, 6, 7);
	insere_um_sentido(grafo, 7, 4);
	insere_um_sentido(grafo, 7, 8);
	insere_um_sentido(grafo, 8, 9);
	imprime_grafo(grafo);

	//Verifica se existe caminho a partir do vertice 1 para 9 
	if(existe_caminho(grafo, 1, 9)){
		printf("Existe caminho entre 1 e 9\n");
	}else{
		printf("Não existe caminho entre 1 e 9\n");
	}
	
	if(existe_caminho(grafo, 0, 4)){
		printf("Existe caminho entre 0 e 4\n");
	}else{
		printf("Não existe caminho entre 0 e 4\n");
	}
	
	if(existe_caminho(grafo, 6, 9)){
		printf("Existe caminho entre 6 e 9\n");
	}else{
		printf("Não existe caminho entre 6 e 9\n");
	}
	
	if(existe_caminho(grafo, 3, 0)){
		printf("Existe caminho entre 3 e 0\n");
	}else{
		printf("Não existe caminho entre 3 e 0\n");
	}
}
