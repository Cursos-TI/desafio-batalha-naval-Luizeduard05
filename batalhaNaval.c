#include <stdio.h>

#define TAM 10
#define NAVIO 3
#define AGUA 0
#define HABILIDADE 5
#define TAM_HABILIDADE 5  

void imprimirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("   ");
    for (int i = 0; i < TAM; i++) printf("%d ", i);
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%2d: ", i);
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == AGUA) printf(". ");
            else if (tabuleiro[i][j] == NAVIO) printf("N ");
            else if (tabuleiro[i][j] == HABILIDADE) printf("* ");
            else printf("? ");
        }
        printf("\n");
    }
}

void aplicarHabilidade(int tabuleiro[TAM][TAM], int matriz[TAM_HABILIDADE][TAM_HABILIDADE], int origem_l, int origem_c) {
    int offset = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (matriz[i][j] == 1) {
                int l = origem_l - offset + i;
                int c = origem_c - offset + j;
                if (l >= 0 && l < TAM && c >= 0 && c < TAM && tabuleiro[l][c] == AGUA) {
                    tabuleiro[l][c] = HABILIDADE;
                }
            }
        }
    }
}

void criarCone(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            matriz[i][j] = (j >= TAM_HABILIDADE / 2 - i && j <= TAM_HABILIDADE / 2 + i) ? 1 : 0;
        }
    }
}

void criarCruz(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            matriz[i][j] = (i == TAM_HABILIDADE / 2 || j == TAM_HABILIDADE / 2) ? 1 : 0;
        }
    }
}

void criarOctaedro(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            matriz[i][j] = (abs(i - centro) + abs(j - centro) <= centro) ? 1 : 0;
        }
    }
}

void posicionarNavioHorizontal(int tabuleiro[TAM][TAM], int l, int c) {
    for (int i = 0; i < 3 && c + i < TAM; i++) {
        tabuleiro[l][c + i] = NAVIO;
    }
}

void posicionarNavioDiagonal(int tabuleiro[TAM][TAM], int l, int c) {
    for (int i = 0; i < 3 && l + i < TAM && c + i < TAM; i++) {
        tabuleiro[l + i][c + i] = NAVIO;
    }
}

int main() {
    int tabuleiro[TAM][TAM] = {0};

    posicionarNavioHorizontal(tabuleiro, 2, 4); 
    posicionarNavioDiagonal(tabuleiro, 5, 5);   

    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    aplicarHabilidade(tabuleiro, cone, 1, 1);        
    aplicarHabilidade(tabuleiro, cruz, 4, 2);        
    aplicarHabilidade(tabuleiro, octaedro, 7, 7);    

    imprimirTabuleiro(tabuleiro);

    return 0;
}
