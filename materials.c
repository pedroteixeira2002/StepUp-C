#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "materials.h"

Material *findMaterialByCode(MaterialsArray *ptr_MaterialsArray, char code[]) {
    for (int i = 0; i < ptr_MaterialsArray->count; i++) {
        if (strcmp(ptr_MaterialsArray->materials[i].code, code) == 0) {
            return &ptr_MaterialsArray->materials[i];
        }
    }
    return NULL;
}

int readMaterial(MaterialsArray *ptr_MaterialsArray, int i) {
    char code[6];
    char description[256];
    int type;

    readString(code, 6, CODE_INPUT_PRODUCT);
    code[5] = '\0';

    // Check if a Material with the same code already exists in the array
    if (findMaterialByCode(ptr_MaterialsArray, code)) {
        printf(CODE_EXISTS);
        return 0;
    }

    readString(description, 256, INSERT_PRODUCT_NAME);
    type = readInteger(0, 2, INSERT_PRODUCT_TYPE);

    // Copy the data into the appropriate elements of the MaterialsArray
    strcpy(ptr_MaterialsArray->materials[i].code, code);
    strcpy(ptr_MaterialsArray->materials[i].description, description);
    ptr_MaterialsArray->materials[i].type = type;

    return 1;
}

MaterialsArray *allocMemoryMaterials() {
    MaterialsArray *ptr_MaterialsArray = (MaterialsArray *) malloc(sizeof(MaterialsArray));
    if (ptr_MaterialsArray == NULL) {
        printf("Error allocating memory for MaterialsArray\n");
        return NULL;
    }

    ptr_MaterialsArray->count = 0;
    ptr_MaterialsArray->size = 20;

    ptr_MaterialsArray->materials = (Material *) calloc(ptr_MaterialsArray->size, sizeof(Material));
    if (ptr_MaterialsArray->materials == NULL) {
        printf("Error allocating memory for materials\n");
        return NULL;
    }

    for (int i = 0; i < ptr_MaterialsArray->size; i++) {
        //initializing the fields of Material struct
        ptr_MaterialsArray->materials[i].code[0] = '\0';
        ptr_MaterialsArray->materials[i].description[0] = '\0';
        ptr_MaterialsArray->materials[i].type = UN;
    }

    return ptr_MaterialsArray;
}

void freeMemoryMaterials(MaterialsArray *ptr_MaterialsArray) {
    if (ptr_MaterialsArray == NULL) {
        return;
    }
    free(ptr_MaterialsArray->materials);
    free(ptr_MaterialsArray);
}

void expandMaterialsArray(MaterialsArray *ptr_MaterialsArray) {
    int new_size;

    if(ptr_MaterialsArray == NULL){
        printf("Error: MaterialsArray pointer is null\n");
        return;
    }

    new_size = ptr_MaterialsArray->size * 2;

    ptr_MaterialsArray->materials = (Material *) realloc(ptr_MaterialsArray->materials,
                                                         new_size * sizeof(Material));
    if (ptr_MaterialsArray->materials == NULL) {
        printf("Error allocating memory for expanded materials array\n");
        return;
    }

    ptr_MaterialsArray->size = new_size;

    for (int i = ptr_MaterialsArray->count; i < new_size; i++) {
        ptr_MaterialsArray->materials[i].code[0] = '\0';
        ptr_MaterialsArray->materials[i].description[0] = '\0';
        ptr_MaterialsArray->materials[i].type = UN;

    }
}

//Complete
int addMaterial(MaterialsArray *ptr_MaterialsArray) {
    if (ptr_MaterialsArray == NULL) {
        printf("Error: MaterialsArray pointer is null\n");
        return 0;
    }
    if (ptr_MaterialsArray->count == ptr_MaterialsArray->size) {
        expandMaterialsArray(ptr_MaterialsArray);
    }
    if (readMaterial(ptr_MaterialsArray, ptr_MaterialsArray->count) != 1) {
        return 0;
    }
    ptr_MaterialsArray->count++;
    return 1;
}

int removeMaterial(MaterialsArray *ptr_MaterialsArray, char *code[]) {
    int position = -1;
    if (ptr_MaterialsArray == NULL) {
        printf("Error: MaterialsArray pointer is null\n");
        return 1;
    }
    readString(code, 6, INSERT_MATERIAL_CODE);
    for (int i = 0; i < ptr_MaterialsArray->count; i++) {
        if (strcmp(ptr_MaterialsArray->materials[i].code, code) == 0) {
            position = i;
            break;
        }
    }

    if (position == -1) {
        printf("Material not found\n");
        return 1;
    }

    for (int i = position; i < ptr_MaterialsArray->count - 1; i++) {
        ptr_MaterialsArray->materials[i] = ptr_MaterialsArray->materials[i + 1];
    }

    ptr_MaterialsArray->count--;
    printf("Material removed\n");
    return 0;
}

int updateMaterial(MaterialsArray *ptr_MaterialsArray, char *code[]) {
    if (ptr_MaterialsArray == NULL) {
        printf("Error: MaterialsArray pointer is null\n");
        return 0;
    }
    readString(code, 6, INSERT_MATERIAL_CODE);
    for (int i = 0; i < ptr_MaterialsArray->count; i++) {
        if (strcmp(ptr_MaterialsArray->materials[i].code,code) == 0) {
            printf("Material found\n");
            return readMaterial(ptr_MaterialsArray, i);
        }
    }
    printf("Material with code %s not found\n", code);
    return 0;
}

void printMaterials(const Material *material) {
    if (material == NULL) {
        printf("Error: Material pointer is null\n");
        return;
    }
    printf("\n----\n");
    printf("Code: %s\n", material->code);
    printf("Description: %s\n", material->description);
    printf("Type: %d\n", material->type);
    printf("\n----\n");
}

void listMaterials(MaterialsArray *materialsArray) {
    if (materialsArray == NULL) {
        printf("Error: MaterialsArray pointer is null\n");
        return;
    }
    if (materialsArray->count == 0) {
        printf("No materials to list\n");
        return;
    }
    for (int i = 0; i < materialsArray->count; i++) {
        printMaterials(&materialsArray->materials[i]);
    }
}

void materialsListCanceled(MaterialsArray *ptr_MaterialsArray) {
    if (ptr_MaterialsArray == NULL) {
        printf("Error: MaterialsArray pointer is null\n");
        return;
    }
    if (ptr_MaterialsArray->count == 0) {
        printf("Materials list is empty\n");
        return;
    }
}

