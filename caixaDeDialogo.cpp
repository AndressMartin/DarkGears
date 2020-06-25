#include "enums.h"

#include<graphics.h>
#include<stdio.h>
#include<string.h>

void ReadDialogue(int posx, int posy, int partToStart, int partToStop, char txtChanger[40], char *Arquivo, void* Sprites_Retratos[], void* Sprites_Retratos_Mascaras[], void* Sprites_HUD[], void* Sprites_HUD_Mascaras[])
{
	int sizeyTemp = posy,
	 	sizexTemp = posx + 9,
	 	contLines = 1;
	bool spacePress = true,
		 pulandoTexto = false;
	char c[] = "c", //Conta cada caractere.
		 f[] = "f", //Ao chegar no symbolImage, f ir� guardar o s�mbolo at� o pr�ximo \n.
	 	 symbol[] = "$",
		 symbolImage[] = "%",
		 symbolChange[] = "#",
	 	 newLine[] = "\n",
		 imgId[4];
	memset(imgId, 0, sizeof imgId);
	FILE * fPointer;
	fPointer = fopen(Arquivo, "r");	
	
	settextstyle(0, 0, 0);
	setbkcolor(RGB(136, 0, 21));
	setcolor(RGB(0, 0, 0));
	setlinestyle(0, 0, 1);
	
	putimage(posx, posy, Sprites_HUD_Mascaras[CAIXADETEXTO], AND_PUT);
	putimage(posx, posy, Sprites_HUD[CAIXADETEXTO], OR_PUT);
	
	while(fscanf(fPointer,"%c", &c)==1)
	{ 
		if (strcmp(c, symbol) != 0)
		{
			if (strcmp(c, symbolImage) != 0 && strcmp(f, symbolImage) != 0)
			{
				if (strcmp(c, symbolChange) != 0)
				{
					if (contLines >= partToStart && contLines <= partToStop)
					{	
						outtextxy(sizexTemp+10, sizeyTemp, c);
						sizexTemp += 12;
						if (!(pulandoTexto))
						{
							delay(50);
						}
						
						if ((GetKeyState(VK_SPACE)&0x80) && spacePress == false)
						{
							pulandoTexto = true;
							spacePress = true;
						}
						if (!(GetKeyState(VK_SPACE)&0x80))
						{
							pulandoTexto = false;
							spacePress = false;
						}
						
					}
					else if (contLines > partToStop)
					{
						return;
					}
				
					if (strcmp(c, newLine) == 0)
					{
						contLines++;
						if(contLines >= partToStart && contLines <= partToStop)
						{
							sizeyTemp += 15;
							sizexTemp = posx + 9;
						}
					
					}
				}
				else
				{
					outtextxy(sizexTemp+10, sizeyTemp, txtChanger);
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
					int imagem = atoi(imgId);
					
					if(contLines >= partToStart && contLines <= partToStop)
					{
						putimage(posx - 180, posy - 105, Sprites_Retratos_Mascaras[imagem], AND_PUT);
						putimage(posx - 180, posy - 105, Sprites_Retratos[imagem], OR_PUT);
					}
					
					memset(f, 0, sizeof f);
					memset(imgId, 0, sizeof imgId);
					contLines++;
				}
			}		
		}
		while(strcmp(c, symbol) == 0)
		{
			if((GetKeyState(VK_SPACE)&0x80 && spacePress == false) or !(contLines >= partToStart))
			{
				memset(c, 0, sizeof c);
				strcpy(c, "c");
				sizeyTemp = posy;

				putimage(posx, posy, Sprites_HUD_Mascaras[CAIXADETEXTO], AND_PUT);
				putimage(posx, posy, Sprites_HUD[CAIXADETEXTO], OR_PUT);
				
				pulandoTexto = false;
				spacePress = true;
			}
			if (!(GetKeyState(VK_SPACE)&0x80))
			{
				spacePress = false;
			}
		}
	}
	
	fclose(fPointer);
}
