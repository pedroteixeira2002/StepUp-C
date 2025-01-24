#ifndef LP_G14_MENUS_H
#define LP_G14_MENUS_H
#include "orders.h"
#include "clients.h"
#include "products.h"
#include "strs.h"

int menusBuilder(const char *menu_msg, const char *input_msg, int min_op, int max_op);

int mainMenu ();

void menuAdmin(ClientsArray *ptr_ClientsArray, ProductsArray *ptr_ProductsArray, MaterialsArray *ptr_MaterialsArray, ProductMaterialsArray *ptr_ProductMaterialsArray);

void clientsManagement(ClientsArray *ptr_ClientsArray, ProductsArray *ptr_ProductsArray, MaterialsArray *ptr_MaterialsArray, ProductMaterialsArray *ptr_ProductMaterialsArray);

void productManagement(ClientsArray *ptr_ClientsArray, ProductsArray *ptr_ProductsArray, MaterialsArray *ptr_MaterialsArray, ProductMaterialsArray *ptr_ProductMaterialsArray);

void materialManagement (ClientsArray *ptr_ClientsArray, ProductsArray *ptr_ProductsArray, MaterialsArray *ptr_MaterialsArray, ProductMaterialsArray *ptr_ProductMaterialsArray);

void menuClient(OrdersArray *ptr_OrdersArray, ClientsArray *ptr_ClientsArray, ProductsArray *ptr_ProductsArray, ProductMaterialsArray *ptr_ProductMaterialsArray);

#endif //LP_G14_MENUS_H