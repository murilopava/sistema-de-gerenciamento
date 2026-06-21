#include "raylib.h"
#include "menu.h"
#include "screen.h"
#include "relatorios.h"

int main(void)
{
	InitWindow(1200, 800, "Sistema");
	SetTargetFPS(144);

	Venda *raizBST = NULL;
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

		case TELA_PRODUTOS:
			// DesenharTelaProdutos(&telaAtual);
			break;

		case TELA_RELATORIOS:
			DesenharTelaRelatorios(&telaAtual, raizBST);
			break;

		case TELA_CONSULTA:
			// DesenharTelaConsulta(&telaAtual);
			break;
		}

		EndDrawing();
	}

	liberarArvore(raizBST);
	CloseWindow();
	return 0;
}