#ifndef ENUMS_H
#define ENUMS_H

//Enumera numeros e atribui a marcadores (o primeiro numero pode ser definido, por exempo enum A {A=1, B}, se não, é 0 por padrao).
//Pode ser utilizado para facilitar o uso de imagens.
enum Sprites {LILY, CHADDRIT, LILY3D};

//ObjetosCEnum {O + AREA_Mapa_NumeroDoObjeto}
enum ObjetosCenaEnum {OTESTE_01_1, OTESTE_01_2, OTESTE_01_3, OTESTE_02_1_p1, OTESTE_02_1_p2};

enum Tipos {PER, OBJ, BAU}; //Enumera os tipos que as structs de PosisoesC podem ter.

//Enumero os indices dos itens do jogo.
enum IndiceItens {POCAO, POCAO2, POCAO3, CAFE, NADA};

//Enumera o indice das imagens a serem carregadas.
enum ImagensIndice {STESTE, CCENTESTE, OCENTESTE, BAUS, RETRATOS, HUD, MOBS, EFEITOS};

//Enumera os indices das imagens de HUD.
enum ImagensHUD {CAIXADETEXTO, MENUBATALHA1, MENUBATALHA2, MENUBATALHA3, SELECAOM, MENUBATALHAR, MENUBATALHAR2};

//Enumera os tipos de retratos de batalha
enum RetratoBatalhaPersonagem {RBLILY, RBCHADDRIT};
enum RetratoBatalhaTipo {RETRATOBATALHANORMAL, RETRATOBATALHAATACANDO, RETRATOBATALHADANO, RETRATOBATALHANOCAUTEADO};

//Enumera as acoes de batalha
enum AcoesDeBatalhaTipos {PERSONAGEM, MOB};
enum AcoesDeBatalha {ATAQUE};

//Enumera as imagens dos inimigos nas batalhas
enum ImagensInimigosBatalha {BGOLEM, BWUMPUS};

//Enumera as imagens dos efeitos
enum ImagensEfeitos {GOLPE};

#endif
