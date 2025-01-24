#include <stdio.h>
#include <stdlib.h>
#include "menus.h"

int menusBuilder(const char *menu_msg, const char *input_msg, int min_op, int max_op) {
    int op;

    printf("%s", menu_msg);
    op = readInteger(min_op, max_op, input_msg);

    return op;
}

int mainMenu() {
    int op;

    ClientsArray *ptr_ClientsArray = NULL;
    ProductsArray *ptr_ProductsArray = NULL;
    MaterialsArray *ptr_MaterialsArray = NULL;
    OrdersArray *ptr_OrdersArray = NULL;
    ProductMaterialsArray *ptr_ProductMaterialsArray = NULL;

    ptr_ClientsArray = (ClientsArray *) allocMemoryClients(ptr_ClientsArray);
    if (ptr_ClientsArray == NULL) {
        free(ptr_ClientsArray);
        perror("Clients Exited\n");
        return 1;
    }

    ptr_ProductsArray = (ProductsArray *) allocMemoryProducts(20,20);
    if (ptr_ProductsArray == NULL) {
        free(ptr_ProductsArray);
        free(ptr_MaterialsArray);
        free(ptr_ProductMaterialsArray);
        perror("Products Exit\n");
        return 1;
    }

    ptr_OrdersArray = (OrdersArray *) allocMemoryOrders(ptr_OrdersArray);
    if (ptr_OrdersArray == NULL) {
        free(ptr_ProductsArray);
        free(ptr_ClientsArray);
        free(ptr_OrdersArray);
        free(ptr_ProductMaterialsArray);
        perror("Orders Exited");
        return 1;
    }

    ptr_MaterialsArray = (MaterialsArray *) allocMemoryMaterials(ptr_MaterialsArray);
    if (ptr_MaterialsArray == NULL) {
        free(ptr_MaterialsArray);
        perror("Materials Exited");
        return 1;
    }
    ptr_ProductMaterialsArray = (ProductMaterialsArray *) allocMemoryProductMaterials(ptr_ProductMaterialsArray);
    if (ptr_ProductMaterialsArray == NULL) {
        free(ptr_ProductMaterialsArray);
        free(ptr_MaterialsArray);
        free(ptr_ProductsArray);
        perror("Products Exit\n");
        return 1;
    }

    do {
        op = menusBuilder(MAIN_MENU, INSERT_PROFILE, 0, 2);
        switch (op) {
            case 0:
                exit(EXIT_SUCCESS);
            case 1:
                menuAdmin(ptr_ClientsArray, ptr_ProductsArray, ptr_MaterialsArray, ptr_ProductMaterialsArray);
                break;
            case 2:
                menuClient(ptr_OrdersArray, ptr_ClientsArray, ptr_ProductsArray, ptr_ProductMaterialsArray);
                break;
            default:
                break;
        }
    } while (op != 0);

    freeMemoryClients(ptr_ClientsArray);
    freeMemoryProducts(ptr_ProductsArray);
    freeMemoryMaterials(ptr_MaterialsArray);
    freeMemoryOrders(ptr_OrdersArray);
    return 1;
}

void menuAdmin(ClientsArray *ptr_ClientsArray, ProductsArray *ptr_ProductsArray, MaterialsArray *ptr_MaterialsArray, ProductMaterialsArray *ptr_ProductMaterialsArray) {
    int op;


    do {
        op = menusBuilder(MENU_ADMIN, INSERT_OPTION, 0, 5);
        switch (op) {
            case 0:
                mainMenu();
            case 1:
                clientsManagement(ptr_ClientsArray, ptr_ProductsArray, ptr_MaterialsArray, ptr_ProductMaterialsArray);
                break;
            case 2:
                productManagement(ptr_ClientsArray, ptr_ProductsArray, ptr_MaterialsArray,ptr_ProductMaterialsArray);
                break;
            case 3:
                materialManagement(ptr_ClientsArray, ptr_ProductsArray, ptr_MaterialsArray, ptr_ProductMaterialsArray);
                break;
            case 4:
                //productionManagement();
                break;
            case 5:
                //files();
                break;
            default:
                break;
        }

    } while (op != 0);
}

void clientsManagement(ClientsArray *ptr_ClientsArray, ProductsArray *ptr_ProductsArray,
                       MaterialsArray *ptr_MaterialsArray, ProductMaterialsArray *ptr_ProductMaterialsArray) {
    int op;


    do {
        op = menusBuilder(MENU_CLIENT_MANAGEMENT, INSERT_OPTION, 0, 5);
        switch (op) {
            case 0:
                menuAdmin(ptr_ClientsArray, ptr_ProductsArray, ptr_MaterialsArray, ptr_ProductMaterialsArray);
                break;
            case 1:
                addClients(ptr_ClientsArray);
                break;
            case 2:
                updateClient(ptr_ClientsArray, readInteger(0, 9999, INSERT_CLIENT_CODE));
                break;
            case 3:
                removeClient(ptr_ClientsArray, readInteger(0, 9999, INSERT_CLIENT_CODE));
                break;
            case 4:
                listClients(ptr_ClientsArray);
                break;
            case 5:
                clientsListCanceled(ptr_ClientsArray);
                break;
            default:
                break;
        }
    } while (op != 0);
}

void productManagement(ClientsArray *ptr_ClientsArray, ProductsArray *ptr_ProductsArray,
                       MaterialsArray *ptr_MaterialsArray, ProductMaterialsArray *ptr_ProductMaterialsArray) {
    int op;
    char code [6];

    do {
        op = menusBuilder(MENU_PRODUCT_MANAGEMENT, INSERT_OPTION, 0, 5);
        switch (op) {
            case 0:
                menuAdmin(ptr_ClientsArray, ptr_ProductsArray, ptr_MaterialsArray, ptr_ProductMaterialsArray);
                break;
            case 1:
                addProduct(ptr_MaterialsArray,ptr_ProductsArray,ptr_ProductMaterialsArray);
                break;
            case 2:
                //readString(ptr_ProductsArray->product->code, 6, INSERT_PRODUCT_CODE);
                updateProduct(ptr_MaterialsArray, ptr_ProductsArray,ptr_ProductMaterialsArray, code);
                break;
            case 3:
                readString(ptr_ProductsArray->product->code, 6, INSERT_PRODUCT_CODE);
                removeProduct(ptr_ProductsArray, code);
                break;
            case 4:
                listProducts(ptr_ProductsArray);
                break;
            case 5:
                productsListCanceled(ptr_ProductsArray);
                break;
            default:
                break;
        }
    } while (op != 0);
}

void materialManagement(ClientsArray *ptr_ClientsArray, ProductsArray *ptr_ProductsArray,
                        MaterialsArray *ptr_MaterialsArray, ProductMaterialsArray *ptr_ProductMaterialsArray) {
    int op;
    char code[6];

    do {
        op = menusBuilder(MENU_MATERIAL_MANAGEMENT, INSERT_OPTION, 0, 5);
        switch (op) {
            case 0:
                menuAdmin(ptr_ClientsArray, ptr_ProductsArray, ptr_MaterialsArray, ptr_ProductMaterialsArray);
                break;
            case 1:
                addMaterial(ptr_MaterialsArray);
                break;
            case 2:
                updateMaterial(ptr_MaterialsArray, code);
                break;
            case 3:
                removeMaterial(ptr_MaterialsArray, code);
                break;
            case 4:
                listMaterials(ptr_MaterialsArray);
                break;
            case 5:
                //materialsListCanceled(ptr_MaterialsArray);  // A função está feita(Completa);
                break;
            default:
                break;

        }

    } while (op != 0);
}

void menuClient(OrdersArray *ptr_OrdersArray, ClientsArray *ptr_ClientsArray, ProductsArray *ptr_ProductsArray, ProductMaterialsArray *ptr_ProductMaterialsArray) {
    int op;

    do {
        op = menusBuilder(MENU_CLIENT, INSERT_OPTION, 0, 2);
        switch (op) {
            case 0:
                exit(EXIT_SUCCESS);
            case 1:
                addOrder(ptr_OrdersArray, ptr_ClientsArray, ptr_ProductsArray);
                break;
            default:
                break;
        }
    } while (op != 0);

}