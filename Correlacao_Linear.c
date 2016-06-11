#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
Programa: Correlacao_linear
Descricao: Le dados e faz calculos de correlacao linear
Autor: Guilherme Guy de Andrade
*/

int main() {

	puts("============\nCorrelacao Linear\n============");

	int n = 0; //tamanho do conjunto (pares de dados)
	int i, j;
	int *x, *y; //ponteiros que vao guardar os dados
	int ler_arquivo = 0;

	int soma_x = 0, soma_y = 0, soma_xy = 0, soma_x2 = 0, soma_y2 = 0; //somatorios
	float x_medio = 0, y_medio = 0;
	float rxy = 0; //coeficiente de correlacao
	float k1 = 0, k2 = 0;
	float variancia_x = 0, variancia_y = 0; //variancia
	float sx = 0, sy = 0; //devio padrao

	puts("Voce deseja ler os dados de um arquivo txt? (1 - sim/outro - nao)");
	scanf("%i", &ler_arquivo);

	if (ler_arquivo == 1) {//leitura de dados de um arquivo txt

		/*
		A primeira linha do txt equivale ao n, ela e lida para dizer a quantidade de pares de dados.
		Por exemplo, se a primeira linha for 6, o programa vai ler da linha 2 ate a linha 7 (6 valores)
		e salvara eles como X, depois vai ler da linha 8 ate a linha 13 e salvara como Y.
		O arquivo NAO deve ter espacos e a divisao entre os numeros e dada por uma nova linha
		*/

		FILE *arq;
		char file_name[FILENAME_MAX];
		int temp = 0;
		char c1[25], c2[25];

		puts("Digite o nome do arquivo: ");
		getchar(); //por algum motivo, o fflush() nao funciona, isto e uma gambiarra para pegar qualquer
		//coisa que ainda estiver no stdin
		gets(file_name); //o gets e usado para ler os espacos (scanf nao e uma boa ideia nesse caso)

		arq = fopen(file_name, "r"); //abre o arquivo para leitura("r")

		if (arq == NULL) { //caso arquivo não seja encontrado
			printf("Erro na abertura do arquivo %s\n", file_name);
			system("pause");
			return 0;
		}

		//pega o numero de pares de dados e salva em n
		fscanf(arq, " %i ", &n);

		//aloca a memoria dos ponteiros
		x = (int*)calloc(n, sizeof(int));
		y = (int*)calloc(n, sizeof(int));


		//le o arquivo e faz alguns calculos
		for (i = 0; i < n; i++) {
			fscanf(arq, " %i ", &x[i]);
	
			soma_x += x[i];
			soma_x2 += x[i] * x[i];
		}

		for (i = 0; i < n; i++) {
			fscanf(arq, " %i ", &y[i]);

			soma_y += y[i];
			soma_y2 += y[i] * y[i];
			soma_xy += y[i] * x[i];
		}

		fclose(arq);

	}
	else {//entrada manual de dados

		//pede para o usuario digitar quantos pares de dados ele tem
		puts("\nDigite o tamanho do conjunto:");
		scanf("%i", &n);

		//aloca a memoria dos ponteiros
		x = (int*)calloc(n, sizeof(int));
		y = (int*)calloc(n, sizeof(int));

		//coleta de dados
		//executa somatorios dentro do loop para aproveitar o codigo
		puts("\nDigite os valores de X: (em ordem)\n");
		for (i = 0; i < n; i++)
		{
			scanf("%d", &x[i]);

			soma_x += x[i];
			soma_x2 += x[i] * x[i];
		}

		puts("\nDigite os valores de Y: (em ordem)\n");
		for (i = 0; i < n; i++)
		{
			scanf("%d", &y[i]);

			soma_y += y[i];
			soma_y2 += y[i] * y[i];
			soma_xy += y[i] * x[i];
		}
	}

	//comeco dos calculos

	//correlacao
	rxy = ((n * soma_xy) - (soma_x * soma_y)) / (sqrt(((n * soma_x2) - (soma_x*soma_x))*((n * soma_y2) - (soma_y * soma_y))));

	//medias
	x_medio = soma_x / (float)n;
	y_medio = soma_y / (float)n;

	//variancia
	for (i = 0; i < n; i++)
	{
		variancia_x += (x[i] - x_medio)*(x[i] - x_medio);
		variancia_y += (y[i] - y_medio)*(y[i] - y_medio);
	}

	//desvio padrao
	sx = sqrt(variancia_x);
	sy = sqrt(variancia_y);

	//k1 e k2
	k1 = rxy*(sx / sy);
	k2 = rxy*(sy / sx);

	//exibir dados

	puts("=====================");

	for (i = 0; i < 5; i++) {// o valor 5 e usado para mostrar as colunas: X, Y, X*Y, X^2 e Y^2
		for (j = 0; j < n; j++) {

			//regras para escrever a borda inicial
			if (j == 0) {
				switch (i)
				{
				case 0:
					printf("\nX > [ ");
					break;
				case 1:
					printf("\nY > [ ");
					break;
				case 2:
					printf("\nX*Y > [ ");
					break;
				case 3:
					printf("\nX^2 > [ ");
					break;
				case 4:
					printf("\nY^2 > [ ");
					break;
				default:
					break;
				}
			}

			//regras para escrever o conteudo
			switch (i)
			{
			case 0:
				printf("%i", x[j]);
				break;
			case 1:
				printf("%i", y[j]);
				break;
			case 2:
				printf("%i", (x[j] * y[j]));
				break;
			case 3:
				printf("%i", (x[j] * x[j]));
				break;
			case 4:
				printf("%i", (y[j] * y[j]));
				break;
			default:
				break;
			}

			//imprime o final de cada linha e a soma
			if (j == (n-1)) {
				switch (i)
				{
				case 0:
					printf("] Soma = %i\n", soma_x);
					break;
				case 1:
					printf("] Soma = %i\n", soma_y);
					break;
				case 2:
					printf("] Soma = %i\n", soma_xy);
					break;
				case 3:
					printf("] Soma = %i\n", soma_x2);
					break;
				case 4:
					printf("] Soma = %i\n", soma_y2);
					break;
				default:
					break;
				}
			}
			else {
				printf(", ");
			}
		}
	}

	//imprime o resto dos dados
	printf("\n\nTamanho do conjunto: n = %i \n", n);
	printf("\nX medio = %f\nY medio = %f\n", x_medio, y_medio);
	printf("\nVariancia de X = %f\nVariancia de Y = %f\n", variancia_x, variancia_y);
	printf("\nDesvio padrao: \nSx = %f\nSy = %f\n", sx, sy);
	printf("\nCorrelacao: rxy = %f\n", rxy);
	printf("\nK1 = %f\nK2 = %f\n", k1, k2);
	printf("\nX^ = %f * Yi + (%f)\n", k1, (x_medio - (k1*y_medio)));
	printf("\nY^ = %f * Xi + (%f)\n\n\n", k2, (y_medio - (k2*x_medio)));

	//libera os ponteiros antes de fechar o programa
	free(x);
	free(y);

	//pausa (espera o usuario apertar um botao antes de fechar o programa)
	system("pause");

	return 0;

}