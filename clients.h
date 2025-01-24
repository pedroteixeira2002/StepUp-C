#ifndef LP_G14_CLIENTS_H
#define LP_G14_CLIENTS_H
#include "utils.h"

typedef struct {
    int code;
    char name[256];
    char address[256];
    int nif;
    char country[64];
    int removed;
} Client;

typedef struct {
    Client *clients;
    int count;  // Representa o espaço total ocupado e a posição livre
    int size;   // Tamanho total do array
} ClientsArray;

/**
 * Procura cliente através do seu NIF.
 * @return o cliente com o NIF procurado.
 */
int findNif(ClientsArray *ptr_clientsArray, int nif);

/**
* Função utilizada usa o código inserido pelo utilizador para encontrar
* um cliente e verifica se ele existe dentro do array dos cliente.
* @param clientsArray
* @param code
* @return 1 se encontrado com sucesso, caso-contrário 0.
*/
int findClientsByCode(ClientsArray *ptr_clientsArray, int code);

 /** Aloca memória para o array de clientes.
 * @return um array de clientes.
 */
ClientsArray *allocMemoryClients();

/**
 * Função para libertar a memória do array de clientes.
 * @param ptr_clientsArray
 */
void freeMemoryClients(ClientsArray *ptr_clientsArray);

/**
 * Adiciona um novo cliente ao array.
 * @return 1 se adicionado com sucesso, caso-contrário 0.
 */
int addClients(ClientsArray *ptr_clientsArray);

/**
 * Procura o cliente pelo seu código e marca-o como removido.
 * @param code código do cliente.
 * @return 1 se encontrado e marcado como removido, caso-contrário 0.
 */
void removeClient(ClientsArray *ptr_clientsArray, int code);

/**
 * Procura o cliente pelo seu código e atualiza-o.
 * @param code código do cliente.
 * @return 1 se encontrado e atualizado, caso-contrário 0.
 */
void updateClient(ClientsArray *ptr_clientsArray, int code);

/**
 * Função utilizada para imprimir toda a informação de um cliente.
 * @param ptr_client
 */
void printClientInfo(const Client *ptr_client);

/**
 * Lista todos os clientes que estão marcados como removidos.
 * @param clientsArray
 */
void clientsListCanceled(ClientsArray *clientsArray);

/**
 * Lista de clientes cancelados.
 * @param ptr_clientsArray
 * @return
 */
int emptyList(ClientsArray *ptr_clientsArray);

/**
 * Itera o array de clientes.
 * @param ptr_clientsArray
 */
void listClients(ClientsArray *ptr_clientsArray);

#endif //LP_G14_CLIENTS_H