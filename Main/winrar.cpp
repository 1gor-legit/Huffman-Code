#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <conio2.h>
#include "func.h"

int main(){

	char frase[] = "ele correu correu sem olhar para tras correu como se a vida dependesse disso correu mesmo quando as forcas faltavam correu apesar do medo correu enquanto a chuva caia correu entre gritos correu entre sombras correu por cada lembranca que o perseguia correu por tudo que havia perdido correu por tudo que ainda sonhava alcancar correu mesmo quando tudo dizia para parar correu com dor correu com esperanca correu com raiva correu com amor correu ate que as pernas cederam ate que o coracao quase parou e mesmo assim ainda correu";

	ListaNos *L = NULL;
	ListaR *LP = NULL;

	//conta a frequencia das palavras e monta uma lista
	preencherListaPalavras(&LP, frase);
	exibirListaR(LP);
	printf("\n\n");
	//monta a lista de simbolo e frequencia de cada palavra
	montaListaFreqSimb(&L, LP);
	exibeListaFreqSimb(L);
	//monta a arvore de Huffman e exibe
	montaHuffman(&L);
	int n = -1;
	exibeHuffman(L -> floresta, LP, &n);
	//pega o codigo de huffman de cada palavra e armezena o registro no arq bin, depois printa a arvore e a lista de registros
	codigoHuffman(L -> floresta, &LP);
	getchar();

	//------------COMO GRAVAR BYTE A BYTE-------------------
	int i;
	union baite ub;
	int bin[] = {1,1,1,1,0,0,0,0,1,1,0,0,1,1,0,0,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1};
	FILE *ptrArq = fopen("Arquivo.dat", "ab");
	int rec[32];
	
	//gravando os bits
	for(i = 0; i < 32; ){
		
		ub.bi.b0 = bin[i++];
		ub.bi.b1 = bin[i++];
		ub.bi.b2 = bin[i++];
		ub.bi.b3 = bin[i++];
		ub.bi.b4 = bin[i++];
		ub.bi.b5 = bin[i++];
		ub.bi.b6 = bin[i++];
		ub.bi.b7 = bin[i++];
		
		fwrite(&ub.num, sizeof(unsigned char), 1, ptrArq);
	}
	
	fclose(ptrArq);
	
	//lendo os bits
	ptrArq = fopen("Arquivo.dat", "rb");
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
	
	for(i = 0; i < 32; i++)
		printf("%d", rec[i]);
	
	getchar();
	return 0;
}
