#ifndef LP_G14_MATERIALS_H
#define LP_G14_MATERIALS_H
#include "utils.h"
enum UNIT_TYPE {
    UN = 0,
    PAIR = 1,
};
typedef struct {
    char code[6];    //codigo de materiais
    int quantity;   //quantidade de material
} MaterialQuantity;

typedef struct {
    MaterialQuantity *materialQuantity;
    int size;
    int count;
} ProductMaterialsArray;  //Lista de Produtos/Materiais

typedef struct {
    char code[6];
    char description[256];
    enum UNIT_TYPE type;
} Material;

typedef struct {
    Material *materials;
    int count;           // Representa o espaço total ocupado e a posição livre
    int size;            // Tamanho total do array
} MaterialsArray;

/**
 * @param ptr_MaterialsArray
 * @param code
 * @return
 */
Material *findMaterialByCode(MaterialsArray *ptr_MaterialsArray, char code[]);

/**
 * @param ptr_MaterialsArray
 * @param i
 * @return "sucess"
 */
int readMaterial(MaterialsArray *ptr_MaterialsArray, int i);

/**
 * Aloca memória para um array de artigos.
 * @return um array de artigos.
 */
MaterialsArray *allocMemoryMaterials();

/**
 * Função para libertar a memória do array de artigos.
 * @param ptr_MaterialsArray
 */
void freeMemoryMaterials(MaterialsArray *ptr_MaterialsArray);

/**
* Expande o array de Materiais.
* @param ptr_MaterialsArray
*/
void expandMaterialsArray(MaterialsArray *ptr_MaterialsArray);

/**
 * Adiciona um artigo ao array de artigos.
 * @return 1 se adicionado com sucesso, caso-contrário 0.
 */
int addMaterial(MaterialsArray *ptr_MaterialsArray);

/**
 *Procura o artigo pelo código e remove-o.
 * @param code código do artigo.
 * @return 1 se removido com sucesso, caso-contrário 0.
 */
int removeMaterial(MaterialsArray *ptr_MaterialsArray, char *code[]);

/**
 * Procura o artigo pelo código e atualiza as informações do artigo.
 * @param code código do artigo.
 * @return 1 se atualizado com sucesso, caso-contrário 0.
 */
int updateMaterial(MaterialsArray *ptr_MaterialsArray, char *code[]);

/**
 *Função utilizada para imprimir toda a informação de um material.
 * @param material
 */
void printMaterials(const Material *material);

/**
 * Itera o array de artigos.
 * @param materialsArray
 */
void listMaterials(MaterialsArray *materialsArray);

/**
 * Itera o array de artigos cancelados.
 * @param materialsArray
 */
void materialsListCanceled(MaterialsArray *ptr_MaterialsArray);

#endif //LP_G14_MATERIALS_H