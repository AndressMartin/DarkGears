#ifndef ENUMS_H
#define ENUMS_H

//Enumera numeros e atribui a marcadores (o primeiro numero pode ser definido, por exempo enum A {A=1, B}, se não, é 0 por padrao).
//Pode ser utilizado para facilitar o uso de imagens.
enum Sprites {LILY, CHADDRIT, LILY3D};

//ObjetosCEnum {O + AREA_Mapa_NumeroDoObjeto}
enum ObjetosCenaEnum {OTESTE_01_1, OTESTE_01_2, OTESTE_01_3, OTESTE_02_1_p1, OTESTE_02_1_p2};

enum Tipos {PER, OBJ, BAU, INIMIGO}; //Enumera os tipos que as structs de PosisoesC podem ter.

//Enumero os indices dos itens do jogo.
enum IndiceItens {POCAO, POCAO2, POCAO3, CAFE, NADA};

//Enumera o indice das imagens a serem carregadas.
enum ImagensIndice {STESTE, CENARIOS, OBJETOSCENARIO, BAUS, RETRATOS, HUD, MOBS, EFEITOS, INIMIGOSMAPA};

//Enumera os indices das imagens de HUD.
enum ImagensHUD {CAIXADETEXTO, MENUBATALHA1, MENUBATALHA2, MENUBATALHA3, SELECAOM, MENUBATALHAR, MENUBATALHAR2, MENUBATALHA4, TELADETITULO, BOTAOJOGAR, BOTAOCREDITOS, BOTAOSAIR, TELADECREDITOS, MENUINVENTARIO1};

//Enumera os tipos de retratos de batalha
enum RetratoBatalhaPersonagem {RBLILY, RBCHADDRIT, RBCAFE, RBSLIME, RBGOLEM};
enum RetratoBatalhaTipo {RETRATOBATALHANORMAL, RETRATOBATALHAATACANDO, RETRATOBATALHADANO, RETRATOBATALHANOCAUTEADO};

enum RetratosImagens {LILYNORMAL, MORCEGONORMAL, BLILYNORMAL, BLILYATACANDO, BLILYLEVANDODANO, BLILYSEMHP, BCHADDRITNORMAL, BCHADDRITATACANDO, BCHADDRITLEVANDODANO, BCHADDRITSEMHP, BCAFERETRATO, BSLIMERETRATO, BGOLEMRETRATO};

//Enumera as acoes de batalha
enum AcoesDeBatalhaTipos {PERSONAGEM, MOB};
enum AcoesDeBatalha {ATAQUE, BPOCAO, BPOCAO2, BPOCAO3, BCAFE};

//Enumera as imagens dos inimigos nas batalhas
enum ImagensInimigosBatalha {BGOLEM, BWUMPUS};

//Enumera as imagens dos efeitos
enum ImagensEfeitos {GOLPE, CURA1_1, CURA1_2, CURA1_3, CURA2_1, CURA2_2, CURA2_3, CURA3_1, CURA3_2, CURA3_3, REVIVER1, REVIVER2, REVIVER3};

//Enumera as telas do jogo
enum TelasDoJogo {MENUINICIAL, CREDITOS, EXPLORACAO};

//Enumera os comandos de som
enum ComandosDeSom {VOLUME1, VOLUME2, VOLUME3, PARAREFEITOSONORO, PARARMUSICA, CURSORMOVE, CURSORVOLTA, CURSORPRONTO, CURSORERRO, MUSICABATALHA, MUSICAVITORIA, SOMCORREBATALHA, SOMDEATAQUE, SOMDECURA, SOMDEREVIVER, SOMINIMIGOMORTO, SOMDEATAQUE2, SOMERROUATAQUE, SOMDECURA2, SOMABRIRBAU};

#endif
