#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "clients.h"

int findClientsByCode(ClientsArray *ptr_clientsArray, int code) {
    for (int i = 0; i < ptr_clientsArray->count; i++) {
        if (ptr_clientsArray->clients[i].code == code) {
            return 1;
        }
    }

    return 0;
}

int findNif(ClientsArray *ptr_clientsArray, int nif) {
    for (int i = 0; i < ptr_clientsArray->count; i++) {
        if (ptr_clientsArray->clients[i].nif == nif) {
            return 1;
        }
    }
    return 0;
}

int readClientInfo(ClientsArray *ptr_clientsArray, int i) {
    int nif;

    //reuse memory
    char *name = ptr_clientsArray->clients[i].name;
    char *country= ptr_clientsArray->clients[i].country;
    char *address =ptr_clientsArray->clients[i].address;

    readString(name, 256, INSERT_CLIENT_NAME"\n");

    nif = readInteger(99999999, 999999999, INSERT_CLIENT_NIF"\n");
    if (findNif(ptr_clientsArray, nif)) {
        printf(NIF_EXISTS"\n");
        return 0;
    }
    readString(address, 256, INSERT_CLIENT_ADDRESS"\n");
    readString(country, 64, INSERT_CLIENT_COUNTRY);

    strcpy(ptr_clientsArray->clients[i].name, name);
    strcpy(ptr_clientsArray->clients[i].country, country);
    strcpy(ptr_clientsArray->clients[i].address, address);
    ptr_clientsArray->clients[i].nif = nif;


    return 1;
}

void expandClientsArray(ClientsArray *ptr_clientsArray) {
    int new_size;

    new_size = ptr_clientsArray->size * 2;

    ptr_clientsArray->clients = (Client *) realloc(ptr_clientsArray->clients, new_size * sizeof(Client));
    if (ptr_clientsArray->clients == NULL) {
        printf("Não alocou!");
        exit(1);
    }

    ptr_clientsArray->size = new_size;

    for (int i = ptr_clientsArray->count; i < ptr_clientsArray->size; i++) {
        strcpy(ptr_clientsArray->clients[i].name, (char *) calloc(256, sizeof(char)));
        strcpy(ptr_clientsArray->clients[i].country, (char *) calloc(64, sizeof(char)));
        ptr_clientsArray->clients[i].removed = 0;
        ptr_clientsArray->clients[i].code = 0;
        ptr_clientsArray->clients[i].nif = 0;
    }
}

ClientsArray *allocMemoryClients() {

    ClientsArray *ptr_clientsArray = (ClientsArray *) malloc(sizeof(ClientsArray));
    if (ptr_clientsArray == NULL) {
        return NULL;
    }

    ptr_clientsArray->count = 0;
    ptr_clientsArray->size = 20;

    ptr_clientsArray->clients = (Client *) calloc(ptr_clientsArray->size, sizeof(Client));
    if (ptr_clientsArray->clients == NULL) {
        return NULL;
    }

    for (int i = 0; i < ptr_clientsArray->size; i++) {
        strcpy(ptr_clientsArray->clients[i].name,
               (char *) calloc(64, sizeof(char)));
        strcpy(ptr_clientsArray->clients[i].country,
               (char *) calloc(3, sizeof(char)));
    }

    return ptr_clientsArray;
}

void freeMemoryClients(ClientsArray *ptr_clientsArray) {
    for (int i = 0; i < ptr_clientsArray->size; i++) {
        free(ptr_clientsArray->clients[i].name);
        free(ptr_clientsArray->clients[i].country);
    }

    free(ptr_clientsArray->clients);
    free(ptr_clientsArray);
}

int addClients(ClientsArray *ptr_clientsArray) {
    int code;

    if (ptr_clientsArray == NULL) {
        return 0;
    }

    if (ptr_clientsArray->count == ptr_clientsArray->size) {
        expandClientsArray(ptr_clientsArray);
    }

    code = readInteger(0, 9999, INSERT_CLIENT_CODE);
    if (findClientsByCode(ptr_clientsArray, code)) {
        printf(CODE_EXISTS"\n");
        return 0;
    }

    ptr_clientsArray->clients[ptr_clientsArray->count].code = code;


    if (readClientInfo(ptr_clientsArray, ptr_clientsArray->count) != 1) {
        return 0;
    }

    ptr_clientsArray->count++;

    return 1;
}

void removeClient(ClientsArray *ptr_clientsArray, int code) {

    if (emptyList(ptr_clientsArray)) {
        return;
    }


    for (int i = 0; i < ptr_clientsArray->count; i++) {
        if (ptr_clientsArray->clients[i].code == code) {
            ptr_clientsArray->clients[i].removed = 1;

            printf("\nRemovido com sucesso\n");
            return;
        }
    }

    printf("\nNão foi removido!\n");
}

void updateClient(ClientsArray *ptr_clientsArray, int code) {

    if (emptyList(ptr_clientsArray)) {
        return;
    }

    for (int i = 0; i < ptr_clientsArray->count; i++) {
        if (ptr_clientsArray->clients[i].code == code) {

            if (readClientInfo(ptr_clientsArray, i)) {
                printf("\nAtualizado com sucesso!\n");
                return;
            }
        }
    }

    printf("\nNão Atualizado!\n");
}

void listClients(ClientsArray *ptr_clientsArray) {

    if (emptyList(ptr_clientsArray)) {
        return;
    }

    for (int i = 0; i < ptr_clientsArray->count; i++) {
        printClientInfo(&ptr_clientsArray->clients[i]);
    }
}

void clientsListCanceled(ClientsArray *ptr_clientsArray) {

    if (ptr_clientsArray->count == 0) {
        printf("Vazio\n");
        return;
    }

    for (int i = 0; i < ptr_clientsArray->count; i++) {
        if (ptr_clientsArray->clients[i].removed == 1) {
            printClientInfo(&ptr_clientsArray->clients[i]);
        }
    }
}

void printClientInfo(const Client *ptr_client) {
    printf("\n----\n");
    printf("Código de cliente: %d\n", ptr_client->code);
    printf("Nome do Cliente: %s\n", ptr_client->name);
    printf("Morada Cliente: %s\n", ptr_client->address);
    printf("Nif do cliente: %d\n", ptr_client->nif);
    printf("País do cliente: %s\n", ptr_client->country);
    printf("Removido: %d", ptr_client->removed);
    printf("\n----\n");
}