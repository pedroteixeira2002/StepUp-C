#ifndef LP_G14_UTILS_H
#define LP_G14_UTILS_H

#define MAX_NAME_LEN  50

//Mensagem para inserir o tipo de utilizador.
#define INSERT_PROFILE "Insira o tipo de utilizador:"

//Mensagens utilizadas para avisar números repetidos.
#define INVALID_VALUE "O valor inserido é inválido."
#define CODE_EXISTS "O código já existe!"
#define NIF_EXISTS "O nif já existe!"
#define INSERT_OPTION "Insira a opção que deseja:"

//Mensagens utilizadas para os produtos.
#define INSERT_PRODUCT_CODE "Insira o código do artigo:"
#define INSERT_PRODUCT_NAME "Insira um nome para o artigo:"
#define INSERT_PRODUCT_DIMENSIONS "Insira as dimensões do produto:(comprimento x altura x profundidade): "
#define INSERT_PRODUCT_TYPE "Tipo do produto: PAR = 1, UNIDADE = 2 :  "
#define ADD_NEW_MATERIAL_TO_PRODUCT "Material inexistente.\nPretende adicionar um novo material ao sistema?: 0-Não...........1-Sim"
#define CODE_INPUT_PRODUCT "Código do Artigo:"
#define PRODUCT_REMOVED_OUTPUT "O artigo foi removido!"
#define INSERT_MATERIAL_CODE "Insira o código do material:"
//Mensagens utilizadas para o cliente.
#define INSERT_CLIENT_CODE "Insira o código do cliente:"
#define INSERT_CLIENT_NAME "Insira o nome do cliente:"
#define INSERT_CLIENT_NIF "Insira o nif do cliente:"
#define INSERT_CLIENT_COUNTRY "Insira o país do cliente:"
#define INSERT_CLIENT_ADDRESS "Insira a morada do cliente:"

//Mensagens utilizadas para as encomendas.
#define INSERT_ORDER_CODE "Insira o código da encomenda:"
#define INSERT_BILLING_ADDRESS_ORDER "Insira a morada de faturação:"
#define INSERT_EXPEDITION_ADDRESS_ORDER "Insira a morada de envio:"
#define INSERT_QUANTITY_SIZE "Insira o quantidade do artigo: "
#define INSERT_OPTION_BUY "Deseja inserir um artigo? "

//Mensagens utilizadas para os custos.
#define INSERT_COSTS_CODE "Insira o código do custo:"
#define INSERT_HAND_WORK_COST "Insira o custo da mão de obra:"
#define INSERT_FIXED_COST_COST "Insira o custo do custo fixo:"
#define INSERT_TYPE_SHOE "Insira o tipo de calçado (Sapato = 0, Sandalias = 1, Botas = 2):"
#define INSERT_MARGIN_COST "Insira o custo da margem:"
#define INSERT_FOOTWEAR_SIZE "Insira o tamanho do calçado:"
#define INSERT_PRICE_PRODUCT "Insira o preço do produto:"

/**
 * Função utilizada para ler caracteres.
 * @param msg
 * @return o caracter.
 */
char readChar(char *msg);

/**
 * Função utilizada para ler inteiros.
 * @param minValor
 * @param maxValor
 * @param msg
 * @return o valor inteiro.
 */
int readInteger(int minValor, int maxValor, const char *msg);

/**
 * Função utilizada para ler float.
 * @param minValor
 * @param maxValor
 * @param msg
 * @return o valor em float
 */
float readFloat(float minValor, float maxValor, char *msg);

/**
 * Função utilizada para ler um array de caracteres.
 * @param string
 * @param tamanho
 * @param msg
 */
void readString(char *string, int tamanho, char *msg);


#endif //LP_G14_UTILS_H
