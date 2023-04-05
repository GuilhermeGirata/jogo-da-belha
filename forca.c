#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


typedef struct Jogador { //definição da struct
	char nome[20]; //definição membros da struct
	char simbolo;
} Jogador; //apelido da struct

typedef struct Velha { //definição da struct
	int partida; //definição membros da struct
	char jogo_velha[3][3];
	char resultado;
} Partida; //apelido da struct


Partida partida = { 0, { '7', '8', '9', '4', '5', '6', '1', '2', '3' } }; //escolhas
int nivel;


int main() {
    setlocale(LC_ALL, "Portuguese");
	int fim = 1;

	while (fim)
		fim = inicia_jogo();
    menu_pos_partida();
	printf("\nOBRIGADO POR JOGAR!\n");
	return 0;
}


//-------------------------jogada_usuario---------------------------------

/* preenche a posição informada pelos parâmetros com 'X' ou 'O' passados
   através de 'jog', retornando:
        0 – se a jogada é válida
        1 – se a posição informada é inválida
        2 – se a posição informada já está preenchida                   */

int jogada_usuario(int lin, int col, char jog) {
	if (partida.jogo_velha[lin][col] == 'X' || partida.jogo_velha[lin][col] == 'O')
		return 1;

	int jog_int = jog - '0';

	if (jog_int < 1 || jog_int > 9)
		return 2;
	return 0;
}

//-------------------------jogada_computador---------------------------------

/* realiza a jogada do computador, definindo 'nivel' para a dificuldade da jogada
   e se o computador será 'X' ou 'O' de acordo com o parâmetro 'jog' definido
   pelo jogador                                                                   */

void jogada_computador(char jog, int nivel) {
	char jog2;

	if (jog == 'X') {
		jog = 'X';
		jog2 = 'O';
	} else {
		jog = 'O';
		jog2 = 'X';
	}
	switch (nivel) {
	case 1:
		facil(jog, jog2);
		break;
	case 2:
		medio(jog, jog2);
		break;
	case 3:
		dificil(jog, jog2);
		break;
	}
}

//-------------------------menu---------------------------------

/* retorna 1 se o usuário quiser jogar contra o computador,
   escolhendo sua dificuldade, ou 2 quando quiser jogar
   contra outro usuário                                    */

int menu() {
	int opcao;

	printf("-------------------------------------------------------\n");
	printf("----------           JOGO DA VELHA           ----------\n");
	printf("-------------------------------------------------------\n\n");
	printf("O jogo da velha é um jogo de estratégia bem simples de ser jogado.\n");
    printf("Nele é necessário colocar três símbolos iguais em sequência para ganhar.\n\n");
	printf("1 -> JOGAR COM UM AMIGO\n");
	printf("2 -> JOGAR COM A MÁQUINA\n");
	while (1) {
		scanf("%d", &opcao);
		if (opcao == 1) {
			return 1;
			break;
		} else if (opcao == 2) {
			printf(
					"--------------------------------------------------------\n");
			printf("                  ESCOLHA A DIFICULDADE\n");
			printf(
					"--------------------------------------------------------\n");
			printf("1 -> FÁCIL\n");
			printf("2 -> MÉDIO\n");
			printf("3 -> DIFÍCIL\n");
			scanf("%d", &nivel);
			return 2;
			break;
		}
	}
}

//-------------------------escolha_simb---------------------------------

/* define quem é o jogador 'X' e o 'O' de acordo com a entrada do jogador */
//usar x e o minusculos para escolher!
void escolha_simb(char *jog1, char *jog2) {
	printf("\nINSIRA QUAL SÍMBOLO O JOGADOR 1 SERÁ (X ou O)\n");
	do {
		scanf("%c", &*jog1);
		if (*jog1 == 'x') {
			*jog1 = 'X';
			*jog2 = 'O';
			break;
		} else if (*jog1 == 'o') {
			*jog1 = 'O';
			*jog2 = 'X';
			break;
		}
	} while (1);
}

//-------------------------inicializa_velha---------------------------------

/* inicializa a matriz vazia */

void inicializa_velha(int num_partida, char jogo_velha[3][3]) {
	printf("\nPartida Numero %d\n\n", num_partida);
	int x, y;
	y = 0;
	for (x = 0; x < 3; x++) {
		if (x == 0 || x == 2)
			printf("	%c |%c |%c \n", jogo_velha[x][y], jogo_velha[x][y + 1],
					jogo_velha[x][y + 2]);
		else {
			printf("	--|--|--\n");
			printf("	%c |%c |%c \n", jogo_velha[x][y], jogo_velha[x][y + 1],
					jogo_velha[x][y + 2]);
			printf("	--|--|--\n");
		}
	}
	printf("\n");
}

//-------------------------verifica_ganhador---------------------------------

/* retorna 1 se o jogador ganhou e 0 caso contrário */

int verifica_ganhador(char jog) {
	int x, preenchidos;
	preenchidos = 0;

	for (x = 0; x < 3; x++)
		if (partida.jogo_velha[x][0] == partida.jogo_velha[x][1]
				&& partida.jogo_velha[x][0] == partida.jogo_velha[x][2])
			return 0;
	for (x = 0; x < 3; x++)
		if (partida.jogo_velha[0][x] == partida.jogo_velha[1][x]
				&& partida.jogo_velha[0][x] == partida.jogo_velha[2][x])
			return 0;
	if (partida.jogo_velha[0][0] == partida.jogo_velha[1][1]
			&& partida.jogo_velha[0][0] == partida.jogo_velha[2][2])
		return 0;
	if (partida.jogo_velha[2][0] == partida.jogo_velha[1][1]
			&& partida.jogo_velha[2][0] == partida.jogo_velha[0][2])
		return 0;
	int y;
	for (x = 0; x < 3; x++)
		for (y = 0; y < 3; y++)
			if (partida.jogo_velha[x][y] == 'X' || partida.jogo_velha[x][y] == 'O')
				++preenchidos;
	if (preenchidos == 9)
		return 2;
	else
		return 1;
}

//-------------------------jogadas---------------------------------


int jog_execoes(char jog, char jog2) {
	if (partida.jogo_velha[0][0] == partida.jogo_velha[2][2]
			&& partida.jogo_velha[0][1] != jog2
			&& partida.jogo_velha[0][1] != jog) {
		partida.jogo_velha[0][1] = jog;
		return 0;
	}
	if (partida.jogo_velha[2][0] == partida.jogo_velha[0][2]
			&& partida.jogo_velha[2][1] != jog2
			&& partida.jogo_velha[2][1] != jog) {
		partida.jogo_velha[2][1] = jog;
		return 0;
	}
	if (partida.jogo_velha[1][1] == partida.jogo_velha[2][2]
			&& partida.jogo_velha[0][2] != jog2
			&& partida.jogo_velha[0][2] != jog) {
		partida.jogo_velha[0][2] = jog;
		return 0;
	}
	if (partida.jogo_velha[2][1] == partida.jogo_velha[1][2]
			&& partida.jogo_velha[2][2] != jog2
			&& partida.jogo_velha[2][2] != jog) {
		partida.jogo_velha[2][2] = jog;
		return 0;
	}
	if (partida.jogo_velha[0][2] == partida.jogo_velha[1][2]
			&& partida.jogo_velha[2][2] != jog2
			&& partida.jogo_velha[2][2] != jog) {
		partida.jogo_velha[2][2] = jog;
		return 0;
	}
	if (partida.jogo_velha[0][2] == partida.jogo_velha[2][1]
			&& partida.jogo_velha[2][2] != jog2
			&& partida.jogo_velha[2][2] != jog) {
		partida.jogo_velha[2][2] = jog;
		return 0;
	}
	if (partida.jogo_velha[0][0] == partida.jogo_velha[2][1]
			&& partida.jogo_velha[2][0] != jog2
			&& partida.jogo_velha[2][0] != jog) {
		partida.jogo_velha[2][0] = jog;
		return 0;
	}
	return 1;
}

int qualquer_posicao(char jog, char jog2) {
	int x, y;

	for (x = 0; x < 3; x++)
		for (y = 0; y < 3; y++)
			if (partida.jogo_velha[x][y] != jog
					&& partida.jogo_velha[x][y] != jog2) {
				partida.jogo_velha[x][y] = jog;
				return 0;
			}
	return 1;
}

int jog_linha(char jog, char jog2) {
	int x, y, z, conta;
	char aux;

	for (x = 0; x < 3; x++) {
		conta = 0;
		aux = ' ';
		for (y = 0; y < 3; y++) {
			if (partida.jogo_velha[x][y] != jog2
					&& partida.jogo_velha[x][y] != jog) {
				for (z = 0; z < 3; ++z) {
					if (z != y) {
						if (aux == partida.jogo_velha[x][z])
							++conta;
						aux = partida.jogo_velha[x][z];
					}
					if (conta) {
						partida.jogo_velha[x][y] = jog;
						return 0;
					}
				}
			}
		}
	}
	return 1;
}

int jog_coluna(char jog, char jog2) {
	int x, y, z, conta;
	char aux;

	for (y = 0; y < 3; y++) {
		conta = 0;
		aux = ' ';
		for (x = 0; x < 3; x++) {
			if (partida.jogo_velha[x][y] != jog2
					&& partida.jogo_velha[x][y] != jog) {
				for (z = 0; z < 3; ++z) {
					if (z != x) {
						if (aux == partida.jogo_velha[z][y])
							++conta;
						aux = partida.jogo_velha[z][y];
					}
					if (conta) {
						partida.jogo_velha[x][y] = jog;
						return 0;
					}
				}
			}
		}
	}
	return 1;
}

int jog_diagonal(char jog, char jog2) {
	if (partida.jogo_velha[0][0] == partida.jogo_velha[1][1]
			&& partida.jogo_velha[2][2] != jog2
			&& partida.jogo_velha[2][2] != jog) {
		partida.jogo_velha[2][2] = jog;
		return 0;
	}
	if (partida.jogo_velha[0][2] == partida.jogo_velha[1][1]
			&& partida.jogo_velha[2][0] != jog2
			&& partida.jogo_velha[2][0] != jog) {
		partida.jogo_velha[2][0] = jog;
		return 0;
	}
	if (partida.jogo_velha[2][0] == partida.jogo_velha[1][1]
			&& partida.jogo_velha[0][2] != jog2
			&& partida.jogo_velha[0][2] != jog) {
		partida.jogo_velha[0][2] = jog;
		return 0;
	}
	if (partida.jogo_velha[2][2] == partida.jogo_velha[1][1]
			&& partida.jogo_velha[0][0] != jog2
			&& partida.jogo_velha[0][0] != jog) {
		partida.jogo_velha[0][0] = jog;
		return 0;
	}
	return 1;
}
//---------------------fim jogadas---------------------------------

//---------------------dificuldade---------------------------------

void facil(char jog, char jog2) {
     qualquer_posicao(jog, jog2);
}

void medio(char jog, char jog2) {
	int fim = 1;

	while (fim) {
		fim = jog_linha(jog, jog2);
		if (fim == 0)
			break;
		fim = jog_coluna(jog, jog2);
		if (fim == 0)
			break;
		fim = qualquer_posicao(jog, jog2);
		break;
	}
}

void dificil(char jog, char jog2) {
	int fim = 1;

	while (fim) {//Primeira jogada, se possivel sempre é o meio
		if (partida.jogo_velha[1][1] == '5') {
			partida.jogo_velha[1][1] = jog;
			break;
		}
		fim = jog_linha(jog, jog2);
		if (fim == 0)
			break;
		fim = jog_coluna(jog, jog2);
		if (fim == 0)
			break;
		fim = jog_diagonal(jog, jog2);
		if (fim == 0)
			break;
		fim = jog_execoes(jog, jog2);
		if (fim == 0)
			break;
		fim = qualquer_posicao(jog, jog2);
		break;
	}
}

//---------------------fim dificuldade---------------------------------

//---------------------configuração partida----------------------------

int config(Jogador *jogador1, Jogador *jogador2) {
	int option;

	option = menu();
	printf("\nINSIRA O NOME DO JOGADOR 1\n");
	scanf(" %[^\n]", jogador1->nome);
	if (option != 2) {
		printf("INSIRA O NOME DO JOGADOR 2\n");
		scanf(" %[^\n]", jogador2->nome);
	} else
		strcpy(jogador2->nome, "Computador");
	return option;
}

int inicia_jogo() {
	int conta_turno, x, y, fim, achou, option;
	char temp, turno_jogador, *ptrjog1, *ptrjog2;
	Jogador jogador1, jogador2;
	char *end_arq_partidas =
			"lista_partidas.bin";
	x = y = conta_turno = achou = 0;
	fim = 1;
	ptrjog1 = &jogador1.simbolo;
	ptrjog2 = &jogador2.simbolo;

	++partida.partida;
	if (partida.partida == 1)
		option = config(&jogador1, &jogador2);
	else
		printf("\nNOVA PARTIDA!\n");

	escolha_simb(ptrjog1, ptrjog2);
	turno_jogador = jogador1.simbolo;
	while (fim) {
		inicializa_velha(partida.partida, partida.jogo_velha);
		printf("Rodada do Jogador: %c\n", turno_jogador);
		if (option == 2 && turno_jogador == jogador2.simbolo)
			jogada_computador(jogador2.simbolo, nivel);
		else {
			while (1) {
				scanf(" %c", &temp);
				for (x = 0; x < 3; x++) {
					for (y = 0; y < 3; y++)
						if (temp == partida.jogo_velha[x][y]) {
							achou = 1;
							break;
						}
					if (achou)
						break;
				}
				achou = 0;
				int result;
				result = jogada_usuario(x, y, temp);
				if (result == 1)
					printf("ESPAÇO JÁ PREENCHIDO\n");
				else if (result == 2)
					printf("JOGADA INVÁLIDA\n");
				else {
					partida.jogo_velha[x][y] = turno_jogador;
					break;
				}
			}
		}
		if (conta_turno > 3) {
			fim = verifica_ganhador(turno_jogador);
			if (fim == 2) {
				partida.resultado = 'V';
				break;
			}
			if (fim == 0) {
				partida.resultado = turno_jogador;
				break;
			}
		}
		if (turno_jogador == 'X')
			turno_jogador = 'O';
		else
			turno_jogador = 'X';
		conta_turno++;
	}
	inicializa_velha(partida.partida, partida.jogo_velha);
	if (partida.resultado == 'V')
		printf("DEU VELHA!\n");
	else {
		if (partida.resultado == 'O')
			printf("O GANHOU!!!\n");
		else
			printf("X GANHOU!!!\n");
	}
	registra_jogadores(jogador1, jogador2, option);
	if (registra_partida(end_arq_partidas, partida))
		printf("Partida Salva com Sucesso!\n");
	else
		printf("Erro ao salvar a partida\n");
	reseta_partida();
	while (1) {
		printf("Jogar novamente? (1 - Sim/0 - Nao)\n");
		int jog_n;
		scanf("%d", &jog_n);
		if (jog_n == 1)
			return 1;
		if (jog_n == 0)
			return 0;
	}

}

//------------registro jogadores--------------------

void registra_jogadores(Jogador jogador1, Jogador jogador2, int opcao) {
	FILE *arq_jogadores;
	char *end_arq_jogadores =
			"lista_jogadores.txt";

	arq_jogadores = fopen(end_arq_jogadores, "a");
	if (arq_jogadores != NULL) {
		fprintf(arq_jogadores, "%s;%c;", jogador1.nome, jogador1.simbolo);
		fprintf(arq_jogadores, "%s;%c.\n", jogador2.nome, jogador2.simbolo);
	} else
		printf("Nao foi possivel abrir o arquivo\n");
	fclose(arq_jogadores);
}

//------------registro partidas--------------------

int registra_partida(char *end_arq_partidas, Partida partidaG) {
	FILE *arq_partidas;

	arq_partidas = fopen(end_arq_partidas, "a+b");
	if (arq_partidas != NULL) {
		fwrite(&partidaG, 1, sizeof(struct Velha), arq_partidas);
		fclose(arq_partidas);
		return 1;
	}
	return 0;
}

//------------reseta arquivos--------------------

void reseta_arquivos() {
	FILE *arq_partidas;
	char *end_arq_partidas =
			"lista_partidas.bin";

	arq_partidas = fopen(end_arq_partidas, "w+b");
	fclose(arq_partidas);

	FILE *arq_jogadores;
	char *end_arq_jogadores =
			"lista_jogadores.txt";

	arq_jogadores = fopen(end_arq_jogadores, "w");
	fclose(arq_jogadores);
}

//------------reseta partida--------------------

void reseta_partida() {
	int x, y, count;
	x = 0;
	count = 9;

	while (count >= 1) {
		for (y = 2; y >= 0; --y) {
			partida.jogo_velha[x][y] = count + '0';
			--count;
		}
		++x;
	}
}

//------------imprime partidas--------------------

void imprime_partidas() {
	FILE *arq_partidas, *arq_jogadores;
	char *end_arq_partidas =
			"lista_partidas.bin";
	char *end_arq_jogadores =
			"lista_jogadores.txt";
	Partida partidas;
	int pnts_jog1, pnts_jog2, x;
	char jog1[20], jog2[20], buffer[50], jog1_c[2], jog2_c[2];
	pnts_jog1 = pnts_jog2 = 0;

	arq_jogadores = fopen(end_arq_jogadores, "r");
	arq_partidas = fopen(end_arq_partidas, "r+b");
	printf("\n-----------------------------------------------------\n");
	for (x = 0; x < partida.partida; ++x) {
		fgets(buffer, 50, arq_jogadores);
		strcpy(jog1, strtok(buffer, ";"));
		strcpy(jog1_c, strtok(NULL, ";"));
		strcpy(jog2, strtok(NULL, ";"));
		strcpy(jog2_c, strtok(NULL, "."));
		fread(&partidas, sizeof(struct Velha), 1, arq_partidas);
		if (partidas.resultado == jog1_c[0])
			++pnts_jog1;
		else if (partidas.resultado == jog2_c[0])
			++pnts_jog2;
		printf("\n%s: %c VS %s: %c", jog1, jog1_c[0], jog2, jog2_c[0]);
		inicializa_velha(partidas.partida, partidas.jogo_velha);
		printf("Resultado: %c\n", partidas.resultado);
		printf("\n----------------------------------------------------\n");
	}
	printf("\n%s: %d VS %s: %d\n", jog1, pnts_jog1, jog2, pnts_jog2);
	if (pnts_jog1 > pnts_jog2)
		printf("O(a) jogador %s foi o(a) campeao(a) do jogo da velha\n", jog1);
	else if (pnts_jog1 < pnts_jog2)
		printf("O(a) jogador %s foi o(a) campeao(a) do jogo da velha\n", jog2);
	else
		printf("EMPATE\n");
	fclose(arq_partidas);
}

//------------busca partida--------------------

Partida busca_partida(char *end_arq_partidas, int partida_busca) {
	Partida partidas;
	FILE *arq_partidas;
	int x;

	arq_partidas = fopen(end_arq_partidas, "r+b");
	for (x = 0; x < partida.partida; ++x) {
		fread(&partidas, sizeof(struct Velha), 1, arq_partidas);
		if (partida_busca == partidas.partida)
			return partidas;
	}
	fclose(arq_partidas);
	partidas.partida = 0;
	return partidas;
}

//------------menu pos partida--------------------

void menu_pos_partida() {
	printf("\nFINAL DO CAMPEONATO!\n");

	int opcao;

	while (1) {
		printf("\n---------------------------------------------------\n");
		printf("SELECIONE UMA DAS OPCOES\n");
		printf("1 -> MOSTRAR TODAS AS PARTIDAS\n");
		printf("2 -> BUSCAR UMA PARTIDA\n");
		printf("0 -> SAIR\n");
		printf("---------------------------------------------------\n");
		scanf("%d", &opcao);
		if (opcao == 1)
			imprime_partidas();
		if (opcao == 2) {
			Partida partida_busca;
			char *end_arq_partidas =
					"lista_partidas.bin";
			int num_partida;

			printf("\nInsira o numero da partida que deseja buscar nos registros!\n");
			scanf("%d", &num_partida);
			partida_busca = busca_partida(end_arq_partidas, num_partida);
			if (partida_busca.partida != 0) {
				printf(
						"\n---------------------------------------------------\n");
				inicializa_velha(partida_busca.partida, partida_busca.jogo_velha);
				printf("Resultado: %c", partida_busca.resultado);
				printf(
						"\n---------------------------------------------------\n");
			} else
				printf("Partida não encontrada nos registros\n");
		}
		if (opcao == 0)
			break;
	}
}


