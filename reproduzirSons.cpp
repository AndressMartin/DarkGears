#include "enums.h"

#include <stdlib.h>
#include <stdio.h> 
#include <windows.h> //Para o PlaySound()

void reproduzirSom(int Comando)
{
	//Alterar o volume dos sons
	if (Comando == VOLUME1)
	{
		waveOutSetVolume(0,0x01111111); //Volume no baixo
	}
    else if (Comando == VOLUME2)
    {
    	waveOutSetVolume(0,0x88888888); //Volume no médio
	}
    else if (Comando == VOLUME3)
    {
    	waveOutSetVolume(0,0xFFFFFFFF); //Volume no maximo
	}
	
	//Reproduzir sons de fundo
	else if (Comando == PARARMUSICA)
	{
		mciSendString("close musica", NULL, 0, 0);    //Para a reprodução do alias musica
	}
	else if (Comando == MUSICABATALHA)
	{
		mciSendString("open .\\Sons\\ff6_battle_theme.mp3 type MPEGVideo alias musica", NULL, 0, 0); 
      	mciSendString("play musica repeat", NULL, 0, 0);
      	
      	//Versao com looping
      	//mciSendString("play musica repeat", NULL, 0, 0);
	}
	else if(Comando == MUSICAVITORIA)
	{
		mciSendString("open .\\Sons\\ff6_victory_fanfare.mp3 type MPEGVideo alias musica", NULL, 0, 0); 
      	mciSendString("play musica", NULL, 0, 0);
	}
	else if(Comando == MUSICAGAMEOVER)
	{
		mciSendString("open .\\Sons\\ff6_rest_in_peace.mp3 type MPEGVideo alias musica", NULL, 0, 0); 
      	mciSendString("play musica", NULL, 0, 0);
	}
	else if(Comando == MUSICACAVERNA)
	{
		mciSendString("open .\\Sons\\chrono_trigger_forest_theme.mp3 type MPEGVideo alias musica", NULL, 0, 0);
      	mciSendString("play musica repeat", NULL, 0, 0);
	}
	else if(Comando == MUSICACHEFE)
	{
		mciSendString("open .\\Sons\\ff6_musica_chefe.mp3 type MPEGVideo alias musica", NULL, 0, 0);
      	mciSendString("play musica repeat", NULL, 0, 0);
	}
	
	//Reproduzir efeitos sonoros
	else if (Comando == PARAREFEITOSONORO)
	{
		sndPlaySound(NULL, NULL); // Interrompe o som wav
	}
    else if (Comando == CURSORMOVE)
    {
    	//Exemplo de som em looping infinito.
    	//sndPlaySound(".\\sons\\barracks.wav", SND_ASYNC + SND_LOOP);
    	sndPlaySound(".\\Sons\\ff7_cursor_move.wav", SND_ASYNC);
	}
	else if (Comando == CURSORVOLTA)
    {
    	sndPlaySound(".\\Sons\\ff7_cursor_volta.wav", SND_ASYNC);
	}
	else if (Comando == CURSORPRONTO)
    {
    	sndPlaySound(".\\Sons\\ff7_cursor_pronto.wav", SND_ASYNC);
	}
	else if (Comando == CURSORERRO)
    {
    	sndPlaySound(".\\Sons\\ff7_cursor_erro.wav", SND_ASYNC);
	}
	else if(Comando == SOMCORREBATALHA)
	{
		sndPlaySound(".\\Sons\\ff6_running_away.wav", SND_ASYNC);
	}
	else if(Comando == SOMDEATAQUE)
	{
		sndPlaySound(".\\Sons\\ff7_som_ataque.wav", SND_ASYNC);
	}
	else if(Comando == SOMDECURA)
	{
		sndPlaySound(".\\Sons\\chrono_trigger_cura_mapa.wav", SND_ASYNC);
	}
	else if(Comando == SOMDEREVIVER)
	{
		sndPlaySound(".\\Sons\\ff7_som_reviver.wav", SND_ASYNC);
	}
	else if (Comando == SOMINIMIGOMORTO)
	{
		sndPlaySound(".\\Sons\\ff7_inimigo_morto.wav", SND_ASYNC);
	}
	else if (Comando == SOMDEATAQUE2)
	{
		sndPlaySound(".\\Sons\\ff6_HitFist.wav", SND_ASYNC);
	}
	else if (Comando == SOMERROUATAQUE)
	{
		sndPlaySound(".\\Sons\\chrono_trigger_miss.wav", SND_ASYNC);
	}
	else if (Comando == SOMDECURA2)
	{
		sndPlaySound(".\\Sons\\chrono_trigger_cura_mapa2.wav", SND_ASYNC);
	}
	else if (Comando == SOMABRIRBAU)
	{
		sndPlaySound(".\\Sons\\chrono_trigger_bau.wav", SND_ASYNC);
	}
}
