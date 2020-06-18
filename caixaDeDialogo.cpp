#include "enums.h"

#include<graphics.h>

void ReadDialogue(int sizex, int sizey, int partToStart, int partToStop, double tamX,double tamY,double recX,double sizeTextX,double sizeTextX2)
{
	int sizeyTemp = sizey;
	int sizexTemp = sizex;
	int contLines = 1;
	bool spacePress = false;
	char c[] = "c"; //Conta cada caractere.
	char f[] = "f"; //Ao chegar no symbolImage, f irá guardar o símbolo até o próximo \n.
	char symbol[] = "$";
	char symbolImage[] = "%";
	char newLine[] = "\n";
	char imgId[4];
	memset(imgId, 0, sizeof imgId);
	FILE * fPointer;
	fPointer = fopen("Teste.txt", "r");	
	
	setbkcolor(RGB(50, 50, 50));
	cleardevice();
  	setcolor(RGB(255, 255, 0));
	rectangle(40, 330, (tamX/2 - recX/1.75), 550);
	bar(40, 330, (tamX/2 - recX/1.75), 550);
	rectangle(sizeTextX, 435, sizeTextX2, 550);
	printf("%f", (sizeTextX2 - sizeTextX));
	printf("\n");
	setcolor(RGB(0, 255, 0));
	setlinestyle(0, 0, 1);
	
	while(!(GetKeyState(VK_UP)&0x80))
	{
		while(fscanf(fPointer,"%c", &c)==1)
		{ 
			if (strcmp(c, symbol) != 0)
			{
				if (strcmp(c, symbolImage) != 0 && strcmp(f, symbolImage) != 0)
				{
					if (contLines >= partToStart && contLines <= partToStop)
					{	
						printf(c);
						outtextxy(sizexTemp+10, sizeyTemp, c);
						sizexTemp += 10;
						if (!(GetKeyState(VK_SPACE)&0x80))
						{
							delay(50);
						}
						else
						{
							spacePress = true;
						}
					}
				
					else if (contLines > partToStop)
					{
						return;
					}
				
					if (strcmp(c, newLine) == 0)
					{
						contLines++;
						sizeyTemp += 15;
						sizexTemp = sizex;
					
					}
				}
				else if (strcmp(f, symbolImage) != 0 && strcmp(c, symbolImage) == 0)
				{
					strcpy(f, c);
					memset(c, 0, sizeof c);
				}
				else if (strcmp(f, symbolImage) == 0 && strcmp(c, symbolImage) != 0)
				{
					if(strcmp(c, "\n") != 0)
					{
						strcat(imgId, c);
					}
					else if(strcmp(c, "\n") == 0)
					{
						puts(imgId);
						memset(f, 0, sizeof f);
						memset(imgId, 0, sizeof imgId);
						contLines++;
					}
				}
					
			}
			while(strcmp(c, symbol) == 0)
			{
				if(GetKeyState(VK_SPACE)&0x80 && spacePress == false)
				{
					memset(c, 0, sizeof c);
					strcpy(c, "c");
					sizeyTemp = sizey;
					//DrawUI(); //Para redesenhar a Interface de Usuario.

					setbkcolor(RGB(50, 50, 50));
					cleardevice();
				  	setcolor(RGB(255, 255, 0));
					rectangle(40, 330, (tamX/2 - recX/1.75), 550);
					bar(40, 330, (tamX/2 - recX/1.75), 550);
					rectangle(sizeTextX, 435, sizeTextX2, 550);
					setcolor(RGB(0, 255, 0));
					setlinestyle(0, 0, 1);
				}
				if (!(GetKeyState(VK_SPACE)&0x80))
				{
					spacePress = false;
				}
			}
		}
	}
	
fclose(fPointer);
}

/*
int main() 
{ 
	int i;
	int *ptos;
	double tamX = 1024;
	double tamY = 576;
	double recX = tamX/2;
	double sizeTextX = (tamX/2 - recX/1.75);
	double sizeTextX2 = (tamX/2 + recX/1.3);
	
	initwindow(tamX, tamY, "Primeiro Pgm Gráfico", 0, 400);
	
	setbkcolor(RGB(50, 50, 50));
	cleardevice();
	ReadDialogue(sizeTextX, 450, 2, 8, tamX, tamY, recX, sizeTextX, sizeTextX2); //Batalha contra o BGI
	//printf("Agora vem a vez do morcego");
	ReadDialogue(sizeTextX, 450, 10, 18, tamX, tamY, recX, sizeTextX, sizeTextX2); //Batalha contra o Morcego
	while(!(GetKeyState(VK_UP)&0x80));
	closegraph();	
	return(0); 
}
*/
