#ifndef PRODUCT_H
#define PRODUCT_H


#include <string>
#include <vector>
#include "hashTable.h"

// The number of fields in the product struct.
const int NUM_FIELDS = 16;
struct Product{
    std::string id;
    std::string product_name;
    std::string category;
    std::string upc_ean_code;
    std::string selling_price;
    std::string model_number;
    std::string about_product;
    std::string product_specification;
    std::string technical_details;
    std::string shipping_weight;
    std::string product_dimensions;
    std::string image;
    std::string variants;
    std::string sku;
    std::string product_url;
    std::string is_amazon_seller;
};

// The class to hold all the products.
class ProductsStructure {
    std::vector<Product> products;
    HashTable<std::string, int> index;

    public:
    void insert(Product p);
    Product get(std::string id);

};




#endif
