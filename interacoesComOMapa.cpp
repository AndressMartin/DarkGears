#include "structs.h"
#include "enums.h"
#include "listaEncadeadaPersonagem.h"

#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<string.h>

void interacoesComOMapa(int CenarioAtual, int PosX, int PosY, int PLarX, int PLarY, int CPosX, int CPosY, int Bau_AreaDeInteracao, RetangulosDeColisao PosicaoBaus[], int Baus[], bool *PodeFazerInteracao, bool *SpacePress, bool *MudancaDeCenario, int *MudancaDeCenarioNumero, RetangulosDeColisao Portas[], bool *CaixaDeTexto, char **Arquivo, int *DialogoPosX, int *DialogoPosY, int *DialogoPartToStart, int *DialogoPartToStop, bool *AdicionarItem, int *AdicionarItemIndice, int *InimigoIndice, bool InimigosVivos[], RetangulosDeColisao InimigosPosicoes[], Personagens **mob, bool *IniciarBatalha, int *MusicaDoCenario, int *MusicaDaBatalha, bool *podeFugirVar)
{
	// Funcao onde vamos tentar colocar todas as interacoes com o mapa. Vai depender do mapa atual.
	// Interacoes como abrir baus, apertar botoes, falr com NPCs, e as transicoes dos mapas.
	// A variavel global PodeFazerInteracao sera usada para limitar a uma interacao por vez.
	switch(CenarioAtual)
	{
		case 0:
			{
				int InteracaoN = 0;
				char golem[6] = "Golem";
				char wumpus[7] = "Wumpus";
				char caracol[8] = "Caracol";
				
				Personagens* a = lista_cria();
				
				//Baus no mapa.
				
				InteracaoN = 0;
				if(!(Baus[InteracaoN] == NADA) && *PodeFazerInteracao == true)
				{
					if((PosX < PosicaoBaus[InteracaoN].DisX + PosicaoBaus[InteracaoN].LarX + CPosX + Bau_AreaDeInteracao) && (PosX + PLarX > PosicaoBaus[InteracaoN].DisX + CPosX - Bau_AreaDeInteracao) && (PosY < PosicaoBaus[InteracaoN].DisY + PosicaoBaus[InteracaoN].LarY + CPosY + Bau_AreaDeInteracao) && (PosY + PLarY > PosicaoBaus[InteracaoN].DisY + CPosY - Bau_AreaDeInteracao))
					{
						if((GetKeyState(VK_SPACE)&0x80) && *SpacePress == false)
					    {
					    	*AdicionarItem = true;
					    	*AdicionarItemIndice = InteracaoN;
							
							*Arquivo = (char *)malloc(sizeof(char) * 17);
					    	strcpy(*Arquivo, "Textos/MensagensDosBaus.txt");
					    	
					    	//*MudancaDeTexto = (char *)malloc(sizeof(char) * 40);
					    	//strcpy(*MudancaDeTexto, "Po��o!");
					    	
					    	*DialogoPosX = 169,
							*DialogoPosY = 435,
							*DialogoPartToStart = 2,
							*DialogoPartToStop = 3;
							
					    	*PodeFazerInteracao = false;
					    	*CaixaDeTexto = true;
						}
					}
				}
				
				InteracaoN = 1;
				if(!(Baus[InteracaoN] == NADA) && *PodeFazerInteracao == true)
				{
					if((PosX < PosicaoBaus[InteracaoN].DisX + PosicaoBaus[InteracaoN].LarX + CPosX + Bau_AreaDeInteracao) && (PosX + PLarX > PosicaoBaus[InteracaoN].DisX + CPosX - Bau_AreaDeInteracao) && (PosY < PosicaoBaus[InteracaoN].DisY + PosicaoBaus[InteracaoN].LarY + CPosY + Bau_AreaDeInteracao) && (PosY + PLarY > PosicaoBaus[InteracaoN].DisY + CPosY - Bau_AreaDeInteracao))
					{
						if((GetKeyState(VK_SPACE)&0x80) && *SpacePress == false)
					    {
					    	*AdicionarItem = true;
					    	*AdicionarItemIndice = InteracaoN;
							
							*Arquivo = (char *)malloc(sizeof(char) * 17);
					    	strcpy(*Arquivo, "Textos/MensagensDosBaus.txt");
					    	
					    	*DialogoPosX = 169,
							*DialogoPosY = 30,
							*DialogoPartToStart = 10,
							*DialogoPartToStop = 13;
							
					    	*PodeFazerInteracao = false;
					    	*CaixaDeTexto = true;
						}
					}
				}
				
				InteracaoN = 2;
				if(!(Baus[InteracaoN] == NADA) && *PodeFazerInteracao == true)
				{
					if((PosX < PosicaoBaus[InteracaoN].DisX + PosicaoBaus[InteracaoN].LarX + CPosX + Bau_AreaDeInteracao) && (PosX + PLarX > PosicaoBaus[InteracaoN].DisX + CPosX - Bau_AreaDeInteracao) && (PosY < PosicaoBaus[InteracaoN].DisY + PosicaoBaus[InteracaoN].LarY + CPosY + Bau_AreaDeInteracao) && (PosY + PLarY > PosicaoBaus[InteracaoN].DisY + CPosY - Bau_AreaDeInteracao))
					{
						if((GetKeyState(VK_SPACE)&0x80) && *SpacePress == false)
					    {
					    	*AdicionarItem = true;
					    	*AdicionarItemIndice = InteracaoN;
							
							*Arquivo = (char *)malloc(sizeof(char) * 17);
					    	strcpy(*Arquivo, "Textos/MensagensDosBaus.txt");
					    	
					    	//*MudancaDeTexto = (char *)malloc(sizeof(char) * 40);
					    	//strcpy(*MudancaDeTexto, "Po��o!");
					    	
					    	*DialogoPosX = 169,
							*DialogoPosY = 435,
							*DialogoPartToStart = 4,
							*DialogoPartToStop = 5;
							
					    	*PodeFazerInteracao = false;
					    	*CaixaDeTexto = true;
						}
					}
				}
				
				InteracaoN = 3;
				if(!(Baus[InteracaoN] == NADA) && *PodeFazerInteracao == true)
				{
					if((PosX < PosicaoBaus[InteracaoN].DisX + PosicaoBaus[InteracaoN].LarX + CPosX + Bau_AreaDeInteracao) && (PosX + PLarX > PosicaoBaus[InteracaoN].DisX + CPosX - Bau_AreaDeInteracao) && (PosY < PosicaoBaus[InteracaoN].DisY + PosicaoBaus[InteracaoN].LarY + CPosY + Bau_AreaDeInteracao) && (PosY + PLarY > PosicaoBaus[InteracaoN].DisY + CPosY - Bau_AreaDeInteracao))
					{
						if((GetKeyState(VK_SPACE)&0x80) && *SpacePress == false)
					    {
					    	*AdicionarItem = true;
					    	*AdicionarItemIndice = InteracaoN;
							
							*Arquivo = (char *)malloc(sizeof(char) * 17);
					    	strcpy(*Arquivo, "Textos/MensagensDosBaus.txt");
					    	
					    	//*MudancaDeTexto = (char *)malloc(sizeof(char) * 40);
					    	//strcpy(*MudancaDeTexto, "Po��o!");
					    	
					    	*DialogoPosX = 169,
							*DialogoPosY = 435,
							*DialogoPartToStart = 6,
							*DialogoPartToStop = 7;
							
					    	*PodeFazerInteracao = false;
					    	*CaixaDeTexto = true;
						}
					}
				}
				
				InteracaoN = 4;
				if(!(Baus[InteracaoN] == NADA) && *PodeFazerInteracao == true)
				{
					if((PosX < PosicaoBaus[InteracaoN].DisX + PosicaoBaus[InteracaoN].LarX + CPosX + Bau_AreaDeInteracao) && (PosX + PLarX > PosicaoBaus[InteracaoN].DisX + CPosX - Bau_AreaDeInteracao) && (PosY < PosicaoBaus[InteracaoN].DisY + PosicaoBaus[InteracaoN].LarY + CPosY + Bau_AreaDeInteracao) && (PosY + PLarY > PosicaoBaus[InteracaoN].DisY + CPosY - Bau_AreaDeInteracao))
					{
						if((GetKeyState(VK_SPACE)&0x80) && *SpacePress == false)
					    {
					    	*AdicionarItem = true;
					    	*AdicionarItemIndice = InteracaoN;
							
							*Arquivo = (char *)malloc(sizeof(char) * 17);
					    	strcpy(*Arquivo, "Textos/MensagensDosBaus.txt");
					    	
					    	//*MudancaDeTexto = (char *)malloc(sizeof(char) * 40);
					    	//strcpy(*MudancaDeTexto, "Po��o!");
					    	
					    	*DialogoPosX = 169,
							*DialogoPosY = 435,
							*DialogoPartToStart = 8,
							*DialogoPartToStop = 9;
							
					    	*PodeFazerInteracao = false;
					    	*CaixaDeTexto = true;
						}
					}
				}
				
				//Inimigos
				InteracaoN = 0;
				if(InimigosVivos[InteracaoN] == true && *PodeFazerInteracao == true)
				{
					if((PosX < InimigosPosicoes[InteracaoN].DisX + InimigosPosicoes[InteracaoN].LarX + CPosX) && (PosX + PLarX > InimigosPosicoes[InteracaoN].DisX + CPosX) && (PosY < InimigosPosicoes[InteracaoN].DisY + InimigosPosicoes[InteracaoN].LarY + CPosY) && (PosY + PLarY > InimigosPosicoes[InteracaoN].DisY + CPosY))
					{
						//printf("\nAntes:");
						//detalhaStatus(*mob);
						
						//Tirar os itens da lista de mobs.
						while(*mob != NULL)
						{
							a = *mob;
							*mob = lista_retira(*mob, a->id);
						}
						
						//Adicionar os novos mobs
						*mob = lista_insere(*mob, 1, caracol, 8, 5, 50, 6, 5, 3, 50, 10);
						
						//printf("\nDepois:");
						//detalhaStatus(*mob);
						
						*MusicaDaBatalha = MUSICABATALHA;
						
						*InimigoIndice = InteracaoN;
						
						*PodeFazerInteracao = false;
						*podeFugirVar = true;
						*IniciarBatalha = true;
						
						//Iniciar um dialogo
						*Arquivo = (char *)malloc(sizeof(char) * 17);
				    	strcpy(*Arquivo, "Textos/Teste.txt");
				    	
				    	*DialogoPosX = 229,
						*DialogoPosY = 435,
						*DialogoPartToStart = 81,
						*DialogoPartToStop = 92;
						
				    	*PodeFazerInteracao = false;
				    	*CaixaDeTexto = true;
					}
				}
				
				InteracaoN = 1;
				if(InimigosVivos[InteracaoN] == true && *PodeFazerInteracao == true)
				{
					if((PosX < InimigosPosicoes[InteracaoN].DisX + InimigosPosicoes[InteracaoN].LarX + CPosX) && (PosX + PLarX > InimigosPosicoes[InteracaoN].DisX + CPosX) && (PosY < InimigosPosicoes[InteracaoN].DisY + InimigosPosicoes[InteracaoN].LarY + CPosY) && (PosY + PLarY > InimigosPosicoes[InteracaoN].DisY + CPosY))
					{
						//Tirar os itens da lista de mobs.
						while(*mob != NULL)
						{
							a = *mob;
							*mob = lista_retira(*mob, a->id);
						}
						
						//Adicionar os novos mobs
						*mob = lista_insere(*mob, 2, wumpus, 5, 10, 80, 9, 20, 2, 60, 10);
						*mob = lista_insere(*mob, 1, caracol, 8, 5, 50, 6, 5, 3, 50, 10);
						
						*MusicaDaBatalha = MUSICABATALHA;
						
						*InimigoIndice = InteracaoN;
						
						*PodeFazerInteracao = false;
						*podeFugirVar = true;
						*IniciarBatalha = true;
					}
				}
				
				InteracaoN = 2;
				if(InimigosVivos[InteracaoN] == true && *PodeFazerInteracao == true)
				{
					if((PosX < InimigosPosicoes[InteracaoN].DisX + InimigosPosicoes[InteracaoN].LarX + CPosX) && (PosX + PLarX > InimigosPosicoes[InteracaoN].DisX + CPosX) && (PosY < InimigosPosicoes[InteracaoN].DisY + InimigosPosicoes[InteracaoN].LarY + CPosY) && (PosY + PLarY > InimigosPosicoes[InteracaoN].DisY + CPosY))
					{
						//Tirar os itens da lista de mobs.
						while(*mob != NULL)
						{
							a = *mob;
							*mob = lista_retira(*mob, a->id);
						}
						
						//Adicionar os novos mobs
						*mob = lista_insere(*mob, 1, wumpus, 5, 10, 80, 9, 20, 2, 60, 10);
						*mob = lista_insere(*mob, 2, caracol, 8, 5, 50, 6, 5, 3, 50, 10);
						*mob = lista_insere(*mob, 3, wumpus, 5, 10, 80, 9, 20, 2, 60, 10);
						
						*MusicaDaBatalha = MUSICABATALHA;
						
						*InimigoIndice = InteracaoN;
						
						*PodeFazerInteracao = false;
						*podeFugirVar = true;
						*IniciarBatalha = true;
					}
				}
				
				InteracaoN = 3;
				if(InimigosVivos[InteracaoN] == true && *PodeFazerInteracao == true)
				{
					if((PosX < InimigosPosicoes[InteracaoN].DisX + InimigosPosicoes[InteracaoN].LarX + CPosX) && (PosX + PLarX > InimigosPosicoes[InteracaoN].DisX + CPosX) && (PosY < InimigosPosicoes[InteracaoN].DisY + InimigosPosicoes[InteracaoN].LarY + CPosY) && (PosY + PLarY > InimigosPosicoes[InteracaoN].DisY + CPosY))
					{
						//Tirar os itens da lista de mobs.
						while(*mob != NULL)
						{
							a = *mob;
							*mob = lista_retira(*mob, a->id);
						}
						
						//Adicionar os novos mobs
						*mob = lista_insere(*mob, 1, wumpus, 5, 10, 80, 9, 20, 2, 60, 10);
						*mob = lista_insere(*mob, 2, golem, 15, 20, 50, 6, 8, 1, 100, 15);
						*mob = lista_insere(*mob, 3, caracol, 8, 5, 50, 6, 5, 3, 50, 10);
						
						*MusicaDaBatalha = MUSICABATALHA;
						
						*InimigoIndice = InteracaoN;
						
						*PodeFazerInteracao = false;
						*podeFugirVar = true;
						*IniciarBatalha = true;
					}
				}
				
				InteracaoN = 4;
				if(InimigosVivos[InteracaoN] == true && *PodeFazerInteracao == true)
				{
					if((PosX < InimigosPosicoes[InteracaoN].DisX + InimigosPosicoes[InteracaoN].LarX + CPosX) && (PosX + PLarX > InimigosPosicoes[InteracaoN].DisX + CPosX) && (PosY < InimigosPosicoes[InteracaoN].DisY + InimigosPosicoes[InteracaoN].LarY + CPosY) && (PosY + PLarY > InimigosPosicoes[InteracaoN].DisY + CPosY))
					{
						//Tirar os itens da lista de mobs.
						while(*mob != NULL)
						{
							a = *mob;
							*mob = lista_retira(*mob, a->id);
						}
						
						//Adicionar os novos mobs
						*mob = lista_insere(*mob, 1, wumpus, 10, 10, 80, 9, 20, 2, 60, 10);
						*mob = lista_insere(*mob, 2, golem, 15, 20, 50, 6, 8, 1, 100, 15);
						*mob = lista_insere(*mob, 3, wumpus, 10, 10, 80, 9, 20, 2, 60, 10);
						
						*MusicaDaBatalha = MUSICABATALHA;
						
						*InimigoIndice = InteracaoN;
						
						*PodeFazerInteracao = false;
						*podeFugirVar = true;
						*IniciarBatalha = true;
					}
				}
				
				InteracaoN = 5;
				if(InimigosVivos[InteracaoN] == true && *PodeFazerInteracao == true)
				{
					if((PosX < InimigosPosicoes[InteracaoN].DisX + InimigosPosicoes[InteracaoN].LarX + CPosX) && (PosX + PLarX > InimigosPosicoes[InteracaoN].DisX + CPosX) && (PosY < InimigosPosicoes[InteracaoN].DisY + InimigosPosicoes[InteracaoN].LarY + CPosY) && (PosY + PLarY > InimigosPosicoes[InteracaoN].DisY + CPosY))
					{
						//Tirar os itens da lista de mobs.
						while(*mob != NULL)
						{
							a = *mob;
							*mob = lista_retira(*mob, a->id);
						}
						
						//Adicionar os novos mobs
						*mob = lista_insere(*mob, 1, wumpus, 20, 20, 100, 9, 50, 2, 300, 100);
						*mob = lista_insere(*mob, 2, golem, 30, 30, 70, 6, 10, 1, 400, 150);
						*mob = lista_insere(*mob, 3, caracol, 18, 10, 80, 6, 5, 3, 350, 100);
						
						*MusicaDaBatalha = MUSICACHEFE;
						
						*InimigoIndice = InteracaoN;
						
						*PodeFazerInteracao = false;
						*podeFugirVar = false;
						*IniciarBatalha = true;
						
						//Iniciar um dialogo
						*Arquivo = (char *)malloc(sizeof(char) * 17);
				    	strcpy(*Arquivo, "Textos/Teste.txt");
				    	
				    	*DialogoPosX = 229,
						*DialogoPosY = 435,
						*DialogoPartToStart = 43,
						*DialogoPartToStop = 79;
						
				    	*PodeFazerInteracao = false;
				    	*CaixaDeTexto = true;
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
				
				/*
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
				*/
				
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
