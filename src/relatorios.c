#include <stdio.h>
#include <stdlib.h>

#include "relatorios.h"
#include "mergesort.h"

// Botão interno 

typedef struct {
	Rectangle rect;
	const char *texto;
} BotaoRel;

static int botaoClicado(BotaoRel b)
{
	Vector2 mouse = GetMousePosition();

	if (CheckCollisionPointRec(mouse, b.rect)) {
		DrawRectangleRec(b.rect, DARKGRAY);
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			return 1;
	} else {
		DrawRectangleRec(b.rect, GRAY);
	}

	DrawText(b.texto, b.rect.x + 12, b.rect.y + 12, 18, WHITE);
	return 0;
}

//Tela principal 

void DesenharTelaRelatorios(Tela *telaAtual, Venda *raizBST)
{
	static Venda *vetorVendas = NULL;
	static int tamanhoVetor   = 0;
	static int modoAtual      = 0;
	static int scrollOffset   = 0;

	ClearBackground(RAYWHITE);

	DrawText("RELATORIOS", 490, 30, 30, BLACK);

	BotaoRel btnVoltar = {{20, 745, 150, 40}, "< Voltar"};
	if (botaoClicado(btnVoltar)) {
		if (vetorVendas != NULL) {
			free(vetorVendas);
			vetorVendas = NULL;
			tamanhoVetor = 0;
		}
		modoAtual    = 0;
		scrollOffset = 0;
		*telaAtual   = TELA_MENU;
	}

	if (modoAtual == 0) {
		DrawText("Selecione um relatorio:", 420, 200, 22, DARKGRAY);

		BotaoRel btnFaturamento = {{350, 280, 500, 55}, "Relatorio por Faturamento"};
		BotaoRel btnCronologico = {{350, 360, 500, 55}, "Relatorio Cronologico (por ID)"};

		if (botaoClicado(btnFaturamento)) {
			if (vetorVendas != NULL)
				free(vetorVendas);

			vetorVendas = emOrdemArray(raizBST, &tamanhoVetor);

			if (vetorVendas != NULL && tamanhoVetor > 1)
				mergeSort(vetorVendas, 0, tamanhoVetor - 1);

			scrollOffset = 0;
			modoAtual    = 1;
		}

		if (botaoClicado(btnCronologico)) {
			if (vetorVendas != NULL)
				free(vetorVendas);

			vetorVendas = emOrdemArray(raizBST, &tamanhoVetor);

			scrollOffset = 0;
			modoAtual    = 2;
		}

		return;
	}


	const char *titulo = (modoAtual == 1)
	    ? "RANKING POR FATURAMENTO (MAIOR -> MENOR)"
	    : "HISTORICO CRONOLOGICO (ORDEM POR ID)";

	DrawText(titulo, 200, 80, 20, DARKBLUE);

	BotaoRel btnFechar = {{880, 745, 300, 40}, "Fechar Relatorio"};
	if (botaoClicado(btnFechar)) {
		free(vetorVendas);
		vetorVendas  = NULL;
		tamanhoVetor = 0;
		scrollOffset = 0;
		modoAtual    = 0;
	}

	if (tamanhoVetor == 0 || vetorVendas == NULL) {
		DrawText("Nenhuma venda registrada.", 420, 400, 22, GRAY);
		return;
	}

	int wheel = (int)GetMouseWheelMove();
	scrollOffset -= wheel;

	int linhasPorPagina = 17;
	int maxScroll       = tamanhoVetor - linhasPorPagina;
	if (maxScroll < 0) maxScroll = 0;
	if (scrollOffset < 0) scrollOffset = 0;
	if (scrollOffset > maxScroll) scrollOffset = maxScroll;

	DrawRectangle(40, 115, 1120, 28, LIGHTGRAY);
	DrawText("Pos.", 55,  120, 17, DARKGRAY);
	DrawText("ID Venda", 160, 120, 17, DARKGRAY);
	DrawText("Valor Total",  430, 120, 17, DARKGRAY);
	DrawText("Data",         750, 120, 17, DARKGRAY);

	for (int i = 0; i < linhasPorPagina && (i + scrollOffset) < tamanhoVetor; i++) {
		int idx = i + scrollOffset;
		Venda v = vetorVendas[idx];
		int y   = 148 + i * 33;

		Color fundo = (i % 2 == 0) ? (Color){245, 245, 245, 255} : RAYWHITE;
		DrawRectangle(40, y - 3, 1120, 30, fundo);

		char buf[64];

		snprintf(buf, sizeof(buf), (modoAtual == 1) ? "#%d" : "%d", idx + 1);
		DrawText(buf, 55, y, 17, BLACK);

		snprintf(buf, sizeof(buf), "%d", v.id);
		DrawText(buf, 160, y, 17, BLACK);

		snprintf(buf, sizeof(buf), "R$ %.2f", v.valor_total);
		DrawText(buf, 430, y, 17, (modoAtual == 1) ? DARKGREEN : BLACK);

		snprintf(buf, sizeof(buf), "%02d/%02d/%04d",
		    v.data.dia, v.data.mes, v.data.ano);
		DrawText(buf, 750, y, 17, BLACK);
	}

	int fim = scrollOffset + linhasPorPagina;
	if (fim > tamanhoVetor) fim = tamanhoVetor;

	char info[64];
	snprintf(info, sizeof(info), "Mostrando %d - %d de %d vendas",
	    scrollOffset + 1, fim, tamanhoVetor);
	DrawText(info, 350, 750, 16, GRAY);

	BotaoRel btnCima  = {{220, 745, 60, 40}, "^"};
	BotaoRel btnBaixo = {{290, 745, 60, 40}, "v"};

	if (botaoClicado(btnCima) && scrollOffset > 0)
		scrollOffset--;

	if (botaoClicado(btnBaixo) && scrollOffset < maxScroll)
		scrollOffset++;
}
