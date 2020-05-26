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

#endif
