//-------------------STRUCT'S-------------------
//------------Pilha -----------------------------------
struct pilha{
    struct tree *arv;
    int profundidade;
    struct pilha *prox;
};
typedef struct pilha Pilha;
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
    int simbolo, frequencia;
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

//------------------TAD Pilha---------------------
void init(Pilha **P){
    *P = NULL;
}

int isEmpty(Pilha *P){
    return P == NULL;
}

void push(Pilha **P, Tree *raiz, int prof){
    Pilha *no = (Pilha*)malloc(sizeof(Pilha));
    no -> arv = raiz;
    no -> profundidade = prof;
    no -> prox = NULL;

    if(*P == NULL)
        *P = no;
    else{
        no ->prox = *P;
        *P = no;
    }
}

void pop(Pilha **P, Tree **raiz, int *prof){
    Pilha *aux;
    if(!isEmpty(*P)){
        aux = *P;
        *raiz = aux ->arv;
        *prof = aux ->profundidade;
        *P = (*P) ->prox;
        free(aux);
    }
}

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

Tree *CriaNoHuff(){
	Tree *No = (Tree*)malloc(sizeof(Tree));
	No -> simb = 0;
	No -> freq = 0;
	No -> esq = No -> dir = NULL;
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
        ListaNos *atual = *L;
        ListaNos *anterior = NULL;

        while(atual != NULL && atual -> floresta -> freq < No -> floresta -> freq){
            anterior = atual;
            atual = atual -> prox;
        }

        while(atual != NULL && atual -> floresta -> freq == No -> floresta -> freq){
            anterior = atual;
            atual = atual -> prox;
        }

        if(anterior == NULL){
            No -> prox = *L;
            *L = No;
        }
		else{
            anterior -> prox = No;
            No -> prox = atual;
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
			printf("%-15d %10d\n", atual -> floresta -> simb, atual -> floresta -> freq);
			atual = atual -> prox;
		}
	}
}

void montaHuffman(ListaNos **L){
	while(*L != NULL && (*L) -> prox != NULL){
		
		ListaNos *atual = *L;
		ListaNos *post = atual -> prox;
		*L = post -> prox;

		ListaNos *No = CriaNoListaNos(0, atual -> floresta -> freq + post -> floresta -> freq);

		No -> floresta -> esq = atual -> floresta;
		No -> floresta -> dir = post -> floresta;
		
		free(atual);
		free(post);

		atual = *L;
		ListaNos *ant = NULL;
		while(atual != NULL && atual -> floresta -> freq <= No -> floresta -> freq){
			ant = atual;
			atual = atual -> prox;
		}

		if (ant == NULL) {
			No->prox = *L;
			*L = No;
		} 
		else{
			ant->prox = No;
			No->prox = atual;
		}
	}
}

char *buscaPalavra(ListaR *LP, int simb){

    while(LP != NULL && LP -> simbolo != simb)
		LP = LP -> prox;

    if(LP != NULL && LP -> simbolo == simb)
        return LP -> palavra;

    return "0";
}

void exibeHuffman(Tree *raiz, ListaR *lista, int *n) {
    if(raiz != NULL){

        if((*n) == -1)
            printf("Arvore de Huffman: \n");
        (*n)++;

        exibeHuffman(raiz -> dir, lista, n);
        for (int i = 0; i < 5 * (*n); i++)
			printf(" ");

        if(raiz -> simb == 0)
            printf("(0,%d)\n", raiz -> freq);
		else
            printf("(\"%s\",%d)\n", buscaPalavra(lista, raiz -> simb), raiz -> freq);
        
        exibeHuffman(raiz -> esq, lista, n);
        (*n)--;
    }
}

void gravarArquivo(ListaR *LP){
	FILE *ptr = fopen("registro.dat", "wb");

	if(ptr != NULL){
		ListaR *auxLP = LP;
		Gravar registro;
		printf("\n\tLista de Registros: \n\n");
		while(auxLP != NULL){

			registro.simbolo = auxLP -> simbolo;
			registro.frequencia = auxLP -> freq;
			strcpy(registro.palavra, auxLP -> palavra);
			strcpy(registro.cod, auxLP -> cod);

			printf("Simbolo:%d Frequencia:%d Palavra:%s, Codigo:%s\n", registro.simbolo, registro.frequencia, registro.palavra, registro.cod);
			fwrite(&registro, 1, sizeof(Gravar), ptr);
			auxLP = auxLP -> prox;
		}
	}

	fclose(ptr);
}

void codigoHuffman(Tree *raiz, ListaR **LP){
    char codigo[256];
    int pos = 0;
    ListaR *inic = NULL;
    Pilha *P;
    init(&P);

    push(&P, raiz, 0);
    while(!isEmpty(P)){

        pop(&P, &raiz, &pos);
        while(raiz != NULL){

            if(raiz -> dir == NULL && raiz -> esq == NULL){
                inic = *LP;
                codigo[pos] = '\0';

                while(inic != NULL && inic -> simbolo != raiz -> simb)
                    inic = inic -> prox;

                if(inic != NULL)
                    strcpy(inic -> cod, codigo);
            } 

            if(raiz -> dir != NULL)
                push(&P, raiz-> dir, pos + 1);
            
            codigo[pos++] = '0';
            raiz = raiz -> esq;
        }   
        if(!isEmpty(P)){
            pop(&P, &raiz, &pos);
        	codigo[pos - 1] = '1';
            push(&P, raiz, pos);
        } 
    }

    gravarArquivo(*LP);
}

void codificarFrase(ListaR **LP, char *frase){
	int i, j = 0;
	union baite ub;
	ListaR palavra;
	char cod[256] = {0};
	char aux[50] = {0};

	// Processar cada palavra da frase
	while(frase[j] != '\0'){
        
		int k = 0;
        if(frase[j] == ' '){
            strcpy(aux, " ");
            j++;
        }
		else{
            while (frase[j] != ' ' && frase[j] != '\0')
                aux[k++] = frase[j++];
            aux[k] = '\0';
        }

        // Procurar a palavra ou espaço na lista de registros
        ListaR *atual = *LP;
        while(atual != NULL && strcmp(atual -> palavra, aux) != 0)
            atual = atual -> prox;
        
        if(atual != NULL)
            strcat(cod, atual -> cod);
    }
	
	i = 1;
    while(cod[i] != '\0')
        i++;
	
    while(i % 8 != 0)
        cod[i++] = '0';
    cod[i] = '\0';

	int tamanho = strlen(cod);
	FILE *ptrArq = fopen("codificado.dat", "wb");
	int rec[tamanho];

	//gravando os bits
	for(i = 0; i < tamanho; ){
		
		ub.bi.b0 = cod[i++];
		ub.bi.b1 = cod[i++];
		ub.bi.b2 = cod[i++];
		ub.bi.b3 = cod[i++];
		ub.bi.b4 = cod[i++];
		ub.bi.b5 = cod[i++];
		ub.bi.b6 = cod[i++];
		ub.bi.b7 = cod[i++];
		
		fwrite(&ub.num, sizeof(unsigned char), 1, ptrArq);
	}
	fclose(ptrArq);

	//-------------------> lendo os bits <-------------------------
	/*
	ptrArq = fopen("codificado.dat", "rb");
	fread(&ub.num, sizeof(unsigned char), 1, ptrArq);
	i = 0;
	while(!feof(ptrArq)){
		
		rec[i++] = ub.bi.b0;
		rec[i++] = ub.bi.b1;
		rec[i++] = ub.bi.b2;
		rec[i++] = ub.bi.b3;
		rec[i++] = ub.bi.b4;
		rec[i++] = ub.bi.b5;
		rec[i++] = ub.bi.b6;
		rec[i++] = ub.bi.b7;
		
		fread(&ub.num, sizeof(unsigned char), 1, ptrArq);
	}
	fclose(ptrArq);

	for(i = 0; i < tamanho; i++)
		printf("%d", rec[i]);*/
}

/*void ConverteBINemTXT(){
	FILE *ptrBin = fopen("codificado.dat", "rb");
	FILE *ptrTxt = fopen("codificadoTXT.txt", "w");
	union baite ub;
	int i = 0;

	if(ptrBin != NULL && ptrTxt != NULL){
		while(fread(&ub.num, sizeof(unsigned char), 1, ptrBin) == 1){
			fprintf(ptrTxt, "%d%d%d%d%d%d%d%d", ub.bi.b0, ub.bi.b1, ub.bi.b2, ub.bi.b3, ub.bi.b4, ub.bi.b5, ub.bi.b6, ub.bi.b7);
			i++;
		}
		fclose(ptrBin);
		fclose(ptrTxt);
		printf("Arquivo convertido com sucesso!\n");
	}
	else
		printf("Erro ao abrir os arquivos.\n");
}*/

//-------------------------------------> PROGRAMA 2 <------------------------------------------------

void decodificarFrase(Tree **raiz){
	FILE *ptrReg = fopen("registro.dat", "rb");
    
    union baite ub;
	int i;
	Gravar registro;

	if(ptrReg != NULL){
		
		*raiz = CriaNoHuff();
		(*raiz) -> simb = 0;
		Tree *auxT;
		
		while(fread(&registro, sizeof(Gravar), 1, ptrReg)){
			auxT = *raiz;

			for(i = 0; registro.cod[i] != '\0'; i++){

				if(registro.cod[i] == '0'){
					if(auxT -> esq == NULL)
						auxT -> esq = CriaNoHuff();
					auxT = auxT -> esq;
				}
				else if(registro.cod[i] == '1'){
					if(auxT -> dir == NULL)
						auxT -> dir = CriaNoHuff();
					auxT = auxT -> dir;
				}
			}
			if(registro.cod[i + 1] == '\0')
            	auxT -> simb = registro.simbolo;
		}

		FILE *ptrFrase = fopen("codificado.dat", "rb");

		fseek(ptrFrase, 0, 2);
		int tamanho = ftell(ptrFrase) * 8;
		int rec[tamanho + 1];

		fseek(ptrFrase, 0, 0);
		i = 0;
		while(fread(&ub.num, sizeof(unsigned char), 1, ptrFrase)){
			
			rec[i++] = ub.bi.b0;
			rec[i++] = ub.bi.b1;
			rec[i++] = ub.bi.b2;
			rec[i++] = ub.bi.b3;
			rec[i++] = ub.bi.b4;
			rec[i++] = ub.bi.b5;
			rec[i++] = ub.bi.b6;
			rec[i++] = ub.bi.b7;
		}
		rec[i] = '\0';
		
		auxT = *raiz;
		printf("\nFrase Decodificada:\n");
		for(i = 0; rec[i] != '\0'; i++){

			if(rec[i] == 0){
				auxT = auxT -> esq;
				if(auxT -> simb != 0){
					while(fread(&registro, sizeof(Gravar), 1, ptrReg)){
						if(registro.simbolo == auxT -> simb){
							printf("%s ", registro.palavra);
							auxT = *raiz;
						}
					}
					fseek(ptrReg, 0, 0);
				}
			}
			else{
				auxT = auxT -> dir;
				if(auxT -> simb != 0){
					while(fread(&registro, sizeof(Gravar), 1, ptrReg)){
						if(registro.simbolo == auxT -> simb){
							printf("%s ", registro.palavra);
							auxT = *raiz;
						}
					}
					fseek(ptrReg, 0, 0);
				}
			}
		}

		fclose(ptrFrase);
		fclose(ptrReg);
	}
}
