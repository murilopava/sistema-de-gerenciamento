#include "raylib.h"
#include "menu.h"
#include "screen.h"
#include "relatorios.h"
#include "register.h"
#include "consulta.h"
#include "teste.h"

int main(void)
{
	InitWindow(1200, 800, "Sistema");
	SetTargetFPS(144);
	SetExitKey(0);
	
	Venda *raizBST = NULL;
	
	// teste provisorio para popular a arvore de vendas
	raizBST = popularArvore(raizBST);
	
	Tela telaAtual = TELA_MENU;

	while (!WindowShouldClose()) {
		BeginDrawing();

		switch (telaAtual) {
		case TELA_MENU:
			DesenharMenu(&telaAtual);
			break;

		case TELA_CAIXA:
			// DesenharTelaCaixa(&telaAtual);
			break;

		case TELA_RELATORIOS:
			DesenharTelaRelatorios(&telaAtual, raizBST);
			break;

		case TELA_CONSULTA:
			DesenharTelaConsulta(&telaAtual, raizBST);
			break;

		case TELA_CADASTRO:
			DesenharTelaCadastro(&telaAtual);
			break;
		}

		EndDrawing();
	}

	liberarArvore(raizBST);
	CloseWindow();
	return 0;
}