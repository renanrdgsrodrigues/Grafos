#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

typedef struct {
	int num;
}NODE;

void printGraph (NODE**);

NODE** createGraph ();

void insertEdge (NODE**, int, int);

void removeEdge (NODE**, int, int);

int hasEdge (NODE**, int, int);

void listEdges (NODE**, int*, int);

void printList (int*, int);


int main (int argc, char** argv) {
	NODE** no = NULL;
	int op;
	int v1, v2;
	int lista[SIZE];

	no = createGraph ();		
	do {
		printf ("Escolha uma opcao : \n");
		printf ("1 - Inserir aresta.\n2 - Remover aresta.\n3 - Existe aresta entre os vertices.\n4 - Lista de arestas do vertice.\n0 - Sair.\n");
		scanf ("%d", &op);
		switch (op) {
			case 1 : printf("Vertices a serem ligados:\n"); 
				scanf("%d %d", &v1, &v2); 
				insertEdge (no, v1 - 1, v2 - 1);	//sempre passar com "- 1", pois no computador comeca no 0 e nao no 1
				printGraph (no);
				break;
	
			case 2 : printf ("Retirar aresta entre os vertices:\n");
				scanf("%d %d", &v1, &v2);
				removeEdge (no, v1 - 1, v2 - 1);
				printGraph (no);
				break;
			
			case 3 : printf ("Existe aresta entre os vertices:\n");
				scanf("%d %d", &v1, &v2);
				if (hasEdge (no, v1 - 1, v2 - 1))
					printf ("Existe aresta entre os vertices %d e %d\n", v1, v2);
				else printf ("Nao existe aresta entre os vertices %d e %d\n", v1, v2);
			
				break;

			case 4 : printf ("Lista de arestas do vertice:\n");
				scanf("%d", &v1);
				listEdges (no, lista, v1 - 1);
				printList (lista, v1 - 1);
		
				break;

			case 0 : break;

			default : printf ("Opcao nao aceita.\n");
				break;
		}
	}while (op != 0);

	return 0;
}

void printGraph (NODE** no) {
	int i, j;

	//dando "boa" aparencia para a matriz
	printf ("\t");
	for (i = 0; i < SIZE; i++) printf (" %d ", i + 1);
	printf ("\n\t");
	for (i = 0; i < SIZE; i++) printf (" | ");
	printf ("\n\t");
	for (i = 0; i < SIZE; i++) printf (" v ");	
	printf ("\n");

	//imprime a matriz
	for (i = 0; i < SIZE; i++) {
		printf ("%d ->\t|", i + 1);
		for (j = 0; j < SIZE; j++) {
			printf ("%d |", no[i][j].num);
		}
		printf("\n");
	}
	printf("\n\n\n");
}

NODE** createGraph () {
	NODE** no = NULL;
	int i, j;
	
	no = (NODE**)malloc(sizeof(NODE*) * SIZE);
	if (no == NULL) {
		printf ("Fail to allocate node.\n");
		exit (1);
	}

	for (i = 0; i < SIZE; i++) {
		no[i] = (NODE*)malloc(sizeof(NODE) * SIZE);
		if (no[i] == NULL) {
			printf ("Fail to allocate node (%d).\n", i);
			exit (1);
		}
		//inicializa a matriz sem arestas (vazia)
		for (j = 0; j < SIZE; j++) {
			no[i][j].num = 0;
		}
	}

	return no;
}

//insere aresta entre os vertives v1 e v2 (consequentemente entre o v2 e v1)
void insertEdge (NODE** no, int v1, int v2) {
	no[v1][v2].num = 1;
	no[v2][v1].num = 1;
}

//remove a areseta entre os vertices v1 e v2 (consequentemente entre o v2 e v1)
void removeEdge (NODE** no, int v1, int v2){
	no[v1][v2].num = 0;
	no[v2][v1].num = 0;
}

//verifica se tem aresta entre os vertices v1 e v2
int hasEdge (NODE** no, int v1, int v2) {
	if (no[v1][v2].num == 1) return 1;
	return 0;	
}

//percorre a linha do vertice v1 buscando os outros vertices que estao ligado a ele
void listEdges (NODE** no, int* lista, int v1) {
	int i, j = 0;
	
	for( i = 0; i < SIZE; i++) {
		lista[i] = 0;		//inicializa a posicao da lista com 0 (tirar o lixo)
		if (no[v1][i].num == 1) {
			lista[j] = i + 1; //soma 1, pois o "i" comeca em 0
			j++;
		}
	}
}

//imprime a lista de ligacoes (arestas) de um vertice
void printList (int* lista, int v1) {
	int i;
	
	printf ("O vertice %d tem arestas com os vertices : ", v1);
	for (i = 0; i < SIZE; i++) {
		if (lista[i] != 0)		//para impedir de imprimir todas as posicoes vazias do vetor de vertices adjacentes
			printf ("%d,", lista[i]);
	}
	printf("\n\n");
}

