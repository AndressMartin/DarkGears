#include "enums.h"

#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<string.h>

#define ESC     27

void iniciarBatalha()
{	
	bool batalhaFinalizada = false;
	
	bool turnoDosPersonagens = false,
		 turnoDosMonstros = false,
		 atacando = false;
	
	int id = 0;
	
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
			
			//Torna visivel a pagina de desenho.
			setvisualpage(PG);
			
			//Acoes
			
			if(turnoDosPersonagens = true)
			{
				
			}
			
			//Variavel Tecla
			if(kbhit())
			{
				Tecla = getch();
			}
		}
	}
}
