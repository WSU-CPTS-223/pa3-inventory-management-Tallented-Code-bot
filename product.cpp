#include "product.h"





void ProductsStructure::insert(Product p){
    products.push_back(p);
    index.insert(p.id, products.size() - 1);
}


Product ProductsStructure::get(std::string id){
    int i = index.get(id);
    return products[i];
}
