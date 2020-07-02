#ifndef BATALHA_H
#define BATALHA_H

void iniciarBatalha(Personagens* li, Personagens* mob, Consumivel** lista_consumiveis, bool podeFugir, bool *fecharJogo, void* Sprites_Retratos[], void* Sprites_Retratos_Mascaras[], void* Sprites_HUD[], void* Sprites_HUD_Mascaras[], void* Sprites_Mobs[], void* Sprites_Mobs_Mascaras[], void* Sprites_Efeitos[], void* Sprites_Efeitos_Mascaras[]);
void retratoDeBatalha(int PosX, int PosY, char Texto[30], int Tipo, int i, void* Sprites_Retratos[], void* Sprites_Retratos_Mascaras[]);
void desenhaMenu(Personagens* li, int *ArrayIds, int iMax, void* Sprites_Retratos[], void* Sprites_Retratos_Mascaras[], void* Sprites_HUD[], void* Sprites_HUD_Mascaras[]);

#endif
