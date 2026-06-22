#include "raylib.h"
#include <string.h>
#include <stdlib.h>

#include "register.h"
#include "hashtable.h"

static char codigo[10] = "";
static char nome[100] = "";
static char preco[10] = "";
static char qtd[10] = "";

static int foco = -1;

static Rectangle rCodigo = {450, 120, 300, 30};
static Rectangle rNome = {450, 170, 300, 30};
static Rectangle rPreco = {450, 220, 300, 30};
static Rectangle rQtd = {450, 270, 300, 30};

static int CampoClicado(Rectangle r)
{
	Vector2 mouse = GetMousePosition();

	if (CheckCollisionPointRec(mouse, r)) {
		DrawRectangleRec(r, LIGHTGRAY);

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			return 1;
	} else {
		DrawRectangleRec(r, RAYWHITE);
		DrawRectangleLines(r.x, r.y, r.width, r.height, GRAY);
	}

	return 0;
}

void DesenharTelaCadastro(Tela *tela)
{
	ClearBackground(RAYWHITE);

	DrawText("CADASTRO DE PRODUTO", 420, 50, 20, BLACK);

	DrawText("Codigo:", 350, 120, 20, BLACK);
	if (CampoClicado(rCodigo))
		foco = 0;
	DrawText(
	    codigo, rCodigo.x + 10, rCodigo.y + 5, 20, foco == 0 ? RED : BLACK);

	DrawText("Nome:", 350, 170, 20, BLACK);
	if (CampoClicado(rNome))
		foco = 1;
	DrawText(nome, rNome.x + 10, rNome.y + 5, 20, foco == 1 ? RED : BLACK);

	DrawText("Preco:", 350, 220, 20, BLACK);
	if (CampoClicado(rPreco))
		foco = 2;
	DrawText(
	    preco, rPreco.x + 10, rPreco.y + 5, 20, foco == 2 ? RED : BLACK);

	DrawText("Qtd:", 350, 270, 20, BLACK);
	if (CampoClicado(rQtd))
		foco = 3;
	DrawText(qtd, rQtd.x + 10, rQtd.y + 5, 20, foco == 3 ? RED : BLACK);

	DrawText("ENTER salva | ESC volta", 400, 350, 18, GRAY);

	// voltar
	if (IsKeyPressed(KEY_ESCAPE))
		*tela = TELA_MENU;

	// input
	int key = GetCharPressed();

	if (foco == 0 && key >= '0' && key <= '9') {
		int len = strlen(codigo);
		codigo[len] = key;
		codigo[len + 1] = 0;
	}

	if (foco == 1 && key >= 32 && key <= 126) {
		int len = strlen(nome);
		nome[len] = key;
		nome[len + 1] = 0;
	}

	if (foco == 2 && ((key >= '0' && key <= '9') || key == '.')) {
		int len = strlen(preco);
		preco[len] = key;
		preco[len + 1] = 0;
	}

	if (foco == 3 && key >= '0' && key <= '9') {
		int len = strlen(qtd);
		qtd[len] = key;
		qtd[len + 1] = 0;
	}

	// salvar
	if (IsKeyPressed(KEY_ENTER)) {
		Produto p;

		p.codigo = atoi(codigo);
		strcpy(p.nome, nome);
		p.preco = atof(preco);
		p.quantidade = atoi(qtd);

		p.dataRegistro.dia = 22;
		p.dataRegistro.mes = 6;
		p.dataRegistro.ano = 2026;

		inserirProduto(p);

		// limpa
		codigo[0] = 0;
		nome[0] = 0;
		preco[0] = 0;
		qtd[0] = 0;

		foco = -1;
	}
}