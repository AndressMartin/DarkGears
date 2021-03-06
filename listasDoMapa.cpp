#include "structs.h"
#include "enums.h"

#include<stdio.h>
#include<stdlib.h>

void criarListaObjetosC(int CenarioAtual, int CPosY, int PosY, PosicoesD PersonagemD, PosicoesD ObjetosCenaDesenho[], PosicoesD BausCenaDesenho[], PosicoesD InimigosDesenho[], int *TamanhoListaOC, PosicoesD **listaObjetosC)
{
	//Muda a lista (ponteiro) que ordena os objetos e a personagem no mapa (quem aparece na frente de quem), baseado no cenario atual.
	// ! - > Apesar do Ponteiro ObjetosCenaDesenho[] na funcao ser outro, as structs dentro dos indices sao as mesmas, entao elas nao podem ser modificadas.
	switch(CenarioAtual)
	{
		case 0:
			{
				//Preciso colocar as chaves para limitar o escopo da variavel local que e declarada (ListaT), se nao da erro.
				*TamanhoListaOC = 12;
				
				PersonagemD.PosY = PosY - PersonagemD.VTroca;
				
				//Crio um ponteiro que equivale a nova lista.
				PosicoesD *ListaT;
				ListaT = (PosicoesD *)malloc(sizeof(PosicoesD) * (*TamanhoListaOC));
				
				//Preencher a ListaT.
				ListaT[0] = PersonagemD;
				ListaT[1] = BausCenaDesenho[0];
				ListaT[2] = BausCenaDesenho[1];
				ListaT[3] = BausCenaDesenho[2];
				ListaT[4] = BausCenaDesenho[3];
				ListaT[5] = BausCenaDesenho[4];
				ListaT[6] = InimigosDesenho[0];
				ListaT[7] = InimigosDesenho[1];
				ListaT[8] = InimigosDesenho[2];
				ListaT[9] = InimigosDesenho[3];
				ListaT[10] = InimigosDesenho[4];
				ListaT[11] = InimigosDesenho[5];
				
				// O valor de X e Y que os objetos guardam e a distancia deles em relacao ao X e Y do cenario,
				// aqui na lista, e necessario o valor real da posicao na tela, por isso a soma.
				ListaT[1].PosY += CPosY;
				ListaT[2].PosY += CPosY;
				ListaT[3].PosY += CPosY;
				ListaT[4].PosY += CPosY;
				ListaT[5].PosY += CPosY;
				ListaT[6].PosY += CPosY;
				ListaT[7].PosY += CPosY;
				ListaT[8].PosY += CPosY;
				ListaT[9].PosY += CPosY;
				ListaT[10].PosY += CPosY;
				ListaT[11].PosY += CPosY;
				
				//Libero o ponteiro que vai ser usado no main.
				free(*listaObjetosC);
				
				//Fa�o ele ser igual ao ponteiro criado nessa funcao.
				//O endereco do primeiro indice dele fica igual ao endereco do primeiro indice da ListaT.
				*listaObjetosC = ListaT;
					
				break;
			}
		
		case 1:
			{
				*TamanhoListaOC = 3;
				
				PersonagemD.PosY = PosY - PersonagemD.VTroca;
				
				PosicoesD *ListaT;
				ListaT = (PosicoesD *)malloc(sizeof(PosicoesD) * (*TamanhoListaOC));
				
				ListaT[0] = PersonagemD;
				ListaT[1] = ObjetosCenaDesenho[OTESTE_02_1_p1];
				ListaT[2] = ObjetosCenaDesenho[OTESTE_02_1_p2];
				
				ListaT[1].PosY += CPosY;
				ListaT[2].PosY += CPosY;
				
				free(*listaObjetosC);
				*listaObjetosC = ListaT;
					
				break;
			}
		
		default:
			printf("\nRaios multiplos! O operador esta incorreto.");	
	}
}

void criarListaRetangulosDeColisao(int CenarioAtual, RetangulosDeColisao RetanguloTeste[], RetangulosDeColisao PosicaoBaus[], int *TamanhoListaRetangulosDeColisao, RetangulosDeColisao **ListaRetangulosDeColisao)
{
	//Muda a lista (ponteiro) que tem os retangulos para colisao.
	switch(CenarioAtual)
	{
		case 0:
			{
				//Preciso colocar as chaves para limitar o escopo da variavel local que e declarada (ListaT), se nao da erro.
				*TamanhoListaRetangulosDeColisao = 5;
				
				//Crio um ponteiro que equivale a nova lista.
				RetangulosDeColisao *ListaT;
				ListaT = (RetangulosDeColisao *)malloc(sizeof(RetangulosDeColisao) * (*TamanhoListaRetangulosDeColisao));
				
				//Preencher a ListaT.
				//ListaT[0] = RetanguloTeste[0];
				//ListaT[1] = RetanguloTeste[1];
				ListaT[0] = PosicaoBaus[0];
				ListaT[1] = PosicaoBaus[1];
				ListaT[2] = PosicaoBaus[2];
				ListaT[3] = PosicaoBaus[3];
				ListaT[4] = PosicaoBaus[4];
				
				//Libero o ponteiro que vai ser usado no main.
				free(*ListaRetangulosDeColisao);
				
				//Fa�o ele ser igual ao ponteiro criado nessa funcao.
				//O endereco do primeiro indice dele fica igual ao endereco do primeiro indice da ListaT.		
				*ListaRetangulosDeColisao = ListaT;
				
				break;
			}
		
		case 1:
			{
				*TamanhoListaRetangulosDeColisao = 1;
				
				RetangulosDeColisao *ListaT;
				ListaT = (RetangulosDeColisao *)malloc(sizeof(RetangulosDeColisao) * (*TamanhoListaRetangulosDeColisao));
				
				ListaT[0].DisX = 0;
				ListaT[0].DisY = 0;
				ListaT[0].LarX = 0;
				ListaT[0].LarY = 0;
				
				free(*ListaRetangulosDeColisao);		
				*ListaRetangulosDeColisao = ListaT;
				
				break;
			}
		
		default:
			printf("\nRaios multiplos! O operador esta incorreto.");	
	}
}
