//-------------------STRUCT'S-------------------
//------------Montar a lista encadeada ordenada (Item A)----------------
struct tree{
	int simb, freq;
	struct tree *esq, *dir;
};
typedef struct tree Tree;

struct listaNos{
    Tree *floresta;
    struct listaNos *prox;
};
typedef struct listaNos ListaNos;
//-------------------------------------------------------------

//------------Montar a lista de registros e gravar no arquivo binario (Item B)----------------
struct listaRegistros{
    int simbolo;
    char palavra[50];
    int freq;
    char cod[50];
    struct listaRegistros *prox;
};
typedef struct listaRegistros ListaR;

struct gravar{
    int simbolo;
    char palavra[50];
    char cod[50];
};
typedef struct gravar Gravar;
//-----------------------------------------------------------------------------------

struct bits{
	unsigned char b7:1;
	unsigned char b6:1;
	unsigned char b5:1;
	unsigned char b4:1;
	unsigned char b3:1;
	unsigned char b2:1;
	unsigned char b1:1;
	unsigned char b0:1;
};

union baite{
	struct bits bi;
	unsigned char num;
};
//----------------------------------------------

//-----------------CriaNo's---------------------

ListaNos *CriaNoListaNos(int simb, int freq){
	ListaNos *No = (ListaNos*)malloc(sizeof(ListaNos));
	No -> floresta = (Tree*)malloc(sizeof(Tree));
	No -> floresta -> simb = simb;
	No -> floresta -> freq = freq;
	No -> floresta -> esq = No -> floresta -> dir = NULL;
	No -> prox = NULL;
	return No;
}

ListaR *CriaNoListaPalavra(char *palavra, int simbolo){
	ListaR *No = (ListaR*)malloc(sizeof(ListaR));
	No -> simbolo = simbolo;
	strcpy(No -> palavra, palavra);
	No -> freq = 1;
	strcpy(No -> cod, " ");
	No -> prox = NULL;
	return No;
}
//----------------------------------------------

void BuscaPalavra(ListaR *LP, char *palavra, ListaR **aux){
	*aux = LP;
	while(*aux != NULL && stricmp((*aux) -> palavra, palavra) != 0)
		*aux = (*aux) -> prox;
}

void ProcessaPalavra(ListaR **LP, char *palavra, int *simbolo){

	ListaR *aux = NULL;

	BuscaPalavra(*LP, palavra, &aux);
	
	if(aux == NULL){

		ListaR *No = CriaNoListaPalavra(palavra, *simbolo);
		(*simbolo)++;

		if(*LP == NULL)
			*LP = No;
		else{
			aux = *LP;
			while(aux -> prox != NULL)
				aux = aux -> prox;

			aux -> prox = No;
		}
		
	}
	else
		aux -> freq++;
}

void preencherListaPalavras(ListaR **LP, char *frase){
	char palavra[20];
	int simbolo = 1;
	int i, j = 0;
	while(frase[j] != '\0'){

		if(frase[j] == ' '){
			palavra[0] = ' ';
            palavra[1] = '\0';
            ProcessaPalavra(LP, palavra, &simbolo);
            j++;
		}
		else{
			for(i = 0; frase[j] != ' ' && frase[j] != '\0'; i++, j++)
				palavra[i] = frase[j];
			palavra[i] = '\0';
			ProcessaPalavra(&(*LP), palavra, &simbolo);
		}
	}
}

void exibirListaR(ListaR *LP) {
    ListaR *atual = LP;
    char palavra[50];

    if(atual != NULL) {
        printf("Lista de Registros: \n");
        printf("%-15s %10s %10s %10s\n", "Palavra", "Simbolo", "Freq", "Codigo");

        while (atual != NULL) {
            sprintf(palavra, "\"%s\"", atual->palavra);
            printf("%-15s %10d %10d %10s\n", palavra, atual->simbolo, atual->freq, atual->cod);
            atual = atual->prox;
        }
    }
}

void montaListaFreqSimb(ListaNos **L, ListaR *LP){
	ListaR *auxLP = LP;
	while(auxLP != NULL){

		ListaNos *No = CriaNoListaNos(auxLP -> simbolo, auxLP -> freq);

		if(*L == NULL || (*L) -> floresta -> freq > No -> floresta -> freq){
			No -> prox = *L;
			*L = No;
		}
		else{
			ListaNos *auxL = *L;
			ListaNos *antL = NULL;
			while(auxL -> prox != NULL && auxL -> floresta -> freq < No -> floresta -> freq){
				antL = auxL;
				auxL = auxL -> prox;
			}

			if(auxL -> floresta -> freq > No -> floresta -> freq){
				antL -> prox = No;
				No -> prox = auxL;
			}
			else if(auxL -> floresta -> freq == No -> floresta -> freq){
				while(auxL != NULL && auxL -> floresta -> freq == No -> floresta -> freq){
					antL = auxL;
					auxL = auxL -> prox;
				}
				antL -> prox = No;
				No -> prox = auxL;
			}
			else
				auxL -> prox = No;
		}

		auxLP = auxLP -> prox;
	}
}

void exibeListaFreqSimb(ListaNos *L){
	ListaNos *atual = L;

	if(atual != NULL) {
		printf("Lista de Frequencia e Simbolo: \n");
		printf("%-15s %10s\n", "Simbolo", "Frequencia");

		while (atual != NULL) {
			printf("%-15d %10d\n", atual->floresta->simb, atual->floresta->freq);
			atual = atual->prox;
		}
	}
}