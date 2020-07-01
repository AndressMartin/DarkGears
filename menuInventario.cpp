#include "structs.h"
#include "enums.h"
#include "listaEncadeadaPersonagem.h"
#include "reproduzirSons.h"
#include "batalha.h"

#include<stdio.h>
#include<graphics.h>
#include<conio.h>

#define ESC  27
#define One  49
#define Two  50
#define Three 51
#define Four 52
#define Five 53
#define MENU 112

#define LEFT   	75
#define RIGHT  	77
#define UP     	72
#define DOWN   	80

#define TECLAENTER		13
#define TECLABACKSPACE	8

void DrawMenu(Personagens* li, Consumivel* lista_consumiveis, void* Sprites_Retratos[], void* Sprites_Retratos_Mascaras[], void* Sprites_HUD[], void* Sprites_HUD_Mascaras[])
{
	int i = 0;

	float x = 83.5;
	float y = 140;
	float c = 166.5;
	char btn[7];
	
	int itemCont = 0;
	int yItem = 50;
	
	int skillCont = 0;
	int ySkill = 50;
	
	int equipCont = 0;
	int yEquip = 50;
	
	int personCont = 0;
	int yPerson = 50;
	
	int beastCont = 0;
	int yBeast = 50;
	
	int iMax = 0,
		iMaxItens = 0,
		itensScroll = 0,
		itensScroll2 = 0,
		Selecao = 0,
		SelecaoItem = 0,
		MenuID = 0,
		MenuID2 = 0;
	
	int *ArrayIds = NULL,
		*ArrayIdsItens = NULL,
		*ArrayIdsAux = NULL;
	
	char Texto[30] = "Texto";
	
	bool Voltar = false;
	
	//Variável usada para percorrer a lista
	Personagens *a = lista_cria();
	Consumivel *lcAux = lista_consumiveis_cria();
	
	char Tecla = 0;
	int PG = 0;
	long long unsigned Gt1, Gt2;
	int FPS = 60;
	
	Gt1 = GetTickCount();
  	Gt2 = Gt1;
			
	while(Tecla != MENU)
	{	
		Gt2 = GetTickCount();
		if(Gt2 < Gt1)
		{
			Gt1 = Gt2;
		}
		if (Gt2 - Gt1 > 1000/FPS)
		{
			Gt1 = Gt2;
			
			//Alterna a pagina de desenho ativa (para fazer o Buffer Duplo).
			if(PG == 1)
			{
				PG = 2;
			}
			else
			{
				PG = 1;
			}
			setactivepage(PG);
			
			//Mostrar os status dos personagens.
			//Para isso, ele fara um array com os Ids e depois o invertera, para caso a ordem dos Ids nao seja crescente.
			iMax = 0;
			for(a = li; a != NULL; a = a->prox)
			{
				iMax ++;
				ArrayIds = (int *)realloc(ArrayIds, sizeof(int) * iMax);
				ArrayIds[iMax - 1] = a->id;
			}
			
			//Inverter os elementos do array dos personagens
			ArrayIdsAux = (int *)realloc(ArrayIdsAux, sizeof(int) * iMax);
			for(i = 0; i < iMax; i++)
			{
				ArrayIdsAux[iMax - 1 - i] = ArrayIds[i];
			}
			for(i = 0; i < iMax; i++)
			{
				ArrayIds[i] = ArrayIdsAux[i];
			}
			
			//Fundo e cenario
			setbkcolor(RGB(50, 50, 50));
			cleardevice();
			
			setbkcolor(RGB(233, 200, 70));
			setcolor(RGB(0, 0, 0));
			setlinestyle(0, 0, 1);
			
			rectangle(12, 13, 1012, 563);
			if (MenuID == 0)
			{
				i = 0;
				x = 83.5;
				c = 166.5;
				
				circle(60, 60, 40);
				line(60, 20, 310, 20);
			 	line(60, 100, 310, 100);
			  	line(310, 20, 310, 100);
			  	circle(400, 60, 40);
			 	line(400, 20, 650, 20);
			  	line(400, 100, 650, 100);
			  	line(650, 20, 650, 100);
			  	circle(740, 60, 40);
			  	line(740, 20, 990, 20);
			  	line(740, 100, 990, 100);
			  	line(990, 20, 990, 100);
		    
			  	for (i; i <= 4; i++)
				{
			  		rectangle(x, y, x + (166.5), y + 160);
			  		circle (c, (y + 160), 12);
			  		itoa(i+1, btn, 10);
			  		outtextxy(c-5, y + 153, btn);
			  		x += 166.5;
			  		c += 166.5;
				}
			  	
			  	//Itens
			  	rectangle(60, 340, 500, 530);
			  	rectangle(500, 340, 960, 530);
			  	
			  	//1st Char
			  	outtextxy(150, 30, "12/30");
			  	outtextxy(140, 50, "EXP: 148");
			  	circle (132, 38, 10);
			  	circle (80, 100, 13);
			  	
			  	//2nd Char
			  	outtextxy(490, 30, "24/45");
			  	outtextxy(480, 50, "EXP: 383");
			  	circle (472, 38, 10);
			  	circle (422, 100, 13);
			  	
			  	//3rd Char
			  	outtextxy(830, 30, "999/999");
			  	outtextxy(820, 50, "EXP: ¨@#$!@#");
			  	circle (812, 38, 10);
			  	circle (762, 100, 13);
				
				memset(btn, 0, sizeof btn);
			}
			//Menu de Itens
		  	if(MenuID == 1)
			{
				//Cria a lista com os tipos dos itens
				iMaxItens = 0;
				for(lcAux = lista_consumiveis; lcAux != NULL; lcAux = lcAux->prox)
				{
					iMaxItens ++;
					ArrayIdsItens = (int *)realloc(ArrayIdsItens, sizeof(int) * iMaxItens);
					ArrayIdsItens[iMaxItens - 1] = lcAux->tipo;
				}
				
				//Inverter os elementos do array dos itens
				ArrayIdsAux = (int *)realloc(ArrayIdsAux, sizeof(int) * iMaxItens);
				for(i = 0; i < iMaxItens; i++)
				{
					ArrayIdsAux[iMaxItens - 1 - i] = ArrayIdsItens[i];
				}
				for(i = 0; i < iMaxItens; i++)
				{
					ArrayIdsItens[i] = ArrayIdsAux[i];
				}
				
				rectangle(12, 13, 1012, 563);
				rectangle(60, 40, 480, 530);
				rectangle(520, 40, 960, 530);
				
				if(MenuID2 == 0)
				{
					itensScroll2 = 0;
					//Mostrar os itens disponiveis para usar
					for(i = 0; i < iMaxItens; i++)
					{
						if((i >= itensScroll) && (i - itensScroll < 6))
						{
							lcAux = lista_consumiveis_busca(lista_consumiveis, ArrayIdsItens[i]);
							
						    putimage(70, 50 + (73 * itensScroll2), Sprites_HUD_Mascaras[MENUBATALHA4], AND_PUT);
							putimage(70, 50 + (73 * itensScroll2), Sprites_HUD[MENUBATALHA4], OR_PUT);
							
							strcpy(Texto, lcAux->nome);
							
							retratoDeBatalha(70, 50, Texto, RETRATOBATALHANORMAL, itensScroll2, Sprites_Retratos, Sprites_Retratos_Mascaras);
							
							// ! - O settextstyle faz o jogo bugar depois de um tempo.
							//settextstyle(0, 0, 0);
							outtextxy(70 + 85 + 10, 50 + (73 * itensScroll2) + 30, Texto);
							
							itoa(lcAux->qtd, Texto, 10);
							
							//settextstyle(1, 0, 3);
							outtextxy(70 + 325 + 15, 50 + (73 * itensScroll2) + 30, Texto);
							
							itensScroll2 ++;
						}
					}
					
					putimage(70 + 410, 50 + (73 * (Selecao - itensScroll)), Sprites_HUD_Mascaras[SELECAOM], AND_PUT);
					putimage(70 + 410, 50 + (73 * (Selecao - itensScroll)), Sprites_HUD[SELECAOM], OR_PUT);
				}
				
				if(MenuID2 == 1)
				{
					//Mostrar os aliados disponiveis para selecionar
					for(i = 0; i < iMax; i++)
					{
						a = lista_busca(li, ArrayIds[i]);
					
					    putimage(70, 50 + (73 * i), Sprites_HUD_Mascaras[MENUBATALHA3], AND_PUT);
						putimage(70, 50 + (73 * i), Sprites_HUD[MENUBATALHA3], OR_PUT);
						
						strcpy(Texto, a->nome);
						
						if(a->hp > 0)
						{
							retratoDeBatalha(70, 50, Texto, RETRATOBATALHANORMAL, i, Sprites_Retratos, Sprites_Retratos_Mascaras);
						}
						else
						{
							retratoDeBatalha(70, 50, Texto, RETRATOBATALHANOCAUTEADO, i, Sprites_Retratos, Sprites_Retratos_Mascaras);
						}
						
						outtextxy(70 + 85 + 10, 50 + (73 * i) + 30, Texto);
					}
					
					putimage(70 + 326, 50 + (73 * Selecao), Sprites_HUD_Mascaras[SELECAOM], AND_PUT);
					putimage(70 + 326, 50 + (73 * Selecao), Sprites_HUD[SELECAOM], OR_PUT);
				}
				
				/*
				itemCont = 0;
				yItem = 50;
				
				//Itens Disponiveis
				for (itemCont; itemCont < qntItens; itemCont++)
				{
					if (yItem+50 < 530)
					{
						rectangle(70, yItem, 470, yItem+50);
						line(150, yItem, 150, yItem+50);
						outtextxy(150+20, yItem+20, (itemNames[itemCont]));
						yItem+= 55;
					}
				}
				printf("1.");
				*/
			}
			//Menu de habilidades
			if(MenuID == 2)
			{
				/*
				skillCont = 0;
				ySkill = 50;
				
				rectangle(12, 13, 1012, 563);
				rectangle(60, 40, 480, 530);
				rectangle(520, 40, 960, 530);
				
				//Itens Disponiveis
				for (skillCont; skillCont < qntSkills; skillCont++)
				{
					if (ySkill+50 < 530)
					{
						rectangle(70, ySkill, 470, ySkill+50);
						line(150, ySkill, 150, ySkill+50);
						outtextxy(150+20, ySkill+20, (skillNames[skillCont]));
						ySkill+= 55;
					}
				}
				
				printf("2.");
				*/
			}
			//Menu de equipamentos
			if(MenuID == 3)
			{
				/*
				equipCont = 0;
				yEquip = 50;
				
				rectangle(12, 13, 1012, 563);
				rectangle(60, 40, 480, 530);
				rectangle(520, 40, 960, 530);
				
				//Itens Disponiveis
				for (equipCont; equipCont < qntEquip; equipCont++)
				{
					if (yEquip+50 < 530)
					{
						rectangle(70, yEquip, 470, yEquip+50);
						line(150, yEquip, 150, yEquip+50);
						outtextxy(150+20, yEquip+20, (equipNames[equipCont]));
						yEquip+= 55;
					}
				}
				
				printf("3.");
				*/
			}
			//Menu de personagens
			if(MenuID == 4)
			{	
				rectangle(12, 13, 1012, 563);
				rectangle(60, 40, 480, 530);
				rectangle(520, 40, 960, 530);
				
				//Mostrar os aliados disponiveis para selecionar
				for(i = 0; i < iMax; i++)
				{
					a = lista_busca(li, ArrayIds[i]);
				
				    putimage(70, 50 + (73 * i), Sprites_HUD_Mascaras[MENUBATALHA3], AND_PUT);
					putimage(70, 50 + (73 * i), Sprites_HUD[MENUBATALHA3], OR_PUT);
					
					strcpy(Texto, a->nome);
					
					if(a->hp > 0)
					{
						retratoDeBatalha(70, 50, Texto, RETRATOBATALHANORMAL, i, Sprites_Retratos, Sprites_Retratos_Mascaras);
					}
					else
					{
						retratoDeBatalha(70, 50, Texto, RETRATOBATALHANOCAUTEADO, i, Sprites_Retratos, Sprites_Retratos_Mascaras);
					}
					
					outtextxy(70 + 85 + 10, 50 + (73 * i) + 30, Texto);
				}
				
				putimage(70 + 326, 50 + (73 * Selecao), Sprites_HUD_Mascaras[SELECAOM], AND_PUT);
				putimage(70 + 326, 50 + (73 * Selecao), Sprites_HUD[SELECAOM], OR_PUT);
				
				/*
				personCont = 0;
				yPerson = 50;
				
				//Itens Disponiveis
				for (personCont; personCont < qntPersons; personCont++)
				{
					if (yPerson+50 < 530)
					{
						rectangle(70, yPerson, 470, yPerson+50);
						line(150, yPerson, 150, yPerson+50);
						outtextxy(150+20, yPerson+20, (personNames[personCont]));
						yPerson+= 55;
					}
				}
				
				printf("4.");
				*/
			}
			//Bestiário
			if(MenuID == 5)
			{
				/*
				beastCont = 0;
				yBeast = 50;
				
				rectangle(12, 13, 1012, 563);
				rectangle(60, 40, 480, 530);
				rectangle(520, 40, 960, 530);
				
				//Itens Disponiveis
				for (beastCont; beastCont < qntBeasts; beastCont++)
				{
					if (yBeast+50 < 530)
					{
						rectangle(70, yBeast, 470, yBeast+50);
						line(150, yBeast, 150, yBeast+50);
						outtextxy(150+20, yBeast+20, (beastNames[beastCont]));
						yBeast+= 55;
					}
				}
				
				printf("5.");
				*/
			}
		  	
		  	//Torna visivel a pagina de desenho.
			setvisualpage(PG);
			
			//Acoes
			if (MenuID == 0)
			{
			  	if(Tecla == One)
				{	
					reproduzirSom(CURSORMOVE);
							
					SelecaoItem = 0;
					MenuID = 1;
					MenuID2 = 0;
					itensScroll = 0;
					Selecao = 0;
				}
				if(Tecla == Two)
				{	
					MenuID = 2;
				}
				if(Tecla == Three)
				{	
					MenuID = 3;
				}
				if(Tecla == Four)
				{	
					reproduzirSom(CURSORMOVE);
					
					MenuID = 4;
					Selecao = 0;
				}
				if(Tecla == Five)
				{	
					MenuID = 5;
				}
			}
			//Menu de Itens
		  	if(MenuID == 1)
			{
				if(MenuID2 == 0)
				{
					if(Tecla == ESC)
					{	
						reproduzirSom(CURSORVOLTA);
						MenuID = 0;
					}
					if((Tecla == UP || Tecla == LEFT) && (Selecao > 0))
					{
						reproduzirSom(CURSORMOVE);
						
						Selecao --;
						if(Selecao < itensScroll)
						{
							itensScroll = Selecao;
						}
					}
					if((Tecla == DOWN || Tecla == RIGHT) && (Selecao < iMaxItens - 1))
					{
						reproduzirSom(CURSORMOVE);
						
						Selecao ++;
						if(Selecao - itensScroll > 5)
						{
							itensScroll = Selecao - 2;
						}
					}
					if(Tecla == TECLAENTER)
					{				
						if(lista_consumiveis != NULL)
						{
							lcAux = lista_consumiveis_busca(lista_consumiveis, ArrayIdsItens[Selecao]);
							
							if(lcAux->qtd > 0)
							{
								reproduzirSom(CURSORMOVE);
								
								SelecaoItem = ArrayIdsItens[Selecao];
								MenuID2 = 1;
								Voltar = false;
								Selecao = 0;
								
								Tecla = 0;
							}
							else
							{
								reproduzirSom(CURSORERRO);
							}
						}
						else
						{
							reproduzirSom(CURSORERRO);
						}
					}
				}
				if(MenuID2 == 1)
				{
					if(Tecla == ESC)
					{
						reproduzirSom(CURSORVOLTA);
						
						MenuID2 = 0;
						itensScroll = 0;
						Selecao = 0;
					}
					if((Tecla == UP || Tecla == LEFT) && (Selecao > 0))
					{
						reproduzirSom(CURSORMOVE);
						Selecao --;
					}
					if((Tecla == DOWN || Tecla == RIGHT) && (Selecao < iMax - 1))
					{
						reproduzirSom(CURSORMOVE);
						Selecao ++;
					}
					if(Tecla == TECLAENTER)
					{
						if(SelecaoItem == POCAO || SelecaoItem == POCAO2 || SelecaoItem == POCAO3)
						{
							a = lista_busca(li, ArrayIds[Selecao]);
							
							if(a->hp > 0)
							{
								reproduzirSom(CURSORMOVE);
								
								lcAux = lista_consumiveis_busca(lista_consumiveis, SelecaoItem);
								
								if(lcAux->qtd <= 1)
								{
									Voltar = true;
								}
								
								li = utilizar_consumivel(lista_consumiveis, SelecaoItem, li, ArrayIds[Selecao]);
								
								if(Voltar == true)
								{
									MenuID2 = 0;
									itensScroll = 0;
									Selecao = 0;
								}
							}
							else
							{
								reproduzirSom(CURSORERRO);
							}
						}
						else if(SelecaoItem == CAFE)
						{
							a = lista_busca(li, ArrayIds[Selecao]);
							
							if(a->hp <= 0)
							{
								reproduzirSom(CURSORMOVE);
								
								lcAux = lista_consumiveis_busca(lista_consumiveis, SelecaoItem);
								
								if(lcAux->qtd <= 1)
								{
									Voltar = true;
								}
								
								li = utilizar_consumivel(lista_consumiveis, SelecaoItem, li, ArrayIds[Selecao]);
								
								if(Voltar == true)
								{
									MenuID2 = 0;
									itensScroll = 0;
									Selecao = 0;
								}
							}
							else
							{
								reproduzirSom(CURSORERRO);
							}
						}
					}
				}
			}
			//Menu de habilidades
			if(MenuID == 2)
			{
				if(Tecla == ESC)
				{	
					MenuID = 0;
				}
				if((Tecla == UP || Tecla == LEFT) && (Selecao > 0))
				{
					reproduzirSom(CURSORMOVE);
					
					Selecao --;
					if(Selecao < itensScroll)
					{
						itensScroll = Selecao;
					}
				}
				if((Tecla == DOWN || Tecla == RIGHT) && (Selecao < iMaxItens - 1))
				{
					reproduzirSom(CURSORMOVE);
					
					Selecao ++;
					if(Selecao - itensScroll > 2)
					{
						itensScroll = Selecao - 2;
					}
				}
			}
			//Menu de equipamentos
			if(MenuID == 3)
			{
				if(Tecla == ESC)
				{	
					MenuID = 0;
				}
			}
			//Menu de personagens
			if(MenuID == 4)
			{
				if(Tecla == ESC)
				{	
					reproduzirSom(CURSORVOLTA);
					MenuID = 0;
				}
				if((Tecla == UP || Tecla == LEFT) && (Selecao > 0))
				{
					reproduzirSom(CURSORMOVE);
					Selecao --;
				}
				if((Tecla == DOWN || Tecla == RIGHT) && (Selecao < iMax - 1))
				{
					reproduzirSom(CURSORMOVE);
					Selecao ++;
				}
			}
			//Bestiário
			if(MenuID == 5)
			{
				if(Tecla == ESC)
				{	
					MenuID = 0;
				}
			}
		  	
		  	fflush(stdin);
			Tecla = 0;
			if(kbhit())
			{
				Tecla = getch();
				//printf("%d", Tecla);
			}
		}
	}
	
	free(ArrayIds);
	free(ArrayIdsItens);
	free(ArrayIdsAux);
}
