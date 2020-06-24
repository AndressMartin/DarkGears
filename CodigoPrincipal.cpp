#include<stdio.h> //Biblioteca padrao
#include<graphics.h> //BGI
#include<conio.h> //kbhit e getch
#include<time.h> //Tempo
#include<string.h> //Funcoes de string

#include "structs.h"
#include "enums.h"
#include "listasDoMapa.h"
#include "desenhosDoMapa.h"
#include "ListaEncadeadaPersonagem.h"
#include "batalha.h"
#include "caixaDeDialogo.h"

#define LEFT   	75
#define RIGHT  	77
#define UP     	72
#define DOWN   	80
#define ESC     27

#define PRETO 0
						  
//Ponteiros com as imagens
char Tipo[13] = "Nice",
	 JPG[5] = ".jpg",
	 BMP[5] = ".bmp",
	 MBMP[13] = "_mascara.bmp",
	 MJPG[13] = "_mascara.jpg";
char StrcatTemp[50] = "Yes"; //O numero de caracteres tem que ser grande para ser usado no carregaento de imagens.

//Imagens

//Vai guardar as imagens.
const int SpritesQ = 3; //Quantidade de sprites, vai ser usado nas outras listas para facilitar mudancas.
void* Sprites[SpritesQ];
void* Sprites_Mascaras[SpritesQ];

const int Cenario_ColisaoQ = 2;
void* Cenario_Colisao[Cenario_ColisaoQ];

const int Cenario_ObjetosQ = 5;
void* Cenario_Objetos[Cenario_ObjetosQ];
void* Cenario_Objetos_Mascaras[Cenario_ObjetosQ];

const int Sprites_BausQ = 2;
void* Sprites_Baus[Sprites_BausQ];
void* Sprites_Baus_Mascaras[Sprites_BausQ];

const int Sprites_RetratosQ = 4;
void* Sprites_Retratos[Sprites_RetratosQ];
void* Sprites_Retratos_Mascaras[Sprites_RetratosQ];

const int Sprites_HUDQ = 5;
void* Sprites_HUD[Sprites_HUDQ];
void* Sprites_HUD_Mascaras[Sprites_HUDQ];

//Nomes e caminhos dos arquivos, sem o tipo, para poder ser usado pelo codigo das mascaras tambem.
// "17"" pois tem que considerar o caractere nulo "\0" que fica no final de uma string.
char Sprites_Nomes[SpritesQ][25] = {"Sprites/imagem01",
							 		"Sprites/imagem02",
									"Sprites/fox_prototype4_2"};

char Cenario_Colisao_Nomes[Cenario_ColisaoQ][38] = {"Sprites/Cenarios/Cenario01_01_Colisao",
									 				"Sprites/Cenarios/Cenario01_02_Colisao"};

char Cenario_Objetos_Nomes[Cenario_ObjetosQ][38] = {"Sprites/ObjetoC_Teste_01-1",
							 						"Sprites/ObjetoC_Teste_01-2",
													"Sprites/ObjetoC_Teste_01-3",
													"Sprites/Cenarios/ObjetoC_Teste_02-1#1",
													"Sprites/Cenarios/ObjetoC_Teste_02-1#2"};

char Sprites_Retratos_Nomes[Sprites_RetratosQ][34] = {"Sprites/Retratos/lily",
									 				  "Sprites/Retratos/morcego",
													  "Sprites/Retratos/lily_batalha",
													  "Sprites/Retratos/chaddrit_batalha"};
									 				
char Sprites_HUD_Nomes[Sprites_HUDQ][29] = {"Sprites/HUD/caixa_de_texto",
											"Sprites/HUD/menuDeBatalha_1",
											"Sprites/HUD/menuDeBatalha_2",
											"Sprites/HUD/menuDeBatalha_3",
											"Sprites/HUD/selecao_monstros"};

//Organizacao = {Bau01 fechado, Bau01 aberto, Bau02 fechado, Bau02 aberto, ...}
char Sprites_Baus_Nomes[Sprites_BausQ][16] = {"Sprites/bau01-F",
							 				  "Sprites/bau01-A"};

//Vai guardas a largura e altura das imagens, respectivamente.
int Sprites_Tamanhos[SpritesQ][2] = {{100, 50},
							  		 {70, 50},
									 {64, 128}};

int Cenario_Colisao_Tamanhos[Cenario_ColisaoQ][2] = {{840, 560},
													 {2000, 1000}};

int Cenario_Objetos_Tamanhos[Cenario_ObjetosQ][2] = {{110, 115},
							  		 				 {110, 115},
													 {110, 115},
													 {192, 281},
													 {96, 281}};

int Sprites_Baus_Tamanhos[Sprites_BausQ][2] = {{50, 60},
											   {50, 60}};

int Sprites_Retratos_Tamanhos[Sprites_RetratosQ][2] = {{180, 220},
											   		   {180, 220},
													   {85, 74},
													   {85, 74}};

int Sprites_HUD_Tamanhos[Sprites_HUDQ][2] = {{686, 115},
											 {970, 220},
											 {460, 74},
											 {326, 74},
											 {85, 74}};

//Definicao das funcoes, as funcoes em si estao depois do main.
void CarregarImagens(int Imagem);
bool hitTestCenario(int PosX, int PosY);
bool colisaoComRetangulos(int CPosX, int CPosY, int PosX, int PosY, int PLarX, int PLarY, int TamanhoListaRetangulosDeColisao, RetangulosDeColisao ListaRetangulosDeColisao[]);

//Funcoes que pretendo separar depois.
void interacoesComOMapa(int CenarioAtual, int PosX, int PosY, int PLarX, int PLarY, int CPosX, int CPosY, int Bau_AreaDeInteracao, RetangulosDeColisao PosicaoBaus[], int NumeroDeBaus, int **Baus, int BausCopia[], bool *PodeFazerInteracao, bool *SpacePress, bool *MudancaDeCenario, int *MudancaDeCenarioNumero, RetangulosDeColisao Portas[], bool *CaixaDeTexto, char **Arquivo, int *DialogoPosX, int *DialogoPosY, int *DialogoPartToStart, int *DialogoPartToStop);

int main()
{
	//Lista dos peronagens, inimigos e itens
	Personagens *li = lista_cria(),
				*mob = lista_cria();
	Item item[5];
	
	// Carregando propriedades dos itens em structs
	strcpy(item[0].descricao, "Espada de aco");
    item[0].atk = 10;
    item[0].def = 0;
    item[0].prec = 0;
    item[0].tipo_item = 1;
    
    strcpy(item[1].descricao, "Malha");
    item[1].atk = 0;
    item[1].def = 10;
    item[1].prec = 0;
    item[1].tipo_item = 2;
    
    strcpy(item[2].descricao, "Anel");
    item[2].atk = 0;
    item[2].def = 0;
    item[2].prec = 5;
    item[2].tipo_item = 3;
    
    strcpy(item[3].descricao, "Graveto");
    item[3].atk = 1;
    item[3].def = 0;
    item[3].prec = 0;
    item[3].tipo_item = 1;
    
	//Definindo personagens e seus status
	char lily [5]  = "Lily";
	char cueio [9] = "Chaddrit";
	char quem [9] = "Qsou eu?";
	
	li = lista_insere(li, 1, lily, 10, 10, 10, 8, 5, 1, 100);
	li = lista_insere(li, 2, cueio, 20, 6, 6, 12, 15, 5, 200);
	li = lista_insere(li, 3, quem, 99, 99, 99, 99, 99, 99, 999);
	
	//Equipando os itens nos personagens, é preciso passar a party, o indice do personagem da party e o item que deseja equipar
	li = equipa_item(li, 1, &item[0]);
	li = equipa_item(li, 1, &item[1]);
	li = equipa_item(li, 1, &item[2]);
	
	//Insere inimigos na lista
	mob = inserir_inimigo(mob, 1);
	mob = inserir_inimigo(mob, 2);
	
	//Variaveis da personagem no mapa
	int PosX = 20,
		PosY = 100,
		PLarX = 30,
		PLarY = 14,
		MovX = 0,
		MovY = 0,
		PVel = 10;
	
	//Variaveis de controle
	int PG = 0,
		i = 0,
		j = 0,
		Imagem = 0,
		TelaLarX = 1024,
		TelaLarY = 576,
		SpritesN = 0;
	char Tecla = 0;
	long long unsigned Gt1, Gt2;
	int FPS = 60;
	
	bool PodeFazerInteracao = true,
		 CaixaDeTexto = false,
	 	 SpacePress = false;
	
	char *Arquivo;
	int DialogoPosX = 0,
		DialogoPosY = 0,
		DialogoPartToStart = 0,
		DialogoPartToStop = 0;
	 	 
	bool MudancaDeCenario = false;
	int MudancaDeCenarioNumero = 0;
	
	//Variaveis dos ponteiros das listas mapa.
	int TamanhoListaOC = 0,
		TamanhoListaRetangulosDeColisao = 0;
	
	//Ponteiro de structs para a lista de objetos do cenario.
	PosicoesD *listaObjetosC = NULL;
	
	//Ponteiro para a lista de retangulos de colisao.
	RetangulosDeColisao *ListaRetangulosDeColisao = NULL;
	
	//Baus
	int NumeroDeBaus = 2;
	int *Baus;
	Baus = (int *)malloc(sizeof(int) * NumeroDeBaus);
	
	Baus[0] = POCAO2;
	Baus[1] = POCAO;
	
	int Bau_AreaDeInteracao = 10;
	
	RetangulosDeColisao PosicaoBaus[NumeroDeBaus];
	
	PosicaoBaus[0].DisX = 700;
	PosicaoBaus[0].DisY = 300;
	PosicaoBaus[0].LarX = 50;
	PosicaoBaus[0].LarY = 50;
	
	PosicaoBaus[1].DisX = 680;
	PosicaoBaus[1].DisY = 370;
	PosicaoBaus[1].LarX = 50;
	PosicaoBaus[1].LarY = 50;
	
	PosicoesD BausCenaDesenho[NumeroDeBaus];
	
	BausCenaDesenho[0].IndIm = 0;
	BausCenaDesenho[1].IndIm = 0;
	
	BausCenaDesenho[0].VTroca = 50;
	BausCenaDesenho[1].VTroca = 50;
	
	BausCenaDesenho[0].DeslocamentoDaImagem = 10;
	BausCenaDesenho[1].DeslocamentoDaImagem = 10;
	
	//Variaveis do cenario
	int CPosX = -10,
		CPosY = -10,
		CenarioAtual = 0;
	
	CenarioInf Cenario[2];
	
	Cenario[0].LimiteCima = -10 + (PVel + 1); //Descontar um espaco equivalente a velocidade do personagem + 1, para evitar que a imagem do mapa possa sair da tela.
	Cenario[0].LimiteBaixo = -10 - (PVel + 1);
	Cenario[0].LimiteEsquerda = -10 + (PVel + 1);
	Cenario[0].LimiteDireita = -10 - (PVel + 1);
	
	Cenario[1].LimiteCima = -408 + (PVel + 1); //Descontar um espaco equivalente a velocidade do personagem + 1, para evitar que a imagem do mapa possa sair da tela.
	Cenario[1].LimiteBaixo = -16 - (PVel + 1);
	Cenario[1].LimiteEsquerda = -960 + (PVel + 1);
	Cenario[1].LimiteDireita = -20 - (PVel + 1);
	
	int NObjetos = 5;
	
	ObjetosCInf ObjetosC[NObjetos];
	
	ObjetosC[0].DisX = 120;
	ObjetosC[0].DisY = 150;
	
	ObjetosC[1].DisX = 360;
	ObjetosC[1].DisY = 360;
	
	ObjetosC[2].DisX = 70;
	ObjetosC[2].DisY = 400;
	
	ObjetosC[3].DisX = 1121; //Um objeto isometrico dividido em dois por causa da perspectiva.
	ObjetosC[3].DisY = 470;
	ObjetosC[4].DisX = 	ObjetosC[3].DisX + Cenario_Objetos_Tamanhos[3][0];
	ObjetosC[4].DisY = 	ObjetosC[3].DisY;
	
	PosicoesD ObjetosCenaDesenho[NObjetos];
	
	//O indice de imagem se refere a imagem que ele vai usar.
	ObjetosCenaDesenho[0].IndIm = 0;
	ObjetosCenaDesenho[1].IndIm = 1;
	ObjetosCenaDesenho[2].IndIm = 2;
	ObjetosCenaDesenho[3].IndIm = 3;
	ObjetosCenaDesenho[4].IndIm = 4;
	
	// O valor usado para organizar a listaObjetosC se refere a base inferior da imagem dos objetos,
	// o VTroca sera subtraido desse valor, para casos em que o ponto de troca tenha que ser em outro lugar.
	ObjetosCenaDesenho[0].VTroca = 0;
	ObjetosCenaDesenho[1].VTroca = 0;
	ObjetosCenaDesenho[2].VTroca = 20;
	ObjetosCenaDesenho[3].VTroca = 48;
	ObjetosCenaDesenho[4].VTroca = 96;
	
	PosicoesD PersonagemD;
	PersonagemD.Tipo = PER; //Se refere ao tipo de objeto que a struct representa, se e um personagem, npc, bau, objeto do cenario, etc.
	PersonagemD.PosY = PosY;
	PersonagemD.IndIm = 0;
	PersonagemD.Ind = 0;
	PersonagemD.VTroca = -PLarY;
	PersonagemD.DeslocamentoDaImagem = 83;
	
	PosicoesD ListaObjCenaTemp; //Struct para ser usada na hora do sort.
	
	//Portas (Se colidir com elas ocorre uma transicao de cenario)
	
	RetangulosDeColisao Portas[2];
	
	Portas[0].DisX = 36;
	Portas[0].DisY = 525;
	Portas[0].LarX = 140;
	Portas[0].LarY = 100;
	
	Portas[1].DisX = 322;
	Portas[1].DisY = 10;
	Portas[1].LarX = 100;
	Portas[1].LarY = 150;
	
	//Retangulos de Colisao de Teste
	
	RetangulosDeColisao RetanguloTeste[2];
	
	RetanguloTeste[0].DisX = 100;
	RetanguloTeste[0].DisY = 80;
	RetanguloTeste[0].LarX = 100;
	RetanguloTeste[0].LarY = 100;
	
	RetanguloTeste[1].DisX = 300;
	RetanguloTeste[1].DisY = 300;
	RetanguloTeste[1].LarX = 150;
	RetanguloTeste[1].LarY = 50;
	
	//Arrumar as posicoes de troca dos objetos do cenario.
	for(i=0; i < NObjetos; i++)
	{
		ObjetosCenaDesenho[i].Tipo = OBJ;
		ObjetosCenaDesenho[i].Ind = i; //Indice do struct, para ser usado quando chamar a lista de objetos.
		ObjetosCenaDesenho[i].DeslocamentoDaImagem = 0;
		ObjetosCenaDesenho[i].PosY = ObjetosC[i].DisY + Cenario_Objetos_Tamanhos[ObjetosCenaDesenho[i].IndIm][1] - ObjetosCenaDesenho[i].VTroca;
	}
	
	for(i=0; i < NumeroDeBaus; i++)
	{
		BausCenaDesenho[i].Tipo = BAU;
		BausCenaDesenho[i].Ind = i; //Indice do struct, para ser usado quando chamar a lista de objetos.
		BausCenaDesenho[i].PosY = PosicaoBaus[i].DisY + PosicaoBaus[i].LarY - BausCenaDesenho[i].VTroca;
	}
	
	initwindow(2000, 1000, "Dark Gears - Carregamento", 0, 0);
	
	//CarregarImagens
	
	CarregarImagens(STESTE);
	CarregarImagens(CCENTESTE);
	CarregarImagens(OCENTESTE);
	CarregarImagens(BAUS);
	CarregarImagens(RETRATOS);
	CarregarImagens(HUD);
	
	closegraph();
	
	//Codigo para liberar os ponteiros das imagens, precisa de testes para ver se nao buga e se realmente libera a memoria.
	
	/*
	
	printf("\n\nSprites: %d", sizeof(Sprites));
	printf("\nSpritesM: %d", sizeof(Sprites_Mascaras));
	printf("\nSprites[0]: %d", sizeof(Sprites[0]));
	printf("\nSpritesM[0]: %d", sizeof(Sprites_Mascaras[0]));

	for(i=0; i < SpritesQ; i++)
	{
		free(Sprites[i]);
		free(Sprites_Mascaras[i]);
	}
	
	for(i=0; i < Cenario_ObjetosQ; i++)
	{
		free(Cenario_Objetos[i]);
		free(Cenario_Objetos_Mascaras[i]);
	}
	
	printf("\n\nSprites: %d", sizeof(Sprites));
	printf("\nSpritesM: %d", sizeof(Sprites_Mascaras));
	printf("\nSprites[0]: %d", sizeof(Sprites[0]));
	printf("\nSpritesM[0]: %d", sizeof(Sprites_Mascaras[0]));
	
	CarregarImagens(STESTE);
	CarregarImagens(OCENTESTE);
	
	printf("\n\nSprites: %d", sizeof(Sprites));
	printf("\nSpritesM: %d", sizeof(Sprites_Mascaras));
	printf("\nSprites[0]: %d", sizeof(Sprites[0]));
	printf("\nSpritesM[0]: %d", sizeof(Sprites_Mascaras[0]));
	
	*/
	
	initwindow(TelaLarX, TelaLarY, "Dark Gears - Testes", 50, 30);
	
	iniciarBatalha(li, mob, Sprites_Retratos, Sprites_Retratos_Mascaras, Sprites_HUD, Sprites_HUD_Mascaras);
	
	Gt1 = GetTickCount();
  	Gt2 = Gt1;
	while(Tecla != ESC)
	{
		Gt2 = GetTickCount();
		if(Gt2 < Gt1)
		{
			Gt1 = Gt2;
		}
		if (Gt2 - Gt1 > 1000/FPS)
		{
			Gt1 = Gt2;
			
			//Esse codigo foi movido para o inicio da parte de colisao do personagem com o cenario.
			//Alterna a pagina de desenho ativa (para fazer o Buffer Duplo).
			//if(PG == 1)
			//{
				//PG = 2;
			//}
			//else
			//{
				//PG = 1;
			//}
			//setactivepage(PG);
			
			//Desenhos
	        
	        setbkcolor(RGB(200, 200, 200));
	        setfillstyle(1, RGB(133, 144, 200));
	        cleardevice();
			
			//Vai ser substituido pela funcao de desenhar o cenario em si depois.
	        desenhaCenario(CPosX, CPosY, Cenario_Colisao, CenarioAtual);
	        
	        //Cria a lista com os retangulos de colisao.
	        criarListaRetangulosDeColisao(CenarioAtual, RetanguloTeste, PosicaoBaus, &TamanhoListaRetangulosDeColisao, &ListaRetangulosDeColisao);
	        
			//Teste
			setfillstyle(0, RGB(130, 45, 70));
        	for(i = 0; i < TamanhoListaRetangulosDeColisao; i++)
			{
				bar(ListaRetangulosDeColisao[i].DisX + CPosX, ListaRetangulosDeColisao[i].DisY + CPosY, ListaRetangulosDeColisao[i].DisX + ListaRetangulosDeColisao[i].LarX + CPosX, ListaRetangulosDeColisao[i].DisY + ListaRetangulosDeColisao[i].LarY + CPosY);
			}
			
			//Arrumar a ordem (quem fica na frente de quem) dos objetos e da personagem, e desenha-los no mapa.
			//Cria a lista e a coloca em um ponteiro.
			criarListaObjetosC(CenarioAtual, CPosY, PosY, PersonagemD, ObjetosCenaDesenho, BausCenaDesenho, &TamanhoListaOC, &listaObjetosC);
			
			//Ordenar a lista
			for(i=0; i < TamanhoListaOC - 1; i++)
			{
				for(j=i+1; j < TamanhoListaOC; j++)
				{
					if(listaObjetosC[i].PosY > listaObjetosC[j].PosY)
					{
						ListaObjCenaTemp = listaObjetosC[i];
						listaObjetosC[i] = listaObjetosC[j];
						listaObjetosC[j] = ListaObjCenaTemp;
						
						//printf("\n\nEndereco de ListaOCT         = %p", &ListaObjCenaTemp);
						//printf("\nEndereco de listaObjetosC[j] = %p", &listaObjetosC[j]);
					}
				}
			}
			
			/*
			printf("\n\n");
			for(i=0; i < TamanhoListaOC; i++)
			{
				if(listaObjetosC[i].Tipo == PER)
				{
					printf("Per %d, ", listaObjetosC[i].Ind);
				}
				if(listaObjetosC[i].Tipo == OBJ)
				{
					printf("Obj %d, ", listaObjetosC[i].Ind);
				}
				if(listaObjetosC[i].Tipo == BAU)
				{
					printf("Bau %d, ", listaObjetosC[i].Ind);
				}
			}
			*/
			
			//Desenhar os objetos e a personagem
			
			if(CenarioAtual == 0)
			{
				i = 0;
				setfillstyle(4, RGB(23, 47, 180));
				bar(Portas[i].DisX + CPosX, Portas[i].DisY + CPosY, Portas[i].DisX + CPosX + Portas[i].LarX, Portas[i].DisY + CPosY + Portas[i].LarY);
			}
			
			if(CenarioAtual == 1)
			{
				i = 1;
				setfillstyle(4, RGB(23, 47, 180));
				bar(Portas[i].DisX + CPosX, Portas[i].DisY + CPosY, Portas[i].DisX + CPosX + Portas[i].LarX, Portas[i].DisY + CPosY + Portas[i].LarY);
			}
			
			//printf("\nPosX = %d, PosY = %d", PosX, PosY);
			//printf("\nCPosX = %d, CPosY = %d", CPosX, CPosY);
			
			for(i=0; i < TamanhoListaOC; i++)
			{
				if(listaObjetosC[i].Tipo == PER)
				{
					setfillstyle(1, RGB(133, 144, 200));
					bar(PosX, PosY, PosX + PLarX, PosY + PLarY);
					//setfillstyle(1, RGB(255, 242, 0));
					//bar(PosX - 50, PosY - 80, PosX + PLarX + 50, PosY + PLarY - 80);
					//putimage(PosX, PosY, Sprites_Mascaras[LILY], AND_PUT); //Primeiro a mascara.
					//putimage(PosX, PosY, Sprites[LILY], OR_PUT); //Depois a imagem normal.
					//putimage(PosX - 30, PosY - 60, Sprites_Mascaras[CHADDRIT], AND_PUT);
					//putimage(PosX - 30, PosY - 60, Sprites[CHADDRIT], OR_PUT);
					putimage(PosX - 13, PosY - PersonagemD.DeslocamentoDaImagem, Sprites_Mascaras[LILY3D], AND_PUT);
					putimage(PosX - 13, PosY - PersonagemD.DeslocamentoDaImagem, Sprites[LILY3D], OR_PUT);
				}
				
				if(listaObjetosC[i].Tipo == OBJ)
				{
					if(((CPosX + ObjetosC[listaObjetosC[i].Ind].DisX >= (0 - Cenario_Objetos_Tamanhos[listaObjetosC[i].IndIm][0])) && (CPosX + ObjetosC[listaObjetosC[i].Ind].DisX <= TelaLarX)) && ((CPosY + ObjetosC[listaObjetosC[i].Ind].DisY >= (0 - Cenario_Objetos_Tamanhos[listaObjetosC[i].IndIm][1])) && (CPosY + ObjetosC[listaObjetosC[i].Ind].DisY <= TelaLarY)))
					{
						putimage(CPosX + ObjetosC[listaObjetosC[i].Ind].DisX, CPosY + ObjetosC[listaObjetosC[i].Ind].DisY, Cenario_Objetos_Mascaras[listaObjetosC[i].IndIm], AND_PUT);
						putimage(CPosX + ObjetosC[listaObjetosC[i].Ind].DisX, CPosY + ObjetosC[listaObjetosC[i].Ind].DisY, Cenario_Objetos[listaObjetosC[i].IndIm], OR_PUT);
					}
				}
				
				if(listaObjetosC[i].Tipo == BAU)
				{
							
					if(((CPosX + PosicaoBaus[listaObjetosC[i].Ind].DisX >= (0 - Sprites_Baus_Tamanhos[listaObjetosC[i].IndIm][0])) && (CPosX + PosicaoBaus[listaObjetosC[i].Ind].DisX  <= TelaLarX)) && ((CPosY + PosicaoBaus[listaObjetosC[i].Ind].DisY - BausCenaDesenho[listaObjetosC[i].Ind].DeslocamentoDaImagem >= (0 - Sprites_Baus_Tamanhos[listaObjetosC[i].IndIm][1])) && (CPosY + ObjetosC[listaObjetosC[i].Ind].DisY - BausCenaDesenho[listaObjetosC[i].Ind].DeslocamentoDaImagem <= TelaLarY)))
					{
						if(Baus[listaObjetosC[i].Ind] == NADA)
						{
							putimage(CPosX + PosicaoBaus[listaObjetosC[i].Ind].DisX, CPosY + PosicaoBaus[listaObjetosC[i].Ind].DisY - BausCenaDesenho[listaObjetosC[i].Ind].DeslocamentoDaImagem, Sprites_Baus_Mascaras[listaObjetosC[i].IndIm + 1], AND_PUT);
							putimage(CPosX + PosicaoBaus[listaObjetosC[i].Ind].DisX, CPosY + PosicaoBaus[listaObjetosC[i].Ind].DisY - BausCenaDesenho[listaObjetosC[i].Ind].DeslocamentoDaImagem, Sprites_Baus[listaObjetosC[i].IndIm + 1], OR_PUT);
						}
						else
						{
							putimage(CPosX + PosicaoBaus[listaObjetosC[i].Ind].DisX, CPosY + PosicaoBaus[listaObjetosC[i].Ind].DisY - BausCenaDesenho[listaObjetosC[i].Ind].DeslocamentoDaImagem, Sprites_Baus_Mascaras[listaObjetosC[i].IndIm], AND_PUT);
							putimage(CPosX + PosicaoBaus[listaObjetosC[i].Ind].DisX, CPosY + PosicaoBaus[listaObjetosC[i].Ind].DisY - BausCenaDesenho[listaObjetosC[i].Ind].DeslocamentoDaImagem, Sprites_Baus[listaObjetosC[i].IndIm], OR_PUT);
						}
					}
				}
			}

			//Torna visivel a pagina de desenho.
			setvisualpage(PG);
			
			//Caixa de Texto
			if(CaixaDeTexto == true)
			{
				ReadDialogue(DialogoPosX, DialogoPosY, DialogoPartToStart, DialogoPartToStop, Arquivo, Sprites_Retratos, Sprites_Retratos_Mascaras, Sprites_HUD, Sprites_HUD_Mascaras);
				CaixaDeTexto = false;
				PodeFazerInteracao = true;
			}
			
			//Mexendo com a posicao da personagem
			if(PG == 1)
			{
				PG = 2;
			}
			else
			{
				PG = 1;
			}
			setactivepage(PG);
			
			setbkcolor(RGB(255, 255, 255));
	        cleardevice();
	        
	        //Vai chamar a funcao para desenhar a colisao do cenario.
	        desenhaCenario(CPosX, CPosY, Cenario_Colisao, CenarioAtual);
			
			// MovX mexe com o movimento no eixo X e MovY com o movimento no eixo Y.
			// Caso um deles um deles seja diferente de 0, o valor sera adicionado a posicao correspondente do personagem,
			// mas antes o codigo confere se ha colisao com a posicao que essa adicao ira resultar (ou se ela sai da tela),
			// se houver, o valor do MovX ou MovY sera diminuido ou aumentado (depende se o valor e menor ou maior que 0)
			// ate que nao haja mais colisao (ou que a posicao nao faca o personagem sair da tela, se for a razao do codigo
			// ter sido ativado), e entao ele sera adicionado a posicao do personagem.
			if(MovX > 0)
			{
				while(hitTestCenario(PosX + PLarX + MovX, PosY)||hitTestCenario(PosX + PLarX + MovX, PosY + PLarY/2)||hitTestCenario(PosX + PLarX + MovX, PosY + PLarY)||(PosX + PLarX + MovX) >= TelaLarX)
				{
					MovX --;
				}
				
				while(colisaoComRetangulos(CPosX, CPosY, PosX + MovX, PosY, PLarX, PLarY, TamanhoListaRetangulosDeColisao, ListaRetangulosDeColisao))
				{
					MovX --;
				}
				
				//Confere se o jogo vai fazer o scroll da tela ou nao.
				if((PosX > (TelaLarX/2 + 20) - PLarX/2) && (CPosX > Cenario[CenarioAtual].LimiteEsquerda))
				{
					CPosX -= MovX;
				}
				else
				{
					PosX += MovX;
				}
			}
			if(MovX < 0)
			{
				while(hitTestCenario(PosX + MovX, PosY)||hitTestCenario(PosX + MovX, PosY + PLarY/2)||hitTestCenario(PosX + MovX, PosY + PLarY)||(PosX + MovX) <= 0)
				{
					MovX ++;
				}
				
				while(colisaoComRetangulos(CPosX, CPosY, PosX + MovX, PosY, PLarX, PLarY, TamanhoListaRetangulosDeColisao, ListaRetangulosDeColisao))
				{
					MovX ++;
				}
				
				if((PosX < (TelaLarX/2 - 20) - PLarX/2) && (CPosX < Cenario[CenarioAtual].LimiteDireita))
				{
					CPosX -= MovX;
				}
				else
				{
					PosX += MovX;
				}
			}
			if(MovY > 0)
			{
				while(hitTestCenario(PosX, PosY + PLarY + MovY)||hitTestCenario(PosX + PLarX/2, PosY + PLarY + MovY)||hitTestCenario(PosX + PLarX, PosY + PLarY + MovY)||(PosY + PLarY + MovY) >= TelaLarY)
				{
					MovY --;
				}
				
				while(colisaoComRetangulos(CPosX, CPosY, PosX, PosY + MovY, PLarX, PLarY, TamanhoListaRetangulosDeColisao, ListaRetangulosDeColisao))
				{
					MovY --;
				}
				
				if((PosY > (TelaLarY/2 + 10) - PLarY/2) && (CPosY > Cenario[CenarioAtual].LimiteCima))
				{
					CPosY -= MovY;
				}
				else
				{
					PosY += MovY;
				}
			}
			if(MovY < 0)
			{
				while(hitTestCenario(PosX, PosY + MovY)||hitTestCenario(PosX + PLarX/2, PosY + MovY)||hitTestCenario(PosX + PLarX, PosY + MovY)||(PosY + MovY) <= 0)
				{
					MovY ++;
				}
				
				while(colisaoComRetangulos(CPosX, CPosY, PosX, PosY + MovY, PLarX, PLarY, TamanhoListaRetangulosDeColisao, ListaRetangulosDeColisao))
				{
					MovY ++;
				}
				
				if((PosY < (TelaLarY/2 - 10) - PLarY/2) && (CPosY < Cenario[CenarioAtual].LimiteBaixo))
				{
					CPosY -= MovY;
				}
				else
				{
					PosY += MovY;
				}
			}
			
			// Caso nenhuma das teclas esteja sendo pressionada, deixa o MovX ou Y igual a 0,
			// dependendo de qual conjunto de teclas nao estiver pressionado.
			if(!((GetKeyState(VK_RIGHT)&0x80) && (GetKeyState(VK_LEFT)&0x80)))
			{
				MovX = 0;
			}
			if(!((GetKeyState(VK_UP)&0x80) && (GetKeyState(VK_DOWN)&0x80)))
			{
				MovY = 0;
			}
			
			//Interacoes com o mapa.
			interacoesComOMapa(CenarioAtual, PosX, PosY, PLarX, PLarY, CPosX, CPosY, Bau_AreaDeInteracao, PosicaoBaus, NumeroDeBaus, &Baus, Baus, &PodeFazerInteracao, &SpacePress, &MudancaDeCenario, &MudancaDeCenarioNumero, Portas, &CaixaDeTexto, &Arquivo, &DialogoPosX, &DialogoPosY, &DialogoPartToStart, &DialogoPartToStop);
			
			//Transicoes de mapas.
			if(MudancaDeCenario == true)
			{
				TransicaoDeMapa(MudancaDeCenarioNumero, &CenarioAtual, &PosX, &PosY, &CPosX, &CPosY);
				MudancaDeCenario = false;
				PodeFazerInteracao = true;
			}
			
			//Comandos
			
			//Movimento
			//Tem como colocar aceleracao se quiser.
			//Muda o valor das variaveis que alteram a posicao da personagem.
			if(GetKeyState(VK_RIGHT)&0x80)
			{
				MovX = PVel;
			}
		    else if(GetKeyState(VK_LEFT)&0x80)
		    {
		    	MovX = -PVel;
			}
		    if(GetKeyState(VK_UP)&0x80)
		    {
		    	MovY = -PVel;
			}
		    else if(GetKeyState(VK_DOWN)&0x80)
		    {
		    	MovY = PVel;
			}
			
			if((GetKeyState(VK_SPACE)&0x80))
		    {
		    	SpacePress = true;
			}
			if(!(GetKeyState(VK_SPACE)&0x80))
	      	{
	      		SpacePress = false;
			}
			
			fflush(stdin); //Aparentemente limpa algum endereco de memoria.
			
			//Se alguma tecla for pressionada, coloca o valor dela na variavel Tecla.
			// Com essa funcao, ela so pode ter um valor por vez que o laco e rodado, entao pode ser
			// usada em alguma ocasiao em que duas teclas nao podem ser pressionadas de uma vez.
			if(kbhit())
			{
				Tecla = getch();
			}
		}
	}
	
	//Nao precisa usar free com esse ponteiro, por alguma razao (o C++ relata algum erro).
	//free(Sprites);
	
	//Liberar a memoria dos ponteiros.
	free(listaObjetosC);
	free(ListaRetangulosDeColisao);
			
	closegraph();	
	return 0; 
}

//Funcoes
bool hitTestCenario(int PosX,int PosY)
{
	//Testa a colisao vendo se o pixel na posicao dada e preto (com colisao) ou nao (sem colisao).
	
	int CorPixel = 0;
	bool Colisao = false;
	
	Colisao = false;
	
	CorPixel = getpixel(PosX, PosY);
	if(CorPixel == PRETO)
	{
		Colisao = true;
	}
	
	return Colisao;
}

bool colisaoComRetangulos(int CPosX, int CPosY, int PosX, int PosY, int PLarX, int PLarY, int TamanhoListaRetangulosDeColisao, RetangulosDeColisao ListaRetangulosDeColisao[])
{
	//Confere a colisao com retângulos.
	
	bool Colisao = false;
	
	for(int i = 0; i < TamanhoListaRetangulosDeColisao; i++)
	{
		if((PosX < ListaRetangulosDeColisao[i].DisX + ListaRetangulosDeColisao[i].LarX + CPosX) && (PosX + PLarX > ListaRetangulosDeColisao[i].DisX + CPosX) && (PosY < ListaRetangulosDeColisao[i].DisY + ListaRetangulosDeColisao[i].LarY + CPosY) && (PosY + PLarY > ListaRetangulosDeColisao[i].DisY + CPosY))
		{
			Colisao = true;
		}
	}
	
	return Colisao;
}

void CarregarImagens(int Imagem)
{
	//Muda as imagens a serem carregadas.
	// ! -> A BGI não salva imagens fora da tela, essas partes ficam pretas.
	switch(Imagem)
	{
		case STESTE:	
			//Sprites de teste
			
			cleardevice();
			setactivepage(1);
			
			setbkcolor(RGB(255, 255, 255));
			cleardevice();
			
			for(int i=0; i < SpritesQ; i++)
			{
				//StrcatTemp vai ser usada para juntar o nome do sprite com o tipo de arquivo
				//e, caso seja uma mascara, como o "_mascara".
				//strcpy(s1, s2) copia a segunda string na primeira.
				//strcat(s1, s2) adiciona a segunda string na primeira.
				strcpy(StrcatTemp, Sprites_Nomes[i]);
				
				// ! -> Como o 0 conta como 1 pixel, as posicoes x e y finais tem que ser 1 pixel menor
				//		que as dimensoes totais da imagem, para compensar o pixel "a mais" do 0.
				readimagefile(strcat(StrcatTemp, BMP), 0, 0, Sprites_Tamanhos[i][0]-1, Sprites_Tamanhos[i][1]-1); //Le uma imagem e copia ela para a tela.
			    Sprites[i] = malloc(imagesize(0, 0, Sprites_Tamanhos[i][0]-1, Sprites_Tamanhos[i][1]-1)); //Aloca a memoria necessaria para guardar a imagem na RAM.
				getimage(0, 0, Sprites_Tamanhos[i][0]-1, Sprites_Tamanhos[i][1]-1, Sprites[i]); //Copia a imagem na tela para a memoria.
			}
			
			for(int i=0; i < SpritesQ; i++)
			{
				strcpy(StrcatTemp, Sprites_Nomes[i]);
		
				readimagefile(strcat(StrcatTemp, MBMP), 0, 0, Sprites_Tamanhos[i][0]-1, Sprites_Tamanhos[i][1]-1);
			    Sprites_Mascaras[i] = malloc(imagesize(0, 0, Sprites_Tamanhos[i][0]-1, Sprites_Tamanhos[i][1]-1));
			    getimage(0, 0, Sprites_Tamanhos[i][0]-1, Sprites_Tamanhos[i][1]-1, Sprites_Mascaras[i]);
			}
			
			cleardevice();
			setactivepage(0);
			
			break;
		
		case CCENTESTE:
			//Colisao dos cenarios
			
			cleardevice();
			setactivepage(1);
			
			setbkcolor(RGB(255, 255, 255));
			cleardevice();
			
			for(int i=0; i < Cenario_ColisaoQ; i++)
			{
				strcpy(StrcatTemp, Cenario_Colisao_Nomes[i]);
				
				readimagefile(strcat(StrcatTemp, BMP), 0, 0, Cenario_Colisao_Tamanhos[i][0]-1, Cenario_Colisao_Tamanhos[i][1]-1);
			    Cenario_Colisao[i] = malloc(imagesize(0, 0, Cenario_Colisao_Tamanhos[i][0]-1, Cenario_Colisao_Tamanhos[i][1]-1));
			    getimage(0, 0, Cenario_Colisao_Tamanhos[i][0]-1, Cenario_Colisao_Tamanhos[i][1]-1, Cenario_Colisao[i]);
			}
			
			cleardevice();
			setactivepage(0);
			
			break;
		
		case OCENTESTE:
			//Objetos dos cenarios
			
			cleardevice();
			setactivepage(1);
			
			setbkcolor(RGB(255, 255, 255));
			cleardevice();
			
			for(int i=0; i < Cenario_ObjetosQ; i++)
			{
				strcpy(StrcatTemp, Cenario_Objetos_Nomes[i]);
		
				readimagefile(strcat(StrcatTemp, BMP), 0, 0, Cenario_Objetos_Tamanhos[i][0]-1, Cenario_Objetos_Tamanhos[i][1]-1);
			    Cenario_Objetos[i] = malloc(imagesize(0, 0, Cenario_Objetos_Tamanhos[i][0]-1, Cenario_Objetos_Tamanhos[i][1]-1));
			    getimage(0, 0, Cenario_Objetos_Tamanhos[i][0]-1, Cenario_Objetos_Tamanhos[i][1]-1, Cenario_Objetos[i]);
			}
			
			for(int i=0; i < Cenario_ObjetosQ; i++)
			{
				strcpy(StrcatTemp, Cenario_Objetos_Nomes[i]);
		
				readimagefile(strcat(StrcatTemp, MBMP), 0, 0, Cenario_Objetos_Tamanhos[i][0]-1, Cenario_Objetos_Tamanhos[i][1]-1);
			    Cenario_Objetos_Mascaras[i] = malloc(imagesize(0, 0, Cenario_Objetos_Tamanhos[i][0]-1, Cenario_Objetos_Tamanhos[i][1]-1));
			    getimage(0, 0, Cenario_Objetos_Tamanhos[i][0]-1, Cenario_Objetos_Tamanhos[i][1]-1, Cenario_Objetos_Mascaras[i]);
			}
			
			cleardevice();
			setactivepage(0);
			
			break;
		
		case BAUS:
			//Baus
			
			cleardevice();
			setactivepage(1);
			
			setbkcolor(RGB(255, 255, 255));
			cleardevice();
			
			for(int i=0; i < Sprites_BausQ; i++)
			{
				strcpy(StrcatTemp, Sprites_Baus_Nomes[i]);
		
				readimagefile(strcat(StrcatTemp, JPG), 0, 0, Sprites_Baus_Tamanhos[i][0]-1, Sprites_Baus_Tamanhos[i][1]-1);
			    Sprites_Baus[i] = malloc(imagesize(0, 0, Sprites_Baus_Tamanhos[i][0]-1, Sprites_Baus_Tamanhos[i][1]-1));
			    getimage(0, 0, Sprites_Baus_Tamanhos[i][0]-1, Sprites_Baus_Tamanhos[i][1]-1, Sprites_Baus[i]);
			}
			
			for(int i=0; i < Sprites_BausQ; i++)
			{
				strcpy(StrcatTemp, Sprites_Baus_Nomes[i]);
		
				readimagefile(strcat(StrcatTemp, MJPG), 0, 0, Sprites_Baus_Tamanhos[i][0]-1, Sprites_Baus_Tamanhos[i][1]-1);
			    Sprites_Baus_Mascaras[i] = malloc(imagesize(0, 0, Sprites_Baus_Tamanhos[i][0]-1, Sprites_Baus_Tamanhos[i][1]-1));
			    getimage(0, 0, Sprites_Baus_Tamanhos[i][0]-1, Sprites_Baus_Tamanhos[i][1]-1, Sprites_Baus_Mascaras[i]);
			}
			
			cleardevice();
			setactivepage(0);
			
			break;
		
		case RETRATOS:
			//Retratos dos personagens
			
			cleardevice();
			setactivepage(1);
			
			setbkcolor(RGB(255, 255, 255));
			cleardevice();
			
			for(int i=0; i < Sprites_RetratosQ; i++)
			{
				strcpy(StrcatTemp, Sprites_Retratos_Nomes[i]);
		
				readimagefile(strcat(StrcatTemp, BMP), 0, 0, Sprites_Retratos_Tamanhos[i][0]-1, Sprites_Retratos_Tamanhos[i][1]-1);
			    Sprites_Retratos[i] = malloc(imagesize(0, 0, Sprites_Retratos_Tamanhos[i][0]-1, Sprites_Retratos_Tamanhos[i][1]-1));
			    getimage(0, 0, Sprites_Retratos_Tamanhos[i][0]-1, Sprites_Retratos_Tamanhos[i][1]-1, Sprites_Retratos[i]);
			}
			
			for(int i=0; i < Sprites_RetratosQ; i++)
			{
				strcpy(StrcatTemp, Sprites_Retratos_Nomes[i]);
		
				readimagefile(strcat(StrcatTemp, MBMP), 0, 0, Sprites_Retratos_Tamanhos[i][0]-1, Sprites_Retratos_Tamanhos[i][1]-1);
			    Sprites_Retratos_Mascaras[i] = malloc(imagesize(0, 0, Sprites_Retratos_Tamanhos[i][0]-1, Sprites_Retratos_Tamanhos[i][1]-1));
			    getimage(0, 0, Sprites_Retratos_Tamanhos[i][0]-1, Sprites_Retratos_Tamanhos[i][1]-1, Sprites_Retratos_Mascaras[i]);
			}
			
			cleardevice();
			setactivepage(0);
			
			break;
		
		case HUD:
			//Imagens do HUD
			
			cleardevice();
			setactivepage(1);
			
			setbkcolor(RGB(255, 255, 255));
			cleardevice();
			
			for(int i=0; i < Sprites_HUDQ; i++)
			{
				strcpy(StrcatTemp, Sprites_HUD_Nomes[i]);
		
				readimagefile(strcat(StrcatTemp, BMP), 0, 0, Sprites_HUD_Tamanhos[i][0]-1, Sprites_HUD_Tamanhos[i][1]-1);
			    Sprites_HUD[i] = malloc(imagesize(0, 0, Sprites_HUD_Tamanhos[i][0]-1, Sprites_HUD_Tamanhos[i][1]-1));
			    getimage(0, 0, Sprites_HUD_Tamanhos[i][0]-1, Sprites_HUD_Tamanhos[i][1]-1, Sprites_HUD[i]);
			}
			
			for(int i=0; i < Sprites_HUDQ; i++)
			{
				strcpy(StrcatTemp, Sprites_HUD_Nomes[i]);
		
				readimagefile(strcat(StrcatTemp, MBMP), 0, 0, Sprites_HUD_Tamanhos[i][0]-1, Sprites_HUD_Tamanhos[i][1]-1);
			    Sprites_HUD_Mascaras[i] = malloc(imagesize(0, 0, Sprites_HUD_Tamanhos[i][0]-1, Sprites_HUD_Tamanhos[i][1]-1));
			    getimage(0, 0, Sprites_HUD_Tamanhos[i][0]-1, Sprites_HUD_Tamanhos[i][1]-1, Sprites_HUD_Mascaras[i]);
			}
			
			cleardevice();
			setactivepage(0);
			
			break;
		
		default:
		printf("\nRaios multiplos! O operador esta incorreto.");
	}
}

void interacoesComOMapa(int CenarioAtual, int PosX, int PosY, int PLarX, int PLarY, int CPosX, int CPosY, int Bau_AreaDeInteracao, RetangulosDeColisao PosicaoBaus[], int NumeroDeBaus, int **Baus, int BausCopia[], bool *PodeFazerInteracao, bool *SpacePress, bool *MudancaDeCenario, int *MudancaDeCenarioNumero, RetangulosDeColisao Portas[], bool *CaixaDeTexto, char **Arquivo, int *DialogoPosX, int *DialogoPosY, int *DialogoPartToStart, int *DialogoPartToStop)
{
	// Funcao onde vamos tentar colocar todas as interacoes com o mapa. Vai depender do mapa atual.
	// Interacoes como abrir baus, apertar botoes, falr com NPCs, e as transicoes dos mapas.
	// A variavel global PodeFazerInteracao sera usada para limitar a uma interacao por vez.
	switch(CenarioAtual)
	{
		case 0:
			{
				int InteracaoN = 0;
				
				//Baus no mapa.
				
				InteracaoN = 0;
				if(!(BausCopia[InteracaoN] == NADA) && *PodeFazerInteracao == true)
				{
					if((PosX < PosicaoBaus[InteracaoN].DisX + PosicaoBaus[InteracaoN].LarX + CPosX + Bau_AreaDeInteracao) && (PosX + PLarX > PosicaoBaus[InteracaoN].DisX + CPosX - Bau_AreaDeInteracao) && (PosY < PosicaoBaus[InteracaoN].DisY + PosicaoBaus[InteracaoN].LarY + CPosY + Bau_AreaDeInteracao) && (PosY + PLarY > PosicaoBaus[InteracaoN].DisY + CPosY - Bau_AreaDeInteracao))
					{
						if((GetKeyState(VK_SPACE)&0x80) && *SpacePress == false)
					    {
					    	int *BausTemp;
					    	BausTemp = (int *)malloc(sizeof(int) * NumeroDeBaus);
					    	
					    	BausCopia[InteracaoN] = NADA;
					    	
					    	for(int i=0; i < NumeroDeBaus; i++)
					    	{
					    		BausTemp[i] = BausCopia[i];
							}
							
							free(*Baus);
							*Baus = BausTemp;
							*Arquivo = (char *)malloc(sizeof(char) * 17);
					    	strcpy(*Arquivo, "Textos/Teste.txt");
					    	
					    	*DialogoPosX = 169,
							*DialogoPosY = 435,
							*DialogoPartToStart = 36,
							*DialogoPartToStop = 37;
							
					    	*PodeFazerInteracao = false;
					    	*CaixaDeTexto = true;
						}
					}
				}
				
				InteracaoN = 1;
				if(!(BausCopia[InteracaoN] == NADA) && *PodeFazerInteracao == true)
				{
					if((PosX < PosicaoBaus[InteracaoN].DisX + PosicaoBaus[InteracaoN].LarX + CPosX + Bau_AreaDeInteracao) && (PosX + PLarX > PosicaoBaus[InteracaoN].DisX + CPosX - Bau_AreaDeInteracao) && (PosY < PosicaoBaus[InteracaoN].DisY + PosicaoBaus[InteracaoN].LarY + CPosY + Bau_AreaDeInteracao) && (PosY + PLarY > PosicaoBaus[InteracaoN].DisY + CPosY - Bau_AreaDeInteracao))
					{
						if((GetKeyState(VK_SPACE)&0x80) && *SpacePress == false)
					    {
					    	int *BausTemp;
					    	BausTemp = (int *)malloc(sizeof(int) * NumeroDeBaus);
					    	
					    	BausCopia[InteracaoN] = NADA;
					    	
					    	for(int i=0; i < NumeroDeBaus; i++)
					    	{
					    		BausTemp[i] = BausCopia[i];
							}
							
							free(*Baus);
							*Baus = BausTemp;
							
							free(*Baus);
							*Baus = BausTemp;
							*Arquivo = (char *)malloc(sizeof(char) * 17);
					    	strcpy(*Arquivo, "Textos/Teste.txt");
					    	
					    	*DialogoPosX = 169,
							*DialogoPosY = 30,
							*DialogoPartToStart = 38,
							*DialogoPartToStop = 40;
							
					    	*PodeFazerInteracao = false;
					    	*CaixaDeTexto = true;
						}
					}
				}
				
				//Dialogos
				InteracaoN = 0;
				if((PosX < PosicaoBaus[InteracaoN].DisX + PosicaoBaus[InteracaoN].LarX + CPosX + Bau_AreaDeInteracao) && (PosX + PLarX > PosicaoBaus[InteracaoN].DisX + CPosX - Bau_AreaDeInteracao) && (PosY < PosicaoBaus[InteracaoN].DisY + PosicaoBaus[InteracaoN].LarY + CPosY + Bau_AreaDeInteracao) && (PosY + PLarY > PosicaoBaus[InteracaoN].DisY + CPosY - Bau_AreaDeInteracao))
				{
					if((GetKeyState(VK_SPACE)&0x80) && *SpacePress == false && *PodeFazerInteracao == true)
				    {
				    	*Arquivo = (char *)malloc(sizeof(char) * 17);
				    	strcpy(*Arquivo, "Textos/Teste.txt");
				    	
				    	*DialogoPosX = 229,
						*DialogoPosY = 435,
						*DialogoPartToStart = 2,
						*DialogoPartToStop = 9;
						
				    	*PodeFazerInteracao = false;
				    	*CaixaDeTexto = true;
					}
				}
				
				InteracaoN = 1;
				if((PosX < PosicaoBaus[InteracaoN].DisX + PosicaoBaus[InteracaoN].LarX + CPosX + Bau_AreaDeInteracao) && (PosX + PLarX > PosicaoBaus[InteracaoN].DisX + CPosX - Bau_AreaDeInteracao) && (PosY < PosicaoBaus[InteracaoN].DisY + PosicaoBaus[InteracaoN].LarY + CPosY + Bau_AreaDeInteracao) && (PosY + PLarY > PosicaoBaus[InteracaoN].DisY + CPosY - Bau_AreaDeInteracao))
				{
					if((GetKeyState(VK_SPACE)&0x80) && *SpacePress == false && *PodeFazerInteracao == true)
				    {
				    	*Arquivo = (char *)malloc(sizeof(char) * 17);
				    	strcpy(*Arquivo, "Textos/Teste.txt");
				    	
				    	*DialogoPosX = 229,
						*DialogoPosY = 130,
						*DialogoPartToStart = 11,
						*DialogoPartToStop = 21;
						
				    	*PodeFazerInteracao = false;
				    	*CaixaDeTexto = true;
					}
				}
				
				//Portas
				
				InteracaoN = 0;
				if(*PodeFazerInteracao == true)
				{
					if((PosX < Portas[InteracaoN].DisX + Portas[InteracaoN].LarX + CPosX) && (PosX + PLarX > Portas[InteracaoN].DisX + CPosX) && (PosY < Portas[InteracaoN].DisY + Portas[InteracaoN].LarY + CPosY) && (PosY + PLarY > Portas[InteracaoN].DisY + CPosY))
					{
						*MudancaDeCenario = true;
						*MudancaDeCenarioNumero = InteracaoN;
						*PodeFazerInteracao = false;
					}	
				}
				
				break;
			}
		
		case 1:
			{
				int InteracaoN = 0;
				
				//Portas
				
				InteracaoN = 1;
				if(*PodeFazerInteracao == true)
				{
					if((PosX < Portas[InteracaoN].DisX + Portas[InteracaoN].LarX + CPosX) && (PosX + PLarX > Portas[InteracaoN].DisX + CPosX) && (PosY < Portas[InteracaoN].DisY + Portas[InteracaoN].LarY + CPosY) && (PosY + PLarY > Portas[InteracaoN].DisY + CPosY))
					{
						*MudancaDeCenario = true;
						*MudancaDeCenarioNumero = InteracaoN;
						*PodeFazerInteracao = false;
					}	
				}
				
				break;
			}
			
	}
}
