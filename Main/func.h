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
typedef struct listaRegistros ListR;

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

ListaNos *CriaNoListaNos(int simb){
	ListaNos *No = (ListaNos*)malloc(sizeof(ListaNos));
	No -> floresta -> simb = simb;
	No -> floresta -> freq = 0;
	No -> floresta -> esq = No -> floresta -> dir = No -> prox = NULL;
	return No;
}

ListR *CriaNoListaPalavra(char *palavra, int simbolo){
	ListR *No = (ListR*)malloc(sizeof(ListR));
	No -> simbolo = simbolo;
	strcpy(No -> palavra, palavra);
	No -> freq = 1;
	strcpy(No -> cod, ' ');
	No -> prox = NULL;
	return No;
}
//----------------------------------------------

void BuscaPalavra(ListR *LP, char *palavra, ListR **aux){
	*aux = LP;
	while(*aux != NULL && stricmp((*aux) -> palavra, palavra) != 0)
		*aux = (*aux) -> prox;
}

void ProcessaPalavra(ListR *LP, char *palavra){

	ListR *aux = NULL;
	ListR *andar = LP;
	int simbolo = 1;

	BuscaPalavra(LP, palavra, &aux);
	
	if(aux == NULL){
		ListR *No = CriaNoListaPalavra(palavra, simbolo++);

		while(andar -> prox != NULL)
			andar = andar -> prox;

		andar -> prox = No;
	}
	else
		aux -> freq++;
}

void preencherListaPalavras(ListR *LP, char *frase, int *freq){
	char palavra[20];
	for(int j = 0; j < strlen(frase); j++){
		
		for(int i = j; frase[i] != ' '; i++)
			palavra[i] = frase[j];
		palavra[i] = '\0';

		ProcessaPalavra(LP, palavra);
		
		j = i;
	}
}

void exibirListR(ListR *lista) {
    ListR *atual = lista;
    char palavra[50];

    if (atual != NULL) {
        printf("Lista de Registros: \n");
        printf("%-15s %10s %10s %10s\n", "Palavra", "Simbolo", "Freq", "Codigo");

        while (atual != NULL) {
            sprintf(palavra, "\"%s\"", atual->palavra);
            printf("%-15s %10d %10d %10s\n", palavra, atual->simbolo, atual->freq, atual->cod);
            atual = atual->prox;
        }
    }
}
