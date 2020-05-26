#ifndef LISTASDOMAPA_H
#define LISTASDOMAPA_H

void criarListaObjetosC(int CenarioAtual, int CPosY, int PosY, PosicoesD PersonagemD, PosicoesD ObjetosCenaDesenho[], PosicoesD BausCenaDesenho[], int *TamanhoListaOC, PosicoesD **listaObjetosC);
void criarListaRetangulosDeColisao(int CenarioAtual, RetangulosDeColisao RetanguloTeste[], RetangulosDeColisao PosicaoBaus[], int *TamanhoListaRetangulosDeColisao, RetangulosDeColisao **ListaRetangulosDeColisao);

#endif
