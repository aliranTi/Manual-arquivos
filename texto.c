#include <stdio.h>
#include <stdlib.h>

void salvarTexto(char *texto, char *nomeArquivo, char *modo);
FILE * abrirArquivo(char *nomeArquivo, char *modo);
char *lerTexto(const char *nomeArquivo);


void salvarTexto(char *texto, char *nomeArquivo,char * modo){
    FILE * arquivo = abrirArquivo(nomeArquivo, modo);
    fprintf(arquivo, "%s", texto);
    fclose(arquivo);
}

FILE * abrirArquivo(char *nomeArquivo, char *modo) {
    FILE *arquivo = fopen(nomeArquivo, modo);
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        exit(1);
    }
    return arquivo;
}

char *lerTexto(const char *nomeArquivo) {
    // Abre o arquivo para leitura
    FILE *arquivo = abrirArquivo(nomeArquivo, "r");

    // Move o ponteiro do arquivo para o final e obtém o tamanho do arquivo
    fseek(arquivo, 0, SEEK_END);
    long tamanho = ftell(arquivo);
    rewind(arquivo);

    // Aloca memória para armazenar o texto, incluindo o caractere nulo
    char *texto = (char *) malloc(tamanho + 1);
    if (texto == NULL) {
        perror("Erro ao alocar memória");
        fclose(arquivo);
        exit(EXIT_FAILURE);
    }

    // Lê o conteúdo do arquivo para o buffer de texto
    fread(texto, 1, tamanho, arquivo);
    texto[tamanho] = '\0';

    // Fecha o arquivo
    fclose(arquivo);

    // Retorna o texto lido
    return texto;
}

int main() {
    char *texto = lerTexto("texto.txt");
    printf("Texto lido:\n%s\n", texto);
    free(texto);

    salvarTexto("Hello, World!", "saida.txt", "w");
    return 0;
}
