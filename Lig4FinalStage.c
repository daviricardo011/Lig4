//------------------------------------------------------------+//
//+                   LIG 4                                   +//
//+         AUTORES: DAVI RICARDO INOCENCIO DOS SANTOS        +//
//+                  JUSTINO BISPO NETO                       +//
//+                  VINICIUS DE MENEZES ALVES                +//
//+                                                           +//
//+                                                           +//
//------------------------------------------------------------+//
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

char tabuleiro[6][7];
int coluna_jogada,linha, explosiva=0, portal=0, explosivaP2=0,portalP2=0;
int cont[8]; 
int rodadas = 1;
char nomeJogador[30], sobrenomeJogador [30];
char nomeJogadorDois[30], sobrenomeJogadorDois [30];

//CHAMADA DAS FUNCOES PARA NAO DAR ERRADO
int main();
int analizar_diagonalp();
int analizar_diagonals();
int analizar_horizontal();
int analizar_vertical();
int analizar_tudo();
int analizar_tudo_PC();
int atualizarTabuleiro(char ficha_jogador);
int hall_dos_campeoes();
void menuDoHall();
int CriaArquivoHall();
void inicializaTabuleiro();
void jogadaComp1(); 
void jogadaComp2(); 
void jogadaP1();
void jogadaP2();
void jogo_P1vsP2();
void jogo_P1vsPC();
void jogo_PCvsPC();
void mostraTabuleiro();
void sair();
//FIM DA CHAMADA


//STRUCT PARA SALVAR O NOME E AS RODADAS//
typedef struct {
  char vencedor[20];
  int rodada;
} ParaHall;
ParaHall nomePlayer[2];


	

//FUNCAO POS FINAL DE JOGO, QUE LEVA AO MENU INICIAL//
int recomecar(){
	printf("\n");
	sleep(7);
	system("cls||clear");//ATENCAO AQUI! pois não funciona em algumas maquinas
return main();
}//FIM DA FUNCAO RECOMECAR


// ANALISE VERTICAL PARA ENCONTRAR VENCEDOR//
int analizar_vertical(){
	int p1Venceu = 0, p2Venceu = 0;
	int p1Cont = 0, p2Cont = 0;
	char ficha_atual;
	int linha, coluna;
	for (coluna = 0; coluna < 7; coluna ++){
		ficha_atual = tabuleiro[5][coluna];
		if(ficha_atual == 'X'){
			p1Cont = 1;
		} else if( ficha_atual == 'O'){
			p2Cont = 1;
		}
		for (linha = 4; linha >= 0 && tabuleiro[linha][coluna] != ' '; linha --){
			if(tabuleiro[linha][coluna] == 'X'){
				if(ficha_atual == 'X'){
					p1Cont++;
				} else {
					ficha_atual = 'X';
					p2Cont = 0;
					p1Cont++;
				}
			} else {
				if(ficha_atual == 'O'){
					p2Cont++;
				} else {
					ficha_atual = 'O';
					p1Cont = 0;
					p2Cont++;
				}
			}
			if(p1Cont >= 4){
				p1Venceu = 1;
			} else if (p2Cont >= 4){
				p2Venceu = 1;
			}
		}
		p1Cont = 0;
		p2Cont = 0;
	}
	if(p1Venceu == 1 && p2Venceu == 1){
		printf("Empate\n"); //So dara empate, se ocorrer de uma peca explosiva juntar as pecas
		return 1;
	} else if (p1Venceu == 1){
		printf("%s venceu na vertical\n",nomePlayer[0].vencedor);
		return 1;
	} else if (p2Venceu == 1){
		printf("%s venceu na vertical\n",nomePlayer[1].vencedor);
		return 1;
	} else {
		return 0;
	}
}//FIM DA ANALISE VERTICAL


// ANALISE HORIZONTAL PARA ENCONTRAR VENCEDOR//
int analizar_horizontal(){
	int p1Venceu = 0, p2Venceu = 0;
	int p1Cont = 0, p2Cont = 0;
	char ficha_atual;
	int linha, coluna;
	for (linha = 5; linha >= 0; linha --){
		ficha_atual = tabuleiro[linha][0];
		if(ficha_atual == 'X'){
			p1Cont = 1;
		} else if( ficha_atual == 'O'){
			p2Cont = 1;
		}
		for (coluna = 1; coluna <= 6; coluna ++){
			if(tabuleiro[linha][coluna] == 'X'){
				if(ficha_atual == 'X'){
					p1Cont++;
				} else {
					ficha_atual = 'X';
					p2Cont = 0;
					p1Cont++;
				}
			} else if (tabuleiro[linha][coluna] == 'O'){
				if(ficha_atual == 'O'){
				p2Cont++;
				} else {
					ficha_atual = 'O';
					p1Cont = 0;
					p2Cont++;
				}
			} else {
				p1Cont = 0;
				p2Cont = 0;
				ficha_atual = tabuleiro[linha][coluna+1];
			}
			if(p1Cont >= 4){
				p1Venceu = 1;
			} else if (p2Cont >= 4){
				p2Venceu = 1;
			}
		}
		p1Cont = 0;
		p2Cont = 0;
	}
	if(p1Venceu == 1 && p2Venceu == 1){
		printf("Empate\n"); //So dara empate, se ocorrer de uma peca explosiva juntar as pecas
		return 1;
	} else if (p1Venceu == 1){
		printf("%s venceu na horizontal\n",nomePlayer[0].vencedor);
		return 1;
	} else if (p2Venceu == 1){
		printf("%s venceu na horizontal\n", nomePlayer[1].vencedor);
		return 1;
	} else {
		return 0;
	}
} //FIM DA ANALISE HORIZONTAL



//ANALISE DAS DIAGONAIS PRIMARIAS PARA ENCONTRAR VENCEDOR
int analizar_diagonalp(){
	int p1Venceu = 0, p2Venceu = 0;
	int p1Cont = 0, p2Cont = 0;
	char ficha_atual;
	int linha, coluna;
	int coluna_geral, linha_geral;
	coluna_geral = 0;
	linha_geral =1;
	while (linha_geral < 3){
		if(coluna_geral <= 3){
			linha = 0;
			coluna = coluna_geral;
		} else {
			coluna = 0;
			linha = linha_geral;
		}
		ficha_atual = tabuleiro[linha][coluna];
		if(ficha_atual == 'X'){
			p1Cont = 1;
		} else if( ficha_atual == 'O'){
			p2Cont = 1;
		}
			linha++;
			coluna++;
		while ( linha < 6 && coluna < 7){
			if(tabuleiro[linha][coluna] == 'X'){
				if(ficha_atual == 'X'){
					p1Cont++;
				} else {
					ficha_atual = 'X';
					p2Cont = 0;
					p1Cont++;
				}
			} else if (tabuleiro[linha][coluna] == 'O'){
				if(ficha_atual == 'O'){
					p2Cont++;
				} else {
					ficha_atual = 'O';
					p1Cont = 0;
					p2Cont++;
				}
			} else {
				p1Cont = 0;
				p2Cont = 0;
				ficha_atual = tabuleiro[linha+1][coluna+1];
			}
			if(p1Cont >= 4){
				p1Venceu = 1;
			} else if (p2Cont >= 4){
				p2Venceu = 1;
			}
			linha++;
			coluna++;
		}
		p1Cont = 0;
		p2Cont = 0;
		if(coluna_geral <= 3){
			coluna_geral++;
		} else {
			linha_geral++;
		}
	}
	if(p1Venceu == 1 && p2Venceu == 1){
		printf("Empate\n"); //So dara empate, se ocorrer de uma peca explosiva juntar as pecas
		return 1;
	} else if (p1Venceu == 1){
		printf("%s venceu na diagonal primaria\n",nomePlayer[0].vencedor);
		return 1;
	} else if (p2Venceu == 1){
		printf("%s venceu na diagonal primaria\n",nomePlayer[1].vencedor);
		return 1;
	} else {
		return 0;
	}
} //FIM DA ANALISE DIAGONAL PRINCIPAL


//ANALISE DA DIAGONAL SECUNDARIA PARA ENCONTRAR VENCEDOR
int analizar_diagonals(){
	int p1Venceu = 0, p2Venceu = 0;	
	int p1Cont = 0, p2Cont = 0;
	char ficha_atual;
	int linha, coluna;
	int coluna_geral, linha_geral;
	coluna_geral = 6;
	linha_geral =1;
	while (linha_geral < 3){
		if(coluna_geral >= 3){
			linha = 0;
			coluna = coluna_geral;
		} else {
			coluna = 6;
			linha = linha_geral;
		}
		ficha_atual = tabuleiro[linha][coluna];
		if(ficha_atual == 'X'){
			p1Cont = 1;
		} else if( ficha_atual == 'O'){
			p2Cont = 1;
		}
		linha++;
		coluna--;
		while ( linha < 6 && coluna < 7){
			if(tabuleiro[linha][coluna] == 'X'){
				if(ficha_atual == 'X'){
					p1Cont++;
				} else {
					ficha_atual = 'X';
					p2Cont = 0;
					p1Cont++;
				}
			} else if (tabuleiro[linha][coluna] == 'O'){
				if(ficha_atual == 'O'){
					p2Cont++;
				} else {
					ficha_atual = 'O';
					p1Cont = 0;
					p2Cont++;
				}
			} else {
				p1Cont = 0;
				p2Cont = 0;
				ficha_atual = tabuleiro[linha+1][coluna-1];
			}
			if(p1Cont >= 4){
				p1Venceu = 1;
			} else if (p2Cont >= 4){
				p2Venceu = 1;
			}
			linha++;
			coluna--;
		}
		p1Cont = 0;
		p2Cont = 0;
		if(coluna_geral >= 3){
			coluna_geral--;
		} else {
			linha_geral++;
		}
	}
	if(p1Venceu == 1 && p2Venceu == 1){
		printf("Empate\n"); //So dara empate, se ocorrer de uma peca explosiva juntar as pecas
		return 1;
	} else if (p1Venceu == 1){
		printf("%s venceu na diagonal secundaria\n",nomePlayer[0].vencedor);
		return 1;
	} else if (p2Venceu == 1){
		printf("%s venceu na diagonal secundaria\n",nomePlayer[1].vencedor);
		return 1;
	} else {
		return 0;
	}
}//FIM DA ANALISE DIAGONAL SECUNDARIA



// ANALISE GERAL DOS JOGADORES: ANALISA TODO O TABULEIRO, IDENFICANDO SE ALGUM JOGADOR VENCEU NAS ANALISES ANTERIORES
int analizar_tudo(){
	int parar = 0;
	parar += analizar_vertical();
	parar += analizar_horizontal();
	parar += analizar_diagonalp();
	parar += analizar_diagonals();
	if (parar >=1){
		printf("\nFim de Jogo!");
		CriaArquivoHall(); // Momento em que o vencedor entrará no Hall de Campeões
		printf("\nVoltando ao menu inicial... Por favor, aguarde.");
		recomecar();
	}
return parar;
} //FIM DA ANALISE GERAL DOS JOGADORES



// ANALISE GERAL DOS PCS: ANALISA TODO O TABULEIRO, IDENFICANDO SE ALGUM JOGADOR VENCEU NAS ANALISES ANTERIORES
int analizar_tudo_PC(){ //OS COMPUTADORES TEM UM ANALIZAR PROPRIO, POIS ELES NAO ENTRAM NO HALL DE CAMPEOES
	int parar = 0;
	parar += analizar_vertical();
	parar += analizar_horizontal();
	parar += analizar_diagonalp();
	parar += analizar_diagonals();
	if (parar >=1){
		printf("\nFim de Jogo!");
		printf("\nVoltando ao menu inicial... Por favor, aguarde.");
		recomecar();
	}
return parar;
} //FIM DA ANALISE GERAL DOS COMPUTADORES




//INICIALIZANDO TABULEIRO, GARANTE QUE AO COMECAR O JOGO O TABULEIRO ESTARA VAZIO//
void inicializaTabuleiro(){
    int linha, coluna;
        for(linha=0 ; linha < 6 ; linha++ ){
            for(coluna=0 ; coluna < 7 ; coluna++ ){
                tabuleiro[linha][coluna]= ' ';
			}
		}
}//FIM DA INICIALIZACAO DO TABULEIRO//



//MOSTRAR TABULEIRO, IMPRECAO DO TABULEIRO NA TELA//
void mostraTabuleiro(){
    int linha, coluna ;
	printf("\n");
	printf("   1    2    3    4    5    6    7                    Rodada: %d\n", rodadas);
	for(linha=0 ; linha < 6 ; linha++ ){
		printf("%d",linha+1);
		for(coluna=0 ; coluna < 7 ; coluna++ ){                 
			printf("[ %c ]", tabuleiro[linha][coluna]);
		}//fim do for da coluna
		printf("\n");//proxima linha do tabuleiro
	}//fim do for da linha
}//FIM DO MOSTRAR TABULEURO//



//ATUALIZAR TABULEIRO, MOSTRA TABULEIRO COM SIMBOLO E POSICAO DA FICHA DE CADA JOGADOR//
int atualizarTabuleiro(char ficha_jogador){
	int linha=5;
	
	while (tabuleiro[linha][coluna_jogada] != ' ' && linha >=0){
		linha --;
	} //Fim do while
	if (linha <0){
		return 0;
	} else {
		tabuleiro[linha][coluna_jogada] = ficha_jogador;
		return 1;  
	}
}//FIM DO ATUALIZAR TABULEIRO//


//Jogada do Player 1 (X): onde o jogador escolhe o tipo da ficha e coluna jogada
void jogadaP1(){
	int ficha=0;
	if (rodadas >=5){
		if (rodadas%5==0){
			explosiva+=1;
			portal +=1;
		}
		printf("\nVoce tem %d fichas explosivas e %d fichas portais \n\n", explosiva, portal);
			if ((explosiva != 0)||(portal!=0)){
				printf("%s , escolha o tipo de peca:\n ", nomePlayer[0].vencedor);
				printf("1. Normal \n 2. Explosiva \n 3. Portal\n");
				while ((ficha<1 || ficha >3)){
					scanf ("%d", &ficha);
					switch (ficha){
						case 1: //nao precisa mudar. Ja esta correto.;
							break;
						case 2: //explosiva
							if (explosiva==0){
								printf ("Voce nao possui pecas explosivas.\n PERDEU A CHANCE DE UTILIZAR PECA ESPECIAL!!\n"); 
							}else{
								explosiva-=1;
							}
							break;
						case 3://portal
							if (portal==0){
								printf ("Voce nao possui pecas portal.\n PERDEU A CHANCE DE UTILIZAR PECA ESPECIAL!!\n"); 
							}else{
								portal-=1;
							}
							break;
						default:
							printf ("Digite uma opcao valida.\n1. Normal \n2. Explosiva \n3. Portal\n");
					}
				}
			}
			
	}
	printf("%s, escolha uma coluna: ", nomePlayer[0].vencedor); 
	scanf("%d",&coluna_jogada); //Leitura do local da jogada
	while ( coluna_jogada <1 || coluna_jogada >7 || cont [coluna_jogada]==6){ //AQUI IDENTIFICA SE A COLUNA ESTA CHEIA OU SE A JOGADA FOI EM UM LUGAR INVALIDO
		printf ("ERRO: COLUNA INVALIDA\n");
		printf("%s , escolha uma coluna: ", nomePlayer[0].vencedor);
		scanf("%d",&coluna_jogada); //Leitura do local da jogada VALIDA
	}
	switch(coluna_jogada){ //AQUI SOMA UMA PECA A COLUNA
		case 1:
			cont[1]++;			
			break;
		case 2:
			cont[2]++;
			break;
		case 3:
			cont[3]++;
			break;
		case 4:
			cont[4]++;
			break;
		case 5:
			cont[5]++;
			break;
		case 6:
			cont[6]++;
			break;
		case 7:
			cont[7]++;
			break;
	}
	system("clear || cls");  //ATENCAO AQUI! pois não funciona em algumas maquinas
	coluna_jogada--;    
	atualizarTabuleiro('X');
	mostraTabuleiro();
	analizar_tudo();
}

//Jogada do Player 2 (O): onde o jogador escolhe o tipo da ficha e coluna jogada
void jogadaP2(){ 
	int ficha=0;
	if (rodadas >=5){
		if (rodadas%5==0){
			explosivaP2+=1;
			portalP2 +=1;
		}
		printf("\nVoce tem %d fichas explosivas e %d fichas portais \n\n", explosivaP2, portalP2);
			if ((explosivaP2 != 0)||(portalP2!=0)){
				printf("%s, escolha o tipo de peca:\n ", nomePlayer[1].vencedor);
				printf("1. Normal \n 2. Explosiva \n 3. Portal\n");
				while ((ficha<1 || ficha >3)){
					scanf ("%d", &ficha);
					switch (ficha){
						case 1: //nao precisa mudar. Ja esta correto.;
							break;
						case 2: //explosiva
							if (explosivaP2==0){
								printf ("Voce nao possui pecas explosivas.\n PERDEU A CHANCE DE UTILIZAR PECA ESPECIAL!!\n"); 
							}else{
								explosivaP2-=1;
							}
							break;
						case 3://portal
							if (portalP2==0){
								printf ("Voce nao possui pecas portal.\n PERDEU A CHANCE DE UTILIZAR PECA ESPECIAL!!\n"); 
							}else{
								portalP2-=1;
							}
							break;
						default:
							printf ("Digite uma opcao valida.\n1. Normal \n2. Explosiva \n3. Portal\n");
					}
				}
			}
			
	}
	printf("%s, escolha uma coluna: ", nomePlayer[1].vencedor); 
	scanf("%d",&coluna_jogada); //Leitura do local da jogada
	while ( coluna_jogada <1 || coluna_jogada >7 || cont [coluna_jogada]==6){ //AQUI IDENTIFICA SE A COLUNA ESTA CHEIA OU SE A JOGADA FOI EM UM LUGAR INVALIDO
		printf ("ERRO: COLUNA INVALIDA\n");
		printf("%s, escolha uma coluna: ", nomePlayer[1].vencedor);
		scanf("%d",&coluna_jogada); //Leitura do local da jogada VALIDA
	}
	switch(coluna_jogada){ //AQUI SOMA UMA PECA A COLUNA
		case 1:
			cont[1]++;			
			break;
		case 2:
			cont[2]++;
			break;
		case 3:
			cont[3]++;
			break;
		case 4:
			cont[4]++;
			break;
		case 5:
			cont[5]++;
			break;
		case 6:
			cont[6]++;
			break;
		case 7:
			cont[7]++;
			break;
	}
	system("clear || cls");  //ATENCAO AQUI! pois não funciona em algumas maquinas
	coluna_jogada--;    
	atualizarTabuleiro('O');
	rodadas++;
	mostraTabuleiro();
	analizar_tudo();
}



//Jogada do Computador 1 (X): Neste caso, a maquina escolhe a coluna jogada
void jogadaComp1(){   
	printf ("%s esta jogando... Por Favor, aguarde!", nomePlayer[0].vencedor);
	srand(time(NULL));
	sleep(1.5);
	coluna_jogada = 1+(rand()%7); // local aleatorio da jogada
	while (cont [coluna_jogada]==6){
		coluna_jogada = 1+(rand()%7); // local aleatorio da jogada
	}
	switch(coluna_jogada){
		case 1:
			cont[1]++;			
			break;
		case 2:
			cont[2]++;
			break;
		case 3:
			cont[3]++;
			break;
		case 4:
			cont[4]++;
			break;
		case 5:
			cont[5]++;
			break;
		case 6:
			cont[6]++;
			break;
		case 7:
			cont[7]++;
			break;
	}
	system("clear || cls");  //ATENCAO AQUI! pois não funciona em algumas maquinas
	coluna_jogada--;    
	atualizarTabuleiro('X');
	mostraTabuleiro();
	analizar_tudo_PC();
}


//Jogada do Computador 2 (O): Neste caso, a maquina escolhe a coluna jogada
void jogadaComp2(){  
	printf ("%s esta jogando... Por Favor, aguarde!", nomePlayer[1].vencedor);
	srand(time(NULL));
	sleep(2);
	coluna_jogada = 1+(rand()%7); // local aleatorio da jogada
	while (cont [coluna_jogada]==6){
		coluna_jogada = 1+(rand()%7); // local aleatorio da jogada
	}
	switch(coluna_jogada){
		case 1:
			cont[1]++;			
			break;
		case 2:
			cont[2]++;
			break;
		case 3:
			cont[3]++;
			break;
		case 4:
			cont[4]++;
			break;
		case 5:
			cont[5]++;
			break;
		case 6:
			cont[6]++;
			break;
		case 7:
			cont[7]++;
			break;
	}
	system("clear || cls");  //ATENCAO AQUI! pois não funciona em algumas maquinas
	coluna_jogada--;    
	atualizarTabuleiro('O');
	rodadas++;
	mostraTabuleiro();
	analizar_tudo_PC();
}//FIM DA FUNCAO DAS JOGADAS//


//PLAYER (X) VS MAQUINA (0)//
void jogo_P1vsPC(){ 
	printf("1. Jogador vs Computador\n");
	printf("Digite seu nome:  ");
	scanf ("%s", nomePlayer[0].vencedor);
	fflush(stdin);   // COMANDO PARA O PROGRAMA NAO LER O ENTER. O DO LINUX E "__fpurge"//
	nomePlayer[1].vencedor[0] = 'L';nomePlayer[1].vencedor[1] ='i';nomePlayer[1].vencedor[2] ='n';nomePlayer[1].vencedor[3] ='d';nomePlayer[1].vencedor[4] ='i';nomePlayer[1].vencedor[5] ='n';nomePlayer[1].vencedor[6] ='a'; nomePlayer[1].vencedor[7] ='l';nomePlayer[1].vencedor[8] ='v';nomePlayer[1].vencedor[9] ='a';   //Nome da maquina(o)
	mostraTabuleiro();//inicializaTabuleiro(tabuleiro);
	explosiva =0;
	explosivaP2 =0;
	portal = 0;
	portalP2 = 0;
	while (rodadas<22){
		jogadaP1();
		jogadaComp2();
	}
	printf ("\n Tabuleiro Cheio: Empate!!");
	recomecar();// quando tabuleiro estiver cheio, será declarado Empate
}


//PLAYER 1 (X) VS PLAYER 2 (O)//
void jogo_P1vsP2(){
	printf("2. Jogador vs Jogador\n");
	printf("Digite o nome do jogador 1:  ");
    scanf ("%s", nomePlayer[0].vencedor);
    fflush(stdin);   // COMANDO PARA O PROGRAMA NAO LER O ENTER. O DO LINUX E "__fpurge"//
    printf("Digite o nome do jogador 2:  ");
    scanf ("%s", nomePlayer[1].vencedor);
    fflush(stdin);   // COMANDO PARA O PROGRAMA NAO LER O ENTER. O DO LINUX E "__fpurge"//
	mostraTabuleiro();
	explosiva =0;
	explosivaP2 =0;
	portal = 0;
	portalP2 = 0;
	while (rodadas<22) {
		jogadaP1();
		jogadaP2();	
	} 
	printf ("\n Tabuleiro Cheio: Empate!!");
	recomecar();// quando tabuleiro estiver cheio, será declarado Empate
}



//MAQUINA (X) VS MAQUINA (O)//
void jogo_PCvsPC(){
	printf("3. Computador vs Computador\n");
	nomePlayer[0].vencedor[0] = 'J';nomePlayer[0].vencedor[1] ='o';nomePlayer[0].vencedor[2] ='s';nomePlayer[0].vencedor[3] ='i';nomePlayer[0].vencedor[4] ='v';nomePlayer[0].vencedor[5] ='a';nomePlayer[0].vencedor[6] ='l'; nomePlayer[0].vencedor[7] ='d';nomePlayer[0].vencedor[8] ='o';
	nomePlayer[1].vencedor[0] = 'L';nomePlayer[1].vencedor[1] ='i';nomePlayer[1].vencedor[2] ='n';nomePlayer[1].vencedor[3] ='d';nomePlayer[1].vencedor[4] ='i';nomePlayer[1].vencedor[5] ='n';nomePlayer[1].vencedor[6] ='a'; nomePlayer[1].vencedor[7] ='l';nomePlayer[1].vencedor[8] ='v';nomePlayer[1].vencedor[9] ='a';
	
	//inicializaTabuleiro(tabuleiro);
	mostraTabuleiro();
	while (rodadas<22){
		jogadaComp1();
		jogadaComp2();
	}
	printf ("\n Tabuleiro Cheio: Empate!!");
	recomecar();// quando tabuleiro estiver cheio, será declarado Empate
}
/*typedef struct {
  char vencedor[100];
  int rodada;
} ParaHall;
ParaHall nomePlayer[2];*/

//FUNÇAO QUE VAI EDITAR O ARQUIVO DO HALL
int CriaArquivoHall(){
	ParaHall lista[1];
	FILE* hall;
	if((hall = fopen("hall_campeoes.txt", "a+")) == NULL) return 1;
    printf("\nDigite o nome do jogador que venceu: ");
    scanf ("%s", lista[0].vencedor);
    printf("Digite quantas rodadas foram usadas: ");
    scanf("%d%*c", &lista[0].rodada);
	fwrite(lista, sizeof(lista[0]), 1, hall); 
	fclose(hall);
	return 0;
}//FIM DA EDICAO DO HALL



//FUNÇAO QUE VAI LER O ARQUIVO DO HALL
int LeArquivoHall(){
	ParaHall HallC;
	FILE* hall;
	if((hall = fopen("hall_campeoes.txt", "r+")) == NULL) return 1;
	while(fread(&HallC, sizeof(ParaHall), 1, hall) == 1) {
		printf("%s venceu em %d rodadas\n", HallC.vencedor, HallC.rodada);
	}
	fclose(hall);
	return 0;
}//FIM DA LEITURA DO HALL



//HALL DOS CAMPEOES//
int hall_dos_campeoes(){
	printf("Bem vindo ao Hall dos Campeoes!\n");
	printf("Aqui mostraremos todos os vencedores desse jogo maravilhoso:\n\n");
	LeArquivoHall();
	menuDoHall();
	return 0;
}

void menuDoHall(){
	int menuHall;
	printf("\n\nO que deseja fazer agora?\n");
	printf("\n1. Voltar ao menu inicial\n0. Sair do jogo. ");
	scanf ("%d",&menuHall);
	switch (menuHall){
		case 1:
			main();
			break;
		case 0:
			sair();
			break;	
		default:
			printf ("digite uma opção valida!");
			menuDoHall();
	}
}


//SAIR//
void sair(){
	system("clear || cls"); //ATENCAO AQUI! pois não funciona em algumas maquinas 
	printf("Saindo do jogo.\n");
	exit(0);//Finalização do jogo
}
 
 
 
int main(){
//MENU INICIAL DO JOGO//

    int i, menu1, menu2;    
	system("clear || cls");//ATENCAO AQUI! pois não funciona em algumas maquinas
	printf("\n\t\t\t\tLig4++\n\n");
	printf("\t\t\t1. Novo Jogo\n");
	printf("\t\t\t2. Hall dos Campeoes\n");
	printf("\t\t\t0. Sair\n");
	scanf("%d", &menu1);
	system("clear || cls");//ATENCAO AQUI! pois não funciona em algumas maquinas
	switch(menu1){
		case 1:
//MENU PARA SELECIONAR TIPO DE JOGO//
			printf("\n\tJogo sendo iniciado! Por favor, escolha a opcao desejada:\n\n");
			printf("\t\t\t1. Jogador vs Computador\n");
			printf("\t\t\t2. Jogador vs Jogador\n");
			printf("\t\t\t3. Computador vs Computador\n");
			printf("\t\t\t0. Voltar ao menu anterior\n");
			scanf ("%d", &menu2);
			system("clear || cls"); //ATENCAO AQUI! pois não funciona em algumas maquinas 
			rodadas = 1;
			for (i = 0 ; i < 8 ; i++){
				cont[i] = 0;
			}
			inicializaTabuleiro();
			switch (menu2){
				case 1: 
					jogo_P1vsPC();
					break;
				case 2:
					jogo_P1vsP2();
					break;
				case 3:
					jogo_PCvsPC();
					break;
				case 0:
					return main();
					break;
				default:
					printf("Voce digitou uma opcao invalida. Por isso, sera redirecionado ao menu inicial.\n");
					sleep (4);
					system ("clear || cls");//ATENCAO AQUI! pois não funciona em algumas maquinas
					return main();
			}
			break; //final do case 1 do menu1

		case 2:
			hall_dos_campeoes();
			break;

		case 0:
			sair();
			break;

		default:
			printf("Voce digitou uma opcao invalida. Por isso, sera redirecionado ao menu inicial\n");
			sleep (3);
			system ("clear || cls");//ATENCAO AQUI! pois não funciona em algumas maquinas
            return main();    
	
	}
	return 0;
}
