#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

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

typedef struct personagem{
	int id;
	int exp;
	int levels;
	int hp;
	char nome[10];
	int atk;
	int def;
	int prec;
	int luc;
	int vel;
	Item *itens = NULL;
    struct personagem *ant;
    struct personagem *prox;
}Personagens; //definição da lista

Personagens * lista_cria()
{
    return NULL;
}

Item * lista_itens_cria()
{
    return NULL;
}

/* insere o novo dado no início da lista  e retorna a lista atualizada*/
Personagens* lista_insere( Personagens* li, int id, char nome[], int atk, int def, int prec, int luc, int vel, int levels, int hp)
{
  	Personagens *novo = (Personagens*) malloc (sizeof(Personagens));
  	strcpy(novo->nome, nome);
    novo->levels = levels;
    novo->exp = 0;
    novo->hp = hp;
	novo->atk = atk;
    novo->def = def;
    novo->prec = prec;
    novo->luc = luc;
    novo->vel = vel;
    novo->id = id;
    novo->prox=li;
    novo->ant=NULL;
    
    //verifica se a lista não esta vazia
    if(li!= NULL)
        li->ant=novo;         
    return novo;
}

/* retorna 1 se vazia ou zero se falso*/
int lista_vazia(Personagens* li)
{     
    return(li==NULL); 
}         

int lista_itens_vazia(Item* li)
{     
    return(li==NULL); 
}  

/* retorna o elemento ou NULL se não achou*/
Personagens* lista_busca(Personagens* li, int id)
{     
	//variável usada para percorrer a lista
	Personagens *a;
	int i = 0; 
	for(a = li; a != NULL; a = a->prox)
	{ 
	    if(a->id == id) 
		{
			return a;
		}
	}     

	return NULL;
}

Item* lista_itens_busca(Item* li, int tipo_item)
{     
	//variável usada para percorrer a lista
	Item *a; 
	for(a=li;a!=NULL;a=a->prox)
	{ 
	    if(a->tipo_item == tipo_item) return a;
	}         
	return NULL;
}

/* retorna o novo inicio ou a lista original*/
Personagens* lista_retira(Personagens* li, int tipo_item){
 	//procura o elemento na lista usando a função busca
    Personagens* aux=lista_busca(li, tipo_item);
    if (aux==NULL) //não achou o elemento
        return li; 
    //retira o elemento encadeado
    if(li==aux) //verifica se é o primeiro da lista
    	li=aux->prox;
    else
        aux->ant->prox=aux->prox;
    //testa para ver se é o ultimo da lista
    if (aux->prox!=NULL)        
        aux->prox->ant=aux->ant;
    free(aux);
    return li;
}

Item* lista_itens_retira(Item* li, int tipo_item){
 	//procura o elemento na lista usando a função busca
    Item* aux=lista_itens_busca(li, tipo_item);
    if (aux==NULL) //não achou o elemento
        return li; 
    //retira o elemento encadeado
    if(li==aux) //verifica se é o primeiro da lista
    	li=aux->prox;
    else
        aux->ant->prox=aux->prox;
    //testa para ver se é o ultimo da lista
    if (aux->prox!=NULL)        
        aux->prox->ant=aux->ant;
    free(aux);
    return li;
}

Item* lista_itens_insere(Item* li, Item *item)
{
	// Procura e remove da lista caso já houver um item do mesmo tipo equipado;
	li = lista_itens_retira(li, item->tipo_item);

  	Item *novo= (Item*) malloc (sizeof(Item));
    strcpy(novo->descricao, item->descricao);
    novo->atk = item->atk;
    novo->def = item->def;
    novo->prec = item->prec;
    novo->luc = item->luc;
    novo->vel = item->vel;
    novo->tipo_item = item->tipo_item;
    novo->prox=li;
    novo->ant=NULL;
    
    if(li!= NULL)
        li->ant=novo;         
    return novo;
}

Personagens* equipa_item(Personagens*li, int id, Item *item)
{
	Personagens* personagem = lista_busca(li, id);
	
	if(personagem != NULL)
	{
		personagem->itens = lista_itens_insere(personagem->itens, item);
	}
	
	return li;
}
