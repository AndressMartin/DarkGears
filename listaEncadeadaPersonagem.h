#ifndef LISTAENCADEADAPERSONAGEM_H
#define LISTAENCADEADAPERSONAGEM_H

Personagens * lista_cria();
Item * lista_itens_cria();
Personagens* lista_insere( Personagens* li, int id, char nome[], int atk, int def, int prec, int luc, int vel, int levels, int hp);
int lista_vazia(Personagens* li);
int lista_itens_vazia(Item* li);
Personagens* lista_busca(Personagens* li, int id);
Item* lista_itens_busca(Item* li, int tipo_item);
Personagens* lista_retira(Personagens* li, int tipo_item);
Item* lista_itens_retira(Item* li, int tipo_item);
Item* lista_itens_insere(Item* li, Item *item);
Personagens* equipa_item(Personagens*li, int id, Item *item);
Personagens* aplicar_dano(Personagens* li, int id, int dano);
int calcular_dano(Personagens* li, int id);
Personagens* inserir_inimigo(Personagens* mob, int id);

#endif
