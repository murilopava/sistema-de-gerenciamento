#include "raylib.h"
#include <string.h>
#include <stdlib.h>

#include "register.h"
#include "hashtable.h"

// Campos de texto do formulário
static char codigo[10] = "";
static char nome[100] = "";
static char preco[10] = "";
static char qtd[10] = "";

// Campo atualmente selecionado
static int foco = -1;

// Áreas dos campos na tela
static Rectangle rCodigo = {450, 120, 300, 30};
static Rectangle rNome = {450, 170, 300, 30};
static Rectangle rPreco = {450, 220, 300, 30};
static Rectangle rQtd = {450, 270, 300, 30};

// Verifica se um campo foi clicado
static int CampoClicado(Rectangle r)
{
	// Obtém posição do mouse
	Vector2 mouse = GetMousePosition();

	// Verifica se o mouse está dentro do campo
	if (CheckCollisionPointRec(mouse, r)) {
		// Destaca o campo ao passar o mouse
		DrawRectangleRec(r, LIGHTGRAY);

		// Retorna verdadeiro se houver clique
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			return 1;
	} else {
		// Desenha o campo normalmente
		DrawRectangleRec(r, RAYWHITE);
		DrawRectangleLines(r.x, r.y, r.width, r.height, GRAY);
	}

	return 0;
}

// Desenha a tela de cadastro
void DesenharTelaCadastro(Tela *tela)
{
	// Limpa a tela
	ClearBackground(RAYWHITE);

	// Título
	DrawText("CADASTRO DE PRODUTO", 420, 50, 20, BLACK);

	// Campo código
	DrawText("Codigo:", 350, 120, 20, BLACK);
	if (CampoClicado(rCodigo))
		foco = 0;

	DrawText(
	    codigo, rCodigo.x + 10, rCodigo.y + 5, 20, foco == 0 ? RED : BLACK);

	// Campo nome
	DrawText("Nome:", 350, 170, 20, BLACK);
	if (CampoClicado(rNome))
		foco = 1;

	DrawText(nome, rNome.x + 10, rNome.y + 5, 20, foco == 1 ? RED : BLACK);

	// Campo preço
	DrawText("Preco:", 350, 220, 20, BLACK);
	if (CampoClicado(rPreco))
		foco = 2;

	DrawText(
	    preco, rPreco.x + 10, rPreco.y + 5, 20, foco == 2 ? RED : BLACK);

	// Campo quantidade
	DrawText("Qtd:", 350, 270, 20, BLACK);
	if (CampoClicado(rQtd))
		foco = 3;

	DrawText(qtd, rQtd.x + 10, rQtd.y + 5, 20, foco == 3 ? RED : BLACK);

	// Instruções para o usuário
	DrawText("ENTER salva | ESC volta", 400, 350, 18, GRAY);

	// Volta para o menu
	if (IsKeyPressed(KEY_ESCAPE))
		*tela = TELA_MENU;

	// Captura caractere digitado
	int key = GetCharPressed();

	// Entrada do código
	if (foco == 0 && key >= '0' && key <= '9') {
		int len = strlen(codigo);
		codigo[len] = key;
		codigo[len + 1] = 0;
	}

	// Entrada do nome
	if (foco == 1 && key >= 32 && key <= 126) {
		int len = strlen(nome);
		nome[len] = key;
		nome[len + 1] = 0;
	}

	// Entrada do preço
	if (foco == 2 && ((key >= '0' && key <= '9') || key == '.')) {
		int len = strlen(preco);
		preco[len] = key;
		preco[len + 1] = 0;
	}

	// Entrada da quantidade
	if (foco == 3 && key >= '0' && key <= '9') {
		int len = strlen(qtd);
		qtd[len] = key;
		qtd[len + 1] = 0;
	}

	// Salva o produto
	if (IsKeyPressed(KEY_ENTER)) {
		Produto p;

		// Converte texto para números
		p.codigo = atoi(codigo);
		strcpy(p.nome, nome);
		p.preco = atof(preco);
		p.quantidade = atoi(qtd);

		// Define data de cadastro
		p.dataRegistro.dia = 22;
		p.dataRegistro.mes = 6;
		p.dataRegistro.ano = 2026;

		// Insere o produto na tabela hash
		inserirProduto(p);

		// Limpa os campos
		codigo[0] = 0;
		nome[0] = 0;
		preco[0] = 0;
		qtd[0] = 0;

		// Remove o foco dos campos
		foco = -1;
	}
}