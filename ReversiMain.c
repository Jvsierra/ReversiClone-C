#include <stdio.h>
#include <conio.h>
#include "meuconio.h"

#define L 8 //Número de linhas do tabuleiro de jogo
#define C 8 //Número de colunas do tabuleiro de jogo

//========================================//

//Posições iniciais das duas peças brancas

int INICIO_BRANCO_1_LINHA = 3;
int INICIO_BRANCO_1_COLUNA = 3;

int INICIO_BRANCO_2_LINHA = 4;
int INICIO_BRANCO_2_COLUNA = 4;

//======================================//

//Posições iniciais das duas peças pretas

int INICIO_PRETO_1_LINHA = 3;
int INICIO_PRETO_1_COLUNA = 4;

int INICIO_PRETO_2_LINHA = 4;
int INICIO_PRETO_2_COLUNA = 3;

//========================================//

int turno = 1;//Variável que indicará de qual jogador é o turno atual
int board[L][C] = {0}; /*Matriz que representará o tabuleiro de jogo
0 -> Posição vazia
1 -> Posição ocupada por uma peça preta
2 - > Posição ocupada por uma peça branca */

//Função que retornará 0 se o jogo terminou, 1 se as pretas ganharam, 2 se as brancas ganharam e 3 se houve um empate.
int checaResultado();
//Função que retornará 1 se a posicao escolhida pelo usuário e valida e 0 se é inválida
int checaPosicaoValida(int linha, int coluna, int pecaAtual);
//Função que coloca os botões inicais no tabuleiro
void inicializaMatriz();
//Função que imprime a matriz, colorindo as posições de acordo com os valores
void imprimeMatriz();
//Loop do jogo (lerá as entradas dos usuários até o final do jogo)
void gameLoop();
//Função que troca as peças do tabuleiro quando é escolhida uma posição válida
void trocaPecas(int linha, int coluna, int pecaAtual);

int main()
{
	int op;
	
	do
	{
		gameLoop();
		
		printf("Digite 1 para jogar novamente:\n");
		scanf("%d", &op);
	}while(op == 1);
	getch();
}

int checaResultado()
{
	int i, j, contBranco, contPreto, contPecas, ret;
	
	contBranco = 0;
	contPreto = 0;
	contPecas = 0;
	
	for(i = 0; i < L; i++)
		for(j = 0; j < C; j++)
			if(board[i][j] > 0)
			{
				contPecas++;
				
				if(board[i][j] == 1)
					contPreto++;
				else
					contBranco++;	
			}	
			
	if(contPecas == L * C)
		if(contPreto > contBranco)
			ret = 1;
		else if(contPreto == contBranco)
			ret = 3;
		else
			ret = 2;
	else
	{
		contPreto = 0;
		
		for(i = 0; i < L; i++)
			for(j = 0; j < C; j++)
				if(checaPosicaoValida(i , j, 1) == 1)
					contPreto++;
					
		if(contPreto == 0)
			ret = 2;
		else
		{
			contBranco = 0;
			
			for(i = 0; i < L; i++)
				for(j = 0; j < C; j++)
					if(checaPosicaoValida(i, j, 2) == 1)
						contBranco++;
						
			if(contBranco == 0)
				ret = 1;
			else
				ret = 0;
		}
	}
	
	return ret;
}

int checaPosicaoValida(int linha, int coluna, int pecaAtual)
{
	int contador, ret, contrario, i, j;
	
	if(pecaAtual == 1)
		contrario = 2;
	else	
		contrario = 1;
	
	contador = 0;
	
	if(linha > 0)
	{
		if(coluna > 0)
		{
			//Subindo diagonal princiapl
			i = linha;
			j = coluna;
			
			while(board[i - 1][j - 1] == contrario)
			{
				i--;
				j--;
			}
			
			if(i < linha && j < coluna)
				if(board[i - 1][j - 1] == pecaAtual)
					contador++;
		}
		
		if(coluna < C - 1)
		{
			//Subindo diagonal secundária
			i = linha;
			j = coluna;
			
			while(board[i - 1][j + 1] == contrario)
			{
				i--;
				j++;
			}
			
			if(i < linha && j > coluna)
				if(board[i - 1][j + 1] == pecaAtual)
					contador++;
		}
		
		//Subindo
		i = linha;
		j = coluna;
		
		while(board[i - 1][j] == contrario)
			i--;
			
		if(i < linha)
			if(board[i - 1][j] == pecaAtual)
					contador++;
	}
	
	if(linha < L - 1)
	{
		if(coluna > 0)
		{
			//Descendo diagonal secundária
			i = linha;
			j = coluna;
			
			while(board[i + 1][j - 1] == contrario)
			{
				i++;
				j--;
			}
			
			if(i > linha && j < coluna)
				if(board[i + 1][j - 1] == pecaAtual)
					contador++;
		}
		
		if(coluna < C - 1)
		{
			//Descendo diagonal principal
			i = linha;
			j = coluna;
			
			while(board[i + 1][j + 1] == contrario)
			{
				i++;
				j++;
			}
			
			if(i > linha && j > coluna)
				if(board[i + 1][j + 1] == pecaAtual)
					contador++;
		}
		
		//Descendo
		
		i = linha;
		j = coluna;
		
		while(board[i + 1][j] == contrario)
			i++;
			
		if(i > linha)
			if(board[i + 1][j] == pecaAtual)
				contador++;
	}
	
	if(coluna > 0)
	{
		//Esquerda
		i = linha;
		j = coluna;
		
		while(board[i][j - 1] == contrario)
			j--;
			
		if(j  < coluna)
		{
			if(board[i][j - 1] == pecaAtual)
			{
				contador++;
			}
		}
	}
	
	if(coluna < C - 1)
	{
		//Direita
		i = linha;
		j = coluna;
		
		while(board[i][j + 1] == contrario)
			j++;
		
		if(j > coluna)
			if(board[i][j + 1] == pecaAtual)
				contador++;
	}
	
	if(contador > 0)
		ret = 1;
	else
		ret = 0;
		
	return ret;
}

void inicializaMatriz()
{
	int i, j;
	
	for(i = 0; i < L; i++)
		for(j = 0; j < C; j++)
			board[i][j] = 0;
			
	board[INICIO_BRANCO_1_LINHA][INICIO_BRANCO_1_COLUNA] = 2;
	board[INICIO_BRANCO_2_LINHA][INICIO_BRANCO_2_COLUNA] = 2;
	board[INICIO_PRETO_1_LINHA][INICIO_PRETO_1_COLUNA] = 1;
	board[INICIO_PRETO_2_LINHA][INICIO_PRETO_2_COLUNA] = 1;
}

void imprimeMatriz()
{
	int i, j;
	
	printf("  ");
	textcolor(4);
	for(i = 1; i <= C; i++)
		printf("%d ", i);
	printf("\n");
	
	for(i = 0; i < L; i++)
	{
		textcolor(4);
		printf("%d ", i + 1);
		
		textbackground(2);
		
		for(j = 0; j < C; j++)
			if(board[i][j] > 0)
			{
				if(board[i][j] == 1)
					textcolor(0);
				else if(board[i][j] == 2)
					textcolor(15);
					
				printf("O");
					
				textcolor(1);
					
				printf("|", board[i][j]);
			}
			else
				if(checaPosicaoValida(i, j, turno) == 1)
				{
					textcolor(12);
					printf("X");
					textcolor(1);
					printf("|");
				}
				else
				{
					textcolor(1);
					printf(" |");
				}
					
		textcolor(15);
      	textbackground(0);
				
		printf("\n");
	}
}

void gameLoop()
{
	int linha, coluna, resultado;
	
	inicializaMatriz();
	imprimeMatriz();
	
	printf("Digite a linha e a coluna:\n");
	scanf("%d %d", &linha, &coluna);
	
	resultado = checaResultado();

	while(resultado == 0)
	{
		printf("%d %d", linha, coluna);
		linha--;
		coluna--;
		while(checaPosicaoValida(linha, coluna, turno) == 0)
		{
			printf("Posicao invalida.\n Digite a linha e a coluna:\n");
			scanf("%d %d", &linha, &coluna);
			linha--;
			coluna--;
		}
		
		board[linha][coluna] = turno;
		
		trocaPecas(linha, coluna, turno);
		
		resultado = checaResultado();
		
		if(turno == 1)
			turno = 2;
		else if(turno == 2)
			turno = 1;		
		
		printf("\n");
		
		imprimeMatriz();
		
		if(resultado == 0)
		{
			printf("Digite a linha e a coluna:\n");
			scanf("%d %d", &linha, &coluna);
		}
	}
}
void trocaPecas(int linha, int coluna, int pecaAtual)
{
	int contrario, i, j;
	
	if(pecaAtual == 1)
		contrario = 2;
	else	
		contrario = 1;
	
	if(linha > 0)
	{
		if(coluna > 0)
		{
			//Subindo diagonal princiapl
			i = linha;
			j = coluna;
			
			while(board[i - 1][j - 1] == contrario)
			{
				i--;
				j--;
			}
			
			if(i < linha && j < coluna)
				if(board[i - 1][j - 1] == pecaAtual)
				{
					i = linha;
					j = coluna;
					
					while(board[i - 1][j - 1] == contrario)
					{
						board[i - 1][j - 1] = pecaAtual;
						i--;
						j--;
					}
					
					board[i - 1][j - 1] = contrario;
				}
		}
		
		if(coluna < C - 1)
		{
			//Subindo diagonal secundária
			i = linha;
			j = coluna;
			
			while(board[i - 1][j + 1] == contrario)
			{
				i--;
				j++;
			}
			
			if(i < linha && j > coluna)
				if(board[i - 1][j + 1] == pecaAtual)
				{
					i = linha;
					j = coluna;
					
					while(board[i - 1][j + 1] == contrario)
					{
						board[i - 1][j + 1] = pecaAtual;
						i--;
						j++;
					}
					
					board[i - 1][j + 1] = pecaAtual;
				}
		}
		
		//Subindo
		i = linha;
		j = coluna;
		
		while(board[i - 1][j] == contrario)
			i--;
			
		if(i < linha)
			if(board[i - 1][j] == pecaAtual)
			{
				i = linha;
				j = coluna;
				
				while(board[i - 1][j] == contrario)
				{
					board[i - 1][j] = pecaAtual;
					i--;
				}
				
				board[i - 1][j] = pecaAtual;
			}
	}
	
	if(linha < L - 1)
	{
		if(coluna > 0)
		{
			//Descendo diagonal secundária
			i = linha;
			j = coluna;
			
			while(board[i + 1][j - 1] == contrario)
			{
				i++;
				j--;
			}
			
			if(i > linha && j < coluna)
				if(board[i + 1][j - 1] == pecaAtual)
				{
					i = linha;
					j = coluna;
					
					while(board[i + 1][j - 1] == contrario)
					{
						board[i + 1][j - 1] = pecaAtual;
						i++;
						j--;
					}
					
					board[i + 1][j - 1] = pecaAtual;
				}
		}
		
		if(coluna < C - 1)
		{
			//Descendo diagonal principal
			i = linha;
			j = coluna;
			
			while(board[i + 1][j + 1] == contrario)
			{
				i++;
				j++;
			}
			
			if(i > linha && j > coluna)
				if(board[i + 1][j + 1] == pecaAtual)
				{
					i = linha;
					j = coluna;
					
					while(board[i + 1][j + 1] == contrario)
					{
						board[i + 1][j + 1] = pecaAtual;
						i++;
						j++;
					}
					
					board[i + 1][j + 1] = pecaAtual;
				}
		}
		
		//Descendo
		
		i = linha;
		j = coluna;
		
		while(board[i + 1][j] == contrario)
			i++;
			
		if(i > linha)
			if(board[i + 1][j] == pecaAtual)
			{
				i = linha;
				j = coluna;
				
				while(board[i + 1][j] == contrario)
				{
					board[i + 1][j] = pecaAtual;
					i++;
				}	
				
				board[i + 1][j] = pecaAtual;
			}
	}
	
	if(coluna > 0)
	{
		//Esquerda
		i = linha;
		j = coluna;
		
		while(board[i][j - 1] == contrario)
			j--;
			
		if(j  < coluna)
		{
			if(board[i][j - 1] == pecaAtual)
			{
				i = linha;
				j = coluna;
				
				while(board[i][j - 1] == contrario)
				{
					board[i][j - 1] = pecaAtual;
					j--;
				}
				
				board[i][j - 1] = pecaAtual;
			}
		}
	}
	
	if(coluna < C - 1)
	{
		//Direita
		i = linha;
		j = coluna;
		
		while(board[i][j + 1] == contrario)
			j++;
		
		if(j > coluna)
			if(board[i][j + 1] == pecaAtual)
			{
				i = linha;
				j = coluna;
				
				while(board[i][j + 1] == contrario)
				{
					board[i][j + 1] = pecaAtual;
					j++;
				}
				
				board[i][j + 1] = pecaAtual;
			}
	}
}
