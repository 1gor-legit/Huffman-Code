#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <conio2.h>
#include "func.h"

int main(){
	
	char frase[] = "ele correu correu sem olhar para tras correu como se a vida dependesse disso correu mesmo quando as forcas faltavam correu apesar do medo correu enquanto a chuva caia correu entre gritos correu entre sombras correu por cada lembranca que o perseguia correu por tudo que havia perdido correu por tudo que ainda sonhava alcancar correu mesmo quando tudo dizia para parar correu com dor correu com esperanca correu com raiva correu com amor correu ate que as pernas cederam ate que o coracao quase parou e mesmo assim ainda correu";
	char *fraseCodificar = "ele correu sem olhar para tras correu como se a vida dependesse disso correu apesar do medo";

	ListaNos *L = NULL;
	ListaR *LP = NULL;

	//conta a frequencia das palavras e monta uma lista
	preencherListaPalavras(&LP, frase);
	//exibirListaR(LP);
	//printf("\n\n");

	//monta a lista de simbolo e frequencia de cada palavra
	montaListaFreqSimb(&L, LP);
	//exibeListaFreqSimb(L);

	//monta a arvore de Huffman e exibe
	montaHuffman(&L);
	int n = -1;
	exibeHuffman(L -> floresta, LP, &n);

	//pega o codigo de huffman de cada palavra e armezena o registro no arq bin, depois printa a arvore e a lista de registros
	codigoHuffman(L -> floresta, &LP);

	//codifica a frase usando o codigo de huffman
	codificarFrase(&LP, fraseCodificar);
	
	//Usada para converter o arquivo binario em texto, verificando se o codigo de cada palavra esta correto
	//ConverteBINemTXT();

	getchar();
	return 0;
}