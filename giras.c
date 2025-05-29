#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define GRID_SIZE_MAIN 10
#define GRID_SIZE_FASE2 20
#define GRID_SIZE_FASE3 40

typedef struct {
    int x;
    int y;
} NPC;

void desenhaMapa(char mapa[GRID_SIZE_MAIN][GRID_SIZE_MAIN]) {
    int i, j;
    for (i = 0; i < GRID_SIZE_MAIN; i++) {
        for (j = 0; j < GRID_SIZE_MAIN; j++) {
            printf("%c ", mapa[i][j]);
        }
        printf("\n");
    }
}

void desenhaMapaFase2(char mapa[GRID_SIZE_FASE2][GRID_SIZE_FASE2]) {
    int i, j;
    for (i = 0; i < GRID_SIZE_FASE2; i++) {
        for (j = 0; j < GRID_SIZE_FASE2; j++) {
            printf("%c ", mapa[i][j]);
        }
        printf("\n");
    }
}

void desenhaMapaFase3(char mapa[GRID_SIZE_FASE3][GRID_SIZE_FASE3]) {
    int i, j;
    for (i = 0; i < GRID_SIZE_FASE3; i++) {
        for (j = 0; j < GRID_SIZE_FASE3; j++) {
            printf("%c ", mapa[i][j]);
        }
        printf("\n");
    }
}

void moverNPC(NPC *npc, char *mapa, int gridSize, char paredesChar, int targetY, int targetX) {
    int proximoY = npc->y;
    int proximoX = npc->x;

    if (targetY != -1 && targetX != -1) {
        int dy = targetY - npc->y;
        int dx = targetX - npc->x;

        if (abs(dy) > abs(dx)) {
            if (dy > 0) proximoY++;
            else proximoY--;
        } else {
            if (dx > 0) proximoX++;
            else proximoX--;
        }

        if (proximoY < 0 || proximoY >= gridSize || proximoX < 0 || proximoX >= gridSize ||
            *(mapa + proximoY * gridSize + proximoX) == paredesChar) {
            proximoY = npc->y;
            proximoX = npc->x;

            if (abs(dy) <= abs(dx)) {
                if (dx > 0) proximoX++;
                else proximoX--;
            } else {
                if (dy > 0) proximoY++;
                else proximoY--;
            }
        }
    } else {
        int direcao = rand() % 4;
        switch (direcao) {
            case 0: proximoY--; break;
            case 1: proximoY++; break;
            case 2: proximoX--; break;
            case 3: proximoX++; break;
        }
    }

    if (proximoY >= 0 && proximoY < gridSize &&
        proximoX >= 0 && proximoX < gridSize &&
        *(mapa + proximoY * gridSize + proximoX) != paredesChar) {
        npc->y = proximoY;
        npc->x = proximoX;
    }
}

void telaDeMorte() {
    system("cls");
    printf("Voce morreu! Tentando novamente...\n");
    Sleep(1500);
    system("cls");
}

int entraNaFase3() {
    char mapa_fase3[GRID_SIZE_FASE3][GRID_SIZE_FASE3];
    char heroi = '&';
    int pos_y_fase3_inicial = 1;
    int pos_x_fase3_inicial = 1;
    int pos_y_fase3;
    int pos_x_fase3;
    int i, j;
    char tecla;
    int vidas_restantes = 3;
    int contador_movimentos = 0;

    NPC monstro_fase3_1;
    char simbolo_monstro1 = 'X';
    NPC monstro_fase3_2;
    char simbolo_monstro2 = 'V';

    int tele_entrada_y = 15;
    int tele_entrada_x = 15;
    int tele_saida_y = 30;
    int tele_saida_x = 30;

    int chave3_y = 7;
    int chave3_x = 7;
    int bloqueio3_y = GRID_SIZE_FASE3 - 2;
    int bloqueio3_x = GRID_SIZE_FASE3 - 3;
    int botao3_y = 10;
    int botao3_x = 10;
    int tem_chave3;
    int espinhos_gerados;

    for (vidas_restantes = 3; vidas_restantes > 0; vidas_restantes--) {
        pos_y_fase3 = pos_y_fase3_inicial;
        pos_x_fase3 = pos_x_fase3_inicial;
        contador_movimentos = 0;
        tem_chave3 = 0;
        espinhos_gerados = 0;

        monstro_fase3_1.y = 20;
        monstro_fase3_1.x = 20;
        monstro_fase3_2.y = 25;
        monstro_fase3_2.x = 25;

        for (i = 0; i < GRID_SIZE_FASE3; i++) {
            for (j = 0; j < GRID_SIZE_FASE3; j++) {
                if (i == 0 || j == 0 || i == GRID_SIZE_FASE3 - 1 || j == GRID_SIZE_FASE3 - 1) {
                    mapa_fase3[i][j] = '#';
                } else {
                    mapa_fase3[i][j] = ' ';
                }
            }
        }

        mapa_fase3[3][3] = '#';
        mapa_fase3[3][4] = '#';
        mapa_fase3[7][2] = '#';
        mapa_fase3[7][3] = '#';
        mapa_fase3[15][5] = '#';
        mapa_fase3[20][25] = '#';
        mapa_fase3[21][25] = '#';
        mapa_fase3[25][15] = '#';

        mapa_fase3[tele_entrada_y][tele_entrada_x] = '>';
        mapa_fase3[tele_saida_y][tele_saida_x] = '<';
        mapa_fase3[chave3_y][chave3_x] = '@';
        mapa_fase3[botao3_y][botao3_x] = 'O';
        mapa_fase3[bloqueio3_y][bloqueio3_x] = tem_chave3 ? '=' : 'D';

        mapa_fase3[GRID_SIZE_FASE3 - 2][GRID_SIZE_FASE3 - 1] = '#';
        mapa_fase3[GRID_SIZE_FASE3 - 1][GRID_SIZE_FASE3 - 2] = '#';
        mapa_fase3[GRID_SIZE_FASE3 - 3][GRID_SIZE_FASE3 - 2] = '#';
        mapa_fase3[bloqueio3_y - 1][bloqueio3_x] = '#';
        mapa_fase3[bloqueio3_y + 1][bloqueio3_x] = '#';
        mapa_fase3[bloqueio3_y - 1][bloqueio3_x - 1] = '#';
        mapa_fase3[bloqueio3_y + 1][bloqueio3_x - 1] = '#';

        while (1) {
            system("cls");
            mapa_fase3[monstro_fase3_1.y][monstro_fase3_1.x] = simbolo_monstro1;
            mapa_fase3[monstro_fase3_2.y][monstro_fase3_2.x] = simbolo_monstro2;
            mapa_fase3[pos_y_fase3][pos_x_fase3] = heroi;

            desenhaMapaFase3(mapa_fase3);

            printf("\nVoce esta na Fase 3! Vidas restantes: %d\n", vidas_restantes);
            printf("Cuidado com '#' (espinhos), 'X' (monstro nivel 1), 'V' (monstro nivel 2)!\n");
            printf("Interaja com '@' (chave) ou 'O' (botao) usando 'i'. Use '>' para teletransportar. Alcance a porta aberta para vencer.\n");
            printf("Pressione ESC para retornar.\n");

            tecla = getch();

            if (tecla == 27) {
                system("cls");
                return 0;
            }

            if (pos_x_fase3 == chave3_x && pos_y_fase3 == chave3_y && tecla == 'i' && !tem_chave3) {
                tem_chave3 = 1;
                mapa_fase3[chave3_y][chave3_x] = ' ';
                mapa_fase3[bloqueio3_y][bloqueio3_x] = '=';
                system("cls");
                printf("Chave coletada! Porta aberta!\n");
                Sleep(1000);
                system("cls");
                continue;
            }

            if (pos_x_fase3 == botao3_x && pos_y_fase3 == botao3_y && tecla == 'i' && !espinhos_gerados) {
                espinhos_gerados = 1;
                mapa_fase3[botao3_y][botao3_x] = ' ';
                mapa_fase3[12][12] = '#';
                mapa_fase3[12][13] = '#';
                mapa_fase3[13][12] = '#';
                mapa_fase3[13][13] = '#';
                system("cls");
                printf("Botao ativado! Novos espinhos apareceram!\n");
                Sleep(1000);
                system("cls");
                continue;
            }

            int proximo_y = pos_y_fase3;
            int proximo_x = pos_x_fase3;

            if (tecla == 'w') proximo_y--;
            if (tecla == 'a') proximo_x--;
            if (tecla == 's') proximo_y++;
            if (tecla == 'd') proximo_x++;

            if (proximo_y >= 0 && proximo_y < GRID_SIZE_FASE3 &&
                proximo_x >= 0 && proximo_x < GRID_SIZE_FASE3) {
                char celula_alvo = mapa_fase3[proximo_y][proximo_x];
                if (celula_alvo == 'D') {
                } else if (celula_alvo == '=') {
                    system("cls");
                    printf("Parabens! Voce completou a Fase 3!\n");
                    Sleep(2000);
                    printf("Parabens! Voce terminou o jogo!\n");
                    Sleep(2000);
                    system("cls");
                    return 0;
                } else if (celula_alvo == '#' || celula_alvo == simbolo_monstro1 || celula_alvo == simbolo_monstro2) {
                    telaDeMorte();
                    break;
                } else if (celula_alvo == '>') {
                    mapa_fase3[pos_y_fase3][pos_x_fase3] = 
                        (mapa_fase3[pos_y_fase3][pos_x_fase3] == '>') ? '>' : 
                        (mapa_fase3[pos_y_fase3][pos_x_fase3] == '<') ? '<' : 
                        (pos_x_fase3 == chave3_x && pos_y_fase3 == chave3_y && !tem_chave3) ? '@' : 
                        (pos_x_fase3 == botao3_x && pos_y_fase3 == botao3_y && !espinhos_gerados) ? 'O' : ' ';
                    pos_y_fase3 = tele_saida_y;
                    pos_x_fase3 = tele_saida_x;
                } else {
                    mapa_fase3[pos_y_fase3][pos_x_fase3] = 
                        (mapa_fase3[pos_y_fase3][pos_x_fase3] == '>') ? '>' : 
                        (mapa_fase3[pos_y_fase3][pos_x_fase3] == '<') ? '<' : 
                        (pos_x_fase3 == chave3_x && pos_y_fase3 == chave3_y && !tem_chave3) ? '@' : 
                        (pos_x_fase3 == botao3_x && pos_y_fase3 == botao3_y && !espinhos_gerados) ? 'O' : ' ';
                    pos_y_fase3 = proximo_y;
                    pos_x_fase3 = proximo_x;
                }
            }

            if (tecla == 'w' || tecla == 'a' || tecla == 's' || tecla == 'd') {
                contador_movimentos++;
            }

            mapa_fase3[monstro_fase3_1.y][monstro_fase3_1.x] = ' ';
            moverNPC(&monstro_fase3_1, (char *)mapa_fase3, GRID_SIZE_FASE3, '#', -1, -1);

            if (contador_movimentos >= 2) {
                mapa_fase3[monstro_fase3_2.y][monstro_fase3_2.x] = ' ';
                moverNPC(&monstro_fase3_2, (char *)mapa_fase3, GRID_SIZE_FASE3, '#', pos_y_fase3, pos_x_fase3);
                contador_movimentos = 0;
            }

            if ((monstro_fase3_1.y == pos_y_fase3 && monstro_fase3_1.x == pos_x_fase3) ||
                (monstro_fase3_2.y == pos_y_fase3 && monstro_fase3_2.x == pos_x_fase3)) {
                telaDeMorte();
                break;
            }
        }
    }

    system("cls");
    printf("Haha, voce foi derrotado! Tente ser menos atrapalhado da proxima vez!\n");
    Sleep(2000);
    system("cls");
    return 0;
}

int entraNaFase2() {
    char mapa_fase2[GRID_SIZE_FASE2][GRID_SIZE_FASE2];
    char heroi = '&';
    int pos_y_fase2_inicial = 1;
    int pos_x_fase2_inicial = 1;
    int pos_y_fase2;
    int pos_x_fase2;
    int i, j;
    char tecla;
    int vidas_restantes = 3;

    NPC monstro_fase2;
    char simbolo_monstro = 'X';

    int chave2_y = 5;
    int chave2_x = 5;
    int bloqueio2_y = GRID_SIZE_FASE2 - 2;
    int bloqueio2_x = GRID_SIZE_FASE2 - 3;
    int botao2_y = 5;
    int botao2_x = 10;
    int passagem2_y = GRID_SIZE_FASE2 - 2;
    int passagem2_x = GRID_SIZE_FASE2 - 5;
    int tem_chave2;
    int passagem_aberta;

    for (vidas_restantes = 3; vidas_restantes > 0; vidas_restantes--) {
        pos_y_fase2 = pos_y_fase2_inicial;
        pos_x_fase2 = pos_x_fase2_inicial;
        tem_chave2 = 0;
        passagem_aberta = 0;

        monstro_fase2.y = GRID_SIZE_FASE2 / 2;
        monstro_fase2.x = GRID_SIZE_FASE2 / 2;

        for (i = 0; i < GRID_SIZE_FASE2; i++) {
            for (j = 0; j < GRID_SIZE_FASE2; j++) {
                if (i == 0 || j == 0 || i == GRID_SIZE_FASE2 - 1 || j == GRID_SIZE_FASE2 - 1) {
                    mapa_fase2[i][j] = '#';
                } else {
                    mapa_fase2[i][j] = ' ';
                }
            }
        }

        mapa_fase2[3][3] = '#';
        mapa_fase2[3][4] = '#';
        mapa_fase2[7][2] = '#';
        mapa_fase2[7][3] = '#';
        mapa_fase2[10][10] = '#';
        mapa_fase2[10][11] = '#';
        mapa_fase2[15][5] = '#';

        mapa_fase2[chave2_y][chave2_x] = '@';
        mapa_fase2[botao2_y][botao2_x] = 'O';
        mapa_fase2[bloqueio2_y][bloqueio2_x] = tem_chave2 ? '=' : 'D';
        mapa_fase2[passagem2_y][passagem2_x] = passagem_aberta ? ' ' : '#';

        mapa_fase2[GRID_SIZE_FASE2 - 2][GRID_SIZE_FASE2 - 1] = '#';
        mapa_fase2[GRID_SIZE_FASE2 - 1][GRID_SIZE_FASE2 - 2] = '#';
        mapa_fase2[GRID_SIZE_FASE2 - 3][GRID_SIZE_FASE2 - 2] = '#';
        mapa_fase2[bloqueio2_y - 1][bloqueio2_x] = '#';
        mapa_fase2[bloqueio2_y + 1][bloqueio2_x] = '#';
        mapa_fase2[bloqueio2_y - 1][bloqueio2_x - 1] = '#';
        mapa_fase2[bloqueio2_y + 1][bloqueio2_x - 1] = '#';

        while (1) {
            system("cls");
            mapa_fase2[monstro_fase2.y][monstro_fase2.x] = simbolo_monstro;
            mapa_fase2[pos_y_fase2][pos_x_fase2] = heroi;

            desenhaMapaFase2(mapa_fase2);

            printf("\nVoce esta na Fase 2! Vidas restantes: %d\n", vidas_restantes);
            printf("Cuidado com '#' (espinhos) e 'X' (monstro nivel 1)!\n");
            printf("Interaja com '@' (chave) ou 'O' (botao) usando 'i'. Alcance a porta aberta para vencer.\n");
            printf("Pressione ESC para retornar.\n");

            tecla = getch();

            if (tecla == 27) {
                system("cls");
                return 0;
            }

            if (pos_x_fase2 == chave2_x && pos_y_fase2 == chave2_y && tecla == 'i' && !tem_chave2) {
                tem_chave2 = 1;
                mapa_fase2[chave2_y][chave2_x] = ' ';
                mapa_fase2[bloqueio2_y][bloqueio2_x] = '=';
                system("cls");
                printf("Chave coletada! Porta aberta!\n");
                Sleep(1000);
                system("cls");
                continue;
            }

            if (pos_x_fase2 == botao2_x && pos_y_fase2 == botao2_y && tecla == 'i' && !passagem_aberta) {
                passagem_aberta = 1;
                mapa_fase2[botao2_y][botao2_x] = ' ';
                mapa_fase2[passagem2_y][passagem2_x] = ' ';
                system("cls");
                printf("Botao ativado! Passagem secreta aberta!\n");
                Sleep(1000);
                system("cls");
                continue;
            }

            int proximo_y = pos_y_fase2;
            int proximo_x = pos_x_fase2;

            if (tecla == 'w') proximo_y--;
            if (tecla == 'a') proximo_x--;
            if (tecla == 's') proximo_y++;
            if (tecla == 'd') proximo_x++;

            if (proximo_y >= 0 && proximo_y < GRID_SIZE_FASE2 &&
                proximo_x >= 0 && proximo_x < GRID_SIZE_FASE2) {
                char celula_alvo = mapa_fase2[proximo_y][proximo_x];
                if (celula_alvo == 'D') {
                } else if (celula_alvo == '=') {
                    system("cls");
                    printf("Parabens! Voce completou a Fase 2! Avancando para a Fase 3...\n");
                    Sleep(2000);
                    system("cls");
                    int resultado_fase3 = entraNaFase3();
                    return resultado_fase3;
                } else if (celula_alvo == '#' || celula_alvo == simbolo_monstro) {
                    telaDeMorte();
                    break;
                } else {
                    mapa_fase2[pos_y_fase2][pos_x_fase2] = 
                        (pos_x_fase2 == chave2_x && pos_y_fase2 == chave2_y && !tem_chave2) ? '@' : 
                        (pos_x_fase2 == botao2_x && pos_y_fase2 == botao2_y && !passagem_aberta) ? 'O' : ' ';
                    pos_y_fase2 = proximo_y;
                    pos_x_fase2 = proximo_x;
                }
            }

            mapa_fase2[monstro_fase2.y][monstro_fase2.x] = ' ';
            moverNPC(&monstro_fase2, (char *)mapa_fase2, GRID_SIZE_FASE2, '#', -1, -1);

            if (monstro_fase2.y == pos_y_fase2 && monstro_fase2.x == pos_x_fase2) {
                telaDeMorte();
                break;
            }
        }
    }

    system("cls");
    printf("Haha, voce foi derrotado! Tente ser menos atrapalhado da proxima vez!\n");
    Sleep(2000);
    system("cls");
    return 0;
}

int main() {
    srand(time(NULL));

    int opcao = 0;
    while (opcao != 3) {
        printf("---DUNGEON CRAWLER---\n");
        printf("1 - Jogar\n");
        printf("2 - Creditos\n");
        printf("3 - Sair\n");
        if (scanf("%i", &opcao) != 1) {
            while (getchar() != '\n');
            system("cls");
            continue;
        }
        if (opcao == 1) {
            system("cls");
            char tecla;
            int tam_x = GRID_SIZE_MAIN;
            int tam_y = GRID_SIZE_MAIN;
            char mapa[GRID_SIZE_MAIN][GRID_SIZE_MAIN];
            char heroi = '&';
            int i, j;
            int pos_y = 1;
            int pos_x = 1;
            int npc_x = 5;
            int npc_y = 5;
            int porta_y = 3;
            int porta_x = 9;
            int jogo_completo = 0;

            for (i = 0; i < tam_x; i++) {
                for (j = 0; j < tam_y; j++) {
                    if (i == 0 || j == 0 || i == tam_x - 1 || j == tam_y - 1) {
                        mapa[i][j] = '*';
                    } else {
                        mapa[i][j] = ' ';
                    }
                }
            }
            mapa[porta_y][porta_x] = ' ';
            mapa[pos_y][pos_x] = heroi;
            mapa[npc_y][npc_x] = 'P';

            while (!jogo_completo) {
                desenhaMapa(mapa);

                tecla = getch();

                if (tecla == 27) {
                    system("cls");
                    break;
                }

                if (pos_x == npc_x && pos_y == npc_y && tecla == 'i') {
                    system("cls");
                    printf("Bem-vindo ao tutorial!\n");
                    printf("D: representa a porta fechada\n");
                    printf("@: representa a chave para abrir a porta\n");
                    printf("=: representa a porta aberta\n");
                    printf("#: representa os espinhos\n");
                    printf(">: representa um teletransporte\n");
                    printf("X: representa um monstro nivel 1\n");
                    printf("V: representa um monstro nivel 2\n");
                    printf("O: representa um botao\n");
                    Sleep(2500);
                    system("cls");
                    continue;
                }

                if (pos_x == porta_x && pos_y == porta_y && tecla == 'i') {
                    system("cls");
                    printf("Voce entrou na Fase 1!\n");
                    Sleep(1500);
                    system("cls");

                    char mapa_fase2[GRID_SIZE_MAIN][GRID_SIZE_MAIN];
                    int chave_x = 7;
                    int chave_y = 1;
                    int porta_fase2_x = 9;
                    int porta_fase2_y = 6;
                    int tem_chave = 0;
                    int pos_y = 2;
                    int pos_x = 1;

                    for (i = 0; i < tam_x; i++) {
                        for (j = 0; j < tam_y; j++) {
                            if (i == 0 || j == 0 || i == tam_x - 1 || j == tam_y - 1) {
                                mapa_fase2[i][j] = '*';
                            } else {
                                mapa_fase2[i][j] = ' ';
                            }
                        }
                    }
                    mapa_fase2[porta_fase2_y][porta_fase2_x] = 'D';
                    mapa_fase2[chave_y][chave_x] = '@';
                    mapa_fase2[porta_y][porta_x] = '*';
                    mapa_fase2[pos_y][pos_x] = heroi;

                    while (1) {
                        desenhaMapa(mapa_fase2);

                        tecla = getch();

                        if (tecla == 27) {
                            system("cls");
                            break;
                        }

                        if (pos_x == chave_x && pos_y == chave_y && tecla == 'i' && !tem_chave) {
                            tem_chave = 1;
                            mapa_fase2[chave_y][chave_x] = ' ';
                            mapa_fase2[porta_fase2_y][porta_fase2_x] = '=';
                            system("cls");
                            printf("Chave coletada! Porta aberta!\n");
                            Sleep(1000);
                            system("cls");
                            continue;
                        }

                        int proximo_y = pos_y;
                        int proximo_x = pos_x;

                        if (tecla == 'w') proximo_y--;
                        if (tecla == 'a') proximo_x--;
                        if (tecla == 's') proximo_y++;
                        if (tecla == 'd') proximo_x++;

                        if (proximo_y >= 0 && proximo_y < tam_y && proximo_x >= 0 && proximo_x < tam_x) {
                            char celula_alvo = mapa_fase2[proximo_y][proximo_x];
                            if (celula_alvo == 'D') {
                            } else if (celula_alvo == '=') {
                                system("cls");
                                printf("Voce entrou na Fase 2!\n");
                                Sleep(1500);
                                system("cls");
                                int resultado_fase2 = entraNaFase2();
                                if (resultado_fase2 == 0) {
                                    jogo_completo = 1;
                                    system("cls");
                                    break;
                                }
                            } else if (celula_alvo != '*') {
                                mapa_fase2[pos_y][pos_x] = 
                                    (pos_x == chave_x && pos_y == chave_y && !tem_chave) ? '@' : ' ';
                                pos_y = proximo_y;
                                pos_x = proximo_x;
                            }
                        }

                        mapa_fase2[pos_y][pos_x] = heroi;
                        system("cls");
                    }
                    if (jogo_completo) break;
                }

                int proximo_y = pos_y;
                int proximo_x = pos_x;

                if (tecla == 'w') proximo_y--;
                if (tecla == 'a') proximo_x--;
                if (tecla == 's') proximo_y++;
                if (tecla == 'd') proximo_x++;

                if (proximo_y >= 0 && proximo_y < tam_y && proximo_x >= 0 && proximo_x < tam_x &&
                    mapa[proximo_y][proximo_x] != '*') {
                    mapa[pos_y][pos_x] = (pos_x == npc_x && pos_y == npc_y) ? 'P' : 
                                         (pos_x == porta_x && pos_y == porta_y) ? ' ' : ' ';
                    pos_y = proximo_y;
                    pos_x = proximo_x;
                }

                mapa[pos_y][pos_x] = heroi;
                system("cls");
            }
        }

        if (opcao == 2) {
            system("cls");
            printf("Desenvolvido por:\n");
            printf("Enzo Martins\n");
            printf("Hermes Tupinamba\n");
            printf("Carlos Alonso\n");
            Sleep(2500);
            system("cls");
        }

        if (opcao == 3) {
            system("cls");
            printf("Obrigado por jogar\n");
        }
    }
    return 0;
}