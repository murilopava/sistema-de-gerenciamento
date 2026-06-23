#include "menu.h"

typedef struct {
	Rectangle rect; // posição e tamanho do botão
	const char *texto; // texto exibido dentro do botão
} Botao;

static int BotaoClicado(Botao b)
{
	Vector2 mouse = GetMousePosition();

	if (CheckCollisionPointRec(mouse, b.rect)) {
		DrawRectangleRec(b.rect, DARKGRAY);

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			return 1;
	} else {
		DrawRectangleRec(b.rect, GRAY);
	}

	DrawText(b.texto, b.rect.x + 20, b.rect.y + 20, 20, WHITE);

	return 0;
}

void DesenharMenu(Tela *telaAtual)
{
	ClearBackground(RAYWHITE);

	DrawText("MENU", 520, 80, 30, BLACK);

	Botao caixa = {{450, 160, 300, 60}, "Caixa"};
	Botao cadastro = {{450, 240, 300, 60}, "Cadastro Produtos"};
	Botao relatorios = {{450, 320, 300, 60}, "Relatorios"};
	Botao consulta = {{450, 400, 300, 60}, "Consulta"};

	// troca de tela
	if (BotaoClicado(caixa))
		*telaAtual = TELA_CAIXA;

	if (BotaoClicado(cadastro))
		*telaAtual = TELA_CADASTRO;

	if (BotaoClicado(relatorios))
		*telaAtual = TELA_RELATORIOS;

	if (BotaoClicado(consulta))
		*telaAtual = TELA_CONSULTA;
}