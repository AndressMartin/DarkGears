#ifndef LISTAENCADEADAPERSONAGEM_H
#define LISTAENCADEADAPERSONAGEM_H

// FUNÇÕES PARA GERENCIAR LISTAS
// Inicialização
Personagens * lista_cria();
Item * lista_itens_cria();
Consumivel * lista_consumiveis_cria()

// Verificacar se vazia
int lista_vazia(Personagens* li);
int lista_itens_vazia(Item* li);
int lista_consumiveis_vazia(Consumivel* li)

// Busca
Personagens* lista_busca(Personagens* li, int id);
Item* lista_itens_busca(Item* li, int tipo_item);
Consumivel* lista_consumiveis_busca(Consumivel* li, int tipo)

// Exclusão
Personagens* lista_retira(Personagens* li, int tipo_item);
Item* lista_itens_retira(Item* li, int tipo_item);
Consumivel* lista_consumiveis_retira(Consumivel* li, int tipo){

// Inserção
Consumivel* lista_consumiveis_insere(Consumivel* li, Consumivel *item)
Item* lista_itens_insere(Item* li, Item *item);
Personagens* lista_insere( Personagens* li, int id, char nome[], int atk, int def, int prec, int luc, int vel, int levels, int hp);

// Funções para manuseio de inventario e calculos de batalha
Personagens* equipa_item(Personagens*li, int id, Item *item);
Personagens* aplicar_dano(Personagens* li, int id, int dano);
int calcular_dano(Personagens* li, int id);
Personagens* inserir_inimigo(Personagens* mob, int id);

void detalhaStatus(Personagens *item);

#endif
