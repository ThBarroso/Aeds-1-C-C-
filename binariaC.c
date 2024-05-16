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
    token = strtok(linha, ";");
    p->id = token ? strdup(token) : NULL;
    p->nome = (token = strtok(NULL, ";")) ? strdup(token) : NULL;
    p->nome_alternativo = (token = strtok(NULL, ";")) ? strdup(token) : NULL;
    p->casa = (token = strtok(NULL, ";")) ? strdup(token) : NULL;
    p->ancestral = (token = strtok(NULL, ";")) ? strdup(token) : NULL;
    p->especie = (token = strtok(NULL, ";")) ? strdup(token) : NULL;
    p->patronus = (token = strtok(NULL, ";")) ? strdup(token) : NULL;
    p->staff = (token = strtok(NULL, ";")) ? !strcmp(token, "true") : false;
    p->estudante = (token = strtok(NULL, ";")) ? strdup(token) : NULL;
    p->nomeator = (token = strtok(NULL, ";")) ? strdup(token) : NULL;
    p->vivo = (token = strtok(NULL, ";")) ? !strcmp(token, "true") : false;
    p->atoresalternativos = (token = strtok(NULL, ";")) ? strdup(token) : NULL;
    p->dianascimento = (token = strtok(NULL, ";")) ? strdup(token) : NULL;
    p->anonascimento = (token = strtok(NULL, ";")) ? atoi(token) : 0;
    p->corolho = (token = strtok(NULL, ";")) ? strdup(token) : NULL;
    p->sexo = (token = strtok(NULL, ";")) ? strdup(token) : NULL;
    p->corcabelo = (token = strtok(NULL, ";")) ? strdup(token) : NULL;
    p->bruxo = (token = strtok(NULL, ";")) ? !strcmp(token, "true") : false;

    return p;
}
void imprimir(Personagem *p) {
    if (p) {
        //printf("ID: %s, Nome: %s, Casa: %s\n", p->id, p->nome, p->casa);
          printf("[%s ## %s ## %s ## %s ## %s ## %s ## %s ## %s ## %s ## %s ## %s ## %s ## %d ## %s ## %s ## %s ## %s]\n",
           p->id, p->nome, p->nome_alternativo, p->casa, p->ancestral, p->especie, p->patronus,
           p->staff ? "true" : "false", p->estudante, p->nomeator, p->vivo ? "true" : "false",
           p->dianascimento, p->anonascimento, p->corolho, p->sexo, p->corcabelo, p->bruxo ? "true" : "false");
    }
}

void insertionSortList(List *list) {
    if (list == NULL || list->head == NULL || list->head->next == NULL) {
        return;  
    }

    Node *sorted = NULL; 
    Node *current = list->head; 

    while (current != NULL) {
        Node *next = current->next; 
        if (sorted == NULL || strcmp(sorted->personagem->nome, current->personagem->nome) >= 0) {
            current->next = sorted;
            sorted = current;
        } else {
            Node *sortedCurrent = sorted;
            while (sortedCurrent->next != NULL && strcmp(sortedCurrent->next->personagem->nome, current->personagem->nome) < 0) {
                sortedCurrent = sortedCurrent->next;
            }
            current->next = sortedCurrent->next;
            sortedCurrent->next = current;
        }
        current = next;
    }
    list->head = sorted; 
}

char **convertListToArray(List *list, int *size) {
    *size = list->size;
    char **array = malloc(list->size * sizeof(char *));
    if (!array) {
        perror("Falha ao alocar memória para o array");
        return NULL;
    }

    Node *current = list->head;
    for (int i = 0; i < list->size; i++, current = current->next) {
        array[i] = current->personagem->nome;
    }
    return array;
}
void trim(char *str) {
    int index, i;

    // Trim trailing white spaces
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

    insertionSortList(listapersonagensencontrados);
    int contadornomeusuario;
    char **nomesusuario = convertListToArray(listapersonagensencontrados, &contadornomeusuario);
    // Busca binária nos nomes
    char nome_lido[60];
    while (scanf(" %59[^\n]", nome_lido) == 1 && strcmp(nome_lido, "FIM") != 0) {
        bool encontrou = false;
        int dir = contadornomeusuario - 1, esq = 0, meio;
        trim(nome_lido);
    while (esq <= dir) {
        meio = (esq + dir) / 2;
        //printf("Comparando: %s com %s\n", nome_lido, nomesusuario[meio]);
        int result = strcmp(nome_lido, nomesusuario[meio]);
       // printf("Resultado da strcmp: %d\n", result);
        if (strcmp(nome_lido, nomesusuario[meio]) == 0) {
            encontrou = true;
             break;
        } else if (strcmp(nome_lido, nomesusuario[meio]) > 0) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
     }
}
        if (encontrou==true) {
            printf("SIM\n");
        } else {
            printf("NAO\n");
        }
    }

    freeList(personagens);
    return 0;
}