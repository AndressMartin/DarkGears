#include "structs.h"
#include "enums.h"
#include "listaEncadeadaPersonagem.h"

#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<string.h>

void interacoesComOMapa(int CenarioAtual, int PosX, int PosY, int PLarX, int PLarY, int CPosX, int CPosY, int Bau_AreaDeInteracao, RetangulosDeColisao PosicaoBaus[], int NumeroDeBaus, int **Baus, int BausCopia[], bool *PodeFazerInteracao, bool *SpacePress, bool *MudancaDeCenario, int *MudancaDeCenarioNumero, RetangulosDeColisao Portas[], bool *CaixaDeTexto, char **Arquivo, int *DialogoPosX, int *DialogoPosY, int *DialogoPartToStart, int *DialogoPartToStop, char **MudancaDeTexto, bool *AdicionarItem, int *AdicionarItemIndice, int NInimigos, bool **InimigosVivos, bool InimigosVivosCopia[], RetangulosDeColisao InimigosPosicoes[], Personagens **mob, bool *IniciarBatalha, int *MusicaDoCenario, int *MusicaDaBatalha)
{
	// Funcao onde vamos tentar colocar todas as interacoes com o mapa. Vai depender do mapa atual.
	// Interacoes como abrir baus, apertar botoes, falr com NPCs, e as transicoes dos mapas.
	// A variavel global PodeFazerInteracao sera usada para limitar a uma interacao por vez.
	switch(CenarioAtual)
	{
		case 0:
			{
				int InteracaoN = 0;
				char golem[] = "Golem";
				char wumpus[] = "Wumpus";
				
				//Baus no mapa.
				
				InteracaoN = 0;
				if(!(BausCopia[InteracaoN] == NADA) && *PodeFazerInteracao == true)
				{
					if((PosX < PosicaoBaus[InteracaoN].DisX + PosicaoBaus[InteracaoN].LarX + CPosX + Bau_AreaDeInteracao) && (PosX + PLarX > PosicaoBaus[InteracaoN].DisX + CPosX - Bau_AreaDeInteracao) && (PosY < PosicaoBaus[InteracaoN].DisY + PosicaoBaus[InteracaoN].LarY + CPosY + Bau_AreaDeInteracao) && (PosY + PLarY > PosicaoBaus[InteracaoN].DisY + CPosY - Bau_AreaDeInteracao))
					{
						if((GetKeyState(VK_SPACE)&0x80) && *SpacePress == false)
					    {
					    	int *BausTemp;
					    	BausTemp = (int *)malloc(sizeof(int) * NumeroDeBaus);
					    	
					    	*AdicionarItem = true;
					    	*AdicionarItemIndice = BausCopia[InteracaoN];
					    	BausCopia[InteracaoN] = NADA;
					    	
					    	for(int i=0; i < NumeroDeBaus; i++)
					    	{
					    		BausTemp[i] = BausCopia[i];
							}
							
							free(*Baus);
							*Baus = BausTemp;
							*Arquivo = (char *)malloc(sizeof(char) * 17);
					    	strcpy(*Arquivo, "Textos/Teste.txt");
					    	
					    	*MudancaDeTexto = (char *)malloc(sizeof(char) * 40);
					    	strcpy(*MudancaDeTexto, "Poção!");
					    	
					    	*DialogoPosX = 169,
							*DialogoPosY = 435,
							*DialogoPartToStart = 36,
							*DialogoPartToStop = 37;
							
					    	*PodeFazerInteracao = false;
					    	*CaixaDeTexto = true;
						}
					}
				}
				
				InteracaoN = 1;
				if(!(BausCopia[InteracaoN] == NADA) && *PodeFazerInteracao == true)
				{
					if((PosX < PosicaoBaus[InteracaoN].DisX + PosicaoBaus[InteracaoN].LarX + CPosX + Bau_AreaDeInteracao) && (PosX + PLarX > PosicaoBaus[InteracaoN].DisX + CPosX - Bau_AreaDeInteracao) && (PosY < PosicaoBaus[InteracaoN].DisY + PosicaoBaus[InteracaoN].LarY + CPosY + Bau_AreaDeInteracao) && (PosY + PLarY > PosicaoBaus[InteracaoN].DisY + CPosY - Bau_AreaDeInteracao))
					{
						if((GetKeyState(VK_SPACE)&0x80) && *SpacePress == false)
					    {
					    	int *BausTemp;
					    	BausTemp = (int *)malloc(sizeof(int) * NumeroDeBaus);
					    	
					    	*AdicionarItem = true;
					    	*AdicionarItemIndice = BausCopia[InteracaoN];
					    	BausCopia[InteracaoN] = NADA;
					    	
					    	for(int i=0; i < NumeroDeBaus; i++)
					    	{
					    		BausTemp[i] = BausCopia[i];
							}
							
							free(*Baus);
							*Baus = BausTemp;
							
							free(*Baus);
							*Baus = BausTemp;
							*Arquivo = (char *)malloc(sizeof(char) * 17);
					    	strcpy(*Arquivo, "Textos/Teste.txt");
					    	
					    	*MudancaDeTexto = (char *)malloc(sizeof(char) * 40);
					    	strcpy(*MudancaDeTexto, "Poção!");
					    	
					    	*DialogoPosX = 169,
							*DialogoPosY = 30,
							*DialogoPartToStart = 38,
							*DialogoPartToStop = 40;
							
					    	*PodeFazerInteracao = false;
					    	*CaixaDeTexto = true;
						}
					}
				}
				
				//Inimigos
				InteracaoN = 0;
				if(InimigosVivosCopia[InteracaoN] == true && *PodeFazerInteracao == true)
				{
					if((PosX < InimigosPosicoes[InteracaoN].DisX + InimigosPosicoes[InteracaoN].LarX + CPosX) && (PosX + PLarX > InimigosPosicoes[InteracaoN].DisX + CPosX) && (PosY < InimigosPosicoes[InteracaoN].DisY + InimigosPosicoes[InteracaoN].LarY + CPosY) && (PosY + PLarY > InimigosPosicoes[InteracaoN].DisY + CPosY))
					{
						printf("\nAntes:");
						detalhaStatus(*mob);
						//Tirar os itens da lista de mobs.
						while(*mob != NULL)
						{
							*mob = lista_retira(*mob, *mob->id);
						}
						
						//Adicionar os novos mobs
						*mob = lista_insere(*mob, 1, golem, 20, 18, 50, 6, 5, 1, 400, 15);
						
						printf("\nDepois:");
						detalhaStatus(*mob);
						
						*MusicaDaBatalha = MUSICABATALHA;
						
						//Deixar o inimigo "morto"
						bool *InimigosVivosTemp;
				    	InimigosVivosTemp = (bool *)malloc(sizeof(bool) * NInimigos);
				    	
				    	InimigosVivosCopia[InteracaoN] = false;
				    	
				    	for(int i=0; i < NInimigos; i++)
				    	{
				    		InimigosVivosTemp[i] = InimigosVivosCopia[i];
						}
						
						free(*InimigosVivos);
						*InimigosVivos = InimigosVivosTemp;
						
						*PodeFazerInteracao = false;
						*IniciarBatalha = true;
					}
				}
				
				
				//Dialogos
				InteracaoN = 0;
				if((PosX < PosicaoBaus[InteracaoN].DisX + PosicaoBaus[InteracaoN].LarX + CPosX + Bau_AreaDeInteracao) && (PosX + PLarX > PosicaoBaus[InteracaoN].DisX + CPosX - Bau_AreaDeInteracao) && (PosY < PosicaoBaus[InteracaoN].DisY + PosicaoBaus[InteracaoN].LarY + CPosY + Bau_AreaDeInteracao) && (PosY + PLarY > PosicaoBaus[InteracaoN].DisY + CPosY - Bau_AreaDeInteracao))
				{
					if((GetKeyState(VK_SPACE)&0x80) && *SpacePress == false && *PodeFazerInteracao == true)
				    {
				    	*Arquivo = (char *)malloc(sizeof(char) * 17);
				    	strcpy(*Arquivo, "Textos/Teste.txt");
				    	
				    	*DialogoPosX = 229,
						*DialogoPosY = 435,
						*DialogoPartToStart = 2,
						*DialogoPartToStop = 9;
						
				    	*PodeFazerInteracao = false;
				    	*CaixaDeTexto = true;
					}
				}
				
				InteracaoN = 1;
				if((PosX < PosicaoBaus[InteracaoN].DisX + PosicaoBaus[InteracaoN].LarX + CPosX + Bau_AreaDeInteracao) && (PosX + PLarX > PosicaoBaus[InteracaoN].DisX + CPosX - Bau_AreaDeInteracao) && (PosY < PosicaoBaus[InteracaoN].DisY + PosicaoBaus[InteracaoN].LarY + CPosY + Bau_AreaDeInteracao) && (PosY + PLarY > PosicaoBaus[InteracaoN].DisY + CPosY - Bau_AreaDeInteracao))
				{
					if((GetKeyState(VK_SPACE)&0x80) && *SpacePress == false && *PodeFazerInteracao == true)
				    {
				    	*Arquivo = (char *)malloc(sizeof(char) * 17);
				    	strcpy(*Arquivo, "Textos/Teste.txt");
				    	
				    	*DialogoPosX = 229,
						*DialogoPosY = 130,
						*DialogoPartToStart = 11,
						*DialogoPartToStop = 21;
						
				    	*PodeFazerInteracao = false;
				    	*CaixaDeTexto = true;
					}
				}
				
				//Portas
				
				InteracaoN = 0;
				if(*PodeFazerInteracao == true)
				{
					if((PosX < Portas[InteracaoN].DisX + Portas[InteracaoN].LarX + CPosX) && (PosX + PLarX > Portas[InteracaoN].DisX + CPosX) && (PosY < Portas[InteracaoN].DisY + Portas[InteracaoN].LarY + CPosY) && (PosY + PLarY > Portas[InteracaoN].DisY + CPosY))
					{
						*MudancaDeCenario = true;
						*MudancaDeCenarioNumero = InteracaoN;
						*PodeFazerInteracao = false;
					}
				}
				
				break;
			}
		
		case 1:
			{
				int InteracaoN = 0;
				
				//Portas
				
				InteracaoN = 1;
				if(*PodeFazerInteracao == true)
				{
					if((PosX < Portas[InteracaoN].DisX + Portas[InteracaoN].LarX + CPosX) && (PosX + PLarX > Portas[InteracaoN].DisX + CPosX) && (PosY < Portas[InteracaoN].DisY + Portas[InteracaoN].LarY + CPosY) && (PosY + PLarY > Portas[InteracaoN].DisY + CPosY))
					{
						*MudancaDeCenario = true;
						*MudancaDeCenarioNumero = InteracaoN;
						*PodeFazerInteracao = false;
					}
				}
				
				break;
			}
			
	}
}
