#ifndef LP_G14_PRODUCTS_H
#define LP_G14_PRODUCTS_H
#include "utils.h"
#include "materials.h"

typedef struct {
    char code[6];        //Done
    char name[256];      //Done
    char dimensions[11]; // Array inteiro ou char
    float price;         //Done
    int removed;         //Para alterar o estado do Produto/Inativo
    ProductMaterialsArray productMaterialsArray;  //Lista de Materiais para cada produto
} Product;

typedef struct {
    Product *product;
    int count; // Representa o espaço total ocupado e a posição livre
    int size; // Tamanho total do array
} ProductsArray;

/**
 * @param ptr_ProductsArray
 * @param code
 * @return
 */
Product *findProductByCode(ProductsArray *ptr_ProductsArray, char code[]);

/**
 *Função utilizada para inserir materiais num produto.
 * @param ptr_MaterialsArray,ptr_ProductsArray
 */
int readMaterialsToProduct(MaterialsArray *ptr_MaterialsArray, ProductsArray *ptr_ProductsArray, int i);

/**
 *Função utilizada para inserir ler as informações de um produto.
 * @param ptr_MaterialsArray,ptr_ProductsArray
 */
int readProduct(MaterialsArray *ptr_MaterialsArray, ProductsArray *ptr_ProductsArray,ProductMaterialsArray *ptr_ProductMaterial, int i);


/**
* Expande o array de Produtos.
* @param ptr_MaterialsArray
*/
void expandProductsArray(ProductsArray *ptr_ProductsArray);

/**
 * Aloca memória para um array de artigos.
 * @return um array de artigos.
 */
ProductsArray *allocMemoryProducts(int productSize, int materialSize);

/**
 * Função para libertar a memória do array de artigos.
 * @param ptr_ProductsArray
 */
void freeMemoryProducts(ProductsArray *ptr_ProductsArray);

/**
 * Adiciona um artigo ao array de artigos.
 * @return 1 se adicionado com sucesso, caso-contrário 0.
 */
int addProduct(MaterialsArray *ptr_MaterialsArray, ProductsArray *ptr_ProductsArray, ProductMaterialsArray *ptr_ProductMaterial);

/**
 * Adiciona um maerial ao produto.
 * @return 1 se adicionado com sucesso, caso-contrário 0.
 */
int addMaterialsToProduct(ProductMaterialsArray *ptr_ProductMaterialsArray, MaterialsArray *ptr_MaterialsArray,
                          ProductsArray *ptr_ProductsArray,int i);

/**
 *Procura o artigo pelo código e remove-o.
 * @param code código do artigo.
 * @return 1 se removido com sucesso, caso-contrário 0.
 */
int removeProduct(ProductsArray *ptr_ProductsArray, char code[6]);

/**
 * Procura o artigo pelo código e atualiza as informações do artigo.
 * @param code código do artigo.
 * @return 1 se atualizado com sucesso, caso-contrário 0.
 */
int updateProduct(MaterialsArray *ptr_MaterialsArray, ProductsArray *ptr_ProductsArray,ProductMaterialsArray *ptr_ProductMaterial,char code[]);

/**
 *Função utilizada para imprimir toda a informação de um artigo.
 * @param Product
 */
void printProducts(const Product *ptr_Product);

/**
 * Itera o array de artigos.
 * @param ptr_ProductsArray
 */
void listProducts(ProductsArray *ptr_ProductsArray);

/**
 * Itera o array de artigos cancelados.
 * @param materialsArray
 */
void productsListCanceled(ProductsArray *ptr_ProductsArray);

///FUNÇÕES PARA MATERIAIS DO PRODUTO

/**
* Aloca memória para um array de artigos.
* @return um array de artigos.
*/
void expandProductsMaterialsArray(ProductMaterialsArray *ptr_ProductMaterialsArray);

/**
 * Aloca memória para um array de artigos.
 * @return um array de artigos.
 */
ProductMaterialsArray *allocMemoryProductMaterials();

/**
 * Função para libertar a memória do array de artigos.
 * @param ptr_ProductsArray
 */
void freeMemoryProductMaterials(ProductMaterialsArray *ptr_ProductMaterialsArray);
#endif //LP_G14_PRODUCTS_H

