#include <string.h>
#include <stdlib.h>

#include "consulta.h"

void DesenharTelaConsulta(Tela *telaAtual, Venda *raizBST)
{
	static char campoBusca[10] = "";
	static Venda *resultado    = NULL;
	static int buscaFeita      = 0;

	ClearBackground(RAYWHITE);

	DrawText("CONSULTA DE VENDA", 450, 30, 30, BLACK);

	// campo de texto
	DrawText("Digite o ID da venda:", 380, 150, 20, DARKGRAY);

	Rectangle rCampo = {380, 180, 300, 35};
	Vector2 mouse = GetMousePosition();

	if (CheckCollisionPointRec(mouse, rCampo))
		DrawRectangleLinesEx(rCampo, 2, DARKBLUE);
	else
		DrawRectangleLinesEx(rCampo, 1, GRAY);

	DrawRectangleRec(rCampo, RAYWHITE);
	DrawRectangleLinesEx(rCampo, 1, GRAY);
	DrawText(campoBusca, rCampo.x + 10, rCampo.y + 8, 20, BLACK);

	// input
	int key = GetCharPressed();
	if (key >= '0' && key <= '9') {
		int len = strlen(campoBusca);
		if (len < 9) {
			campoBusca[len]     = key;
			campoBusca[len + 1] = 0;
		}
	}
	if (IsKeyPressed(KEY_BACKSPACE)) {
		int len = strlen(campoBusca);
		if (len > 0)
			campoBusca[len - 1] = 0;
	}

	// botao buscar
	Rectangle rBuscar = {700, 180, 120, 35};
	Color corBuscar = CheckCollisionPointRec(mouse, rBuscar) ? DARKGRAY : GRAY;
	DrawRectangleRec(rBuscar, corBuscar);
	DrawText("Buscar", rBuscar.x + 20, rBuscar.y + 8, 20, WHITE);

	if (CheckCollisionPointRec(mouse, rBuscar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		int id = atoi(campoBusca);
		resultado  = buscar(raizBST, id);
		buscaFeita = 1;
	}

	// resultado
	if (buscaFeita) {
		if (resultado != NULL) {
			DrawRectangle(300, 270, 600, 130, (Color){235, 245, 255, 255});
			DrawRectangleLinesEx((Rectangle){300, 270, 600, 130}, 1, DARKBLUE);

			char buf[64];

			snprintf(buf, sizeof(buf), "ID da Venda:  %d", resultado->id);
			DrawText(buf, 330, 295, 20, BLACK);

			snprintf(buf, sizeof(buf), "Valor Total:  R$ %.2f", resultado->valor_total);
			DrawText(buf, 330, 330, 20, DARKGREEN);

			snprintf(buf, sizeof(buf), "Data:         %02d/%02d/%04d",
			    resultado->data.dia, resultado->data.mes, resultado->data.ano);
			DrawText(buf, 330, 365, 20, BLACK);
		} else {
			DrawText("Venda nao encontrada.", 390, 300, 22, RED);
		}
	}

	// botao voltar
	Rectangle rVoltar = {20, 745, 150, 40};
	Color corVoltar = CheckCollisionPointRec(mouse, rVoltar) ? DARKGRAY : GRAY;
	DrawRectangleRec(rVoltar, corVoltar);
	DrawText("< Voltar", rVoltar.x + 12, rVoltar.y + 12, 18, WHITE);

	if (CheckCollisionPointRec(mouse, rVoltar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		campoBusca[0] = 0;
		resultado     = NULL;
		buscaFeita    = 0;
		*telaAtual    = TELA_MENU;
	}
}
