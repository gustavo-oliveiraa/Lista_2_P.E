// Nome: Gustavo Maxwel de Sousa Oliveira	Matrícula: UC21101257

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#define MAX_PRE 50
#define MAX_JOGOS 450
#define TAM_CIDADE 120

typedef struct{
	int id;
	float valor;
	char cidade[TAM_CIDADE];
}Jogo;

void le_valida_presid(char prtPre[], int tam);
void le_valida_id(Jogo jogo[], int index);
void le_valida_valor(Jogo jogo[], int index);
void le_valida_cidade(Jogo jogo[], int index);
void le_valida_ordena_jogos(Jogo jogo[], int index);
void le_valida_apresenta_jogos(Jogo jogo[], int index, char pre[]);
void le_valida_consulta_jogos(Jogo jogo[], int index);

int main(){
	setlocale(LC_ALL, "Portuguese");
	FILE *arq;
	char nomePresid[MAX_PRE], opcao;
	int i=0, x=0, tamanho=0, espaco=0, cont=0;
	
	Jogo jogo[MAX_JOGOS];
	
	arq = fopen("Nome_Presidente.txt", "r");
	
	if(fgets(nomePresid, MAX_PRE, arq) != NULL){
		printf("%s", nomePresid);
	}else{
		if(arq == NULL){
  			printf("Erro na abertura do arquivo!");
  			return 1;
		}else{
			printf("Informe o nome do presidente da CBF:");
			scanf("%[^\n]s", &nomePresid);
			fflush(stdin);
			
			tamanho=strlen(nomePresid);
			
			le_valida_presid(nomePresid,tamanho);
			
			for(i=0; i<tamanho; i++){
				nomePresid[i] = tolower(nomePresid[i]);										
			}
				
			nomePresid[0] = toupper(nomePresid[0]);
			for(i=0; i<tamanho; i++){
				if(nomePresid[i]==' '){
					espaco=i;
					nomePresid[espaco+1] = toupper(nomePresid[espaco+1]);
				}
			}
			
			fprintf(arq, "%s", nomePresid);
			fclose(arq);
				
			}
		}
		
		do{
			getch("");
			
			system("cls");
			
			printf("Para cadastrar um jogo, aperte a tecla (a).\n");
			printf("Para mostrar os jogos já cadastrados, aperte a tecla (b).\n");
			printf("Para consultar jogos cadastrados em uma cidade, aperte a tecla (c).\n");
			printf("Para sair do programa, aperte a tecla (d).\n");
			printf("Oque deseja fazer:");
			scanf("%c", &opcao);
			
			switch(opcao){
				case 'a':
					le_valida_id(&jogo, cont);
					
					le_valida_valor(&jogo, cont);
					
					le_valida_cidade(&jogo, cont);
					
					cont++;
										
				break;
				
				case 'b':
					le_valida_ordena_jogos(&jogo, cont);
					
					le_valida_apresenta_jogos(&jogo, cont, nomePresid);
										
				break;
					
				case 'c':
					le_valida_consulta_jogos(&jogo, cont);
										
				break;
				
				case 'd':
					printf("Obrigado por usar este programa, saindo.");
								
				break;										
			}
			
		}while(opcao!='d' );
			
	return 0;	 
}

void le_valida_presid(char prtPre[], int tam){
	
	while(tam < 4 || tam > MAX_PRE){
		printf("O nome não pode ser vazio e nem maior que 50:");
		scanf("%[^\n]s", &(*prtPre));
		
		tam = strlen(prtPre);
		fflush(stdin);
	}
}

void le_valida_id(Jogo jogo[], int index){
	int unidadId = 0;
	
	do{
		printf("Digite a identificação do jogo (300 - 10.000):");
		scanf("%d", &jogo[index].id);
		
		for(unidadId; unidadId<index; unidadId++){
			if(jogo[index].id == jogo[unidadId].id){
				printf("Esta identificação já foi cadastrada!\n");
				printf("Digite a identificação do jogo (300 - 10.000):");
				scanf("%d", &jogo[index].id);
			}
			
		}
		
		if(jogo[index].id<300 || jogo[index].id>10000){
			printf("Este número não pode ser cadastrado, tente ente (300 - 10.000)\n");
		}
	}while(jogo[index].id<300 || jogo[index].id>10000);
}

void le_valida_valor(Jogo jogo[], int index){
	
	do{
		printf("Digite o valor arrecadado (1.000 - 1.000.000):");
		scanf("%f", &jogo[index].valor);
		if(jogo[index].valor < 1000 || jogo[index].valor > 1000000){
			printf("Este valor não pode ser cadastrado, tente ente (1.000 - 1.000.000).\n");
		}
	}while(jogo[index].valor < 1000 || jogo[index].valor > 1000000);	
}

void le_valida_cidade(Jogo jogo[], int index){
	
	int size, j = 0, espaco;
	
	do{
		fflush(stdin);
		
		printf("Cidade:");
		scanf("%[^\n]s", &jogo[index].cidade);
		size = strlen(jogo[index].cidade);
		
		fflush(stdin);
		
		for(j; j<size;j++){
			jogo[index].cidade[j] = tolower(jogo[index].cidade[j]);
		}
			
		jogo[index].cidade[0] = toupper(jogo[index].cidade[0]);
		for(j=0; j<size; j++){
			if(jogo[index].cidade[j]==' '){
				espaco = j; 
				jogo[index].cidade[espaco+1] = toupper(jogo[index].cidade[espaco+1]);
			}
		}
	}while(size<1 || size>TAM_CIDADE);
}

void le_valida_ordena_jogos(Jogo jogo[], int index){
	char auxCidade[80];
	int f = 0, p = 0;
	int auxId, auxValor;
	
	for(f; f<index; f++){
		for(p=f+1; p < index; p++){
			if(strcmp(jogo[f].cidade,jogo[p].cidade) > 0){
				strcpy(auxCidade, jogo[f].cidade);
				strcpy(jogo[f].cidade, jogo[p].cidade);
				strcpy(jogo[p].cidade, auxCidade);
				
				auxId = jogo[f].id;
				jogo[f].id = jogo[p].id;
				jogo[p].id = auxId;
				
				auxValor = jogo[f].valor;
				jogo[f].valor = jogo[p].valor;
				jogo[p].valor = auxValor;
			}
		}
	}
}

void le_valida_apresenta_jogos(Jogo jogo[], int index, char pre[]){
	int a = 0;
	if(index > 0){
		printf("\t%s\n\n", pre);
		printf("Cidade. - Identificador. - Valor Arrecadado.");
		for(a; a < index; a++){
			printf("\n%s -\t %d - R$%.2f", jogo[a].cidade, jogo[a].id, jogo[a].valor);
		}
	}else printf("Cadastre ao menos um jogo!");
}

void le_valida_consulta_jogos(Jogo jogo[], int index){

	fflush(stdin);
	
	char Cidade[TAM_CIDADE];
	int espaco, tamanho = 0, i = 0, g = 0;
	int else_do_if = 0;
	
	if(index > 0){
		printf("Informe a cidade do jogo que deseja consultar:");
		scanf("%[^\n]s", &Cidade);
		fflush(stdin);
		
		tamanho = strlen(Cidade);
		
		for(i=0; i<tamanho; i++){
			Cidade[i] = tolower(Cidade[i]);
		}
			
		Cidade[0] = toupper(Cidade[0]);
		
		for(i=0; i<tamanho; i++){
			if(Cidade[i]==' '){
				espaco = i; 
				Cidade[espaco+1] = toupper(Cidade[espaco+1]);
			}
		}
		
		for(g; g < index; g++){
			if(strcmp(jogo[g].cidade, Cidade)==0){
				printf("\nCidade:%s - Identificador:%d - Valor Arrecadado:%.2f", jogo[g].cidade, jogo[g].id, jogo[g].valor);
				else_do_if = 24;
			}
		}
		
		if(else_do_if != 24){
			printf("\nNão encontrado\n. Dica: tente sem assento!");
		}
		
	}else printf("\nNão há jogos cadastrados. Cadastre um jogo primeiro!");
		
}

