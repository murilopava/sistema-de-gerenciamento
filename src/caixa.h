#ifndef CAIXA_H
#define CAIXA_H

#include "../raylib/include/raylib.h"
#include "screen.h"
#include "bst.h"

void InicializarTelaCaixa(void);
void DesenharTelaCaixa(Tela *telaAtual, Venda **raizBST);
void LiberarTelaCaixa(void);

#endif