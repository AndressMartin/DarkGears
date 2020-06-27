#include "structs.h"
#include "enums.h"
#include "ListaEncadeadaPersonagem.h"

#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<string.h>

#define TECLAA			97
#define TECLAS			115
#define TECLAZ			122
#define TECLAX			120
#define TECLAENTER		13
#define TECLABACKSPACE	8

#define LEFT   	75
#define RIGHT  	77
#define UP     	72
#define DOWN   	80

#define ESC     27

void retratoDeBatalha(int PosX, char *Texto, int Tipo, int i, void* Sprites_Retratos[], void* Sprites_Retratos_Mascaras[])
{
	int Imagem = 0;
	
	char Lily[5] = "Lily",
		 Chaddrit[9] = "Chaddrit";
	
	if(strcmp(Texto, Lily) == 0)
	{
		Imagem = RBLILY;
	}
	
	if(strcmp(Texto, Chaddrit) == 0)
	{
		Imagem = RBCHADDRIT;
	}
	
	switch(Imagem)
	{
		case RBLILY:
			if(Tipo == RETRATOBATALHANORMAL)
			{
				putimage(PosX, 337 + (73 * i), Sprites_Retratos_Mascaras[2], AND_PUT);
				putimage(PosX, 337 + (73 * i), Sprites_Retratos[2], OR_PUT);
				break;	
			}
			if(Tipo == RETRATOBATALHAATACANDO)
			{
				putimage(PosX, 337 + (73 * i), Sprites_Retratos_Mascaras[3], AND_PUT);
				putimage(PosX, 337 + (73 * i), Sprites_Retratos[3], OR_PUT);
				break;	
			}
			if(Tipo == RETRATOBATALHADANO)
			{
				putimage(PosX, 337 + (73 * i), Sprites_Retratos_Mascaras[4], AND_PUT);
				putimage(PosX, 337 + (73 * i), Sprites_Retratos[4], OR_PUT);
				break;	
			}
			if(Tipo == RETRATOBATALHANOCAUTEADO)
			{
				putimage(PosX, 337 + (73 * i), Sprites_Retratos_Mascaras[5], AND_PUT);
				putimage(PosX, 337 + (73 * i), Sprites_Retratos[5], OR_PUT);
				break;
			}
		
		case RBCHADDRIT:
			if(Tipo == RETRATOBATALHANORMAL)
			{
				putimage(PosX, 337 + (73 * i), Sprites_Retratos_Mascaras[6], AND_PUT);
				putimage(PosX, 337 + (73 * i), Sprites_Retratos[6], OR_PUT);
				break;	
			}
			if(Tipo == RETRATOBATALHAATACANDO)
			{
				putimage(PosX, 337 + (73 * i), Sprites_Retratos_Mascaras[7], AND_PUT);
				putimage(PosX, 337 + (73 * i), Sprites_Retratos[7], OR_PUT);
				break;	
			}
			if(Tipo == RETRATOBATALHADANO)
			{
				putimage(PosX, 337 + (73 * i), Sprites_Retratos_Mascaras[8], AND_PUT);
				putimage(PosX, 337 + (73 * i), Sprites_Retratos[8], OR_PUT);
				break;	
			}
			if(Tipo == RETRATOBATALHANOCAUTEADO)
			{
				putimage(PosX, 337 + (73 * i), Sprites_Retratos_Mascaras[9], AND_PUT);
				putimage(PosX, 337 + (73 * i), Sprites_Retratos[9], OR_PUT);
				break;	
			}
		
		default:
			printf("\nRaios multiplos! O operador esta incorreto.");
	}
}

void desenhaMenu(Personagens* li, int *ArrayIds, int iMax, void* Sprites_Retratos[], void* Sprites_Retratos_Mascaras[], void* Sprites_HUD[], void* Sprites_HUD_Mascaras[])
{
	char *Texto = NULL,
		 HpTexto[4] = "999";
	Personagens *a;
	
	settextstyle(0, 0, 0);
	setbkcolor(RGB(159, 79, 51));
	setcolor(RGB(0, 0, 0));
	setlinestyle(0, 0, 1);
	
	putimage(27, 337, Sprites_HUD_Mascaras[MENUBATALHA1], AND_PUT);
	putimage(27, 337, Sprites_HUD[MENUBATALHA1], OR_PUT);
	
	for(int i = 0; i < iMax; i++)
	{
		a = lista_busca(li, ArrayIds[i]);
	
	    putimage(537, 337 + (73 * i), Sprites_HUD_Mascaras[MENUBATALHA2], AND_PUT);
		putimage(537, 337 + (73 * i), Sprites_HUD[MENUBATALHA2], OR_PUT);
		
		Texto = (char *)realloc(Texto, sizeof(char) * 10);
		strcpy(Texto, a->nome);
		
		if(a->hp > 0)
		{
			retratoDeBatalha(537, Texto, RETRATOBATALHANORMAL, i, Sprites_Retratos, Sprites_Retratos_Mascaras);
		}
		else
		{
			retratoDeBatalha(537, Texto, RETRATOBATALHANOCAUTEADO, i, Sprites_Retratos, Sprites_Retratos_Mascaras);
		}
		
		outtextxy(622 + 10, 337 + (73 * i) + 28, Texto);
		
		Texto = (char *)realloc(Texto, sizeof(char) * 20);
		strcpy(Texto, "HP: ");
		
		itoa(a->hp, HpTexto, 10);
		strcat(Texto, HpTexto);
		strcat(Texto, " / ");
		
		itoa(a->hpmax, HpTexto, 10);
		strcat(Texto, HpTexto);
		
		outtextxy(754 + 10, 337 + (73 * i) + 28, Texto);
	}
}

Personagens* iniciarBatalha(Personagens* li, Personagens* mob, void* Sprites_Retratos[], void* Sprites_Retratos_Mascaras[], void* Sprites_HUD[], void* Sprites_HUD_Mascaras[], void* Sprites_Mobs[], void* Sprites_Mobs_Mascaras[], void* Sprites_Efeitos[], void* Sprites_Efeitos_Mascaras[])
{	
	srand(time(0));
	
	bool batalhaFinalizada = false;
	
	bool turnoDosPersonagens = false,
		 turnoDosMonstros = false,
		 atacando = false,
		 animacao = false,
		 personagensMortos = false,
		 monstrosMortos = false;
	
	int id = 0,
		i = 0,
		p = 0,
		q = 0,
		iMax = 0,
		iMaxMob = 0,
		iMaxMobInicial = 0,
		Turno = 0,
		Selecao = 0,
		dano = 0,
		danoCausado = 0,
		MenuID = 0,
		qtd_exp = 0,
		controleAnimacao = 0;
	
	int MobPosXInicial = 0,
		MobPosYInicial = 31,
		MobPosXDistancia = 0;
	
	int *ArrayIds = NULL,
		*ArrayIdsMob = NULL,
		*ArrayIdsMobInicial = NULL,
		*ArrayIdsAux = NULL,
		*ArrayMobPosY = NULL;
	
	ListaDosTurnosS *ListaDosTurnos = NULL;
	ListaDosTurnosS ListaDosTurnosTemp;
	int ListaDosTurnosTamanho = 0;
	
	char *Texto = NULL,
		 *Texto2 = NULL,
		 HpTexto[4] = "999";
	
	int PosYTexto;
	
	//Variável usada para percorrer a lista
	Personagens *a;
	
	turnoDosPersonagens = true;
	id = 0;
	
	int PG = 0;
	char Tecla = 0;
	long long unsigned Gt1, Gt2;
	int FPS = 60;
	
	//Define o tipo posicionamento dos inimigos
	iMaxMob = 0;
	for(a = mob; a != NULL; a = a->prox)
	{
		iMaxMob ++;
	}
	
	if(iMaxMob == 1)
	{
		MobPosXInicial = 375;
		MobPosXDistancia = 0;
	}
	
	if(iMaxMob == 2)
	{
		MobPosXInicial = 170;
		MobPosXDistancia = 409;
	}
	
	if(iMaxMob == 3)
	{
		MobPosXInicial = 59;
		MobPosXDistancia = 315;
	}

	Gt1 = GetTickCount();
  	Gt2 = Gt1;
	
	while(!(batalhaFinalizada) && Tecla != ESC)
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
			
			//Desenhos
			
			//Cria a lista com os ids dos monstros
			iMaxMob = 0;
			for(a = mob; a != NULL; a = a->prox)
			{
				if(a->hp > 0)
				{
					iMaxMob ++;
					ArrayIdsMob = (int *)realloc(ArrayIdsMob, sizeof(int) * iMaxMob);
					ArrayIdsMob[iMaxMob - 1] = a->id;
				}
			}
			
			//Inverter os elementos do array dos mobs
			ArrayIdsAux = (int *)realloc(ArrayIdsAux, sizeof(int) * iMaxMob);
			for(i = 0; i < iMaxMob; i++)
			{
				ArrayIdsAux[iMaxMob - 1 - i] = ArrayIdsMob[i];
			}
			
			for(i = 0; i < iMaxMob; i++)
			{
				ArrayIdsMob[i] = ArrayIdsAux[i];
			}
			
			if(ArrayIdsMobInicial == NULL)
			{	
				iMaxMobInicial = iMaxMob;
				ArrayIdsMobInicial = (int *)realloc(ArrayIdsMobInicial, sizeof(int) * iMaxMobInicial);
				ArrayMobPosY = (int *)realloc(ArrayMobPosY, sizeof(int) * iMaxMobInicial);
				
				for(i = 0; i < iMaxMobInicial; i++)
				{
					ArrayIdsMobInicial[i] = ArrayIdsMob[i];
				}
				
				for(i = 0; i < iMaxMobInicial; i++)
				{
					ArrayMobPosY[i] = MobPosYInicial;
				}
			}
			
			//Mostrar os status dos personagens no menu na ordem do menor id para o maior.
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
			setbkcolor(RGB(255, 255, 255));
			cleardevice();
			
			//Mostrar os mobs
			for(i = 0; i < iMaxMobInicial; i++)
			{
				a = lista_busca(mob, ArrayIdsMobInicial[i]);
				
				if(ArrayMobPosY[i] < 580)
				{
					putimage(MobPosXInicial + (MobPosXDistancia * i), ArrayMobPosY[i], Sprites_Mobs_Mascaras[a->levels - 1], AND_PUT);
					putimage(MobPosXInicial + (MobPosXDistancia * i), ArrayMobPosY[i], Sprites_Mobs[a->levels - 1], OR_PUT);
				}
			}
			
			//Menu
			desenhaMenu(li, ArrayIds, iMax, Sprites_Retratos, Sprites_Retratos_Mascaras, Sprites_HUD, Sprites_HUD_Mascaras);
			
			if(turnoDosPersonagens == true)
			{
				setlinestyle(0, 0, 2);
				setcolor(RGB(255, 242, 0));
				rectangle(537, 337 + (73 * Turno),537 + 460, 337 + (73 * Turno) + 74);
			}
			
			if(turnoDosPersonagens == true)
			{
				setcolor(RGB(0, 0, 0));
				
				if(MenuID == 0)
				{
					Texto = (char *)realloc(Texto, sizeof(char) * 15);
				
					strcpy(Texto, "A -Ataque");
					outtextxy(96, 370, Texto);
					
					strcpy(Texto, "Z -Habilidades");
					outtextxy(96, 483, Texto);
					
					strcpy(Texto, "S - Itens");
					outtextxy(358, 370, Texto);
					
					strcpy(Texto, "X - Dar no pe!");
					outtextxy(358, 483, Texto);
				}
				
				if(MenuID == 1)
				{
					//Mostrar os inimigos disponiveis para atacar
					for(i = 0; i < iMaxMob; i++)
					{
						a = lista_busca(mob, ArrayIdsMob[i]);
					
					    putimage(27, 337 + (73 * i), Sprites_HUD_Mascaras[MENUBATALHA3], AND_PUT);
						putimage(27, 337 + (73 * i), Sprites_HUD[MENUBATALHA3], OR_PUT);
						
						Texto = (char *)realloc(Texto, sizeof(char) * 10);
						strcpy(Texto, a->nome);
						
						retratoDeBatalha(27, Texto, RETRATOBATALHANORMAL, i, Sprites_Retratos, Sprites_Retratos_Mascaras);
						
						outtextxy(112 + 10, 337 + (73 * i) + 28, Texto);
					}
					
					putimage(353, 337 + (73 * Selecao), Sprites_HUD_Mascaras[SELECAOM], AND_PUT);
					putimage(353, 337 + (73 * Selecao), Sprites_HUD[SELECAOM], OR_PUT);
				}
			}
			
			//Torna visivel a pagina de desenho.
			setvisualpage(PG);
			
			//Acoes
			
			if(turnoDosPersonagens == true)
			{
				a = lista_busca(li, ArrayIds[Turno]);
				/*
				printf("\n\nTurno: %d\n", Turno);
				for(i=0; i < iMax; i++)
				{
					printf("%d, ", ArrayIds[i]);
				}
				*/
				
				if(a->hp > 0)
				{
					if(MenuID == 0)
					{
						if(Tecla == TECLAA)
						{
							MenuID = 1;
							Selecao = 0;
						}
					}
					if(MenuID == 1)
					{
						if(Tecla == TECLABACKSPACE)
						{
							MenuID = 0;
						}
						if(Tecla == UP || Tecla == LEFT)
						{
							Selecao --;
							if(Selecao < 0)
							{
								Selecao = 0;
							}
						}
						if(Tecla == DOWN || Tecla == RIGHT)
						{
							Selecao ++;
							if(Selecao >= iMaxMob)
							{
								Selecao = iMaxMob - 1;
							}
						}
						if(Tecla == TECLAENTER)
						{
							ListaDosTurnosTamanho ++;
							ListaDosTurnos = (ListaDosTurnosS *)realloc(ListaDosTurnos, sizeof(ListaDosTurnosS) * ListaDosTurnosTamanho);
							
							ListaDosTurnos[ListaDosTurnosTamanho - 1].Acao = ATAQUE;
							ListaDosTurnos[ListaDosTurnosTamanho - 1].IndiceAtacante = ArrayIds[Turno];
							ListaDosTurnos[ListaDosTurnosTamanho - 1].IndiceRecebedor = ArrayIdsMob[Selecao];
							ListaDosTurnos[ListaDosTurnosTamanho - 1].Tipo = PERSONAGEM;
							
							a = lista_busca(li, ArrayIds[Turno]);
							ListaDosTurnos[ListaDosTurnosTamanho - 1].Vel = a->vel;
							
							Turno ++;
							MenuID = 0;
						}
					}
				}
				else
				{
					printf("\n\n%d", a->hp);
					
					Turno ++;
				}
				
				if(Turno >= iMax)
				{
					turnoDosPersonagens = false;
					turnoDosMonstros = true;
					Turno = 0;
				}
			}
			
			if(turnoDosMonstros == true)
			{
				for(i=0; i < iMaxMob; i++)
				{
					Selecao = rand() % (iMax);
					
					ListaDosTurnosTamanho ++;
					ListaDosTurnos = (ListaDosTurnosS *)realloc(ListaDosTurnos, sizeof(ListaDosTurnosS) * ListaDosTurnosTamanho);
					
					ListaDosTurnos[ListaDosTurnosTamanho - 1].Acao = ATAQUE;
					ListaDosTurnos[ListaDosTurnosTamanho - 1].IndiceAtacante = ArrayIdsMob[Turno];
					ListaDosTurnos[ListaDosTurnosTamanho - 1].IndiceRecebedor = ArrayIds[Selecao];
					ListaDosTurnos[ListaDosTurnosTamanho - 1].Tipo = MOB;
					
					a = lista_busca(mob, ArrayIdsMob[Turno]);
					ListaDosTurnos[ListaDosTurnosTamanho - 1].Vel = a->vel;
					
					Turno ++;
				}
				
				turnoDosMonstros = false;
				Turno = 0;
				atacando = true;
				
				//Ordenar a lista
				for(i=0; i < ListaDosTurnosTamanho - 1; i++)
				{
					for(p=i+1; p < ListaDosTurnosTamanho; p++)
					{
						if(ListaDosTurnos[i].Vel < ListaDosTurnos[p].Vel)
						{
							ListaDosTurnosTemp = ListaDosTurnos[i];
							ListaDosTurnos[i] = ListaDosTurnos[p];
							ListaDosTurnos[p] = ListaDosTurnosTemp;
						}
					}
				}
				
				for(i=0; i < ListaDosTurnosTamanho; i++)
				{
					printf("\n\nAcao:    %d", ListaDosTurnos[i].Acao);
					printf("\nAtacante:  %d", ListaDosTurnos[i].IndiceAtacante);
					printf("\nRecebedor: %d", ListaDosTurnos[i].IndiceRecebedor);
					printf("\nTipo:      %d", ListaDosTurnos[i].Tipo);
					printf("\nVel:       %d", ListaDosTurnos[i].Vel);
				}
			}
			
			if(atacando == true)
			{
				for(i=0; i < ListaDosTurnosTamanho; i++)
				{
					dano = 0;
					danoCausado = 0;
					
					if(ListaDosTurnos[i].Tipo == PERSONAGEM)
					{
						a = lista_busca(li, ListaDosTurnos[i].IndiceAtacante);
					}
					else
					{
						a = lista_busca(mob, ListaDosTurnos[i].IndiceAtacante);
					}
					
					if(a->hp > 0)
					{
						if(ListaDosTurnos[i].Acao == ATAQUE) // Se for ataque
						{
							if(ListaDosTurnos[i].Tipo == PERSONAGEM)
							{
								a = lista_busca(mob, ListaDosTurnos[i].IndiceRecebedor);
								
								// Verifica se o HP do inimigo já foi zerado e escolhe um novo alvo da lista
								if(a->hp <= 0)
								{
									ListaDosTurnos[i].IndiceRecebedor = -1;
									
									for(p = 0; p < iMaxMob; p++)
									{
										a = lista_busca(mob, ArrayIdsMob[p]);
										
										if(a->hp > 0)
										{
											ListaDosTurnos[i].IndiceRecebedor = ArrayIdsMob[p];
											
											break;
										}
									}
								}
								
								if(ListaDosTurnos[i].IndiceRecebedor != -1)
								{
									dano = calcular_dano(li, ListaDosTurnos[i].IndiceAtacante);
								
									danoCausado = a->hp;
									
									if(dano > 0)
									{
										mob = aplicar_dano(mob, ListaDosTurnos[i].IndiceRecebedor, dano);
									}
									
									danoCausado -= a->hp;
									
									animacao = true;
									controleAnimacao = 0;
								}
								
								while(animacao == true)
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
										
										//Desenhos
										
										//Fundo e cenario
										setbkcolor(RGB(255, 255, 255));
										cleardevice();
										
										for(p = 0; p < iMaxMobInicial; p++)
										{
											a = lista_busca(mob, ArrayIdsMobInicial[p]);
											
											if(ArrayMobPosY[p] < 580)
											{
												if(ArrayIdsMobInicial[p] != ListaDosTurnos[i].IndiceRecebedor)
												{
													putimage(MobPosXInicial + (MobPosXDistancia * p), ArrayMobPosY[p], Sprites_Mobs_Mascaras[a->levels - 1], AND_PUT);
													putimage(MobPosXInicial + (MobPosXDistancia * p), ArrayMobPosY[p], Sprites_Mobs[a->levels - 1], OR_PUT);
												}
												else
												{
													if(controleAnimacao < 30)
													{
														putimage(MobPosXInicial + (MobPosXDistancia * p), ArrayMobPosY[p], Sprites_Mobs_Mascaras[a->levels - 1], AND_PUT);
														putimage(MobPosXInicial + (MobPosXDistancia * p), ArrayMobPosY[p], Sprites_Mobs[a->levels - 1], OR_PUT);
													}
													else if(controleAnimacao < 35)
													{
														putimage(MobPosXInicial + (MobPosXDistancia * p) + 5, ArrayMobPosY[p], Sprites_Mobs_Mascaras[a->levels - 1], AND_PUT);
														putimage(MobPosXInicial + (MobPosXDistancia * p) + 5, ArrayMobPosY[p], Sprites_Mobs[a->levels - 1], OR_PUT);
														
														putimage(MobPosXInicial + (MobPosXDistancia * p) + 10, ArrayMobPosY[p] + 30, Sprites_Efeitos_Mascaras[GOLPE], AND_PUT);
														putimage(MobPosXInicial + (MobPosXDistancia * p) + 10, ArrayMobPosY[p] + 30, Sprites_Efeitos[GOLPE], OR_PUT);
													}
													else if(controleAnimacao < 40)
													{
														putimage(MobPosXInicial + (MobPosXDistancia * p) - 5, ArrayMobPosY[p], Sprites_Mobs_Mascaras[a->levels - 1], AND_PUT);
														putimage(MobPosXInicial + (MobPosXDistancia * p) - 5, ArrayMobPosY[p], Sprites_Mobs[a->levels - 1], OR_PUT);
														
														putimage(MobPosXInicial + (MobPosXDistancia * p) + 30, ArrayMobPosY[p] + 10, Sprites_Efeitos_Mascaras[GOLPE], AND_PUT);
														putimage(MobPosXInicial + (MobPosXDistancia * p) + 30, ArrayMobPosY[p] + 10, Sprites_Efeitos[GOLPE], OR_PUT);
													}
													else if(controleAnimacao < 45)
													{
														putimage(MobPosXInicial + (MobPosXDistancia * p) + 5, ArrayMobPosY[p], Sprites_Mobs_Mascaras[a->levels - 1], AND_PUT);
														putimage(MobPosXInicial + (MobPosXDistancia * p) + 5, ArrayMobPosY[p], Sprites_Mobs[a->levels - 1], OR_PUT);
														
														putimage(MobPosXInicial + (MobPosXDistancia * p) + 20, ArrayMobPosY[p] + 40, Sprites_Efeitos_Mascaras[GOLPE], AND_PUT);
														putimage(MobPosXInicial + (MobPosXDistancia * p) + 20, ArrayMobPosY[p] + 40, Sprites_Efeitos[GOLPE], OR_PUT);
													}
													else if (controleAnimacao < 46)
													{
														putimage(MobPosXInicial + (MobPosXDistancia * p), ArrayMobPosY[p], Sprites_Mobs_Mascaras[a->levels - 1], AND_PUT);
														putimage(MobPosXInicial + (MobPosXDistancia * p), ArrayMobPosY[p], Sprites_Mobs[a->levels - 1], OR_PUT);
														
														PosYTexto = ArrayMobPosY[p] + 20;
														
														Texto = (char *)realloc(Texto, sizeof(char) * 15);
														
														if(dano <= 0)
														{
															strcpy(Texto, "Errou");
														}
														else
														{
															itoa(danoCausado, Texto, 10);
														}
													}
													else if(controleAnimacao < 60)
													{
														putimage(MobPosXInicial + (MobPosXDistancia * p), ArrayMobPosY[p], Sprites_Mobs_Mascaras[a->levels - 1], AND_PUT);
														putimage(MobPosXInicial + (MobPosXDistancia * p), ArrayMobPosY[p], Sprites_Mobs[a->levels - 1], OR_PUT);
														
														
														settextstyle(1, 0, 2);
														setbkcolor(RGB(255, 255, 255));
														setcolor(RGB(0, 0, 0));
														setlinestyle(0, 0, 1);
														
														outtextxy(MobPosXInicial + (MobPosXDistancia * p) + 80, PosYTexto, Texto);
														
														if(PosYTexto > ArrayMobPosY[p] - 10)
														{
															PosYTexto --;
														}
													}
													else
													{
														putimage(MobPosXInicial + (MobPosXDistancia * p), ArrayMobPosY[p], Sprites_Mobs_Mascaras[a->levels - 1], AND_PUT);
														putimage(MobPosXInicial + (MobPosXDistancia * p), ArrayMobPosY[p], Sprites_Mobs[a->levels - 1], OR_PUT);
														
														if(a->hp > 0)
														{
															animacao = false;
														}
														else
														{
															ArrayMobPosY[p] += 20;
															if(ArrayMobPosY[p] > 580)
															{
																qtd_exp += a->exp;
																animacao = false;
															}
														}
													}
												}
											}
										}
										
										//Menu
										desenhaMenu(li, ArrayIds, iMax, Sprites_Retratos, Sprites_Retratos_Mascaras, Sprites_HUD, Sprites_HUD_Mascaras);
										
										if(controleAnimacao >= 30)
										{
											for(q = 0; q < iMax; q++)
											{
												if(ArrayIds[q] == ListaDosTurnos[i].IndiceAtacante)
												{
													a = lista_busca(li, ListaDosTurnos[i].IndiceAtacante);
													
													Texto2 = (char *)realloc(Texto2, sizeof(char) * 10);
													strcpy(Texto2, a->nome);
													
													retratoDeBatalha(537, Texto2, RETRATOBATALHAATACANDO, q, Sprites_Retratos, Sprites_Retratos_Mascaras);
												}
											}
										}
										
										//Controle
										controleAnimacao ++;
										
										//Torna visivel a pagina de desenho.
										setvisualpage(PG);
										
										//Variavel Tecla
										fflush(stdin); //Aparentemente limpa algum endereco de memoria.
										Tecla = 0;
										if(kbhit())
										{
											Tecla = getch();
											//printf("%d", Tecla);
										}
									}
								}
							}
							else // Se for ataque do mob
							{
								a = lista_busca(li, ListaDosTurnos[i].IndiceRecebedor);
								
								// Verifica se o HP do inimigo já foi zerado e escolhe um novo alvo da lista
								if(a->hp <= 0)
								{
									ListaDosTurnos[i].IndiceRecebedor = -1;
									
									for(p = 0; p < iMax; p++)
									{
										a = lista_busca(li, ArrayIds[p]);
										
										if(a->hp > 0)
										{
											ListaDosTurnos[i].IndiceRecebedor = ArrayIds[p];
											
											break;
										}
									}
								}
								
								if(ListaDosTurnos[i].IndiceRecebedor != -1)
								{
									dano = calcular_dano(mob, ListaDosTurnos[i].IndiceAtacante);
									
									animacao = true;
									controleAnimacao = 0;
								}
								
								while(animacao == true)
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
										
										//Desenhos
										
										//Fundo e cenario
										setbkcolor(RGB(255, 255, 255));
										cleardevice();
										
										for(p = 0; p < iMaxMobInicial; p++)
										{
											a = lista_busca(mob, ArrayIdsMobInicial[p]);
											
											if(ArrayMobPosY[p] < 580)
											{
												if(ArrayIdsMobInicial[p] != ListaDosTurnos[i].IndiceAtacante)
												{
													putimage(MobPosXInicial + (MobPosXDistancia * p), ArrayMobPosY[p], Sprites_Mobs_Mascaras[a->levels - 1], AND_PUT);
													putimage(MobPosXInicial + (MobPosXDistancia * p), ArrayMobPosY[p], Sprites_Mobs[a->levels - 1], OR_PUT);
												}
												else
												{
													if(controleAnimacao < 30)
													{
														putimage(MobPosXInicial + (MobPosXDistancia * p), ArrayMobPosY[p], Sprites_Mobs_Mascaras[a->levels - 1], AND_PUT);
														putimage(MobPosXInicial + (MobPosXDistancia * p), ArrayMobPosY[p], Sprites_Mobs[a->levels - 1], OR_PUT);
													}
													else if(controleAnimacao < 35)
													{
														if(controleAnimacao < 31)
														{
															a = lista_busca(li, ListaDosTurnos[i].IndiceRecebedor);
															
															danoCausado = a->hp;
															
															if(dano > 0)
															{
																li = aplicar_dano(li, ListaDosTurnos[i].IndiceRecebedor, dano);
															}
															danoCausado -= a->hp;
															
															a = lista_busca(mob, ArrayIdsMobInicial[p]);
														}
														
														putimage(MobPosXInicial + (MobPosXDistancia * p), ArrayMobPosY[p] - 5, Sprites_Mobs_Mascaras[a->levels - 1], AND_PUT);
														putimage(MobPosXInicial + (MobPosXDistancia * p), ArrayMobPosY[p] - 5, Sprites_Mobs[a->levels - 1], OR_PUT);
													}
													else if(controleAnimacao < 40)
													{
														putimage(MobPosXInicial + (MobPosXDistancia * p), ArrayMobPosY[p] - 5, Sprites_Mobs_Mascaras[a->levels - 1], AND_PUT);
														putimage(MobPosXInicial + (MobPosXDistancia * p), ArrayMobPosY[p] - 5, Sprites_Mobs[a->levels - 1], OR_PUT);
													}
													else if(controleAnimacao < 45)
													{
														putimage(MobPosXInicial + (MobPosXDistancia * p), ArrayMobPosY[p] - 5, Sprites_Mobs_Mascaras[a->levels - 1], AND_PUT);
														putimage(MobPosXInicial + (MobPosXDistancia * p), ArrayMobPosY[p] - 5, Sprites_Mobs[a->levels - 1], OR_PUT);
													}
													else if (controleAnimacao < 46)
													{
														putimage(MobPosXInicial + (MobPosXDistancia * p), ArrayMobPosY[p], Sprites_Mobs_Mascaras[a->levels - 1], AND_PUT);
														putimage(MobPosXInicial + (MobPosXDistancia * p), ArrayMobPosY[p], Sprites_Mobs[a->levels - 1], OR_PUT);
													}
													else if(controleAnimacao < 60)
													{
														putimage(MobPosXInicial + (MobPosXDistancia * p), ArrayMobPosY[p], Sprites_Mobs_Mascaras[a->levels - 1], AND_PUT);
														putimage(MobPosXInicial + (MobPosXDistancia * p), ArrayMobPosY[p], Sprites_Mobs[a->levels - 1], OR_PUT);
													}
													else
													{
														putimage(MobPosXInicial + (MobPosXDistancia * p), ArrayMobPosY[p], Sprites_Mobs_Mascaras[a->levels - 1], AND_PUT);
														putimage(MobPosXInicial + (MobPosXDistancia * p), ArrayMobPosY[p], Sprites_Mobs[a->levels - 1], OR_PUT);
														
														animacao = false;
													}
												}
											}
										}
										
										//Menu
										desenhaMenu(li, ArrayIds, iMax, Sprites_Retratos, Sprites_Retratos_Mascaras, Sprites_HUD, Sprites_HUD_Mascaras);
										
										if(controleAnimacao < 30)
										{
											//Nada.
										}
										else if(controleAnimacao < 35)
										{
											for(q = 0; q < iMax; q++)
											{
												if(ArrayIds[q] == ListaDosTurnos[i].IndiceRecebedor)
												{
													a = lista_busca(li, ListaDosTurnos[i].IndiceRecebedor);
													
													Texto = (char *)realloc(Texto, sizeof(char) * 10);
													strcpy(Texto, a->nome);
													
													retratoDeBatalha(537, Texto, RETRATOBATALHADANO, q, Sprites_Retratos, Sprites_Retratos_Mascaras);
													
													putimage(790 - 15, 337 + (73 * q) - 30, Sprites_Efeitos_Mascaras[GOLPE], AND_PUT);
													putimage(790 - 15, 337 + (73 * q) - 30, Sprites_Efeitos[GOLPE], OR_PUT);
												}
											}
										}
										else if(controleAnimacao < 40)
										{										
											for(q = 0; q < iMax; q++)
											{
												if(ArrayIds[q] == ListaDosTurnos[i].IndiceRecebedor)
												{
													a = lista_busca(li, ListaDosTurnos[i].IndiceRecebedor);
													
													Texto = (char *)realloc(Texto, sizeof(char) * 10);
													strcpy(Texto, a->nome);
													
													retratoDeBatalha(537, Texto, RETRATOBATALHADANO, q, Sprites_Retratos, Sprites_Retratos_Mascaras);
													
													putimage(790 + 10, 337 + (73 * q) - 15, Sprites_Efeitos_Mascaras[GOLPE], AND_PUT);
													putimage(790 + 10, 337 + (73 * q) - 15, Sprites_Efeitos[GOLPE], OR_PUT);
												}
											}
										}
										else if(controleAnimacao < 45)
										{	
											for(q = 0; q < iMax; q++)
											{
												if(ArrayIds[q] == ListaDosTurnos[i].IndiceRecebedor)
												{
													a = lista_busca(li, ListaDosTurnos[i].IndiceRecebedor);
													
													Texto = (char *)realloc(Texto, sizeof(char) * 10);
													strcpy(Texto, a->nome);
													
													retratoDeBatalha(537, Texto, RETRATOBATALHADANO, q, Sprites_Retratos, Sprites_Retratos_Mascaras);
													
													putimage(790, 337 + (73 * q) - 25, Sprites_Efeitos_Mascaras[GOLPE], AND_PUT);
													putimage(790, 337 + (73 * q) - 25, Sprites_Efeitos[GOLPE], OR_PUT);
												}
											}
										}
										else if (controleAnimacao < 46)
										{	
											for(q = 0; q < iMax; q++)
											{
												if(ArrayIds[q] == ListaDosTurnos[i].IndiceRecebedor)
												{
													PosYTexto = 337 + (73 * q) + 10;
												}
											}
											
											Texto = (char *)realloc(Texto, sizeof(char) * 15);
											
											if(dano <= 0)
											{
												strcpy(Texto, "Errou");
											}
											else
											{
												itoa(danoCausado, Texto, 10);
											}
										}
										else if(controleAnimacao < 60)
										{
											settextstyle(1, 0, 2);
											setbkcolor(RGB(255, 255, 255));
											setcolor(RGB(0, 0, 0));
											setlinestyle(0, 0, 1);
											
											outtextxy(754 + 65, PosYTexto, Texto);
											
											for(q = 0; q < iMax; q++)
											{
												if(ArrayIds[q] == ListaDosTurnos[i].IndiceRecebedor)
												{
													if(PosYTexto > 337 + (73 * q) - 10)
													{
														PosYTexto --;
													}
												}
											}
										}
										
										//Controle
										controleAnimacao ++;
										
										//Torna visivel a pagina de desenho.
										setvisualpage(PG);
										
										//Variavel Tecla
										fflush(stdin); //Aparentemente limpa algum endereco de memoria.
										Tecla = 0;
										if(kbhit())
										{
											Tecla = getch();
											//printf("%d", Tecla);
										}
									}
								}
							}
						}
					}		
				}
				
				//detalhaStatus(li);
				//detalhaStatus(mob);
				
				atacando = false;
				Turno = 0;
				ListaDosTurnosTamanho = 0;
				turnoDosPersonagens = true;
				
				printf("\n\n");
				monstrosMortos = true;
				for(i = 0; i < iMaxMob; i++)
				{
					a = lista_busca(mob, ArrayIdsMob[i]);
					printf("HP: %d, ", a->hp);
					
					if(a->hp > 0)
					{
						monstrosMortos = false;
					}
				}
				
				printf("\n");
				personagensMortos = true;
				for(i = 0; i < iMax; i++)
				{
					a = lista_busca(li, ArrayIds[i]);
					printf("HP: %d, ", a->hp);
					
					if(a->hp > 0)
					{
						personagensMortos = false;
					}
				}
			}
			
			if(personagensMortos == true || monstrosMortos == true)
			{
				batalhaFinalizada = true;
			}
			
			//Variavel Tecla
			fflush(stdin); //Aparentemente limpa algum endereco de memoria.
			Tecla = 0;
			if(kbhit())
			{
				Tecla = getch();
				//printf("%d", Tecla);
			}
		}
	}
	
	for(i = 0; i < iMaxMobInicial; i++)
	{
		a = lista_busca(mob, ArrayIdsMobInicial[i]);
		
		printf("\nExp[%d]: %d .", i, a->exp);
	}
	printf("\n\nExp: %d", qtd_exp);
	
	if(personagensMortos == false)
	{
		li = aplicar_experiencia(li, qtd_exp);
	}
	
	return li;
}
