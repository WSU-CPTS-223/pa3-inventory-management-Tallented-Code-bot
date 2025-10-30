#include "product.h"
#include "test.h"
#include <ostream>

// Const-correct equality operator matching the declaration in the header.
bool Product::operator==(const Product& other) const {
    return this->id == other.id
        && this->product_name == other.product_name
        && this->category == other.category
        && this->upc_ean_code == other.upc_ean_code
        && this->selling_price == other.selling_price
        && this->model_number == other.model_number
        && this->about_product == other.about_product
        && this->product_specification == other.product_specification
        && this->technical_details == other.technical_details
        && this->shipping_weight == other.shipping_weight
        && this->product_dimensions == other.product_dimensions
        && this->image == other.image
        && this->variants == other.variants
        && this->sku == other.sku
        && this->product_url == other.product_url
        && this->is_amazon_seller == other.is_amazon_seller;
}

// Non-member stream insertion operator (declared as friend in the header).
std::ostream& operator<<(std::ostream& os, const Product& p) {
    return os << p.id << std::endl
              << p.product_name << std::endl
              << p.category << std::endl
              << p.upc_ean_code << std::endl
              << p.selling_price << std::endl
              << p.model_number << std::endl
              << p.about_product << std::endl
              << p.product_specification << std::endl
              << p.technical_details << std::endl
              << p.shipping_weight << std::endl
              << p.product_dimensions << std::endl
              << p.image << std::endl
              << p.variants << std::endl
              << p.sku << std::endl
              << p.product_url << std::endl
              << p.is_amazon_seller << std::endl;
}

void ProductsStructure::insert(Product p){
    products.push_back(p);
    index.insert(p.id, products.size() - 1);
}

Product ProductsStructure::get(std::string id){
    int i = index.get(id);
    return products[i];
}


std::vector<Product> ProductsStructure::findAllInCategory(std::string category){
    std::vector<Product> output;
    for(Product p : products){
        if(p.category.find(category) != std::string::npos){
            output.push_back(p);
        }
    }

    return output;
}

TEST(testInsertToProductStorage, {
    ProductsStructure allProducts;

    Product p;
    p.id = "helloworld";
    p.product_name = "Test product";
    p.about_product = "This is a test product, to see if things are working.";
    allProducts.insert(p);

    Product q = allProducts.get(p.id);
    assert_eq(p,q);
})
