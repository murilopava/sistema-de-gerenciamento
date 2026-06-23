#include "raylib.h"
#include "caixa.h"
#include "hashtable.h"
#include "stack.h"
#include "queue.h"
#include "bst.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CODIGO 16

static Pilha carrinho;
static Fila filaClientes;
static float totalCarrinho;
static char clienteAtual[32];
static char inputCodigo[MAX_CODIGO];
static int inputLen;
static bool campoFocado;
static int proximoIdVenda = 1;

static Rectangle btnVoltar = { 30, 30, 100, 35 };
static Rectangle btnChamarCliente = { 30, 80, 220, 45 };
static Rectangle campoBipe = { 30, 220, 220, 40 };
static Rectangle btnBipar = { 30, 270, 220, 40 };
static Rectangle btnDesfazer = { 30, 470, 220, 45 };
static Rectangle btnFinalizar = { 30, 525, 220, 45 };

int obterClientesNaFila(void)
{
	return tamanhoFila(&filaClientes);
}

static void chamarProximoCliente(void) {
    if (tamanhoFila(&filaClientes) == 0) {
        strcpy(clienteAtual, "Fila vazia");
        return;
    }
    Cliente c = desenfileirar(&filaClientes);
    strcpy(clienteAtual, c.nome);
}

static void biparItem(void) {
    if (inputLen == 0) return;
    if (strcmp(clienteAtual, "Nenhum cliente chamado") == 0) return;

    int codigo = atoi(inputCodigo);
    Produto *p = buscarProduto(codigo);

    if (p != NULL && p->quantidade > 0) {
        p->quantidade--;
        empilhar(&carrinho, p);
        totalCarrinho += p->preco;
    }

    inputCodigo[0] = '\0';
    inputLen = 0;
}

static void desfazerUltimoItem(void) {
    Produto *p = desempilhar(&carrinho);
    if (p != NULL) {
        p->quantidade++;
        totalCarrinho -= p->preco;
    }
}

static void finalizarVenda(Venda **raizBST) {
    if (pilhaVazia(&carrinho)) return;

    float total = 0.0f;
    Produto *p;
    while ((p = desempilhar(&carrinho)) != NULL) {
        total += p->preco;
    }

    time_t t = time(NULL);
    struct tm *tmInfo = localtime(&t);
    Data hoje = { tmInfo->tm_mday, tmInfo->tm_mon + 1, tmInfo->tm_year + 1900 };

    *raizBST = inserir(*raizBST, proximoIdVenda++, total, hoje);

    totalCarrinho = 0.0f;
    strcpy(clienteAtual, "Nenhum cliente chamado");
}

void inicializarTelaCaixa(void) {
    inicializarHash();
    carregarProdutos("produtos.txt");
    inicializarPilha(&carrinho);

    inicializarFila(&filaClientes);
    carregarClientes(&filaClientes, "clientes.txt");

    strcpy(clienteAtual, "Nenhum cliente chamado");
    totalCarrinho = 0.0f;
    inputCodigo[0] = '\0';
    inputLen = 0;
    campoFocado = false;
}

void desenharTelaCaixa(Tela *telaAtual, Venda **raizBST) {

    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        campoFocado = CheckCollisionPointRec(mouse, campoBipe);

        if (CheckCollisionPointRec(mouse, btnVoltar))        *telaAtual = TELA_MENU;
        if (CheckCollisionPointRec(mouse, btnChamarCliente)) chamarProximoCliente();
        if (CheckCollisionPointRec(mouse, btnBipar))         biparItem();
        if (CheckCollisionPointRec(mouse, btnDesfazer))      desfazerUltimoItem();
        if (CheckCollisionPointRec(mouse, btnFinalizar))     finalizarVenda(raizBST);
    }

    if (campoFocado) {
        int key = GetCharPressed();
        while (key > 0) {
            if (inputLen < MAX_CODIGO - 1 && key >= '0' && key <= '9') {
                inputCodigo[inputLen++] = (char)key;
                inputCodigo[inputLen] = '\0';
            }
            key = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE) && inputLen > 0) {
            inputCodigo[--inputLen] = '\0';
        }
        if (IsKeyPressed(KEY_ENTER)) biparItem();
    }

    ClearBackground(RAYWHITE);

    bool hoverVoltar = CheckCollisionPointRec(mouse, btnVoltar);
    DrawRectangleRec(btnVoltar, hoverVoltar ? LIGHTGRAY : GRAY);
    DrawText("Voltar", 50, 40, 18, BLACK);

    DrawText("Frente de Caixa e Atendimento", 150, 35, 26, DARKGRAY);

    DrawText("Cliente em atendimento:", 30, 130, 16, GRAY);
    DrawText(clienteAtual, 30, 150, 20, BLACK);

    bool hoverChamar = CheckCollisionPointRec(mouse, btnChamarCliente);
    DrawRectangleRec(btnChamarCliente, hoverChamar ? LIGHTGRAY : GRAY);
    DrawText("Chamar Próximo", 45, 92, 18, BLACK);

    char filaInfo[32];
    snprintf(filaInfo, sizeof(filaInfo), "Na fila: %d clientes", tamanhoFila(&filaClientes));
    DrawText(filaInfo, 30, 170, 14, GRAY);

    DrawText("Bipe de Item (código):", 30, 195, 16, GRAY);
    DrawRectangleRec(campoBipe, campoFocado ? LIGHTGRAY : WHITE);
    DrawRectangleLinesEx(campoBipe, 1, GRAY);
    DrawText(inputCodigo, campoBipe.x + 8, campoBipe.y + 10, 18, BLACK);

    bool hoverBipar = CheckCollisionPointRec(mouse, btnBipar);
    DrawRectangleRec(btnBipar, hoverBipar ? LIGHTGRAY : GRAY);
    DrawText("Bipar Item", 80, 282, 18, BLACK);

    bool hoverDesfazer = CheckCollisionPointRec(mouse, btnDesfazer);
    DrawRectangleRec(btnDesfazer, hoverDesfazer ? PINK : MAROON);
    DrawText("Desfazer Último", 45, 482, 18, WHITE);

    bool hoverFinalizar = CheckCollisionPointRec(mouse, btnFinalizar);
    DrawRectangleRec(btnFinalizar, hoverFinalizar ? LIME : DARKGREEN);
    DrawText("Finalizar Venda", 50, 537, 18, WHITE);

    DrawText("Carrinho (Pilha):", 320, 60, 18, GRAY);
    DrawRectangleLines(320, 85, 550, 420, GRAY);

    int y = 95;
    Item *atual = carrinho.topo;
    while (atual != NULL) {
        char linha[150];
        snprintf(linha, sizeof(linha), "%s  -  R$ %.2f", atual->produto->nome, atual->produto->preco);
        Color cor = (atual == carrinho.topo) ? DARKBLUE : BLACK;
        DrawText(linha, 335, y, 18, cor);
        y += 30;
        atual = atual->prox;
    }

    char totalTxt[32];
    snprintf(totalTxt, sizeof(totalTxt), "TOTAL: R$ %.2f", totalCarrinho);
    DrawText(totalTxt, 320, 525, 28, MAROON);
}

void liberarTelaCaixa(void) {
    liberarPilha(&carrinho);
    liberarFila(&filaClientes);
    liberarHash();
}