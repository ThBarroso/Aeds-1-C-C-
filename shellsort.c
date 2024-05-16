#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

typedef struct Node {
    Personagem *personagem;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    int size;
} List;
Personagem *parsePersonagem(char *linha);
void free_personagem(Personagem *p);
char *cleanToken(char *token);

List *createList() {
    List *list = malloc(sizeof(List));
    if (list) {
        list->head = NULL;
        list->size = 0;
    }
    return list;
}

void addToList(List *list, Personagem *personagem) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode) {
        newNode->personagem = personagem;
        newNode->next = list->head;
        list->head = newNode;
        list->size++;
    }
}

void freeList(List *list) {
    Node *current = list->head;
    while (current) {
        Node *temp = current;
        current = current->next;
        free_personagem(temp->personagem);
        free(temp);
    }
    free(list);
}

Personagem *getFromList(List *list, int index) {
    Node *current = list->head;
    while (index-- > 0 && current) {
        current = current->next;
    }
    return current ? current->personagem : NULL;
}

List *lerTodosPersonagens(FILE *file) {
    List *lista = createList();
    char linha[1024];
    while (fgets(linha, sizeof(linha), file) != NULL) {
        Personagem *p = parsePersonagem(linha);  
        if (p) {
            addToList(lista, p);
        }
    }
    return lista;
}
Personagem *buscarPersonagem(List *lista, char *codigo) {
    Node *current = lista->head;
    while (current) {
        if (strcmp(current->personagem->id, codigo) == 0) {
            return current->personagem;
        }
        current = current->next;
    }
    return NULL;
}
Personagem *parsePersonagem(char *linha) {
    Personagem *p = malloc(sizeof(Personagem));
    if (p == NULL) {
        fprintf(stderr, "Falha ao alocar memória para Personagem.\n");
        return NULL;
    }

    char *token;
    token = cleanToken(strtok(linha, ";"));
    p->id = token ? strdup(token) : NULL;
    token = cleanToken(strtok(NULL, ";"));
    p->nome = token ? strdup(token) : NULL;
    token = cleanToken(strtok(NULL, ";"));
    p->nome_alternativo = token ? strdup(token) : NULL;
    token = cleanToken(strtok(NULL, ";"));
    p->casa = token ? strdup(token) : NULL;
    token = cleanToken(strtok(NULL, ";"));
    p->ancestral = token ? strdup(token) : NULL;
    token = cleanToken(strtok(NULL, ";"));
    p->especie = token ? strdup(token) : NULL;
    token = cleanToken(strtok(NULL, ";"));
    p->patronus = token ? strdup(token) : NULL;
    token = cleanToken(strtok(NULL, ";"));
    p->staff = token && strcmp(token, "VERDADEIRO") == 0;
    token = cleanToken(strtok(NULL, ";"));
    p->estudante = token ? strdup(token) : NULL;
    token = cleanToken(strtok(NULL, ";"));
    p->nomeator = token ? strdup(token) : NULL;
    token = cleanToken(strtok(NULL, ";"));
    p->vivo = token && strcmp(token, "VERDADEIRO") == 0;
    token = cleanToken(strtok(NULL, ";"));
    p->atoresalternativos = token ? strdup(token) : NULL;
    token = cleanToken(strtok(NULL, ";"));
    p->dianascimento = token ? strdup(token) : NULL;
    token = cleanToken(strtok(NULL, ";"));
    p->anonascimento = token ? atoi(token) : 0;
    token = cleanToken(strtok(NULL, ";"));
    p->corolho = token ? strdup(token) : NULL;
    token = cleanToken(strtok(NULL, ";"));
    p->sexo = token ? strdup(token) : NULL;
    token = cleanToken(strtok(NULL, ";"));
    p->corcabelo = token ? strdup(token) : NULL;
    token = cleanToken(strtok(NULL, ";"));
    p->bruxo = token && strcmp(token, "VERDADEIRO") == 0;

    return p;
}

char *cleanToken(char *token) {
    if (token == NULL) {
        return NULL;
    }
    while (isspace(*token)) {
        token++;
    }
    char *end = token + strlen(token) - 1;
    while (end > token && isspace(*end)) {
        *end = '\0';
        end--;
    }
    return token;
}

void imprimir(Personagem *p) {
    if (p) {
        // Format alternative names correctly
        char nome_alternativo_formatado[1024] = ""; // Start with empty string
        if (p->nome_alternativo && strlen(p->nome_alternativo) > 0) {
            // Copy first alternative name
            strcpy(nome_alternativo_formatado, p->nome_alternativo);
            // Replace brackets and single quotes for cleaner output
            for (int i = 0; nome_alternativo_formatado[i] != '\0'; i++) {
                if (nome_alternativo_formatado[i] == '[' || nome_alternativo_formatado[i] == ']' || nome_alternativo_formatado[i] == '\'') {
                    nome_alternativo_formatado[i] = (nome_alternativo_formatado[i] == '[' || nome_alternativo_formatado[i] == ']') ? ' ' : ',';
                }
            }
        }

        printf("[%s ## %s ## {%s} ## %s ## %s ## %s ## %s ## %s ## %s ## %s ## %s ## %s ## %d ## %s ## %s ## %s ## %s]\n",
              p->id, p->nome, nome_alternativo_formatado, p->casa, p->ancestral, p->especie,
              p->patronus ? p->patronus : "", 
              p->staff ? "true" : "false", p->estudante,
              p->nomeator, p->vivo ? "true" : "false",
              p->dianascimento, p->anonascimento, p->corolho,
              p->sexo, p->corcabelo, p->bruxo ? "true" : "false");
    }
}

void insercaoPorCor(Personagem **nomesusuario, int n, int cor, int h){
    for (int i = (h + cor); i < n; i+=h) {
        Personagem *tmp = nomesusuario[i];
        int j = i - h;
        while ((j >= 0) && (nomesusuario[j]->corolho > tmp->corolho)) {
            nomesusuario[j + h] = nomesusuario[j];
            j-=h;
        }
        nomesusuario[j + h] = tmp;
    }
}

void shellsort(Personagem **nomesusuario, int contadornomeusuario) {
     int h = 1;

    do { h = (h * 3) + 1; } while (h < contadornomeusuario);

    do {
        h /= 3;
        for(int cor = 0; cor < h; cor++){
            insercaoPorCor(nomesusuario, contadornomeusuario, cor, h);
        }
    } while (h != 1);
}


Personagem **convertListToArray(List *list, int *size) {
    *size = list->size;
    Personagem **array = malloc(list->size * sizeof(Personagem *));
    if (!array) {
        perror("Falha ao alocar memória para o array");
        return NULL;
    }

    Node *current = list->head;
    for (int i = 0; i < list->size; i++, current = current->next) {
        array[i] = current->personagem;
    }
    return array;
}

void trim(char *str) {
    int index, i;
    index = -1;
    i = 0;
    while (str[i] != '\0') {
        if (str[i] != ' ' && str[i] != '\n' && str[i] != '\r') {
            index = i;
        }
        i++;
    }
    str[index + 1] = '\0';
}

void free_personagem(Personagem *p) {
    if (p) {
        free(p->id);
        free(p->nome);
        free(p->nome_alternativo);
        free(p->casa);
        free(p->ancestral);
        free(p->especie);
        free(p->patronus);
        free(p->estudante);
        free(p->nomeator);
        free(p->atoresalternativos);
        free(p->dianascimento);
        free(p->corolho);
        free(p->sexo);
        free(p->corcabelo);
        free(p);
    }
}
int main() {
    FILE *file = fopen(FILE_PATH, "r");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    List *personagens = lerTodosPersonagens(file);
    List *listapersonagensencontrados = createList();
    fclose(file); 
    char codigo[60];
    while (scanf("%59s", codigo) == 1 && strcmp(codigo, "FIM") != 0) {
        Personagem *personagem = buscarPersonagem(personagens, codigo);
        if (personagem) {
             addToList(listapersonagensencontrados, personagem);
        } 
    }
    int contadornomeusuario;
    char **nomesusuario = convertListToArray(listapersonagensencontrados, &contadornomeusuario);
    shellsort(nomesusuario,contadornomeusuario);

for(int i = 0; i < contadornomeusuario; i++) {
    imprimir((Personagem *)nomesusuario[i]);  
}

    freeList(personagens);
    return 0;
}