#include "stdio.h"
#include "stdlib.h"
#include "orders.h"
#include "string.h"
#define DELIVERY_TIME_IN_DAYS 3

void addProductToOrder(Order *ptr_Order, ProductsArray  *ptr_ProductsArray) {
    int op;
    char *productCode =ptr_Order->productsOrdersArray->productInOrder->code;         //Produto
    int productQuantity;           //Quantidade de Produtos
    int found = 0;
    int numberMaterials;             //Materiais usados naquele Produto especifico;
    float itemCost=0.00f;
    Product *ptr_Product = NULL;     //Aponta para a estrutura do Produto

    do {
        op = readInteger(0, 1, INSERT_OPTION_BUY); //Deseja inserir um produto
        if (op == 1) {
            if (ptr_Order->productsOrdersArray->count== ptr_Order->productsOrdersArray->size) {
                expandOrderProductArray(ptr_Order);
            }

            productQuantity = readInteger(1, 10, INSERT_QUANTITY_SIZE);//Insira a quantidade do Produto

            do {
                readString(productCode, 9999, INSERT_PRODUCT_CODE);
                if ((ptr_Product = findProductByCode(ptr_ProductsArray, productCode )) == NULL) {
                    printf("Produto não existe!\n");
                } else {
                    found = 1;
                }
            } while (found == 0);

            strcpy(ptr_Order->productsOrdersArray->productInOrder->code, productCode);
            ptr_Order->productsOrdersArray->productInOrder->quantity = productQuantity;
            ptr_ProductsArray->product->price= itemCost * productQuantity;
            ///ATTENTION
             /* esta linha multiplica o preço do produto(item cost)
             *pela quantidade pretendida(productInOrder)
             * para saber o total do produto na encomenda
              */


            ptr_Order->orderTotal += ptr_Order->productsOrdersArray->productInOrder->productTotal;

            printf("Numero de artigos: %d\n", productQuantity);
            printf("Custo total do artigo: %0.1f\n", ptr_Order->productsOrdersArray->productInOrder->productTotal);

            ptr_Order->productsOrdersArray->count++;
        }
    } while (op != 0);

    printf("Custo total da encomenda: %f\n", ptr_Order->orderTotal);
}

void readOrder(OrdersArray *ptr_OrdersArray, int i) {
    // reuse memory
    //char *billing_address = ptr_OrdersArray->orders[i].billingAddress;
    //char *expedition_address = ptr_OrdersArray->orders[i].expeditionAddress;

    //readString(billing_address, 64, INSERT_BILLING_ADDRESS_ORDER);
    //readString(expedition_address, 64, INSERT_EXPEDITION_ADDRESS_ORDER);

    //ptr_OrdersArray->orders[i].billingAddress = billing_address;
    //ptr_OrdersArray->orders[i].expeditionAddress = expedition_address;
}

void expandOrderProductArray(Order *order) {

    order->productsOrdersArray->size *= 2;

    order->productsOrdersArray = (ProductsOrderArray *) realloc(order->productsOrdersArray,
                                                     order->productsOrdersArray->size * sizeof(ProductsOrderArray));

    if (order->productsOrdersArray == NULL) {
        perror("Not allocated\n");
        exit(EXIT_FAILURE);
    }

    for (int j = order->productsOrdersArray->count; j < order->productsOrdersArray->size; j++) {
        strcpy(order->productsOrdersArray[j].productInOrder->code ,"");
        order->productsOrdersArray[j].productInOrder->productTotal = 0.0f;
        order->productsOrdersArray[j].productInOrder->quantity = 0;
    }
}

void expandOrdersArray(OrdersArray *ptr_OrdersArray) {
    int new_order_size;

    new_order_size = ptr_OrdersArray->size * 2;

    ptr_OrdersArray->orders = (Order *) realloc(ptr_OrdersArray->orders, new_order_size * sizeof(Order));
    if (ptr_OrdersArray->orders == NULL) {
        perror("Not allocated\n");
        exit(EXIT_FAILURE);
    }

    ptr_OrdersArray->size = new_order_size;

    for (int i = ptr_OrdersArray->count; i < new_order_size; i++) {
       // ptr_OrdersArray->orders[i].billingAddress = (char *) calloc(64, sizeof(char));
        //ptr_OrdersArray->orders[i].expeditionAddress = (char *) calloc(64, sizeof(char));
        ptr_OrdersArray->orders[i].orderCode = 0;
        ptr_OrdersArray->orders[i].orderTotal = 0.0f;
    }

}

OrdersArray *allocMemoryOrders() {

    OrdersArray *ptr_OrdersArray = (OrdersArray *) malloc(sizeof(OrdersArray));
    if (ptr_OrdersArray == NULL) {
        return NULL;
    }

    ptr_OrdersArray->count = 0;
    ptr_OrdersArray->size = 20;

    ptr_OrdersArray->orders = (Order *) calloc(ptr_OrdersArray->size, sizeof(Order));
    if (ptr_OrdersArray->orders == NULL) {
        return NULL;
    }

    for (int i = 0; i < ptr_OrdersArray->size; i++) {
        /*ptr_OrdersArray->orders[i].billingAddress = (char *) calloc(64, sizeof(char));
        if (ptr_OrdersArray->orders[i].billingAddress == NULL) {
            return NULL;
        }

        ptr_OrdersArray->orders[i].expeditionAddress = (char *) calloc(64, sizeof(char));
        if (ptr_OrdersArray->orders[i].expeditionAddress == NULL) {
            return NULL;
        }
*/
        ptr_OrdersArray->orders[i].clientCode = 0;
        ptr_OrdersArray->orders[i].orderCode = 0;
        ptr_OrdersArray->orders[i].orderTotal = 0.0f;
        ptr_OrdersArray->orders[i].canceled = 0;

        //Discutir nossa estrutura ProductsOrderArray
        // Allocate memory for ProductsOrderArray array
        ptr_OrdersArray->orders[i].productsOrdersArray = (ProductsOrderArray *) calloc(20, sizeof(ProductsOrderArray));
        if (ptr_OrdersArray->orders[i].productsOrdersArray == NULL) {
            return NULL;
        }

        // Initialize ProductsOrderArray array fields
        for (int j = 0; j < ptr_OrdersArray->orders->productsOrdersArray->size; j++) {
            strcpy(ptr_OrdersArray->orders[i].productsOrdersArray[j].productInOrder->code,(char *) calloc(64, sizeof(char)));
            ptr_OrdersArray->orders[i].productsOrdersArray[j].productInOrder->quantity = 0;
            ptr_OrdersArray->orders[i].productsOrdersArray[j].productInOrder->productTotal = 0;

        }
    }
    return ptr_OrdersArray;
}

void freeMemoryOrders(OrdersArray *ptr_OrdersArray) {
    for (int i = 0; i < ptr_OrdersArray->size; i++) {
     //   free(ptr_OrdersArray->orders[i].billingAddress);
     //  free(ptr_OrdersArray->orders[i].expeditionAddress);
    }

    free(ptr_OrdersArray->orders);
    free(ptr_OrdersArray);
}

int addOrder(OrdersArray *ptr_OrdersArray, ClientsArray *ptr_ClientsArray, ProductsArray *ptr_ProductsArray) {
    int client_code;
    int order_code;

    client_code = readInteger(0, 9999, INSERT_CLIENT_CODE);
    if (findClientsByCode(ptr_ClientsArray, client_code) == 0) {
        printf("Cliente não existe\n");
        return 0;
    }

    if (ptr_OrdersArray->count == ptr_OrdersArray->size) {
        expandOrdersArray(ptr_OrdersArray);
    }

    readOrder(ptr_OrdersArray, ptr_OrdersArray->count);
    addProductToOrder(&ptr_OrdersArray->orders[ptr_OrdersArray->count], ptr_ProductsArray);

    srand(time(NULL));
    order_code = rand() % 9999;

    printf("Código da encomenda: %d\n", order_code);

    ptr_OrdersArray->orders[ptr_OrdersArray->count].clientCode = client_code;
    ptr_OrdersArray->orders[ptr_OrdersArray->count].orderCode = order_code;

    ptr_OrdersArray->count++;

    return 1;
}

int cancelOrder(OrdersArray *ptr_OrdersArray) {
    int orderCode;

    orderCode = readInteger(0, 9999, INSERT_ORDER_CODE);

    for (int i = 0; i < ptr_OrdersArray->count; i++) {
        if (ptr_OrdersArray->orders[i].orderCode == orderCode) {
            ptr_OrdersArray->orders[i].canceled = 1;
            return 1;
        }
    }

    return 0;
}

int updateOrder(OrdersArray *ptr_OrdersArray) {
    int orderCode;

    orderCode = readInteger(0, 9999, INSERT_ORDER_CODE);

    for (int i = 0; i < ptr_OrdersArray->count; i++) {
        if (ptr_OrdersArray->orders[i].orderCode == orderCode) {
            readOrder(ptr_OrdersArray, i);
        }
    }

    return 0;
}

void printOrder(Order *ptr_Order) {
    printf("Código do cliente: %d\n", ptr_Order->clientCode);
    printf("Código da encomenda: %d\n", ptr_Order->orderCode);
    //printf("Morada de envio: %s\n", ptr_Order->expeditionAddress);
    //printf("Morada de faturação: %s\n", ptr_Order->billingAddress);
    printf("Valor da encomenda: %.2f\n", ptr_Order->orderTotal);

    if (ptr_Order->canceled) {
        printf("Estado da encomenda: CANCELADO\n");
    }
}

void ordersListByClient(OrdersArray *ptr_OrdersArray) {

    if (ptr_OrdersArray->count == 0) {
        printf("Vazio");
        return;
    }

    int client_code = readInteger(0, 9999, INSERT_CLIENT_CODE);

    for (int i = 0; i < ptr_OrdersArray->count; i++) {
        if (ptr_OrdersArray->orders[i].clientCode == client_code) {
            printOrder(&ptr_OrdersArray->orders[i]);
        }
    }
}

void ordersList(OrdersArray *ptr_OrdersArray) {

    if (ptr_OrdersArray->count == 0) {
        printf("Vazio\n");
        return;
    }

    for (int i = 0; i < ptr_OrdersArray->count; i++) {
        printOrder(&ptr_OrdersArray->orders[i]);
    }
}

void ordersListCanceled(OrdersArray *ptr_OrdersArray) {

    if (ptr_OrdersArray->count == 0) {
        printf("Vazio\n");
        return;
    }

    for (int i = 0; i < ptr_OrdersArray->count; i++) {
        if (ptr_OrdersArray->orders[i].canceled == 1) {
            printOrder(&ptr_OrdersArray->orders[i]);
        }
    }
}