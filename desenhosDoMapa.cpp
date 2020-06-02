#include "enums.h"

#include<graphics.h>

void desenhaCenario(int CPosX, int CPosY, void* Cenario[], int CenarioAtual)
{
	putimage(CPosX, CPosY, Cenario[CenarioAtual], COPY_PUT);
}

void TransicaoDeMapa(int MudancaDeCenarioNumero, int *CenarioAtual, int *PosX, int *PosY, int *CPosX, int *CPosY)
{
	//Faz a transicao dos mapas, mudando o CenarioAtual e as posicoes do personagem e do cenario.
	
	switch(MudancaDeCenarioNumero)
	{
		case 0:
			*CenarioAtual = 1;
			*PosX = 302;
			*PosY = 160;
			*CPosX = -31;
			*CPosY = -18;
			
			break;
		
		case 1:
		*CenarioAtual = 0;
		*PosX = 70;
		*PosY = 480;
		*CPosX = -10;
		*CPosY = -10;
		
		break;
		
		default:
			printf("\nRaios multiplos! O operador esta incorreto.");
	}
}
