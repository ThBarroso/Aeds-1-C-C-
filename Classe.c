#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define FILE_PATH "/tmp/characters.csv"

typedef struct {
    char *id;
    char *nome;
    char *nome_alternativo;
    char *casa;
    char *ancestral;
    char *especie;
    char *patronus;
    bool staff;
    char *estudante;
    char *nomeator;
    bool vivo;
    char *atoresalternativos;
    char *dianascimento;
    int anonascimento;
    char *corolho;
    char *sexo;
    char *corcabelo;
    bool bruxo;
} Personagem;

void free_string_array(char **array, int length) {
    if (array == NULL)
        return;

    for (int i = 0; i < length; i++)
        free(array[i]);
    free(array);
}

char *read_string(FILE *file) {
    char *str = NULL;
    int capacity = 16; // Initial capacity
    int length = 0;
    char c;

    while ((c = fgetc(file)) != EOF && c != ';') {
        if (length >= capacity - 1) {
            capacity *= 2;
            str = realloc(str, capacity);
            if (str == NULL) {
                perror("Memory allocation error");
                return NULL;
            }
        }
        str[length++] = c;
    }
    str[length] = '\0';

    return str;
}

bool read_boolean(FILE *file) {
    char *str = read_string(file);
    if (str == NULL) {
        perror("Error reading boolean");
        return false;
    }
    bool value = (strcmp(str, "true") == 0);
    free(str);
    return value;
}

char **read_multivalued(FILE *file, int *count) {
    char **array = NULL;
    int capacity = 5; // Initial capacity
    int length = 0;
    char c;

    while ((c = fgetc(file)) != EOF && c != ']') {
        if (c == '[' || c == ' ')
            continue;
        if (length >= capacity) {
            capacity *= 2;
            array = realloc(array, capacity * sizeof(char *));
            if (array == NULL) {
                perror("Memory allocation error");
                return NULL;
            }
        }
        array[length++] = read_string(file);
    }
    *count = length;
    return array;
}

Personagem ler(FILE *file, char *codigo) {
    Personagem p;
    char linha[1024];

    while (fgets(linha, sizeof(linha), file) != NULL) {
        char *separador = strtok(linha, ";");
        p.id = strdup(separador);
        if (strcmp(p.id, codigo) == 0) {
            separador = strtok(NULL, ";");
            p.nome = strdup(separador);
            separador = strtok(NULL, ";");
            p.nome_alternativo = strdup(separador);
            separador = strtok(NULL, ";");
            p.casa = strdup(separador);
            separador = strtok(NULL, ";");
            p.ancestral = strdup(separador);
            separador = strtok(NULL, ";");
            p.especie = strdup(separador);
            separador = strtok(NULL, ";");
            p.patronus = strdup(separador);
            separador = strtok(NULL, ";");
            p.staff = (strcmp(separador, "true") == 0);
            separador = strtok(NULL, ";");
            p.estudante = strdup(separador);
            separador = strtok(NULL, ";");
            p.nomeator = strdup(separador);
            separador = strtok(NULL, ";");
            p.vivo = (strcmp(separador, "true") == 0);
            separador = strtok(NULL, ";");
            p.atoresalternativos = strdup(separador);
            separador = strtok(NULL, ";");
            p.dianascimento = strdup(separador);
            separador = strtok(NULL, ";");
            p.anonascimento = atoi(separador);
            separador = strtok(NULL, ";");
            p.corolho = strdup(separador);
            separador = strtok(NULL, ";");
            p.sexo = strdup(separador);
            separador = strtok(NULL, ";");
            p.corcabelo = strdup(separador);
            separador = strtok(NULL, ";");
            p.bruxo = (strcmp(separador, "true") == 0);
            return p;
        }
    }
    perror("Personagem não encontrado");
    exit(1);
}

void imprimir(Personagem p) {
    printf("[%s ## %s ## %s ## %s ## %s ## %s ## %s ## %s ## %s ## %s ## %s ## %s ## %d ## %s ## %s ## %s ## %s]\n",
           p.id, p.nome, p.nome_alternativo, p.casa, p.ancestral, p.especie, p.patronus,
           p.staff ? "true" : "false", p.estudante, p.nomeator, p.vivo ? "true" : "false",
           p.dianascimento, p.anonascimento, p.corolho, p.sexo, p.corcabelo, p.bruxo ? "true" : "false");
}

int main() {
    FILE *file = fopen(FILE_PATH, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    char codigo[60];
    scanf("%s", codigo);

    Personagem p = ler(file, codigo);
    
    imprimir(p);

    fclose(file);
    return 0;
}
