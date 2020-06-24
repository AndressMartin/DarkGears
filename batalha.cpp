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
		
		case RBCHADDRIT:
			if(Tipo == RETRATOBATALHANORMAL)
			{
				putimage(PosX, 337 + (73 * i), Sprites_Retratos_Mascaras[3], AND_PUT);
				putimage(PosX, 337 + (73 * i), Sprites_Retratos[3], OR_PUT);
				break;	
			}
		
		default:
			printf("\nRaios multiplos! O operador esta incorreto.");
	}
}

void iniciarBatalha(Personagens* li, Personagens* mob, void* Sprites_Retratos[], void* Sprites_Retratos_Mascaras[], void* Sprites_HUD[], void* Sprites_HUD_Mascaras[])
{	
	srand(time(0));
	
	bool batalhaFinalizada = false;
	
	bool turnoDosPersonagens = false,
		 turnoDosMonstros = false,
		 atacando = false;
	
	int id = 0,
		i = 0,
		iMax = 0,
		iMaxMob = 0,
		Turno = 0,
		Selecao = 0,
		MenuID = 0;
	
	int *ArrayIds = NULL,
		*ArrayIdsMob = NULL,
		*ArrayIdsAux = NULL;
	
	ListaDosTurnosS *ListaDosTurnos = NULL;
	int ListaDosTurnosTamanho = 0;
	
	char *Texto = NULL,
		 HpTexto[4] = "999";
	
	//Variável usada para percorrer a lista
	Personagens *a;
	
	turnoDosPersonagens = true;
	id = 0;
	
	int PG = 0;
	char Tecla = 0;
	long long unsigned Gt1, Gt2;
	int FPS = 60;
	
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
			
			setbkcolor(RGB(255, 255, 255));
			cleardevice();
			
			settextstyle(0, 0, 0);
			setbkcolor(RGB(185, 122, 87));
			setcolor(RGB(0, 0, 0));
			setlinestyle(0, 0, 1);
			
			putimage(27, 337, Sprites_HUD_Mascaras[MENUBATALHA1], AND_PUT);
			putimage(27, 337, Sprites_HUD[MENUBATALHA1], OR_PUT);
			
			//Cria a lista com os ids dos monstros
			iMaxMob = 0;
			for(a = mob; a != NULL; a = a->prox)
			{
				iMaxMob ++;
				ArrayIdsMob = (int *)realloc(ArrayIdsMob, sizeof(int) * iMaxMob);
				ArrayIdsMob[iMaxMob - 1] = a->id;
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
			
			for(i = 0; i < iMax; i++)
			{
				a = lista_busca(li, ArrayIds[i]);
			
			    putimage(537, 337 + (73 * i), Sprites_HUD_Mascaras[MENUBATALHA2], AND_PUT);
				putimage(537, 337 + (73 * i), Sprites_HUD[MENUBATALHA2], OR_PUT);
				
				Texto = (char *)realloc(Texto, sizeof(char) * 10);
				strcpy(Texto, a->nome);
				
				retratoDeBatalha(537, Texto, RETRATOBATALHANORMAL, i, Sprites_Retratos, Sprites_Retratos_Mascaras);
				
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
						if(Turno >= iMax)
						{
							turnoDosPersonagens = false;
							turnoDosMonstros = true;
							Turno = 0;
						}
					}
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
				
				for(i=0; i < ListaDosTurnosTamanho; i++)
				{
					printf("\n\nAcao:      %d", ListaDosTurnos[i].Acao);
					printf("\nAtacante:   %d", ListaDosTurnos[i].IndiceAtacante);
					printf("\nRecebedor: %d", ListaDosTurnos[i].IndiceRecebedor);
					printf("\nTipo:      %d", ListaDosTurnos[i].Tipo);
					printf("\nVel:       %d", ListaDosTurnos[i].Vel);
				}
			}
			
			if(atacando == true)
			{
				
			}
			
			//Variavel Tecla
			Tecla = 0;
			if(kbhit())
			{
				Tecla = getch();
				//printf("%d", Tecla);
			}
		}
	}
}
