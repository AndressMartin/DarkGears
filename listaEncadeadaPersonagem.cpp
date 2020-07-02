#include "enums.h"
#include "structs.h"

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

Personagens * lista_cria()
{
    return NULL;
}

Item * lista_itens_cria()
{
    return NULL;
}

Consumivel * lista_consumiveis_cria()
{
	return NULL;
}

/* insere o novo dado no início da lista  e retorna a lista atualizada*/
Personagens* lista_insere( Personagens* li, int id, char nome[], int atk, int def, int prec, int luc, int vel, int levels, int hp, int exp)
{
  	Personagens *novo = (Personagens*) malloc (sizeof(Personagens));
  	strcpy(novo->nome, nome);
    novo->levels = levels;
    novo->exp = exp;
    novo->hp = hp;
    novo->hpmax = hp;
	novo->atk = atk;
    novo->def = def;
    novo->prec = prec;
    novo->luc = luc;
    novo->vel = vel;
    novo->id = id;
    novo->prox=li;
    novo->ant=NULL;
    novo->itens=NULL;
    
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

int lista_consumiveis_vazia(Consumivel* li)
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

Consumivel* lista_consumiveis_busca(Consumivel* li, int tipo)
{
	//variável usada para percorrer a lista
	Consumivel *a; 
	for(a=li;a!=NULL;a=a->prox)
	{ 
	    if(a->tipo == tipo) return a;
	}         
	return NULL;
}

/* retorna o novo inicio ou a lista original*/
Personagens* lista_retira(Personagens* li, int id){
 	//procura o elemento na lista usando a função busca
    Personagens* aux=lista_busca(li, id);
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

Consumivel* lista_consumiveis_retira(Consumivel* li, int tipo){
 	//procura o elemento na lista usando a função busca
    Consumivel* aux=lista_consumiveis_busca(li, tipo);
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

Consumivel* lista_consumiveis_insere(Consumivel* li, Consumivel *item)
{
	// Procura e remove da lista caso já houver um item do mesmo tipo equipado;
	Consumivel *a = lista_consumiveis_busca(li, item->tipo);
	
	if(a != NULL)
	{
		a->qtd += item->qtd;
		return li;
	}
	else
	{
		Consumivel *novo= (Consumivel*) malloc (sizeof(Consumivel));
	    strcpy(novo->nome, item->nome);
	    novo->tipo = item->tipo;
	    novo->qtd = item->qtd;
	    novo->id = item->id;
	    novo->prox=li;
	    novo->ant=NULL;
	    
	    if(li!= NULL)
	        li->ant=novo;         
	    return novo;
	}
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

// Funcao para aplicar dano no personagem (player ou mob)
Personagens* aplicar_dano(Personagens* li, int id, int dano)
{
	Personagens *aux = lista_cria();
	Item *item = lista_itens_cria();
	
	aux = lista_busca(li, id);
	int defesa = 0;
	
	if(aux != NULL)
	{
		item = lista_itens_busca(aux->itens, 2); // 2 = item de defesa
		if(item != NULL)
		{
			defesa = item->def;
		}
		
		dano = dano - defesa; // calcula dano e trava o valor para nao ser menor que 1
		if(dano < 1)
		{
			dano = 1;	
		}
		
		aux->hp -= dano; // aplica o dano e trava o valor para nao ser menor que 0
		if(aux->hp < 0)
		{
			aux->hp = 0;
		}
	}
	
	return li;
}

// Retorna o dano do inimigo que ira realizar o ataque
int calcular_dano(Personagens* li, int id)
{
	int min = 0, max = 99;
	Personagens *aux = lista_cria();
	Item *item = lista_itens_cria();
	
	int randNum = rand()%(max-min + 1) + min;
	
	aux = lista_busca(li, id);
	int dano = 0;
	
	if(aux != NULL)
	{
		dano = aux->atk;
		
		item = lista_itens_busca(aux->itens, 1); // 1 = item de ataque
		if(item != NULL)
		{
			dano += item->atk;
		}
	}
	
	if(randNum > aux->prec) // Caso tire um numero maior que a precisao, erra o golpe
	{
		dano = 0;
	}
	else if(randNum == aux->prec) // Dano critico caso acerte o max de precisao do personagem
	{
		dano = dano * 2;
	}
	
	return dano;
}

// Adiciona um inimigo na lista, a partir de um id escolhido
Personagens* inserir_inimigo(Personagens* mob, int id)
{
	char nome [10];
	switch(id)
	{
		case 1:
			strcpy(nome, "Golem");
			mob = lista_insere(mob, 1, nome, 10, 8, 6, 6, 4, 5, 30, 0);
			break;
		case 2:
			strcpy(nome, "Wumpus");
			mob = lista_insere(mob, 2, nome, 15, 9, 10, 9, 2, 4, 30, 0);
			break;
		case 3:
			strcpy(nome, "Darius");
			mob = lista_insere(mob, 3, nome, 10, 3, 6, 1, 6, 15, 40, 0);
			break;
		default:
			strcpy(nome, "Dagon");
			mob = lista_insere(mob, 4, nome, 7, 5, 10, 5, 7, 10, 50, 0);
			break;
	}
		
	return mob;	
}

// Level UP
Personagens* aplicar_experiencia(Personagens* li, int qtd_exp)
{
	Personagens *aux = lista_cria();
	int subiu;
	
	for(aux = li; aux != NULL; aux = aux->prox)
	{
		aux->exp += qtd_exp;
		subiu = 1;
		
		while(subiu == 1)
		{
			if(aux->exp > ((aux->levels * 10) + (aux->levels + 1) * 10))
			{
				aux->levels += 1;
				aux->hp += 4;
				aux->hpmax += 4;
				aux->atk += 3;
				aux->def += 2;
				subiu = 1;
			}
			else
			{
				subiu = 0;
			}
		}
	}
	
	return li;
}

int personagem_vivo(int hp)
{
	if(hp > 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

// Funcao para realizar a utilizacao de um item consumivel
Personagens* utilizar_consumivel(Consumivel *li_cons, int tipo_consumivel, Personagens *li, int id_personagem)
{
	Personagens *aux_li = lista_cria();
	Consumivel *aux = lista_consumiveis_cria();
	int vivo;
	
	aux_li = lista_busca(li, id_personagem);
	
	if(aux_li != NULL)
	{		
		vivo = personagem_vivo(aux_li->hp);
	
		aux = lista_consumiveis_busca(li_cons, tipo_consumivel);
	
		if(aux != NULL)
		{
			if(aux->tipo == POCAO && vivo == 1)
			{
				aux->qtd -= 1;
				
				aux_li->hp += 30;
				
				// Verifica se o valor do HP ultrapassou o maximo e trava este valor
				if(aux_li->hp > aux_li->hpmax)
				{
					aux_li->hp = aux_li->hpmax;
				}
			}
			else if(aux->tipo == POCAO2 && vivo == 1)
			{
				aux->qtd -= 1;
				
				aux_li->hp += 60;
				
				// Verifica se o valor do HP ultrapassou o maximo e trava este valor
				if(aux_li->hp > aux_li->hpmax)
				{
					aux_li->hp = aux_li->hpmax;
				}
			}
			else if(aux->tipo == POCAO3 && vivo == 1)
			{
				aux->qtd -= 1;
				
				aux_li->hp += 150;
				
				// Verifica se o valor do HP ultrapassou o maximo e trava este valor
				if(aux_li->hp > aux_li->hpmax)
				{
					aux_li->hp = aux_li->hpmax;
				}	
			}
			else if(aux->tipo == CAFE && vivo == 0)
			{
				aux->qtd -= 1;
				
				aux_li->hp += aux_li->hpmax / 2;
				// Verifica se o valor do HP ultrapassou o maximo e trava este valor
				if(aux_li->hp > aux_li->hpmax)
				{
					aux_li->hp = aux_li->hpmax;
				}
			}
			
			/*
			if(aux->qtd <= 0) // Se a quantidade for menor ou igual a 0, o item sera removido da lista
			{
				li_cons = lista_consumiveis_retira(li_cons, tipo_consumivel);
			}
			*/
		}
	}
	
	return li;
}

void detalhaStatus(Personagens *item)
{
	Personagens *aux = lista_cria();
	Item *item_aux = lista_itens_cria();
	Consumivel *consumivel_aux = lista_consumiveis_cria();
	
	for(aux = item; aux != NULL; aux = aux->prox)
	{
		printf("\nPersonagem: %s; ATK %d / DEF %d / PREC %d / HP %d", aux->nome, aux->atk, aux->def, aux->prec, aux->hp);
		printf("\nItems: ");

		for(item_aux = aux->itens; item_aux != NULL; item_aux = item_aux->prox)
		{
			printf("\nDescricao: %s", item_aux->descricao);
		}
		
		printf("\n----------------------------------------\n");
	}
}

void detalhaConsumiveis(Consumivel *consumiveis)
{
	Consumivel *consumivel_aux = lista_consumiveis_cria();

	printf("\nConsumiveis: ");
	
	for(consumivel_aux = consumiveis; consumivel_aux != NULL; consumivel_aux = consumivel_aux->prox)
	{
		printf("\nDescricao: %s / qtd: %d", consumivel_aux->nome, consumivel_aux->qtd);
	}
}
