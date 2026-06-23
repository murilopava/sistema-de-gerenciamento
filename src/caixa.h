#ifndef CAIXA_H
#define CAIXA_H

#include "../raylib/include/raylib.h"
#include "screen.h"
#include "bst.h"

void inicializarTelaCaixa(void);
void desenharTelaCaixa(Tela *telaAtual, Venda **raizBST);
void liberarTelaCaixa(void);
int  obterClientesNaFila(void);

#endif