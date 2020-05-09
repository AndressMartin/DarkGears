#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<string.h>

#define LEFT   	75
#define RIGHT  	77
#define UP     	72
#define DOWN   	80
#define ESC     27

#define PRETO 0

//Ponteiros e variaveis globais

int TamanhoListaOC = 0,
	TamanhoListaRetangulosDeColisao = 0;
bool PodeFazerInteracao = true;

//Enumera numeros e atribui a marcadores (o primeiro numero pode ser definido, por exempo enum A {A=1, B}, se n�o, � 0 por padrao).
//Pode ser utilizado para facilitar o uso de imagens.
enum Sprites {LILY, CHADDRIT};
	
//CColisoes {AREA_Mapa_ParteDoMapa}
enum CColisoes {TESTEC_01_1, TESTEC_01_2, TESTEC_01_3, TESTEC_01_4};

//ObjetosCEnum {O + AREA_Mapa_NumeroDoObjeto}
enum ObjetosCEnum {OTESTE_01_1, OTESTE_01_2, OTESTE_01_3};

enum Tipos {PER, OBJ, BAU}; //Enumera os tipos que as structs de PosisoesC podem ter.

//Enumero os indices dos itens do jogo.
enum IndiceItens {NADA, POCAO, POCAO2};

//Definicao de structs
typedef struct
{
	int LimiteCima,
		LimiteBaixo,
		LimiteEsquerda,
		LimiteDireita;
} CenarioInf; //Informacoes de cada cenario.

typedef struct
{
	//Distancia que sua posicao esta em relacao ao CPosX e ao CPosY.
	int DisX,
		DisY;
} ObjetosCInf; //Informacoes de cada objeto dos cenarios.

typedef struct
{
	int PosY,
		VTroca,
		IndIm,
		Ind,
		Tipo;
} PosicoesD; //Informacoes das posicos para desenhar coisas que se sobrepoem (podem ficar na frente ou atras umas das outras).

typedef struct
{
	int DisX,
		DisY,
		LarX,
		LarY;
} RetangulosDeColisao;

//Ponteiro de structs para a funcao desenhaCenariosObjetosC.
PosicoesD *listaObjetosC = NULL;

//Ponteiro para a lista de retangulos de colisao.
RetangulosDeColisao *ListaRetangulosDeColisao = NULL;

//Definicao das funcoes, as funcoes em si estao depois do main.
bool hitTestCenario(int PosX,int PosY);
bool colisaoComRetangulos(int CPosX, int CPosY, int PosX, int PosY, int PLarX, int PLarY);
void desenhaCenarioColisao(int CPosX, int CPosY, void* Cenario_Colisao[], int CenarioAtual, int Cenario_Colisao_Tamanhos[][2], int TelaLarX, int TelaLarY);
void criarListaObjetosC(int CenarioAtual, int CPosY, int PosY, PosicoesD PersonagemD, PosicoesD ObjetosCD[], PosicoesD BausCD[]);
void criarListaRetangulosDeColisao(int CenarioAtual, RetangulosDeColisao RetanguloTeste[], RetangulosDeColisao PosicaoBaus[]);

void interacoesComOMapa()
{
	// Funcao onde vamos tentar colocar todas as interacoes com o mapa. Vai depender do mapa atual.
	// Interacoes como abrir baus, apertar botoes, falr com NPCs, e as transicoes dos mapas.
	// A variavel global PodeFazerInteracao sera usada para limitar a uma interacao por vez.
}

//void desenhaCenarioObjetos(int PosX, int PosY, int CPosX, int CPosY, void* Cenario_Objetos[], void* Cenario_Objetos_Mascaras[], int CenarioAtual, int Cenario_Objetos_Tamanhos[][2], int TelaLarX, int TelaLarY, struct ObjetosCInf ObjetosC[]);

int main()
{
	//Variaveis da personagem no mapa
	int PosX = 20,
		PosY = 100,
		PLarX = 50,
		PLarY = 70,
		MovX = 0,
		MovY = 0,
		PVel = 10;
	
	//Variaveis de controle
	int PG = 0,
		i = 0,
		j = 0,
		TelaLarX = 640,
		TelaLarY = 360,
		SpritesN = 0;
	char Tecla = 0;
	long long unsigned Gt1, Gt2;
	
	//Baus
	int NumeroDeBaus = 2,
		Bau_AreaDeInteracao = 10;
	int Baus[NumeroDeBaus] = {POCAO,
							  POCAO2};
	
	RetangulosDeColisao PosicaoBaus[NumeroDeBaus];
	
	PosicaoBaus[0].DisX = 700;
	PosicaoBaus[0].DisY = 270;
	PosicaoBaus[0].LarX = 50;
	PosicaoBaus[0].LarY = 50;
	
	PosicaoBaus[1].DisX = 700;
	PosicaoBaus[1].DisY = 330;
	PosicaoBaus[1].LarX = 50;
	PosicaoBaus[1].LarY = 50;
	
	PosicoesD BausCD[NumeroDeBaus];
	
	BausCD[0].IndIm = 0;
	BausCD[1].IndIm = 0;
	
	BausCD[0].VTroca = 0;
	BausCD[1].VTroca = 0;
	
	
	//Variaveis do cenario
	int CPosX = -100,
		CPosY = -100,
		CenarioAtual = 0;
	
	CenarioInf Cenario[1];
	
	Cenario[0].LimiteCima = -198 + (PVel + 1); //Descontar um espaco equivalente a velocidade do personagem + 1, para evitar que a imagem do mapa possa sair da tela.
	Cenario[0].LimiteBaixo = 0 - (PVel + 1);
	Cenario[0].LimiteEsquerda = -198 + (PVel + 1);
	Cenario[0].LimiteDireita = 0 - (PVel + 1);
	
	int NObjetos = 3;
	
	ObjetosCInf ObjetosC[NObjetos];
	
	ObjetosC[0].DisX = 120;
	ObjetosC[0].DisY = 150;
	
	ObjetosC[1].DisX = 360;
	ObjetosC[1].DisY = 360;
	
	ObjetosC[2].DisX = 70;
	ObjetosC[2].DisY = 400;
	
	PosicoesD ObjetosCD[NObjetos];
	
	//O indice de imagem se refere a imagem que ele vai usar.
	ObjetosCD[0].IndIm = 0;
	ObjetosCD[1].IndIm = 1;
	ObjetosCD[2].IndIm = 2;
	
	// O valor usado para organizar a listaObjetosC se refere a base inferior da imagem dos objetos,
	// o VTroca sera subtraido desse valor, para casos em que o ponto de troca tenha que ser em outro lugar.
	ObjetosCD[0].VTroca = 0;
	ObjetosCD[1].VTroca = 0;
	ObjetosCD[2].VTroca = 20;
	
	PosicoesD PersonagemD;
	PersonagemD.Tipo = PER; //Se refere ao tipo de objeto que a struct representa, se e um personagem, npc, bau, objeto do cenario, etc.
	PersonagemD.PosY = PosY;
	PersonagemD.IndIm = 0;
	PersonagemD.Ind = 0;
	PersonagemD.VTroca = -PLarY;
	
	PosicoesD ListaOCT; //Struct para ser usada na hora do sort.
	
	RetangulosDeColisao RetanguloTeste[2];
	RetanguloTeste[0].DisX = 100;
	RetanguloTeste[0].DisY = 80;
	RetanguloTeste[0].LarX = 100;
	RetanguloTeste[0].LarY = 100;
	
	RetanguloTeste[1].DisX = 300;
	RetanguloTeste[1].DisY = 300;
	RetanguloTeste[1].LarX = 150;
	RetanguloTeste[1].LarY = 50;
	
	char Tipo[13] = "Nice",
		 JPG[5] = ".jpg",
		 BMP[5] = ".bmp",
		 MBMP[13] = "_mascara.bmp",
		 MJPG[13] = "_mascara.jpg";
	char StrcatTemp[50] = "Yes"; //O numero de caracteres tem que ser grande para ser usado no carregaento de imagens.
	
	//Imagens
	
	//Vai guardar as imagens.
	int SpritesQ = 2; //Quantidade de sprites, vai ser usado nas outras listas para facilitar mudancas.
	void* Sprites[SpritesQ];
	
	int Cenario_ColisaoQ = 4;
	void* Cenario_Colisao[Cenario_ColisaoQ];
	
	int Cenario_ObjetosQ = 3;
	void* Cenario_Objetos[Cenario_ObjetosQ];
	
	//Vai guardar as mascaras das imagens que precisarem de uma.
	void* Sprites_Mascaras[SpritesQ];
	void* Cenario_Objetos_Mascaras[Cenario_ObjetosQ];
	
	//Nomes e caminhos dos arquivos, sem o tipo, para poder ser usado pelo codigo das mascaras tambem.
	// "17"" pois tem que considerar o caractere nulo "\0" que fica no final de uma string.
	char Sprites_Nomes[SpritesQ][17] = {"Sprites/imagem01",
								 		"Sprites/imagem02"};
	
	char Cenario_Colisao_Nomes[Cenario_ColisaoQ][35] = {"Sprites/Cenario_Teste_01-1_Colisao",
										 				"Sprites/Cenario_Teste_01-2_Colisao",
										 				"Sprites/Cenario_Teste_01-3_Colisao",
										 				"Sprites/Cenario_Teste_01-4_Colisao"};
	
	char Cenario_Objetos_Nomes[Cenario_ObjetosQ][27] = {"Sprites/ObjetoC_Teste_01-1",
								 						"Sprites/ObjetoC_Teste_01-2",
														"Sprites/ObjetoC_Teste_01-3"};
	
	//Vai guardas a largura e altura das imagens, respectivamente.
	int Sprites_Tamanhos[SpritesQ][2] = {{100, 50},
								  		 {70, 50}};
	
	int Cenario_Colisao_Tamanhos[Cenario_ColisaoQ][2] = {{640, 360},
														 {199, 360},
														 {640, 199},
														 {199, 199}};
	
	int Cenario_Objetos_Tamanhos[Cenario_ObjetosQ][2] = {{110, 115},
								  		 				 {110, 115},
														 {110, 115}};
	
	//Arrumar as posicoes de troca dos objetos do cenario.
	for(i=0; i < NObjetos; i++)
	{
		ObjetosCD[i].Tipo = OBJ;
		ObjetosCD[i].Ind = i; //Indice do struct, para ser usado quando chamar a lista de objetos.
		ObjetosCD[i].PosY = ObjetosC[i].DisY + Cenario_Objetos_Tamanhos[ObjetosCD[i].IndIm][1] - ObjetosCD[i].VTroca;
	}
	
	for(i=0; i < NumeroDeBaus; i++)
	{
		BausCD[i].Tipo = BAU;
		BausCD[i].Ind = i; //Indice do struct, para ser usado quando chamar a lista de objetos.
		BausCD[i].PosY = PosicaoBaus[i].DisY + PosicaoBaus[i].LarY - BausCD[i].VTroca;
	}
	
	initwindow(TelaLarX, TelaLarY, "Dark Gears - Testes", 50, 30);
	
	// ! -> A BGI n�o salva imagens fora da tela, essas partes ficam pretas.
	//Carregar imagens
	cleardevice();
	setactivepage(1);
	
	setbkcolor(RGB(255, 255, 255));
	cleardevice();
	
	//Ideia de funcao -> CarregarImagens(SpritesN, Sprites, Sprites_Nomes, Sprites_Tamanhos, Tipo)
	// ! -> A funcao nao funcionou pois ela nao aceita o array de strings (Sprites_Nomes), nao sei como arrumar isso.
	
	//Sprites de teste
	SpritesN = SpritesQ; //Numero de sprites.
	strcpy(Tipo, JPG);
	for(i=0; i < SpritesN; i++)
	{
		//StrcatTemp vai ser usada para juntar o nome do sprite com o tipo de arquivo
		//e, caso seja uma mascara, como o "_mascara".
		//strcpy(s1, s2) copia a segunda string na primeira.
		//strcat(s1, s2) adiciona a segunda string na primeira.
		strcpy(StrcatTemp, Sprites_Nomes[i]);
		
		// ! -> Como o 0 conta como 1 pixel, as posicoes x e y finais tem que ser 1 pixel menor
		//		que as dimensoes totais da imagem, para compensar o pixel "a mais" do 0.
		readimagefile(strcat(StrcatTemp, Tipo), 0, 0, Sprites_Tamanhos[i][0]-1, Sprites_Tamanhos[i][1]-1); //Le uma imagem e copia ela para a tela.
	    Sprites[i] = malloc(imagesize(0, 0, Sprites_Tamanhos[i][0]-1, Sprites_Tamanhos[i][1]-1)); //Aloca a memoria necessaria para guardar a imagem na RAM.
	    getimage(0, 0, Sprites_Tamanhos[i][0]-1, Sprites_Tamanhos[i][1]-1, Sprites[i]); //Copia a imagem na tela para a memoria.
	}
	
	strcpy(Tipo, MJPG);
	for(i=0; i < SpritesN; i++)
	{
		strcpy(StrcatTemp, Sprites_Nomes[i]);

		readimagefile(strcat(StrcatTemp, Tipo), 0, 0, Sprites_Tamanhos[i][0]-1, Sprites_Tamanhos[i][1]-1);
	    Sprites_Mascaras[i] = malloc(imagesize(0, 0, Sprites_Tamanhos[i][0]-1, Sprites_Tamanhos[i][1]-1));
	    getimage(0, 0, Sprites_Tamanhos[i][0]-1, Sprites_Tamanhos[i][1]-1, Sprites_Mascaras[i]);
	}
	
	//Colisao dos cenarios
	SpritesN = Cenario_ColisaoQ;
	strcpy(Tipo, BMP);
	for(i=0; i < SpritesN; i++)
	{
		strcpy(StrcatTemp, Cenario_Colisao_Nomes[i]);
		
		readimagefile(strcat(StrcatTemp, Tipo), 0, 0, Cenario_Colisao_Tamanhos[i][0]-1, Cenario_Colisao_Tamanhos[i][1]-1);
	    Cenario_Colisao[i] = malloc(imagesize(0, 0, Cenario_Colisao_Tamanhos[i][0]-1, Cenario_Colisao_Tamanhos[i][1]-1));
	    getimage(0, 0, Cenario_Colisao_Tamanhos[i][0]-1, Cenario_Colisao_Tamanhos[i][1]-1, Cenario_Colisao[i]);
	}
	
	//Objetos dos cenarios
	SpritesN = Cenario_ObjetosQ;
	strcpy(Tipo, BMP);
	for(i=0; i < SpritesN; i++)
	{
		strcpy(StrcatTemp, Cenario_Objetos_Nomes[i]);

		readimagefile(strcat(StrcatTemp, Tipo), 0, 0, Cenario_Objetos_Tamanhos[i][0]-1, Cenario_Objetos_Tamanhos[i][1]-1);
	    Cenario_Objetos[i] = malloc(imagesize(0, 0, Cenario_Objetos_Tamanhos[i][0]-1, Cenario_Objetos_Tamanhos[i][1]-1));
	    getimage(0, 0, Cenario_Objetos_Tamanhos[i][0]-1, Cenario_Objetos_Tamanhos[i][1]-1, Cenario_Objetos[i]);
	}
	
	strcpy(Tipo, MBMP);
	for(i=0; i < SpritesN; i++)
	{
		strcpy(StrcatTemp, Cenario_Objetos_Nomes[i]);

		readimagefile(strcat(StrcatTemp, Tipo), 0, 0, Cenario_Objetos_Tamanhos[i][0]-1, Cenario_Objetos_Tamanhos[i][1]-1);
	    Cenario_Objetos_Mascaras[i] = malloc(imagesize(0, 0, Cenario_Objetos_Tamanhos[i][0]-1, Cenario_Objetos_Tamanhos[i][1]-1));
	    getimage(0, 0, Cenario_Objetos_Tamanhos[i][0]-1, Cenario_Objetos_Tamanhos[i][1]-1, Cenario_Objetos_Mascaras[i]);
	}
	
	cleardevice();
	setactivepage(0);
	
	TamanhoListaRetangulosDeColisao = 2;
	ListaRetangulosDeColisao = (RetangulosDeColisao *)realloc(ListaRetangulosDeColisao, sizeof(RetangulosDeColisao) * TamanhoListaRetangulosDeColisao);
	ListaRetangulosDeColisao[0] = RetanguloTeste[0];
	ListaRetangulosDeColisao[1] = RetanguloTeste[1];
	
	Gt1 = GetTickCount();
  	Gt2 = Gt1;
	while(Tecla != ESC)
	{
		Gt2 = GetTickCount();
		if (Gt2 - Gt1 > 16)
		{
			Gt1 = Gt2;
			
			//Esse codigo foi movido para o inicio da parte de colisao do personagem com o cenario.
			//Alterna a pagina de desenho ativa (para fazer o Buffer Duplo).
			//if(PG == 0)
			//{
				//PG = 1;
			//}
			//else
			//{
				//PG = 0;
			//}
			//setactivepage(PG);
			
			//Desenhos
	        
	        setbkcolor(RGB(200, 200, 200));
	        setfillstyle(1, RGB(133, 144, 200));
	        cleardevice();
			
			//Vai ser substituido pela funcao de desenhar o cenario em si depois.
	        desenhaCenarioColisao(CPosX, CPosY, Cenario_Colisao, CenarioAtual, Cenario_Colisao_Tamanhos, TelaLarX, TelaLarY);
	        
	        //Cria a lista com os retangulos de colisao.
	        criarListaRetangulosDeColisao(CenarioAtual, RetanguloTeste, PosicaoBaus);
	        
			//Teste
			setfillstyle(0, RGB(130, 45, 70));
        	for(i = 0; i < TamanhoListaRetangulosDeColisao; i++)
			{
				bar(ListaRetangulosDeColisao[i].DisX + CPosX, ListaRetangulosDeColisao[i].DisY + CPosY, ListaRetangulosDeColisao[i].DisX + ListaRetangulosDeColisao[i].LarX + CPosX, ListaRetangulosDeColisao[i].DisY + ListaRetangulosDeColisao[i].LarY + CPosY);
			}
			
			//Arrumar a ordem (quem fica na frente de quem) dos objetos e da personagem, e desenha-los no mapa.
			criarListaObjetosC(CenarioAtual, CPosY, PosY, PersonagemD, ObjetosCD, BausCD); //Cria a lista e a coloca em um ponteiro.
			
			//Ordenar a lista
			for(i=0; i < TamanhoListaOC - 1; i++)
			{
				for(j=i+1; j < TamanhoListaOC; j++)
				{
					if(listaObjetosC[i].PosY > listaObjetosC[j].PosY)
					{
						ListaOCT = listaObjetosC[i];
						listaObjetosC[i] = listaObjetosC[j];
						listaObjetosC[j] = ListaOCT;
						
						//printf("\n\nEndereco de ListaOCT         = %p", &ListaOCT);
						//printf("\nEndereco de listaObjetosC[j] = %p", &listaObjetosC[j]);
					}
				}
			}
			
			//Desenhar os objetos e a personagem
			for(i=0; i < TamanhoListaOC; i++)
			{
				if(listaObjetosC[i].Tipo == PER)
				{
					setfillstyle(1, RGB(133, 144, 200));
					bar(PosX, PosY, PosX + PLarX, PosY + PLarY);
					putimage(PosX, PosY, Sprites_Mascaras[LILY], AND_PUT); //Primeiro a mascara.
					putimage(PosX, PosY, Sprites[LILY], OR_PUT); //Depois a imagem normal.
					putimage(PosX - 30, PosY - 60, Sprites_Mascaras[CHADDRIT], AND_PUT);
					putimage(PosX - 30, PosY - 60, Sprites[CHADDRIT], OR_PUT);
				}
				else if(listaObjetosC[i].Tipo == OBJ)
				{
					if(((CPosX + ObjetosC[listaObjetosC[i].Ind].DisX >= (0 - Cenario_Objetos_Tamanhos[listaObjetosC[i].IndIm][0])) && (CPosX + ObjetosC[listaObjetosC[i].Ind].DisX <= TelaLarX)) && ((CPosY + ObjetosC[listaObjetosC[i].Ind].DisY >= (0 - Cenario_Objetos_Tamanhos[listaObjetosC[i].IndIm][1])) && (CPosY + ObjetosC[listaObjetosC[i].Ind].DisY <= TelaLarY)))
					{
						putimage(CPosX + ObjetosC[listaObjetosC[i].Ind].DisX, CPosY + ObjetosC[listaObjetosC[i].Ind].DisY, Cenario_Objetos_Mascaras[listaObjetosC[i].IndIm], AND_PUT);
						putimage(CPosX + ObjetosC[listaObjetosC[i].Ind].DisX, CPosY + ObjetosC[listaObjetosC[i].Ind].DisY, Cenario_Objetos[listaObjetosC[i].IndIm], OR_PUT);
					}
				}
			}
			
			
			//Torna visivel a pagina de desenho.
			setvisualpage(PG);
			
			//Mexendo com a posicao da personagem
			if(PG == 0)
			{
				PG = 1;
			}
			else
			{
				PG = 0;
			}
			setactivepage(PG);
			
			setbkcolor(RGB(255, 255, 255));
	        cleardevice();
	        
	        //Vai chamar a funcao para desenhar a colisao do cenario.
	        desenhaCenarioColisao(CPosX, CPosY, Cenario_Colisao, CenarioAtual, Cenario_Colisao_Tamanhos, TelaLarX, TelaLarY);
			
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
				
				while(colisaoComRetangulos(CPosX, CPosY, PosX + MovX, PosY, PLarX, PLarY))
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
				
				while(colisaoComRetangulos(CPosX, CPosY, PosX + MovX, PosY, PLarX, PLarY))
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
				
				while(colisaoComRetangulos(CPosX, CPosY, PosX, PosY + MovY, PLarX, PLarY))
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
				
				while(colisaoComRetangulos(CPosX, CPosY, PosX, PosY + MovY, PLarX, PLarY))
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
			//InteracoesComOMapa();
			
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

bool colisaoComRetangulos(int CPosX, int CPosY, int PosX, int PosY, int PLarX, int PLarY)
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

void desenhaCenarioColisao(int CPosX, int CPosY, void* Cenario_Colisao[], int CenarioAtual, int Cenario_Colisao_Tamanhos[][2], int TelaLarX, int TelaLarY)
{
	//Dependendo do cenario atual, o mapa vai estar dividido, e nos vamos colocar as imagens na ordem correta.
	//Como a posicao das imagens em relacao umas as outras dependo do mapa, e vou usar switch para cada ocasiao.
	switch(CenarioAtual)
	{
		case 0:
			// O if fara com que a imagem nao seja desenhada se estiver fora da tela.
			if(((CPosX >= (0 - Cenario_Colisao_Tamanhos[TESTEC_01_1][0])) && (CPosX <= TelaLarX)) && ((CPosY >= (0 - Cenario_Colisao_Tamanhos[TESTEC_01_1][1])) && (CPosY <= TelaLarY)))
			{
				putimage(CPosX, CPosY, Cenario_Colisao[TESTEC_01_1], COPY_PUT);
			}
			if(((CPosX + 640 >= (0 - Cenario_Colisao_Tamanhos[TESTEC_01_2][0])) && (CPosX <= TelaLarX)) && ((CPosY >= (0 - Cenario_Colisao_Tamanhos[TESTEC_01_2][1])) && (CPosY <= TelaLarY)))
			{
				putimage(CPosX + 640, CPosY, Cenario_Colisao[TESTEC_01_2], COPY_PUT);
			}
			if(((CPosX >= (0 - Cenario_Colisao_Tamanhos[TESTEC_01_3][0])) && (CPosX <= TelaLarX)) && ((CPosY + 360 >= (0 - Cenario_Colisao_Tamanhos[TESTEC_01_3][1])) && (CPosY <= TelaLarY)))
			{
				putimage(CPosX, CPosY + 360, Cenario_Colisao[TESTEC_01_3], COPY_PUT);
			}
			if(((CPosX + 640 >= (0 - Cenario_Colisao_Tamanhos[TESTEC_01_4][0])) && (CPosX <= TelaLarX)) && ((CPosY + 360 >= (0 - Cenario_Colisao_Tamanhos[TESTEC_01_4][1])) && (CPosY <= TelaLarY)))
			{
				putimage(CPosX + 640, CPosY + 360, Cenario_Colisao[TESTEC_01_4], COPY_PUT);
			}
			break;
		
		//Caso nao haja um codigo para o CenarioAtual, ou seja, dar erro.
		default:
			printf("\nRaios multiplos! O operador esta incorreto.");
	}
}

void criarListaObjetosC(int CenarioAtual, int CPosY, int PosY, PosicoesD PersonagemD, PosicoesD ObjetosCD[], PosicoesD BausCD[])
{
	//Muda a lista (ponteiro) que ordena os objetos e a personagem no mapa (quem aparece na frente de quem), baseado no cenario atual.
	// ! - > Apesar do Ponteiro ObjetosCD[] na funcao ser outro, as structs dentro dos indices sao as mesmas, entao elas nao podem ser modificadas.
	switch(CenarioAtual)
	{
		case 0:
			{
				//Preciso colocar as chaves para limitar o escopo da variavel local que e declarada (ListaT), se nao da erro.
				TamanhoListaOC = 4;
				
				PersonagemD.PosY = PosY - PersonagemD.VTroca;
				
				PosicoesD ListaT[TamanhoListaOC] = {PersonagemD, ObjetosCD[OTESTE_01_1], ObjetosCD[OTESTE_01_2], ObjetosCD[OTESTE_01_3]};
				
				// O valor de X e Y que os objetos guardam e a distancia deles em relacao ao X e Y do cenario,
				// aqui na lista, e necessario o valor real da posicao na tela, por isso a soma.
				ListaT[1].PosY += CPosY;
				ListaT[2].PosY += CPosY;
				ListaT[3].PosY += CPosY;
				
				listaObjetosC = (PosicoesD *)realloc(listaObjetosC, sizeof(PosicoesD) * TamanhoListaOC);
				for(int i=0; i < TamanhoListaOC; i++)
				{
					listaObjetosC[i] = ListaT[i];
				}		
				break;
			}
		
		default:
			printf("\nRaios multiplos! O operador esta incorreto.");	
	}
}

void criarListaRetangulosDeColisao(int CenarioAtual, RetangulosDeColisao RetanguloTeste[], RetangulosDeColisao PosicaoBaus[])
{
	//Muda a lista (ponteiro) que tem os retangulos para colisao.
	switch(CenarioAtual)
	{
		case 0:
			{
				//Preciso colocar as chaves para limitar o escopo da variavel local que e declarada (ListaT), se nao da erro.
				TamanhoListaRetangulosDeColisao = 4;
				
				RetangulosDeColisao ListaT[TamanhoListaRetangulosDeColisao] = {RetanguloTeste[0], RetanguloTeste[1], PosicaoBaus[0], PosicaoBaus[1]};
				
				
				ListaRetangulosDeColisao = (RetangulosDeColisao *)realloc(ListaRetangulosDeColisao, sizeof(RetangulosDeColisao) * TamanhoListaRetangulosDeColisao);
				for(int i=0; i < TamanhoListaRetangulosDeColisao; i++)
				{
					ListaRetangulosDeColisao[i] = ListaT[i];
				}		
				break;
			}
		
		default:
			printf("\nRaios multiplos! O operador esta incorreto.");	
	}
}
