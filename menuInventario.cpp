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

void DrawMenu(Personagens* li, Consumivel** lista_consumiveis, void* Sprites_Retratos[], void* Sprites_Retratos_Mascaras[], void* Sprites_HUD[], void* Sprites_HUD_Mascaras[])
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
	
	char Texto[30] = "Texto",
		 HpTexto[4] = "999";
	
	bool Voltar = false,
		 SairDoMenu = false;
	int resultQuadrado;
	//Variável usada para percorrer a lista
	Personagens *a = lista_cria();
	Consumivel *lcAux = lista_consumiveis_cria();
	
	char Tecla = 0;
	int PG = 0;
	long long unsigned Gt1, Gt2;
	int FPS = 60;
	
	Gt1 = GetTickCount();
  	Gt2 = Gt1;
			
	while(SairDoMenu == false)
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
//			setbkcolor(RGB(50, 50, 50));
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
				
//				circle(60, 60, 40);
//				line(60, 20, 310, 20);
//			 	line(60, 100, 310, 100);
//			  	line(310, 20, 310, 100);
//			  	circle(400, 60, 40);
//			 	line(400, 20, 650, 20);
//			  	line(400, 100, 650, 100);
//			  	line(650, 20, 650, 100);
//			  	circle(740, 60, 40);
//			  	line(740, 20, 990, 20);
//			  	line(740, 100, 990, 100);
//			  	line(990, 20, 990, 100);
		    
			  	for (i; i <= 4; i++)
				{
			  		rectangle(x, y, x + (166.5), y + 160);
			  		circle (c, (y + 160), 12);
			  		itoa(i+1, btn, 10);
			  		outtextxy(c-5, y + 153, btn);
			  		resultQuadrado = c-5;
			  		x += 166.5;
			  		c += 166.5;
				}
			  	
			  	//Itens
			  	rectangle(60, 340, 500, 530);
			  	rectangle(500, 340, 960, 530);
			  	
			  	//Nomes dos personagens e HPs
			  	for(int i = 0; i < iMax; i++)
				{
					a = lista_busca(li, ArrayIds[i]);
					
					putimage(20+(340*i), 20, Sprites_HUD_Mascaras[MENUINVENTARIO1], AND_PUT);
					putimage(20+(340*i), 20, Sprites_HUD[MENUINVENTARIO1], OR_PUT);
					
					strcpy(Texto, a->nome);
					
					if(a->hp > 0)
					{
						retratoDeBatalha(20+(340*i), 20+(-73*i), Texto, RETRATOBATALHANORMAL, i, Sprites_Retratos, Sprites_Retratos_Mascaras);
					}
					else
					{
						retratoDeBatalha(20+(340*i), 20+(-73*i), Texto, RETRATOBATALHANOCAUTEADO, i, Sprites_Retratos, Sprites_Retratos_Mascaras);
					}
					
//					outtextxy(70 + 85 + 10, 50 + (73 * i) + 30, Texto);
					
					strcpy(Texto, a->nome);
					
					outtextxy(150 + (340*i), 30, Texto);
					
					strcpy(Texto, "HP: ");
					
					itoa(a->hp, HpTexto, 10);
					strcat(Texto, HpTexto);
					strcat(Texto, " / ");
					
					itoa(a->hpmax, HpTexto, 10);
					strcat(Texto, HpTexto);
					
					outtextxy(150 + (340*i), 50, Texto);
					
					strcpy(Texto, "Nivel: ");
					
					itoa(a->levels, HpTexto, 10);
					strcat(Texto, HpTexto);
					
					outtextxy(150 + (340*i), 70, Texto);
//					
//					strcpy(Texto, "Exp para o");
//					outtextxy(190 + (340*i), 70, Texto);
//					
//					strcpy(Texto, "proximo nivel:");
//					outtextxy(210 + (340*i), 70, Texto);
//					
//					itoa((((a->levels * 10) + (a->levels + 1) * 10) - a->exp), Texto, 10);
//					outtextxy(199 + 85 + 132 + 142 + 170 + 10, 140 + 75 + (73 * i) + 30, Texto);
				}
				
				
				memset(btn, 0, sizeof btn);
			}
			//Menu de Itens
		  	if(MenuID == 1)
			{
				//Cria a lista com os tipos dos itens
				iMaxItens = 0;
				for(lcAux = *lista_consumiveis; lcAux != NULL; lcAux = lcAux->prox)
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
							lcAux = lista_consumiveis_busca(*lista_consumiveis, ArrayIdsItens[i]);
							
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
							
														
							switch (ArrayIdsItens[Selecao])
							{
								case POCAO:
						            outtextxy(540, 60, "Recupera 80 de vida.");
						            outtextxy(540, 80, "N?o revive um personagem morto.");
						            break;
						        case POCAO2:
						            outtextxy(540, 60, "Recupera 200 de vida.");
						            outtextxy(540, 80, "N?o revive um personagem morto.");
						            break;
					            case POCAO3:
					            	outtextxy(540, 60, "Recupera 500 de vida.");
					            	outtextxy(540, 80, "N?o revive um personagem morto.");
					            	break;
					            case CAFE:
					            	outtextxy(540, 60, "Revive um personagem morto ");
					            	outtextxy(540, 80, "com metade de sua vida m?xima.");
					            	break;
						        default:
						            printf("\n");
							}
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
				
				
				switch (ArrayIds[Selecao])
				{
					case 1:
			            outtextxy(540, 60, "Esta sou eu, Lily. Eu vim lá de cima,");
			            outtextxy(540, 80, "de um vilarejo rodeado por campos de flores.");
			            outtextxy(540, 100, "Não há muito o que falar da minha casa. Resumo: Lá");
			            outtextxy(540, 120, "se planta muita cenoura e batata-doce. Acho que é isso.");
			            outtextxy(540, 140, "Como toda boa raposa, eu sou muito curiosa.");
			            outtextxy(540, 160, "Portanto, do começo do dia até o fim dele, eu estou");
			            outtextxy(540, 180, "correndo e explorando por aí.");
			            outtextxy(540, 220, "Em um dia qualquer, eu acabei indo meio longe");
			            outtextxy(540, 240, "na floresta. Lá encontrei um coelho de características...");
			            outtextxy(540, 260, "Peculiares. Eu o persegui até cair em um buraco profundo,");
			            outtextxy(540, 280, "e agora estava presa em uma caverna.");
			            outtextxy(540, 300, "Até hoje é difícil acreditar no que eu vi:");
			            outtextxy(540, 320, "A caverna era tão grande que não dava para ver o outro lado,"); 
						outtextxy(540, 340, "e uma cidade subterrânea cintilava no horizonte.");
						outtextxy(540, 360, "Casas e monumentos pontudos que alcançam o topo.");
						outtextxy(540, 380, "Máquinas se mexem por toda parte, poluindo o ar com fumaças.");
						outtextxy(540, 400, "Criaturas negras, prateadas e douradas andando pelas ruas.");
			            outtextxy(580, 500, "Foi assim que cheguei à cidade de Dark Gears.");
			            
			            break;
			        case 2:
			            outtextxy(540, 60, "Este é Chaddrit.");
			            outtextxy(540, 80, "Eu não sei muito sobre ele não, mas pelo que sei,");
			            outtextxy(540, 100, "Ele também é parte metal, parte animal, como todo mundo");
			            outtextxy(540, 120, "aqui em Dark Gears.");
			            outtextxy(540, 160, "Será que ele é amigo? Parece ser. Ele tentou me");
			            outtextxy(540, 180, "ajudar a voltar para casa, mas fomos atacados por um");
			            outtextxy(540, 200, "morcego que parecia odiar muito a gente.");
			            outtextxy(540, 220, "Estranho, eu nunca nem vi ele na vida.");
			            outtextxy(540, 240, "Ganhamos a batalha mas Chaddrit ficou machucado demais,");
			            outtextxy(540, 260, "e agora sinto que preciso ajudá-lo.");
			            break;
		            case 3:
		            	outtextxy(540, 60, "");
		            	outtextxy(540, 80, "");
		            	break;
			        default:
			            printf("\n");
				}
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
			if(Tecla == MENU)
			{	
				SairDoMenu = true;
			}
			if (MenuID == 0)
			{
				if(Tecla == TECLABACKSPACE)
				{	
					SairDoMenu = true;
				}
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
					if(Tecla == TECLABACKSPACE)
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
						if(*lista_consumiveis != NULL)
						{
							lcAux = lista_consumiveis_busca(*lista_consumiveis, ArrayIdsItens[Selecao]);
							
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
					if(Tecla == TECLABACKSPACE)
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
								reproduzirSom(SOMDECURA2);
								
								lcAux = lista_consumiveis_busca(*lista_consumiveis, SelecaoItem);
								
								if(lcAux->qtd <= 1)
								{
									Voltar = true;
								}
								
								*lista_consumiveis = utilizar_consumivel(*lista_consumiveis, SelecaoItem, li, ArrayIds[Selecao]);
								
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
								reproduzirSom(SOMDECURA2);
								
								lcAux = lista_consumiveis_busca(*lista_consumiveis, SelecaoItem);
								
								if(lcAux->qtd <= 1)
								{
									Voltar = true;
								}
								
								*lista_consumiveis = utilizar_consumivel(*lista_consumiveis, SelecaoItem, li, ArrayIds[Selecao]);
								
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
				if(Tecla == TECLABACKSPACE)
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
				if(Tecla == TECLABACKSPACE)
				{	
					MenuID = 0;
				}
			}
			//Menu de personagens
			if(MenuID == 4)
			{
				if(Tecla == TECLABACKSPACE)
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
				if(Tecla == TECLABACKSPACE)
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
	
	reproduzirSom(CURSORVOLTA);
	
	free(ArrayIds);
	free(ArrayIdsItens);
	free(ArrayIdsAux);
}
