#ifndef STRUCTS_H
#define STRUCTS_H

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
	// DeslocamentoDaImagem é um valor a ser subtraido para a imagem comecar
	// acima da caixa de colisao, criando perspectiva. Sera usado apenas para
	// ver se essas imagens estao dentro da tela na hora de desenhar.
	int PosY,
		VTroca,
		DeslocamentoDaImagem,
		IndIm, //Indice da imagem que sera usada.
		Ind, //Indice do struct no vetor, para pegar as informacoes na hora de desenhar.
		Tipo;
} PosicoesD; //Informacoes das posicos para desenhar coisas que se sobrepoem (podem ficar na frente ou atras umas das outras).

typedef struct
{
	int DisX,
		DisY,
		LarX,
		LarY;
} RetangulosDeColisao;

typedef struct
{
	int Tipo,
		IndiceAtacante,
		IndiceRecebedor,
		Acao,
		Vel;
} ListaDosTurnosS;

typedef struct item{
    char descricao[10];
	int tipo_item;
	int atk;
	int def;
	int prec;
	int luc;
	int vel;
    struct item *prox;
    struct item *ant;
}Item; //definição da lista

typedef struct consumivel{
	int id;
	int tipo;
	int qtd;
	char nome[20];
	struct consumivel *ant;
	struct consumivel *prox;
}Consumivel;

typedef struct personagem{
	int id;
	int exp;
	int levels;
	int hp;
	int hpmax;
	char nome[10];
	int atk;
	int def;
	int prec;
	int luc;
	int vel;
	Item *itens;
    struct personagem *ant;
    struct personagem *prox;
}Personagens; //definição da lista

#endif
