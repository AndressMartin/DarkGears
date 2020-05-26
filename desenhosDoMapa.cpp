#include "enums.h"

#include<graphics.h>

void desenhaCenario(int CPosX, int CPosY, void* Cenario[], int CenarioAtual, int Cenario_Tamanhos[][2], int TelaLarX, int TelaLarY)
{
	//Dependendo do cenario atual, o mapa vai estar dividido, e nos vamos colocar as imagens na ordem correta.
	//Como a posicao das imagens em relacao umas as outras dependo do mapa, e vou usar switch para cada ocasiao.
	switch(CenarioAtual)
	{
		case 0:
			// O if fara com que a imagem nao seja desenhada se estiver fora da tela.
			if(((CPosX >= (0 - Cenario_Tamanhos[TESTEC_01_1][0])) && (CPosX <= TelaLarX)) && ((CPosY >= (0 - Cenario_Tamanhos[TESTEC_01_1][1])) && (CPosY <= TelaLarY)))
			{
				putimage(CPosX, CPosY, Cenario[TESTEC_01_1], COPY_PUT);
			}
			if(((CPosX + 640 >= (0 - Cenario_Tamanhos[TESTEC_01_2][0])) && (CPosX <= TelaLarX)) && ((CPosY >= (0 - Cenario_Tamanhos[TESTEC_01_2][1])) && (CPosY <= TelaLarY)))
			{
				putimage(CPosX + 640, CPosY, Cenario[TESTEC_01_2], COPY_PUT);
			}
			if(((CPosX >= (0 - Cenario_Tamanhos[TESTEC_01_3][0])) && (CPosX <= TelaLarX)) && ((CPosY + 360 >= (0 - Cenario_Tamanhos[TESTEC_01_3][1])) && (CPosY <= TelaLarY)))
			{
				putimage(CPosX, CPosY + 360, Cenario[TESTEC_01_3], COPY_PUT);
			}
			if(((CPosX + 640 >= (0 - Cenario_Tamanhos[TESTEC_01_4][0])) && (CPosX <= TelaLarX)) && ((CPosY + 360 >= (0 - Cenario_Tamanhos[TESTEC_01_4][1])) && (CPosY <= TelaLarY)))
			{
				putimage(CPosX + 640, CPosY + 360, Cenario[TESTEC_01_4], COPY_PUT);
			}
			break;
		
		//Caso nao haja um codigo para o CenarioAtual, ou seja, dar erro.
		default:
			printf("\nRaios multiplos! O operador esta incorreto.");
	}
}
