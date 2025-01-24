#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "products.h"

int readProduct(MaterialsArray *ptr_MaterialsArray, ProductsArray *ptr_ProductsArray,
                ProductMaterialsArray *ptr_ProductMaterial, int i) {
    char option;
    float price;

    //reuse memory
    char *code = ptr_ProductsArray->product[i].code;
    char *name = ptr_ProductsArray->product[i].name;
    char *dimensions = ptr_ProductsArray->product[i].dimensions;


    readString(code, 6, CODE_INPUT_PRODUCT);
    if (findProductByCode(ptr_ProductsArray, code)) {
        printf(CODE_EXISTS);
        return 0;
    }
    readString(name, 30, INSERT_PRODUCT_NAME);
    readString(dimensions, 11, INSERT_PRODUCT_DIMENSIONS); //TAM(Exemplo: 999x999x999) 11 casas
    price = readFloat(0, 100000, INSERT_PRICE_PRODUCT);

    addMaterialsToProduct(ptr_ProductMaterial, ptr_MaterialsArray, ptr_ProductsArray, i);

    strcpy(ptr_ProductsArray->product[i].code, code);
    strcpy(ptr_ProductsArray->product[i].name, name);
    strcpy(ptr_ProductsArray->product[i].dimensions, dimensions);
    ptr_ProductsArray->product[i].price = price;


    return 1;
}

int readMaterialsToProduct(MaterialsArray *ptr_MaterialsArray, ProductsArray *ptr_ProductsArray, int i) {
    char option;
    char *code = malloc(sizeof(char) * 6);
    int quantity;

    listMaterials(ptr_MaterialsArray); //List materials

    do {
        code = calloc(6,sizeof (char));
        readString(code, 6, INSERT_MATERIAL_CODE);  // Inserir codigo Material;
        if (!findMaterialByCode(ptr_MaterialsArray, code)) {
            printf("CODE_DOES_NOT_EXISTS\n");
        }
    } while (!findMaterialByCode(ptr_MaterialsArray, code));

    do {
        quantity = readInteger(0, 9999, INSERT_QUANTITY_SIZE); //Insere quantidade;
        strcpy(ptr_ProductsArray->product[i].productMaterialsArray.materialQuantity[ptr_ProductsArray->product[i].productMaterialsArray.count].code,
               code);
        ptr_ProductsArray->product[i].productMaterialsArray.materialQuantity[ptr_ProductsArray->product[i].productMaterialsArray.count].quantity = quantity;
        ptr_ProductsArray->product[i].productMaterialsArray.count++;

        printf("\nDeseja inserir outro material ao seu produto? Y/N:  ");
        scanf(" %c", &option);

        switch (option) {
            case 'Y':
            case 'y':
                break;
            case 'N':
            case 'n':
                free(code);
                return 1;
            default:
                printf("Insira uma opcao válida!!");
        }
    } while (option != ('n' | 'N'));
    return 1;
}

Product *findProductByCode(ProductsArray *ptr_ProductsArray, char code[]) {
    for (int i = 0; i < ptr_ProductsArray->count; i++) {
        if (ptr_ProductsArray->product[i].code == code) {
            return &ptr_ProductsArray->product[i];
        }
    }
    return NULL;
}

void expandProductsArray(ProductsArray *ptr_ProductsArray) {
    int new_size;

    new_size = ptr_ProductsArray->size * 2;

    ptr_ProductsArray->product = (Product *) realloc(ptr_ProductsArray->product, new_size * sizeof(Product));
    if (ptr_ProductsArray->product == NULL) {
        printf("Not allocated\n");
        exit(EXIT_FAILURE);
    }

    ptr_ProductsArray->size = new_size;

    for (int i = ptr_ProductsArray->count; i < new_size; i++) {
        strcpy(ptr_ProductsArray->product[i].name, (char *) calloc(256, sizeof(char)));
        strcpy(ptr_ProductsArray->product[i].code, (char *) calloc(64, sizeof(char)));
        strcpy(ptr_ProductsArray->product[i].dimensions, (char *) calloc(11, sizeof(char)));
        ptr_ProductsArray->product[i].price = 0;
        //Talvez falte para os Materiais;
    }
}

ProductsArray *allocMemoryProducts(int productSize, int materialSize) {

    ProductsArray *ptr_ProductsArray = (ProductsArray *) malloc(sizeof(ProductsArray));
    if (ptr_ProductsArray == NULL) {
        perror("Erro ao alocar emoria para ProductsArray");
        return NULL;
    }

    ptr_ProductsArray->count = 0;
    ptr_ProductsArray->size = productSize;

    ptr_ProductsArray->product = (Product *) malloc(sizeof(Product) * ptr_ProductsArray->size);
    if (ptr_ProductsArray->product == NULL) {
        perror("Erro ao alocar emoria para Products");
        return NULL;
    }

    ptr_ProductsArray->product->productMaterialsArray.materialQuantity =
            (MaterialQuantity *) malloc(sizeof(MaterialQuantity) * ptr_ProductsArray->size);
    if (ptr_ProductsArray->product->productMaterialsArray.materialQuantity == NULL) {
        perror("Erro ao alocar emoria para MaterialQuantity");
        return NULL;
    }

    for (int i = 0; i < ptr_ProductsArray->size; i++) {
        ptr_ProductsArray->product[i].removed = 0;
        ptr_ProductsArray->product[i].price = 0.00;
    }

    MaterialQuantity *materialQuantity = malloc(sizeof(MaterialQuantity) * materialSize);
    if (ptr_ProductsArray->product->productMaterialsArray.materialQuantity == NULL) {
        perror("Erro ao alocar emoria para MaterialQuantity");
        return NULL;
    }

    for (int i = 0; i < ptr_ProductsArray->size; i++) {
        ptr_ProductsArray->product[i].productMaterialsArray.materialQuantity = materialQuantity;
        ptr_ProductsArray->product[i].productMaterialsArray.count = 0;
        ptr_ProductsArray->product[i].productMaterialsArray.size = materialSize;
    }


    return ptr_ProductsArray;
}


void freeMemoryProducts(ProductsArray *ptr_ProductsArray) {
    free(ptr_ProductsArray->product[0].productMaterialsArray.materialQuantity);
    free(ptr_ProductsArray->product);
    free(ptr_ProductsArray);
}

int addProduct(MaterialsArray *ptr_MaterialsArray, ProductsArray *ptr_ProductsArray,
               ProductMaterialsArray *ptr_ProductMaterial) {

    if (ptr_ProductsArray == NULL) {
        return 0;
    }

    if (ptr_ProductsArray->count == ptr_ProductsArray->size) {
        expandProductsArray(ptr_ProductsArray);
    }

    if (readProduct(ptr_MaterialsArray, ptr_ProductsArray, ptr_ProductMaterial, ptr_ProductsArray->count) != 1) {
        return 0;
    }

    ptr_ProductsArray->count++;

    return 1;
}

int addMaterialsToProduct(ProductMaterialsArray *ptr_ProductMaterialsArray, MaterialsArray *ptr_MaterialsArray,
                          ProductsArray *ptr_ProductsArray, int i) {
    //char material_code;

    if (ptr_ProductMaterialsArray == NULL) {
        return 0;
    }

    if (ptr_ProductMaterialsArray->count == ptr_ProductMaterialsArray->size) {
        expandProductsMaterialsArray(ptr_ProductMaterialsArray);
    }

    if (readMaterialsToProduct(ptr_MaterialsArray, ptr_ProductsArray, i)) {
        return 0;
    }

    ptr_ProductsArray->product[i].productMaterialsArray.count++;

    return 1;
}

int removeProduct(ProductsArray *ptr_ProductsArray, char code[]) {
    int position = -1;
    for (int i = 0; i < ptr_ProductsArray->count; i++) {
        if (ptr_ProductsArray->product[i].code == code) {
            position = i;
        }
    }

    if (position == -1) {
        return 1;
    }

    for (int i = position; i < ptr_ProductsArray->count; i++) {
        ptr_ProductsArray->product[i] = ptr_ProductsArray->product[i + 1];
    }

    free(ptr_ProductsArray->product[ptr_ProductsArray->count - 1].name);
    strcpy(ptr_ProductsArray->product[ptr_ProductsArray->count - 1].name, (char *) calloc(64, sizeof(char)));
    strcpy(ptr_ProductsArray->product[ptr_ProductsArray->count - 1].code, (char *) calloc(64, sizeof(char)));
    strcpy(ptr_ProductsArray->product[ptr_ProductsArray->count - 1].dimensions, (char *) calloc(64, sizeof(char)));
    ptr_ProductsArray->product[ptr_ProductsArray->count - 1].price = 0;


    //ptr_ProductsArray->product->productMaterialsArray->productMaterials->countMaterial--;
    ptr_ProductsArray->count--;

    printf(PRODUCT_REMOVED_OUTPUT"\n");
    return 0;
}

int updateProduct(MaterialsArray *ptr_MaterialsArray, ProductsArray *ptr_ProductsArray,
                  ProductMaterialsArray *ptr_ProductMaterial, char code[]) {
    for (int i = 0; i < ptr_ProductsArray->count; i++) {
        /*if (strcmp(ptr_ProductsArray->product[i].code, code) == 0) {
            return readProduct(ptr_MaterialsArray, ptr_ProductMaterialsArray, ptr_ProductsArray, i);
        }*/
        if (ptr_ProductsArray->product[i].code == code) {
            return readProduct(ptr_MaterialsArray, ptr_ProductsArray, ptr_ProductMaterial, i);
        }
    }

    return 0;
}

void listProducts(ProductsArray *ptr_ProductsArray) {
    for (int i = 0; i < ptr_ProductsArray->count; i++) {
        printProducts(&ptr_ProductsArray->product[i]);
    }
}

void productsListCanceled(ProductsArray *ptr_ProductsArray) {
    if (ptr_ProductsArray->count == 0) {
        printf("Vazio\n");
        return;
    }

    for (int i = 0; i < ptr_ProductsArray->count; i++) {
        if (ptr_ProductsArray->product[i].removed == 1) {
            printProducts(&ptr_ProductsArray->product[i]);
        }
    }
}

void printProducts(const Product *ptr_Product) {

    printf("\n----\n");
    printf("Código do Produto: %s\n", ptr_Product->code);
    printf("Nome do Produto: %s\n", ptr_Product->name);
    printf("Dimensoes do produto: %s\n", ptr_Product->dimensions);
    printf("Preço do Produto %.2f\n", ptr_Product->price);

    for (int j = 0; j < ptr_Product->productMaterialsArray.count; j++) {
        printf("\n----");
        printf("\nCódigo do Material: %s", ptr_Product->productMaterialsArray.materialQuantity[j].code);
        printf("\nQuantidade :%d", ptr_Product->productMaterialsArray.materialQuantity[j].quantity);
        printf("\n----");
    }
}

//Verificar no Futuro
int emptyList(const ProductsArray *ptr_ProductsArray) {
    if (ptr_ProductsArray->count == 0) {
        printf("\nNão existem produtos a listar");
        return 1;
    }
    return 0;
}


///FUNÇÕES PARA MATERIAIS DO PRODUTO

void expandProductsMaterialsArray(ProductMaterialsArray *ptr_ProductMaterialsArray) {
    int new_size;

    new_size = ptr_ProductMaterialsArray->size * 2;

    ptr_ProductMaterialsArray->materialQuantity = (MaterialQuantity *) realloc(
            ptr_ProductMaterialsArray->materialQuantity, new_size * sizeof(MaterialQuantity));
    if (ptr_ProductMaterialsArray->materialQuantity == NULL) {
        printf("Not allocated\n");
        exit(EXIT_FAILURE);
    }

    ptr_ProductMaterialsArray->size = new_size;

    for (int i = ptr_ProductMaterialsArray->count; i < new_size; i++) {
        strcpy(ptr_ProductMaterialsArray->materialQuantity[i].code, (char *) calloc(64, sizeof(char)));
        ptr_ProductMaterialsArray->materialQuantity[i].quantity = 0;
    }
}

ProductMaterialsArray *allocMemoryProductMaterials() {

    ProductMaterialsArray *ptr_ProductMaterialsArray = (ProductMaterialsArray *) malloc(sizeof(ProductMaterialsArray));
    if (ptr_ProductMaterialsArray == NULL) {
        return NULL;
    }

    ptr_ProductMaterialsArray->count = 0;
    ptr_ProductMaterialsArray->size = 20;

    ptr_ProductMaterialsArray->materialQuantity = (MaterialQuantity *) calloc(ptr_ProductMaterialsArray->size,
                                                                              sizeof(MaterialQuantity));
    if (ptr_ProductMaterialsArray->materialQuantity == NULL) {
        return NULL;
    }

    for (int i = 0; i < ptr_ProductMaterialsArray->size; i++) {
        strcpy(ptr_ProductMaterialsArray->materialQuantity[ptr_ProductMaterialsArray->count].code,
               (char *) calloc(6, sizeof(char)));
        ptr_ProductMaterialsArray->materialQuantity[ptr_ProductMaterialsArray->count].quantity = 0;
    }
    return ptr_ProductMaterialsArray;
}

void freeMemoryProductMaterials(ProductMaterialsArray *ptr_ProductMaterialsArray) {
    for (int i = 0; i < ptr_ProductMaterialsArray->size; i++) {
        free(ptr_ProductMaterialsArray->materialQuantity[i].code);
    }

    free(ptr_ProductMaterialsArray->materialQuantity);
    free(ptr_ProductMaterialsArray);
}