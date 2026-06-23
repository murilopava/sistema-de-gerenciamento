#include "raylib.h"
#include "menu.h"
#include "screen.h"
#include "relatorios.h"
#include "register.h"
#include "consulta.h"
#include "caixa.h"

int main(void)
{
	InitWindow(1200, 800, "Sistema");
	SetTargetFPS(144);
	SetExitKey(0);
	
	Venda *raizBST = NULL;
	
	Tela telaAtual = TELA_MENU;

	inicializarTelaCaixa();

	while (!WindowShouldClose()) {
		BeginDrawing();

		switch (telaAtual) {
		case TELA_MENU:
			DesenharMenu(&telaAtual);
			break;

		case TELA_CAIXA:
			desenharTelaCaixa(&telaAtual, &raizBST);
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

	liberarTelaCaixa();
	liberarArvore(raizBST);
	CloseWindow();
	return 0;
}