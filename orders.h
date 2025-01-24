#ifndef LP_G14_ORDERS_H
#define LP_G14_ORDERS_H

#include "time.h"
#include "clients.h"
#include "products.h"

typedef struct {
    int day;
    int month;
    int year;
}Date;

typedef struct {
    char code[6];   //Codigo do Produto
    int quantity;   //Quantidade de Produtos a encomendar
    float productTotal;
}ProductInOrder;

typedef  struct  {
    ProductInOrder *productInOrder;
    int size;
    int count;
}ProductsOrderArray;  //Lista de Produtos numa encomenda

typedef struct {
    int clientCode;
    int orderCode;
    ProductsOrderArray *productsOrdersArray;
    Date deliveryDate;
    float orderTotal;
    int canceled;
} Order;

typedef struct {
    Order *orders;
    int size;
    int count;
} OrdersArray;

/**
 * Adiciona produtos a uma encomenda.
 *
 */
void addProductToOrder(Order *ptr_Order, ProductsArray *ptr_ProductsArray);

/**
 * Expande a alocação memória para o array de produtos de uma encomenda.
 *
 */
void expandOrderProductArray(Order *order);

//Order *findOrderByCode(OrdersArray *ptr_OrdersArray, const int code);
/**
 * Expande a alocação memória para o array de encomendas.
 *
 */
void expandOrdersArray(OrdersArray *ptr_OrdersArray);

/**
 * Alloca memória para o array de encomendas.
 */
OrdersArray *allocMemoryOrders();

/**
 * Função para libertar a memória do array de encomendas.
 * @param ptr_OrdersArray
 */
void freeMemoryOrders(OrdersArray *ptr_OrdersArray);

/**
 * Adiciona uma encomenda ao array.
 * @param orders_arr
 * @param clients_arr
 * @return 1 se adicionado com sucesso, caso-contrário 0.
 */
int addOrder(OrdersArray *ptr_OrdersArray, ClientsArray *ptr_ClientsArray, ProductsArray *ptr_ProductsArray);

/**
 * Atualiza as informações da encomenda.
 * @param ptr_OrdersArray
 * @return 1 se encontrado e atualizado, caso-contrário 0.
 */
int updateOrder(OrdersArray *ptr_OrdersArray);

/**
 * A função pede ao utilizador o código da encomenda, percorre o array para procurar a encomenda
 * com esse código e remove.
 * @param ptr_OrdersArray
 * @return 1 se removido com sucesso, caso-contrário 0.
 */
int cancelOrder(OrdersArray *ptr_OrdersArray);

/**
 * Função utilizada para imprimir toda a informação de uma encomenda.
 * @param ptr_Order
 */
void printOrder(Order *ptr_Order);

/**
 * A função pede o código ao utilizador e mostra as encomendas
 * do utilizador com aquele código.
 * @param ptr_OrdersArray
 */
void ordersListByClient(OrdersArray *ptr_OrdersArray);

/**
 *  * A função permite ao admin listar todas as encomendas existentes.
 * @param orders_arr
 */
void ordersList(OrdersArray *ptr_OrdersArray);

/**
 * A função permite ao admin listar todas as encomendas canceladas.
 * @param ptr_OrdersArray
 */
void ordersListCanceled(OrdersArray *ptr_OrdersArray);

#endif //LP_G14_ORDERS_H
