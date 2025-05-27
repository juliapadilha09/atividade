#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estrutura do jogador
typedef struct {
    int energia;
    int defesa;
    char nome[50];
} Jogador;

// Funções do jogo
void inicializarJogadores(Jogador *jogador1, Jogador *jogador2);
void exibirStatus(Jogador *jogador1, Jogador *jogador2, int turno, int vitoriasJogador1, int vitoriasJogador2, char* vilaoNome);
int escolherHerói();
int escolherAcaoJogador();
void realizarAcaoJogador(int escolha, Jogador *jogador2, int heroiEscolhido);
int escolherAcaoComputador();
void realizarAcaoComputador(int escolha, Jogador *jogador1, int vilaoEscolhido);
int verificarVencedor(Jogador jogador1, Jogador jogador2);

// Constantes do jogo
#define ENERGIA_INICIAL 100
#define ATAQUE_SUCESSO_CHANCE 70
#define DEFESA_BLOQUEIO_CHANCE 50

// Definição de heróis e vilões
#define ATAQUE_DANO_HOMEM_ARANHA 15
#define ATAQUE_DANO_CAPITAO 20
#define ATAQUE_DANO_HOMEM_DE_FERRO 25
#define ATAQUE_DANO_VIÚVA_NEGRA 18
#define ATAQUE_DANO_MYSTERIO 18
#define ATAQUE_DANO_CAVEIRA_VERMELHA 22
#define ATAQUE_DANO_CHICOTE_NEGRO 24
#define ATAQUE_DANO_TREINADOR 20

int main() {
    srand(time(NULL)); // Inicializa a semente aleatória

    Jogador jogador1, jogador2;
    inicializarJogadores(&jogador1, &jogador2);

    int turno = 1;
    int vencedor = 0;
    int vitoriasJogador1 = 0, vitoriasJogador2 = 0;

    // Escolha do herói
    int heroiEscolhido = escolherHerói();
    int vilaoEscolhido = (heroiEscolhido == 1) ? 1 : (heroiEscolhido == 2) ? 2 : (heroiEscolhido == 3) ? 3 : 4;
    char* vilaoNome;
    
    // Definir o nome do vilão baseado na escolha do herói
    switch (vilaoEscolhido) {
        case 1: vilaoNome = "Mysterio"; break;
        case 2: vilaoNome = "Caveira Vermelha"; break;
        case 3: vilaoNome = "Chicote Negro"; break;
        case 4: vilaoNome = "Treinador"; break;
        default: vilaoNome = "Desconhecido"; break;
    }

    printf("\n=== Bem-vindo ao Jogo! ===\n");

    while (vencedor == 0) {
        exibirStatus(&jogador1, &jogador2, turno, vitoriasJogador1, vitoriasJogador2, vilaoNome);

        // Jogador humano (Herói escolhido)
        int acaoJogador = escolherAcaoJogador();
        realizarAcaoJogador(acaoJogador, &jogador2, heroiEscolhido);

        // Verifica se o jogador venceu
        vencedor = verificarVencedor(jogador1, jogador2);
        if (vencedor != 0) {
            if (vencedor == 1) {
                vitoriasJogador1++;
            }
            break;
        }

        // Computador (Vilão)
        int acaoComputador = escolherAcaoComputador();
        realizarAcaoComputador(acaoComputador, &jogador1, vilaoEscolhido);

        // Verifica se o computador venceu
        vencedor = verificarVencedor(jogador1, jogador2);
        if (vencedor != 0) {
            if (vencedor == 2) {
                vitoriasJogador2++;
            }
            break;
        }
        turno++;
    }

    // Resultado final
    if (vencedor == 1) {
        printf("\nParabéns! Você derrotou o vilão!\n");
    } else {
        printf("\nVocê foi derrotado! O vilão venceu.\n");
    }

    // Exibir o placar final
    printf("\nPlacar Final: Herói: %d | Vilão: %d\n", vitoriasJogador1, vitoriasJogador2);

    return 0;
}

void inicializarJogadores(Jogador *jogador1, Jogador *jogador2) {
    jogador1->energia = ENERGIA_INICIAL;
    jogador1->defesa = 0;

    jogador2->energia = ENERGIA_INICIAL;
    jogador2->defesa = 0;
}

void exibirStatus(Jogador *jogador1, Jogador *jogador2, int turno, int vitoriasJogador1, int vitoriasJogador2, char* vilaoNome) {
    printf("\n----- Turno %d -----\n", turno);
    printf("Energia do Herói: %d | Defesa: %d\n", jogador1->energia, jogador1->defesa);
    printf("Energia do Vilão (%s): %d | Defesa: %d\n", vilaoNome, jogador2->energia, jogador2->defesa);
    printf("Placar: Herói: %d | Vilão: %d\n", vitoriasJogador1, vitoriasJogador2);
}

int escolherHerói() {
    int escolha;
    printf("\nEscolha o seu herói: \n");
    printf("1. Homem-Aranha\n");
    printf("2. Capitão América\n");
    printf("3. Homem de Ferro\n");
    printf("4. Viúva Negra\n");
    printf("Digite sua escolha: ");
    scanf("%d", &escolha);
    return escolha;
}

int escolherAcaoJogador() {
    int escolha;
    printf("\nEscolha sua ação: \n");
    printf("1. Atacar\n");
    printf("2. Defender\n");
    printf("Digite sua escolha: ");
    scanf("%d", &escolha);
    return escolha;
}

void realizarAcaoJogador(int escolha, Jogador *jogador2, int heroiEscolhido) {
    int dano;
    if (heroiEscolhido == 1) {
        // Homem-Aranha
        dano = ATAQUE_DANO_HOMEM_ARANHA;
    } else if (heroiEscolhido == 2) {
        // Capitão América
        dano = ATAQUE_DANO_CAPITAO;
    } else if (heroiEscolhido == 3) {
        // Homem de Ferro
        dano = ATAQUE_DANO_HOMEM_DE_FERRO;
    } else {
        // Viúva Negra
        dano = ATAQUE_DANO_VIÚVA_NEGRA;
    }

    if (escolha == 1) {
        int chance = rand() % 100;
        if (chance < ATAQUE_SUCESSO_CHANCE) {
            jogador2->energia -= dano;
            if (jogador2->energia < 0) jogador2->energia = 0;
            printf("Ataque bem-sucedido! O vilão perdeu %d de energia.\n", dano);
        } else {
            printf("Seu ataque falhou! O vilão bloqueou o ataque.\n");
        }
    } else if (escolha == 2) {
        jogador2->defesa = 1;
        printf("Você se preparou para defender!\n");
    } else {
        printf("Ação inválida! Perdeu a vez.\n");
    }
}

int escolherAcaoComputador() {
    return (rand() % 2) + 1; // 1 ou 2
}

void realizarAcaoComputador(int escolha, Jogador *jogador1, int vilaoEscolhido) {
    int dano;
    if (vilaoEscolhido == 1) {
        // Mysterio
        dano = ATAQUE_DANO_MYSTERIO;
    } else if (vilaoEscolhido == 2) {
        // Caveira Vermelha
        dano = ATAQUE_DANO_CAVEIRA_VERMELHA;
    } else if (vilaoEscolhido == 3) {
        // Chicote Negro
        dano = ATAQUE_DANO_CHICOTE_NEGRO;
    } else {
        // Treinador
        dano = ATAQUE_DANO_TREINADOR;
    }

    if (escolha == 1) {
        printf("O vilão atacou!\n");
        int chance = rand() % 100;
        if (chance < ATAQUE_SUCESSO_CHANCE) {
            jogador1->energia -= dano;
            if (jogador1->energia < 0) jogador1->energia = 0;
            printf("Ataque bem-sucedido! Você perdeu %d de energia.\n", dano);
        } else {
            printf("O ataque do vilão falhou!\n");
        }
    } else if (escolha == 2) {
        jogador1->defesa = 1;
        printf("O vilão se preparou para defender!\n");
    }
}

int verificarVencedor(Jogador jogador1, Jogador jogador2) {
    if (jogador2.energia <= 0)
        return 1; // Herói vence
    else if (jogador1.energia <= 0)
        return 2; // Vilão vence
    else
        return 0; // Continua o jogo
}

