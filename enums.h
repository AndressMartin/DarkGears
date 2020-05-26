#ifndef ENUMS_H
#define ENUMS_H

//Enumera numeros e atribui a marcadores (o primeiro numero pode ser definido, por exempo enum A {A=1, B}, se não, é 0 por padrao).
//Pode ser utilizado para facilitar o uso de imagens.
enum Sprites {LILY, CHADDRIT};
	
//CColisoes {AREA_Mapa_ParteDoMapa}
enum CenaColisoes {TESTEC_01_1, TESTEC_01_2, TESTEC_01_3, TESTEC_01_4};

//ObjetosCEnum {O + AREA_Mapa_NumeroDoObjeto}
enum ObjetosCenaEnum {OTESTE_01_1, OTESTE_01_2, OTESTE_01_3};

enum Tipos {PER, OBJ, BAU}; //Enumera os tipos que as structs de PosisoesC podem ter.

//Enumero os indices dos itens do jogo.
enum IndiceItens {NADA, POCAO, POCAO2};

//Enumera o indice das imagens a serem carregadas.
enum ImagensIndice {STESTE, CCENTESTE, OCENTESTE, BAUS};

#endif
