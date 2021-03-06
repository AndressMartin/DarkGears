#include<stdio.h> //Biblioteca padrao
#include<stdlib.h> //Biblioteca padrao
#include<graphics.h> //BGI
#include<conio.h> //kbhit e getch
#include<time.h> //Tempo
#include<string.h> //Funcoes de string

#include "structs.h"
#include "enums.h"
#include "listasDoMapa.h"
#include "desenhosDoMapa.h"
#include "listaEncadeadaPersonagem.h"
#include "batalha.h"
#include "caixaDeDialogo.h"
#include "reproduzirSons.h"
#include "menuInventario.h"
#include "interacoesComOMapa.h"

#define LEFT   	75
#define RIGHT  	77
#define UP     	72
#define DOWN   	80
#define ESC     27
#define MENU 	112

#define TECLAENTER		13
#define TECLABACKSPACE	8

#define PRETO 0
						  
//Ponteiros com as imagens
char Tipo[13] = "Nice",
	 JPG[5] = ".jpg",
	 BMP[5] = ".bmp",
	 CBMP[13] = "_colisao.bmp",
	 MBMP[13] = "_mascara.bmp",
	 MJPG[13] = "_mascara.jpg";
char StrcatTemp[50] = "Yes"; //O numero de caracteres tem que ser grande para ser usado no carregaento de imagens.

//Imagens

//Vai guardar as imagens.
const int SpritesQ = 3; //Quantidade de sprites, vai ser usado nas outras listas para facilitar mudancas.
void* Sprites[SpritesQ];
void* Sprites_Mascaras[SpritesQ];

const int CenarioQ = 2;
void* Sprites_Cenario[CenarioQ];
void* Cenario_Colisao[CenarioQ];

const int Cenario_ObjetosQ = 5;
void* Cenario_Objetos[Cenario_ObjetosQ];
void* Cenario_Objetos_Mascaras[Cenario_ObjetosQ];

const int Cenario_BatalhaQ = 2;
void* Cenario_Batalha[Cenario_BatalhaQ];

const int Sprites_BausQ = 2;
void* Sprites_Baus[Sprites_BausQ];
void* Sprites_Baus_Mascaras[Sprites_BausQ];

const int Sprites_RetratosQ = 22;
void* Sprites_Retratos[Sprites_RetratosQ];
void* Sprites_Retratos_Mascaras[Sprites_RetratosQ];

const int Sprites_HUDQ = 20;
void* Sprites_HUD[Sprites_HUDQ];
void* Sprites_HUD_Mascaras[Sprites_HUDQ];

const int Sprites_MobsQ = 3;
void* Sprites_Mobs[Sprites_MobsQ];
void* Sprites_Mobs_Mascaras[Sprites_MobsQ];

const int Sprites_InimigosMapaQ = 6;
void* Sprites_InimigosMapa[Sprites_InimigosMapaQ];
void* Sprites_InimigosMapa_Mascaras[Sprites_InimigosMapaQ];

const int Sprites_EfeitosQ = 13;
void* Sprites_Efeitos[Sprites_EfeitosQ];
void* Sprites_Efeitos_Mascaras[Sprites_EfeitosQ];

//Nomes e caminhos dos arquivos, sem o tipo, para poder ser usado pelo codigo das mascaras tambem.
// "17"" pois tem que considerar o caractere nulo "\0" que fica no final de uma string.
char Sprites_Nomes[SpritesQ][25] = {"Sprites/imagem01",
							 		"Sprites/imagem02",
									"Sprites/fox_prototype4_2"};

char Cenario_Nomes[CenarioQ][30] = {"Sprites/Cenarios/area1",
									"Sprites/Cenarios/Cenario01_02"};

char Cenario_Batalha_Nomes[Cenario_BatalhaQ][35] = {"Sprites/Cenarios/cenario_Batalha1",
											  		"Sprites/Cenarios/cenario_Batalha2"};

char Cenario_Objetos_Nomes[Cenario_ObjetosQ][38] = {"Sprites/ObjetoC_Teste_01-1",
							 						"Sprites/ObjetoC_Teste_01-2",
													"Sprites/ObjetoC_Teste_01-3",
													"Sprites/Cenarios/ObjetoC_Teste_02-1#1",
													"Sprites/Cenarios/ObjetoC_Teste_02-1#2"};

char Sprites_Retratos_Nomes[Sprites_RetratosQ][46] = {"Sprites/Retratos/lily",
									 				  "Sprites/Retratos/morcego",
													  "Sprites/Retratos/lily_batalha",
													  "Sprites/Retratos/lily_batalha_atacando",
													  "Sprites/Retratos/lily_batalha_levandoDano",
													  "Sprites/Retratos/lily_batalha_semHP",
													  "Sprites/Retratos/chaddrit_batalha",
													  "Sprites/Retratos/chaddrit_batalha_atacando",
													  "Sprites/Retratos/chaddrit_batalha_levandoDano",
													  "Sprites/Retratos/chaddrit_batalha_semHP",
													  "Sprites/Retratos/cafeMarrom_Pequeno",
													  "Sprites/Retratos/caracol",
													  "Sprites/Retratos/golem",
													  "Sprites/Retratos/potionSmall",
													  "Sprites/Retratos/potionSmall2",
													  "Sprites/Retratos/potionSmall3",
													  "Sprites/Retratos/lily_scared",
													  "Sprites/Retratos/lily_scared_clear",
													  "Sprites/Retratos/lily_smirk",
													  "Sprites/Retratos/chaddrit",
													  "Sprites/Retratos/chaddrit_mee",
													  "Sprites/Retratos/wumpus"};
									 				
char Sprites_HUD_Nomes[Sprites_HUDQ][38] = {"Sprites/HUD/caixa_de_texto",
											"Sprites/HUD/menuDeBatalha_1",
											"Sprites/HUD/menuDeBatalha_2",
											"Sprites/HUD/menuDeBatalha_3",
											"Sprites/HUD/selecao_monstros",
											"Sprites/HUD/menuDeBatalha_resultados",
											"Sprites/HUD/menuDeBatalha_resultados2",
											"Sprites/HUD/menuDeBatalha_4",
											"Sprites/HUD/telaDeTitulo",
											"Sprites/HUD/jogar",
											"Sprites/HUD/creditos",
											"Sprites/HUD/sair",
											"Sprites/HUD/telaDeCreditos",
											"Sprites/HUD/menuInventario_1",
											"Sprites/HUD/atacar",
											"Sprites/HUD/habilidades",
											"Sprites/HUD/habilidades2",
											"Sprites/HUD/itens",
											"Sprites/HUD/correr",
											"Sprites/HUD/correr2"};
											
char Sprites_Mobs_Nomes[Sprites_MobsQ][27] = {"Sprites/Mobs/golem",
											  "Sprites/Mobs/wumpus",
											  "Sprites/Mobs/Lesma_batalha"};

char Sprites_InimigosMapa_Nomes[Sprites_InimigosMapaQ][26] = {"Sprites/Mobs/golem_mapa",
															  "Sprites/Mobs/golem_mapa2",
															  "Sprites/Mobs/golem_mapa3",
															  "Sprites/Mobs/golem_mapa4",
											  				  "Sprites/Mobs/wumpus_mapa",
															  "Sprites/Mobs/caracol_mapa"};

char Sprites_Efeitos_Nomes[Sprites_EfeitosQ][25] = {"Sprites/Efeitos/golpe",
													"Sprites/Efeitos/cura1-1",
													"Sprites/Efeitos/cura1-2",
													"Sprites/Efeitos/cura1-3",
													"Sprites/Efeitos/cura2-1",
													"Sprites/Efeitos/cura2-2",
													"Sprites/Efeitos/cura2-3",
													"Sprites/Efeitos/cura3-1",
													"Sprites/Efeitos/cura3-2",
													"Sprites/Efeitos/cura3-3",
													"Sprites/Efeitos/reviver1",
													"Sprites/Efeitos/reviver2",
													"Sprites/Efeitos/reviver3"};

//Organizacao = {Bau01 fechado, Bau01 aberto, Bau02 fechado, Bau02 aberto, ...}
char Sprites_Baus_Nomes[Sprites_BausQ][16] = {"Sprites/bau01-F",
							 				  "Sprites/bau01-A"};

//Vai guardas a largura e altura das imagens, respectivamente.
int Sprites_Tamanhos[SpritesQ][2] = {{100, 50},
							  		 {70, 50},
									 {64, 128}};

int Cenario_Tamanhos[CenarioQ][2] = {{1024, 576},
									 {2000, 1000}};

int Cenario_Batalha_Tamanhos[Cenario_BatalhaQ][2] = {{1024, 576},
									 				{1024, 576}};

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
													   {85, 74},
													   {85, 74},
													   {85, 74},
													   {85, 74},
													   {85, 74},
													   {85, 74},
													   {85, 74},
													   {85, 74},
													   {85, 74},
													   {85, 74},
													   {85, 74},
													   {85, 74},
													   {85, 74},
													   {180, 220},
													   {180, 220},
													   {180, 220},
													   {180, 220},
													   {180, 220},
													   {85, 74}};

int Sprites_HUD_Tamanhos[Sprites_HUDQ][2] = {{686, 115},
											 {970, 220},
											 {460, 74},
											 {326, 74},
											 {85, 74},
											 {625, 295},
											 {625, 74},
											 {410, 74},
											 {1024, 576},
											 {230, 45},
											 {230, 45},
											 {230, 45},
											 {1024, 576},
											 {280, 74},
											 {360, 45},
											 {360, 45},
											 {360, 45},
											 {360, 45},
											 {360, 45},
											 {360, 45}};
											 
int Sprites_Mobs_Tamanhos[Sprites_MobsQ][2] = {{275, 275},
											   {275, 275},
											   {275, 275}};

int Sprites_InimigosMapa_Tamanhos[Sprites_InimigosMapaQ][2] = {{128, 128},
															   {128, 128},
															   {128, 128},
															   {128, 128},
											   				   {100, 100},
															   {64, 64}};

int Sprites_Efeitos_Tamanhos[Sprites_EfeitosQ][2] = {{150, 150},
													 {85, 74},
													 {85, 74},
													 {85, 74},
													 {85, 74},
													 {85, 74},
													 {85, 74},
													 {85, 74},
													 {85, 74},
													 {85, 74},
													 {85, 74},
													 {85, 74},
													 {85, 74}};

//Definicao das funcoes, as funcoes em si estao depois do main.
void CarregarImagens(int Imagem);
bool hitTestCenario(int PosX, int PosY);
bool colisaoComRetangulos(int CPosX, int CPosY, int PosX, int PosY, int PLarX, int PLarY, int TamanhoListaRetangulosDeColisao, RetangulosDeColisao ListaRetangulosDeColisao[]);

int main()
{
	//Lista dos peronagens, inimigos e itens
	Personagens *li = lista_cria(),
				*mob = lista_cria();
	
	Consumivel *lista_consumiveis = lista_consumiveis_cria();
	Consumivel *lcAux = lista_consumiveis_cria();
	
	Item item[5];
	Consumivel itemconsumivel[4];
	
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
    
    // Carregando propriedades dos itens consumiveis em structs
    strcpy(itemconsumivel[POCAO].nome, "Pocao");
    itemconsumivel[POCAO].id = POCAO + 1;
	itemconsumivel[POCAO].tipo = POCAO;
	itemconsumivel[POCAO].qtd = 1;
	
	strcpy(itemconsumivel[POCAO2].nome, "Super Pocao");
    itemconsumivel[POCAO2].id = POCAO2 + 1;
	itemconsumivel[POCAO2].tipo = POCAO2;
	itemconsumivel[POCAO2].qtd = 1;
	
	strcpy(itemconsumivel[POCAO3].nome, "Mega Pocao");
    itemconsumivel[POCAO3].id = POCAO3 + 1;
	itemconsumivel[POCAO3].tipo = POCAO3;
	itemconsumivel[POCAO3].qtd = 1;
	
	strcpy(itemconsumivel[CAFE].nome, "Cafe");
    itemconsumivel[CAFE].id = CAFE + 1;
	itemconsumivel[CAFE].tipo = CAFE;
	itemconsumivel[CAFE].qtd = 1;
	
	lista_consumiveis = lista_consumiveis_insere(lista_consumiveis, &itemconsumivel[POCAO]);
	lista_consumiveis = lista_consumiveis_insere(lista_consumiveis, &itemconsumivel[CAFE]);
	lista_consumiveis = lista_consumiveis_insere(lista_consumiveis, &itemconsumivel[POCAO2]);
	lista_consumiveis = lista_consumiveis_insere(lista_consumiveis, &itemconsumivel[POCAO3]);
	lista_consumiveis = lista_consumiveis_insere(lista_consumiveis, &itemconsumivel[POCAO3]);
	lista_consumiveis = lista_consumiveis_insere(lista_consumiveis, &itemconsumivel[POCAO]);
    
	//Definindo personagens e seus status
	char lily [5]  = "Lily";
	char cueio [9] = "Chaddrit";
	char quem [9] = "Qsou eu?";
	char golem[6] = "Golem";
	char wumpus[7] = "Wumpus";
	char caracol[8] = "Caracol";
	
	li = lista_insere(li, 1, lily, 20, 10, 70, 12, 5, 1, 100, 0);
	li = lista_insere(li, 2, cueio, 30, 6, 80, 8, 15, 5, 200, 115);
	//li = lista_insere(li, 3, quem, 99, 99, 99, 99, 99, 99, 999, 0);
	
	//Equipando os itens nos personagens, � preciso passar a party, o indice do personagem da party e o item que deseja equipar
	li = equipa_item(li, 1, &item[0]);
	li = equipa_item(li, 1, &item[1]);
	li = equipa_item(li, 1, &item[2]);
	
	/*
	detalhaConsumiveis(lista_consumiveis);
	system("pause");
	
	lista_consumiveis = utilizar_consumivel(lista_consumiveis, 2, li, 1);
	
	detalhaConsumiveis(lista_consumiveis);
	system("pause");
	
	lista_consumiveis = utilizar_consumivel(lista_consumiveis, 2, li, 1);
	
	detalhaConsumiveis(lista_consumiveis);
	system("pause");
	
	lista_consumiveis = utilizar_consumivel(lista_consumiveis, 0, li, 1);
	
	detalhaConsumiveis(lista_consumiveis);
	system("pause");
	
	lista_consumiveis = utilizar_consumivel(lista_consumiveis, 1, li, 1);
	
	detalhaConsumiveis(lista_consumiveis);
	system("pause");*/
	
	//Insere inimigos na lista
	mob = lista_insere(mob, 2, wumpus, 25, 19, 80, 9, 20, 2, 200, 10);
	mob = lista_insere(mob, 1, golem, 20, 18, 50, 6, 5, 1, 300, 15);
	mob = lista_insere(mob, 3, wumpus, 99, 19, 80, 9, 20, 2, 200, 10);
	
	//mob = inserir_inimigo(mob, 1);
	
	//Variaveis da personagem no mapa
	int PosX = 8,
		PosY = 308,
		PLarX = 30,
		PLarY = 14,
		MovX = 0,
		MovY = 0,
		PVel = 5;
	
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
	
	bool fecharJogo = false;
	int telaDoJogo = MENUINICIAL,
		Selecao = 0,
		MenuID = 0;
	
	bool PodeFazerInteracao = true,
		 CaixaDeTexto = false,
		 IniciarBatalha = false,
		 AdicionarItem = false,
	 	 SpacePress = false,
	 	 podeFugirVar = true;
	
	int AdicionarItemIndice = 0,
		InimigoIndice = 0,
		MusicaDoCenario = 0,
		MusicaDaBatalha = 0;
	
	char *Arquivo = NULL,
		 MudancaDeTexto[20] = "Mudanca";
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
	
	//Baus -------------------------------------------------------------------------------------------------------------------
	int NumeroDeBaus = 5;
	int *Baus;
	Baus = (int *)malloc(sizeof(int) * NumeroDeBaus);
	
	Baus[0] = POCAO;
	Baus[1] = CAFE;
	Baus[2] = POCAO2;
	Baus[3] = POCAO3;
	Baus[4] = CAFE;
	
	int Bau_AreaDeInteracao = 10;
	
	RetangulosDeColisao PosicaoBaus[NumeroDeBaus];
	
	PosicaoBaus[0].DisX = 355;
	PosicaoBaus[0].DisY = 552;
	PosicaoBaus[0].LarX = 50;
	PosicaoBaus[0].LarY = 20;
	
	PosicaoBaus[1].DisX = 464;
	PosicaoBaus[1].DisY = 516;
	PosicaoBaus[1].LarX = 50;
	PosicaoBaus[1].LarY = 20;
	
	PosicaoBaus[2].DisX = 114;
	PosicaoBaus[2].DisY = 203;
	PosicaoBaus[2].LarX = 50;
	PosicaoBaus[2].LarY = 20;
	
	PosicaoBaus[3].DisX = 406;
	PosicaoBaus[3].DisY = 298;
	PosicaoBaus[3].LarX = 50;
	PosicaoBaus[3].LarY = 20;
	
	PosicaoBaus[4].DisX = 528;
	PosicaoBaus[4].DisY = 106;
	PosicaoBaus[4].LarX = 50;
	PosicaoBaus[4].LarY = 20;
	
	PosicoesD BausCenaDesenho[NumeroDeBaus];
	
	BausCenaDesenho[0].IndIm = 0;
	BausCenaDesenho[1].IndIm = 0;
	BausCenaDesenho[2].IndIm = 0;
	BausCenaDesenho[3].IndIm = 0;
	BausCenaDesenho[4].IndIm = 0;
	
	BausCenaDesenho[0].VTroca = 19;
	BausCenaDesenho[1].VTroca = 19;
	BausCenaDesenho[2].VTroca = 19;
	BausCenaDesenho[3].VTroca = 19;
	BausCenaDesenho[4].VTroca = 19;
	
	BausCenaDesenho[0].DeslocamentoDaImagem = 40;
	BausCenaDesenho[1].DeslocamentoDaImagem = 40;
	BausCenaDesenho[2].DeslocamentoDaImagem = 40;
	BausCenaDesenho[3].DeslocamentoDaImagem = 40;
	BausCenaDesenho[4].DeslocamentoDaImagem = 40;
	
	//Inimigos --------------------------------------------------------------------------------------------------------------------
	int NInimigos = 6;
	int inimigoIndice = 0;
	
	//Lista dizendo se o inimigo esta ativo ou nao.
	bool *InimigosVivos;
	InimigosVivos = (bool *)malloc(sizeof(bool) * NInimigos);
	
	for(i=0; i < NInimigos; i++)
	{
		InimigosVivos[i] = true;
	}
	
	//Posicoes
	RetangulosDeColisao InimigosPosicoes[NInimigos];
	
	InimigosPosicoes[0].DisX = 275;
	InimigosPosicoes[0].DisY = 480;
	InimigosPosicoes[0].LarX = 40;
	InimigosPosicoes[0].LarY = 20;
	
	InimigosPosicoes[1].DisX = 350;
	InimigosPosicoes[1].DisY = 410;
	InimigosPosicoes[1].LarX = 90;
	InimigosPosicoes[1].LarY = 30;
	
	InimigosPosicoes[2].DisX = 212;
	InimigosPosicoes[2].DisY = 270;
	InimigosPosicoes[2].LarX = 40;
	InimigosPosicoes[2].LarY = 20;
	
	InimigosPosicoes[3].DisX = 381;
	InimigosPosicoes[3].DisY = 97;
	InimigosPosicoes[3].LarX = 92;
	InimigosPosicoes[3].LarY = 40;
	
	InimigosPosicoes[4].DisX = 638;
	InimigosPosicoes[4].DisY = 314;
	InimigosPosicoes[4].LarX = 92;
	InimigosPosicoes[4].LarY = 40;
	
	InimigosPosicoes[5].DisX = 886;
	InimigosPosicoes[5].DisY = 385;
	InimigosPosicoes[5].LarX = 92;
	InimigosPosicoes[5].LarY = 40;
	
	//Struct para o desenho dos inimigos
	PosicoesD InimigosDesenho[NInimigos];
	
	InimigosDesenho[0].IndIm = 5;
	InimigosDesenho[1].IndIm = 4;
	InimigosDesenho[2].IndIm = 5;
	InimigosDesenho[3].IndIm = 2;
	InimigosDesenho[4].IndIm = 2;
	InimigosDesenho[5].IndIm = 0;
	
	
	//Variaveis do cenario ------------------------------------------------------------------------------------------------------------------------
	int CPosX = 0,
		CPosY = 0,
		CenarioAtual = 0;
	
	//Informacoes do Scroll
	
	CenarioInf Cenario[2];
	
	Cenario[0].LimiteCima = 0 + (PVel + 1); //Descontar um espaco equivalente a velocidade do personagem + 1, para evitar que a imagem do mapa possa sair da tela.
	Cenario[0].LimiteBaixo = 0 - (PVel + 1);
	Cenario[0].LimiteEsquerda = 0 + (PVel + 1);
	Cenario[0].LimiteDireita = 0 - (PVel + 1);
	
	Cenario[1].LimiteCima = -408 + (PVel + 1); //Descontar um espaco equivalente a velocidade do personagem + 1, para evitar que a imagem do mapa possa sair da tela.
	Cenario[1].LimiteBaixo = -16 - (PVel + 1);
	Cenario[1].LimiteEsquerda = -960 + (PVel + 1);
	Cenario[1].LimiteDireita = -20 - (PVel + 1);
	
	
	//Objetos do cenario ----------------------------------------------------------------------------------------------------
	
	//Posicoes
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
	
	//Struct para o desenho
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
	
	
	//Para o desenho da personagem no mapa -------------------------------------------------------------------------------------
	PosicoesD PersonagemD;
	PersonagemD.Tipo = PER; //Se refere ao tipo de objeto que a struct representa, se e um personagem, npc, bau, objeto do cenario, etc.
	PersonagemD.PosY = PosY;
	PersonagemD.IndIm = 0;
	PersonagemD.Ind = 0;
	PersonagemD.VTroca = -PLarY;
	PersonagemD.DeslocamentoDaImagem = 71;
	
	PosicoesD ListaObjCenaTemp; //Struct para ser usada na hora do sort.
	
	//Portas (Se colidir com elas ocorre uma transicao de cenario) -------------------------------------------------------------------------------
	
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
	
	RetanguloTeste[0].DisX = 500;
	RetanguloTeste[0].DisY = 10;
	RetanguloTeste[0].LarX = 100;
	RetanguloTeste[0].LarY = 100;
	
	RetanguloTeste[1].DisX = 900;
	RetanguloTeste[1].DisY = 300;
	RetanguloTeste[1].LarX = 150;
	RetanguloTeste[1].LarY = 50;
	
	//Arrumar as posicoes de troca dos objetos do cenario, baus e inimigos do mapa. -------------------------------------------------------------------------------
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
	
	for(i=0; i < NInimigos; i++)
	{
		if(InimigosDesenho[i].IndIm == 0 || InimigosDesenho[i].IndIm == 1 || InimigosDesenho[i].IndIm == 2 || InimigosDesenho[i].IndIm == 3)
		{
			InimigosDesenho[i].DeslocamentoDaImagem = 82;
			InimigosDesenho[i].VTroca = 0;
		}
		else if(InimigosDesenho[i].IndIm == 4)
		{
			InimigosDesenho[i].DeslocamentoDaImagem = 62;
			InimigosDesenho[i].VTroca = 0;
		}
		else if(InimigosDesenho[i].IndIm == 5)
		{
			InimigosDesenho[i].DeslocamentoDaImagem = 26;
			InimigosDesenho[i].VTroca = 0;
		}
		
		InimigosDesenho[i].Tipo = INIMIGO;
		InimigosDesenho[i].Ind = i; //Indice do struct, para ser usado quando chamar a lista de objetos.
		InimigosDesenho[i].PosY = InimigosPosicoes[i].DisY + InimigosPosicoes[i].LarY - InimigosDesenho[i].VTroca;
	}
	
	//Carregar as imagens -------------------------------------------------------------------------------------------------------
	
	initwindow(2000, 1000, "Dark Gears - Carregamento", 0, 0);
	
	CarregarImagens(STESTE);
	CarregarImagens(CENARIOS);
	CarregarImagens(OBJETOSCENARIO);
	CarregarImagens(BAUS);
	CarregarImagens(RETRATOS);
	CarregarImagens(HUD);
	CarregarImagens(MOBS);
	CarregarImagens(EFEITOS);
	CarregarImagens(INIMIGOSMAPA);
	
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
	
	reproduzirSom(VOLUME2);
	MusicaDoCenario = MUSICACAVERNA;
	
	Gt1 = GetTickCount();
  	Gt2 = Gt1;
	while(fecharJogo == false)
	{
		//Menu inicial
		while(telaDoJogo == MENUINICIAL && fecharJogo == false)
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
				
				setbkcolor(RGB(0, 0, 0));
		        cleardevice();
		        
		        if(MenuID == 0)
		        {
		        	putimage(0, 0, Sprites_HUD_Mascaras[TELADETITULO], AND_PUT);
					putimage(0, 0, Sprites_HUD[TELADETITULO], OR_PUT);
		        	
		        	putimage(690, 220 + (45 * 0), Sprites_HUD_Mascaras[BOTAOJOGAR], AND_PUT);
					putimage(690, 220 + (45 * 0), Sprites_HUD[BOTAOJOGAR], OR_PUT);
					
					putimage(690, 220 + (45 * 1), Sprites_HUD_Mascaras[BOTAOCREDITOS], AND_PUT);
					putimage(690, 220 + (45 * 1), Sprites_HUD[BOTAOCREDITOS], OR_PUT);
					
					putimage(690, 220 + (45 * 2), Sprites_HUD_Mascaras[BOTAOSAIR], AND_PUT);
					putimage(690, 220 + (45 * 2), Sprites_HUD[BOTAOSAIR], OR_PUT);
		        	
		        	putimage(690 + 230, 210 + (45 * Selecao), Sprites_HUD_Mascaras[SELECAOM], AND_PUT);
					putimage(690 + 230, 210 + (45 * Selecao), Sprites_HUD[SELECAOM], OR_PUT);
				}
				
				if(MenuID == 1)
				{
					putimage(0, 0, Sprites_HUD_Mascaras[TELADECREDITOS], AND_PUT);
					putimage(0, 0, Sprites_HUD[TELADECREDITOS], OR_PUT);
				}
				
				//Torna visivel a pagina de desenho.
				setvisualpage(PG);
				
				//Acoes
				
				if(MenuID == 0)
				{
					if((Tecla == UP) && (Selecao > 0))
					{
						reproduzirSom(CURSORMOVE);
						Selecao --;
					}
					if((Tecla == DOWN) && (Selecao < 2))
					{
						reproduzirSom(CURSORMOVE);
						Selecao ++;
					}
					if((Tecla == TECLAENTER))
					{
						reproduzirSom(CURSORMOVE);
						
						if(Selecao == 0)
						{
							reproduzirSom(MusicaDoCenario);
							telaDoJogo = EXPLORACAO;
						}
						if(Selecao == 1)
						{
							MenuID = 1;
						}
						if(Selecao == 2)
						{
							 fecharJogo = true;
						}
					}
				}
				if(MenuID == 1)
				{
					if(Tecla == TECLABACKSPACE)
					{
						reproduzirSom(CURSORVOLTA);
						MenuID = 0;
						Selecao = 0;
					}
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
		
		//Tela de exploracao
		while(telaDoJogo == EXPLORACAO && fecharJogo == false)
		{
			Gt2 = GetTickCount();
			if(Gt2 < Gt1)
			{
				Gt1 = Gt2;
			}
			if (Gt2 - Gt1 > 1000/FPS)
			{
				Gt1 = Gt2;
				
				/*
				//Esse codigo foi movido para o inicio da parte de colisao do personagem com o cenario.
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
				*/
				
				//Desenhos
		        
		        setbkcolor(RGB(200, 200, 200));
		        setfillstyle(1, RGB(133, 144, 200));
		        cleardevice();
				
				//Desenha o cenario
		        desenhaCenario(CPosX, CPosY, Sprites_Cenario, CenarioAtual);
		        
		        //Cria a lista com os retangulos de colisao.
		        criarListaRetangulosDeColisao(CenarioAtual, RetanguloTeste, PosicaoBaus, &TamanhoListaRetangulosDeColisao, &ListaRetangulosDeColisao);
				
				//Arrumar a ordem (quem fica na frente de quem) dos objetos e da personagem, e desenha-los no mapa.
				//Cria a lista e a coloca em um ponteiro.
				criarListaObjetosC(CenarioAtual, CPosY, PosY, PersonagemD, ObjetosCenaDesenho, BausCenaDesenho, InimigosDesenho, &TamanhoListaOC, &listaObjetosC);
				
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
				
				/*
				//Teste ----------------
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
				
				setfillstyle(0, RGB(130, 45, 70));
	        	for(i = 0; i < TamanhoListaRetangulosDeColisao; i++)
				{
					bar(ListaRetangulosDeColisao[i].DisX + CPosX, ListaRetangulosDeColisao[i].DisY + CPosY, ListaRetangulosDeColisao[i].DisX + ListaRetangulosDeColisao[i].LarX + CPosX, ListaRetangulosDeColisao[i].DisY + ListaRetangulosDeColisao[i].LarY + CPosY);
				}
				//Teste ----------------
				*/
				
				//printf("\nPosX = %d, PosY = %d", PosX, PosY);
				//printf("\nCPosX = %d, CPosY = %d", CPosX, CPosY);
				
				for(i=0; i < TamanhoListaOC; i++)
				{
					if(listaObjetosC[i].Tipo == PER)
					{
						//setfillstyle(1, RGB(133, 144, 200));
						//bar(PosX, PosY, PosX + PLarX, PosY + PLarY);
						//setfillstyle(1, RGB(255, 242, 0));
						//bar(PosX - 50, PosY - 80, PosX + PLarX + 50, PosY + PLarY - 80);
						//putimage(PosX, PosY, Sprites_Mascaras[LILY], AND_PUT); //Primeiro a mascara.
						//putimage(PosX, PosY, Sprites[LILY], OR_PUT); //Depois a imagem normal.
						//putimage(PosX - 30, PosY - 60, Sprites_Mascaras[CHADDRIT], AND_PUT);
						//putimage(PosX - 30, PosY - 60, Sprites[CHADDRIT], OR_PUT);
						putimage(PosX, PosY - PersonagemD.DeslocamentoDaImagem, Sprites_Mascaras[LILY3D], AND_PUT);
						putimage(PosX, PosY - PersonagemD.DeslocamentoDaImagem, Sprites[LILY3D], OR_PUT);
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
								
						if(((CPosX + PosicaoBaus[listaObjetosC[i].Ind].DisX >= (0 - Sprites_Baus_Tamanhos[listaObjetosC[i].IndIm][0])) && (CPosX + PosicaoBaus[listaObjetosC[i].Ind].DisX  <= TelaLarX)) && ((CPosY + PosicaoBaus[listaObjetosC[i].Ind].DisY - BausCenaDesenho[listaObjetosC[i].Ind].DeslocamentoDaImagem >= (0 - Sprites_Baus_Tamanhos[listaObjetosC[i].IndIm][1])) && (CPosY + PosicaoBaus[listaObjetosC[i].Ind].DisY - BausCenaDesenho[listaObjetosC[i].Ind].DeslocamentoDaImagem <= TelaLarY)))
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
					
					if(listaObjetosC[i].Tipo == INIMIGO)
					{
						if(InimigosVivos[listaObjetosC[i].Ind] == true)
						{
							if(((CPosX + InimigosPosicoes[listaObjetosC[i].Ind].DisX >= (0 - Sprites_InimigosMapa_Tamanhos[listaObjetosC[i].IndIm][0])) && (CPosX + InimigosPosicoes[listaObjetosC[i].Ind].DisX  <= TelaLarX)) && ((CPosY + InimigosPosicoes[listaObjetosC[i].Ind].DisY - InimigosDesenho[listaObjetosC[i].Ind].DeslocamentoDaImagem >= (0 - Sprites_InimigosMapa_Tamanhos[listaObjetosC[i].IndIm][1])) && (CPosY + InimigosPosicoes[listaObjetosC[i].Ind].DisY - InimigosDesenho[listaObjetosC[i].Ind].DeslocamentoDaImagem <= TelaLarY)))
							{
								putimage(CPosX + InimigosPosicoes[listaObjetosC[i].Ind].DisX, CPosY + InimigosPosicoes[listaObjetosC[i].Ind].DisY - InimigosDesenho[listaObjetosC[i].Ind].DeslocamentoDaImagem, Sprites_InimigosMapa_Mascaras[listaObjetosC[i].IndIm], AND_PUT);
								putimage(CPosX + InimigosPosicoes[listaObjetosC[i].Ind].DisX, CPosY + InimigosPosicoes[listaObjetosC[i].Ind].DisY - InimigosDesenho[listaObjetosC[i].Ind].DeslocamentoDaImagem, Sprites_InimigosMapa[listaObjetosC[i].IndIm], OR_PUT);
								
								//bar(CPosX + InimigosPosicoes[listaObjetosC[i].Ind].DisX, CPosY + InimigosPosicoes[listaObjetosC[i].Ind].DisY, CPosX + InimigosPosicoes[listaObjetosC[i].Ind].DisX +  InimigosPosicoes[listaObjetosC[i].Ind].LarX, CPosY + InimigosPosicoes[listaObjetosC[i].Ind].DisY +  InimigosPosicoes[listaObjetosC[i].Ind].LarY);
							}
						}
					}
				}
	
				//Torna visivel a pagina de desenho.
				setvisualpage(PG);
				
				//Fim do jogo - Parte 1
				if(InimigosVivos[5] == false)
				{
					//Iniciar um dialogo
					Arquivo = (char *)malloc(sizeof(char) * 17);
			    	strcpy(Arquivo, "Textos/Teste.txt");
			    	
			    	DialogoPosX = 229,
					DialogoPosY = 435,
					DialogoPartToStart = 94,
					DialogoPartToStop = 133;
					
			    	PodeFazerInteracao = false;
			    	CaixaDeTexto = true;
				}
				
				//Caixa de Texto
				if(CaixaDeTexto == true)
				{
					ReadDialogue(DialogoPosX, DialogoPosY, DialogoPartToStart, DialogoPartToStop, MudancaDeTexto, Arquivo, Sprites_Retratos, Sprites_Retratos_Mascaras, Sprites_HUD, Sprites_HUD_Mascaras);
					CaixaDeTexto = false;
					PodeFazerInteracao = true;
				}
				
				//Fim do jogo - Parte 2
				if(InimigosVivos[5] == false)
				{
					fecharJogo = true;
				}
				
				//Iniciar a batalha
				if(IniciarBatalha == true)
				{
					reproduzirSom(PARARMUSICA);
					reproduzirSom(MusicaDaBatalha);
					iniciarBatalha(li, mob, &lista_consumiveis, podeFugirVar, &fecharJogo, Sprites_Retratos, Sprites_Retratos_Mascaras, Sprites_HUD, Sprites_HUD_Mascaras, Sprites_Mobs, Sprites_Mobs_Mascaras, Sprites_Efeitos, Sprites_Efeitos_Mascaras, Cenario_Batalha);
					reproduzirSom(PARARMUSICA);
					reproduzirSom(MusicaDoCenario);
					
					//Deixar o inimigo "morto".
					InimigosVivos[InimigoIndice] = false;
					
					MovX = 0;
					MovY = 0;
					
					IniciarBatalha = false;
					PodeFazerInteracao = true;
				}
				
				//Menu
				if(Tecla == MENU)
				{
					//reproduzirSom(CURSORPRONTO);
					DrawMenu(li, &lista_consumiveis, Sprites_Retratos, Sprites_Retratos_Mascaras, Sprites_HUD, Sprites_HUD_Mascaras);
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
				interacoesComOMapa(CenarioAtual, PosX, PosY, PLarX, PLarY, CPosX, CPosY, Bau_AreaDeInteracao, PosicaoBaus, Baus, &PodeFazerInteracao, &SpacePress, &MudancaDeCenario, &MudancaDeCenarioNumero, Portas, &CaixaDeTexto, &Arquivo, &DialogoPosX, &DialogoPosY, &DialogoPartToStart, &DialogoPartToStop, &AdicionarItem, &AdicionarItemIndice, &InimigoIndice, InimigosVivos, InimigosPosicoes, &mob, &IniciarBatalha, &MusicaDoCenario, &MusicaDaBatalha, &podeFugirVar);
				
				//Adicionar itens dos baus
				if(AdicionarItem == true)
				{
					//Codigo de adicionar item.
					lista_consumiveis = lista_consumiveis_insere(lista_consumiveis, &itemconsumivel[Baus[AdicionarItemIndice]]);
					
					//Alterar o MudancaDeTexto
					lcAux = lista_consumiveis_busca(lista_consumiveis, Baus[AdicionarItemIndice]);
					strcpy(MudancaDeTexto, lcAux->nome);
					
					//Tirar o item do bau
					Baus[AdicionarItemIndice] = NADA;
					
					reproduzirSom(SOMABRIRBAU);
					AdicionarItem = false;
					
					/*
					detalhaConsumiveis(lista_consumiveis);
					
					printf("\n");
					for(i=0; i < NumeroDeBaus; i++)
					{
						printf("%d", Baus[i]);
					}
					*/
				}
				
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
				
				if(Tecla == ESC)
				{
					fecharJogo = true;
				}
				
				fflush(stdin); //Aparentemente limpa algum endereco de memoria.
				
				//Se alguma tecla for pressionada, coloca o valor dela na variavel Tecla.
				// Com essa funcao, ela so pode ter um valor por vez que o laco e rodado, entao pode ser
				// usada em alguma ocasiao em que duas teclas nao podem ser pressionadas de uma vez.
				Tecla = 0;
				if(kbhit())
				{
					Tecla = getch();
				}
			}
		}
	}
	
	//Dar free separadamente em casa indice dos ponteiros de imagens.
	//free(Sprites);
	
	//Liberar a memoria dos ponteiros.
	//Dar free separadamente em cada um dos itens do li, mob e lista_consumiveis.
	while(li != NULL)
	{
		li = lista_retira(li, li->id);
	}
	while(mob != NULL)
	{
		mob = lista_retira(mob, mob->id);
	}
	while(lista_consumiveis != NULL)
	{
		lista_consumiveis = lista_consumiveis_retira(lista_consumiveis, lista_consumiveis->tipo);
	}
	free(li);
	free(mob);
	free(lista_consumiveis);
	free(lcAux);
	free(Arquivo);
	free(listaObjetosC);
	free(ListaRetangulosDeColisao);
	free(Baus);
	free(InimigosVivos);
			
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
	//Confere a colisao com ret�ngulos.
	
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
	// ! -> A BGI n�o salva imagens fora da tela, essas partes ficam pretas.
	switch(Imagem)
	{
		case STESTE:	
			//Sprites de teste
			
			cleardevice();
			setactivepage(2);
			
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
			setactivepage(1);
			
			break;
		
		case CENARIOS:
			//Cenarios e colisao dos cenarios
			
			cleardevice();
			setactivepage(2);
			
			setbkcolor(RGB(255, 255, 255));
			cleardevice();
			
			for(int i=0; i < CenarioQ; i++)
			{
				strcpy(StrcatTemp, Cenario_Nomes[i]);
				
				readimagefile(strcat(StrcatTemp, BMP), 0, 0, Cenario_Tamanhos[i][0]-1, Cenario_Tamanhos[i][1]-1);
			    Sprites_Cenario[i] = malloc(imagesize(0, 0, Cenario_Tamanhos[i][0]-1, Cenario_Tamanhos[i][1]-1));
			    getimage(0, 0, Cenario_Tamanhos[i][0]-1, Cenario_Tamanhos[i][1]-1, Sprites_Cenario[i]);
			}
			
			for(int i=0; i < CenarioQ; i++)
			{
				strcpy(StrcatTemp, Cenario_Nomes[i]);
				
				readimagefile(strcat(StrcatTemp, CBMP), 0, 0, Cenario_Tamanhos[i][0]-1, Cenario_Tamanhos[i][1]-1);
			    Cenario_Colisao[i] = malloc(imagesize(0, 0, Cenario_Tamanhos[i][0]-1, Cenario_Tamanhos[i][1]-1));
			    getimage(0, 0, Cenario_Tamanhos[i][0]-1, Cenario_Tamanhos[i][1]-1, Cenario_Colisao[i]);
			}
			
			for(int i=0; i < Cenario_BatalhaQ; i++)
			{
				strcpy(StrcatTemp, Cenario_Batalha_Nomes[i]);
				
				readimagefile(strcat(StrcatTemp, BMP), 0, 0, Cenario_Batalha_Tamanhos[i][0]-1, Cenario_Batalha_Tamanhos[i][1]-1);
			    Cenario_Batalha[i] = malloc(imagesize(0, 0, Cenario_Batalha_Tamanhos[i][0]-1, Cenario_Batalha_Tamanhos[i][1]-1));
			    getimage(0, 0, Cenario_Batalha_Tamanhos[i][0]-1, Cenario_Batalha_Tamanhos[i][1]-1, Cenario_Batalha[i]);
			}
			
			cleardevice();
			setactivepage(1);
			
			break;
		
		case OBJETOSCENARIO:
			//Objetos dos cenarios
			
			cleardevice();
			setactivepage(2);
			
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
			setactivepage(1);
			
			break;
		
		case BAUS:
			//Baus
			
			cleardevice();
			setactivepage(2);
			
			setbkcolor(RGB(255, 255, 255));
			cleardevice();
			
			for(int i=0; i < Sprites_BausQ; i++)
			{
				strcpy(StrcatTemp, Sprites_Baus_Nomes[i]);
		
				readimagefile(strcat(StrcatTemp, BMP), 0, 0, Sprites_Baus_Tamanhos[i][0]-1, Sprites_Baus_Tamanhos[i][1]-1);
			    Sprites_Baus[i] = malloc(imagesize(0, 0, Sprites_Baus_Tamanhos[i][0]-1, Sprites_Baus_Tamanhos[i][1]-1));
			    getimage(0, 0, Sprites_Baus_Tamanhos[i][0]-1, Sprites_Baus_Tamanhos[i][1]-1, Sprites_Baus[i]);
			}
			
			for(int i=0; i < Sprites_BausQ; i++)
			{
				strcpy(StrcatTemp, Sprites_Baus_Nomes[i]);
		
				readimagefile(strcat(StrcatTemp, MBMP), 0, 0, Sprites_Baus_Tamanhos[i][0]-1, Sprites_Baus_Tamanhos[i][1]-1);
			    Sprites_Baus_Mascaras[i] = malloc(imagesize(0, 0, Sprites_Baus_Tamanhos[i][0]-1, Sprites_Baus_Tamanhos[i][1]-1));
			    getimage(0, 0, Sprites_Baus_Tamanhos[i][0]-1, Sprites_Baus_Tamanhos[i][1]-1, Sprites_Baus_Mascaras[i]);
			}
			
			cleardevice();
			setactivepage(1);
			
			break;
		
		case RETRATOS:
			//Retratos dos personagens
			
			cleardevice();
			setactivepage(2);
			
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
			setactivepage(1);
			
			break;
		
		case HUD:
			//Imagens do HUD
			
			cleardevice();
			setactivepage(2);
			
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
			setactivepage(1);
			
			break;
		
		case MOBS:
			//Imagens dos inimigos do jogo nas batalhas
			
			cleardevice();
			setactivepage(2);
			
			setbkcolor(RGB(255, 255, 255));
			cleardevice();
			
			for(int i=0; i < Sprites_MobsQ; i++)
			{
				strcpy(StrcatTemp, Sprites_Mobs_Nomes[i]);
		
				readimagefile(strcat(StrcatTemp, BMP), 0, 0, Sprites_Mobs_Tamanhos[i][0]-1, Sprites_Mobs_Tamanhos[i][1]-1);
			    Sprites_Mobs[i] = malloc(imagesize(0, 0, Sprites_Mobs_Tamanhos[i][0]-1, Sprites_Mobs_Tamanhos[i][1]-1));
			    getimage(0, 0, Sprites_Mobs_Tamanhos[i][0]-1, Sprites_Mobs_Tamanhos[i][1]-1, Sprites_Mobs[i]);
			}
			
			for(int i=0; i < Sprites_MobsQ; i++)
			{
				strcpy(StrcatTemp, Sprites_Mobs_Nomes[i]);
		
				readimagefile(strcat(StrcatTemp, MBMP), 0, 0, Sprites_Mobs_Tamanhos[i][0]-1, Sprites_Mobs_Tamanhos[i][1]-1);
			    Sprites_Mobs_Mascaras[i] = malloc(imagesize(0, 0, Sprites_Mobs_Tamanhos[i][0]-1, Sprites_Mobs_Tamanhos[i][1]-1));
			    getimage(0, 0, Sprites_Mobs_Tamanhos[i][0]-1, Sprites_Mobs_Tamanhos[i][1]-1, Sprites_Mobs_Mascaras[i]);
			}
			
			cleardevice();
			setactivepage(1);
			
			break;
		
		case EFEITOS:
			//Imagens dos efeitos do jogo
			
			cleardevice();
			setactivepage(2);
			
			setbkcolor(RGB(255, 255, 255));
			cleardevice();
			
			for(int i=0; i < Sprites_EfeitosQ; i++)
			{
				strcpy(StrcatTemp, Sprites_Efeitos_Nomes[i]);
		
				readimagefile(strcat(StrcatTemp, BMP), 0, 0, Sprites_Efeitos_Tamanhos[i][0]-1, Sprites_Efeitos_Tamanhos[i][1]-1);
			    Sprites_Efeitos[i] = malloc(imagesize(0, 0, Sprites_Efeitos_Tamanhos[i][0]-1, Sprites_Efeitos_Tamanhos[i][1]-1));
			    getimage(0, 0, Sprites_Efeitos_Tamanhos[i][0]-1, Sprites_Efeitos_Tamanhos[i][1]-1, Sprites_Efeitos[i]);
			}
			
			for(int i=0; i < Sprites_EfeitosQ; i++)
			{
				strcpy(StrcatTemp, Sprites_Efeitos_Nomes[i]);
		
				readimagefile(strcat(StrcatTemp, MBMP), 0, 0, Sprites_Efeitos_Tamanhos[i][0]-1, Sprites_Efeitos_Tamanhos[i][1]-1);
			    Sprites_Efeitos_Mascaras[i] = malloc(imagesize(0, 0, Sprites_Efeitos_Tamanhos[i][0]-1, Sprites_Efeitos_Tamanhos[i][1]-1));
			    getimage(0, 0, Sprites_Efeitos_Tamanhos[i][0]-1, Sprites_Efeitos_Tamanhos[i][1]-1, Sprites_Efeitos_Mascaras[i]);
			}
			
			cleardevice();
			setactivepage(1);
			
			break;
		
		case INIMIGOSMAPA:
			//Imagens dos inimigos do jogo no mapa
			
			cleardevice();
			setactivepage(2);
			
			setbkcolor(RGB(255, 255, 255));
			cleardevice();
			
			for(int i=0; i < Sprites_InimigosMapaQ; i++)
			{
				strcpy(StrcatTemp, Sprites_InimigosMapa_Nomes[i]);
		
				readimagefile(strcat(StrcatTemp, BMP), 0, 0, Sprites_InimigosMapa_Tamanhos[i][0]-1, Sprites_InimigosMapa_Tamanhos[i][1]-1);
			    Sprites_InimigosMapa[i] = malloc(imagesize(0, 0, Sprites_InimigosMapa_Tamanhos[i][0]-1, Sprites_InimigosMapa_Tamanhos[i][1]-1));
			    getimage(0, 0, Sprites_InimigosMapa_Tamanhos[i][0]-1, Sprites_InimigosMapa_Tamanhos[i][1]-1, Sprites_InimigosMapa[i]);
			}
			
			for(int i=0; i < Sprites_InimigosMapaQ; i++)
			{
				strcpy(StrcatTemp, Sprites_InimigosMapa_Nomes[i]);
		
				readimagefile(strcat(StrcatTemp, MBMP), 0, 0, Sprites_InimigosMapa_Tamanhos[i][0]-1, Sprites_InimigosMapa_Tamanhos[i][1]-1);
			    Sprites_InimigosMapa_Mascaras[i] = malloc(imagesize(0, 0, Sprites_InimigosMapa_Tamanhos[i][0]-1, Sprites_InimigosMapa_Tamanhos[i][1]-1));
			    getimage(0, 0, Sprites_InimigosMapa_Tamanhos[i][0]-1, Sprites_InimigosMapa_Tamanhos[i][1]-1, Sprites_InimigosMapa_Mascaras[i]);
			}
			
			cleardevice();
			setactivepage(1);
			
			break;
		
		default:
		printf("\nRaios multiplos! O operador esta incorreto.");
	}
}
