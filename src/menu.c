#include "menu.h"


#include "caixa.h"      // para ObterClientesNaFila() no dashboard
#include "hashtable.h"  // para contarProdutos() no dashboard

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

	// dashboard de status: exibe em tempo real o total de clientes na fila
	// e a soma de todas as unidades em estoque 
	char dashClientes[64];
	char dashProdutos[64];
	snprintf(dashClientes, sizeof(dashClientes), "Clientes aguardando na fila: %d", obterClientesNaFila());
	snprintf(dashProdutos, sizeof(dashProdutos), "Produtos cadastrados no estoque: %d", contarProdutos());
	DrawText(dashClientes, 380, 680, 18, DARKGRAY);
	DrawText(dashProdutos, 380, 710, 18, DARKGRAY);

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