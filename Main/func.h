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

