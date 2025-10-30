#include <iostream>
#include <string>
#include <vector>
#include "bpTree.h"
#include "parseCsv.h"
#include "product.h"

using namespace std;

void printHelp() {
  cout << "Supported list of commands: " << endl;
  cout << " 1. find <inventoryid> - Finds if the inventory exists. If exists, "
          "prints details. If not, prints 'Inventory not found'."
       << endl;
  cout << " 2. listInventory <category_string> - Lists just the id and name of "
          "all inventory belonging to the specified category. If the category "
          "doesn't exists, prints 'Invalid Category'.\n"
       << endl;
  cout << " Use :quit to quit the REPL" << endl;
}

bool validCommand(string line) {
  return (line == ":help") || (line.rfind("find", 0) == 0) ||
         (line.rfind("listInventory") == 0);
}

void evalCommand(string line, ProductsStructure& allProducts) {
  if (line == ":help") {
    printHelp();
    return;
  }

  stringstream s(line);

  string command;
  s >> command;

  if(command == "find"){
      string id;
      s >> id;

      cout << "Finding items matching id " << id << "." << endl;

      Product p = allProducts.get(id);
      cout << p.product_name << ", for " << p.selling_price << " at " << p.product_url << endl;
  }else if (command == "listInventory"){
      string category;
      s >> category;

      vector<Product> products = allProducts.findAllInCategory(category);

      cout << "Finding items in category " << category << "." << endl;

      for(Product p : products){
          cout << "ID: " << p.id << ", Name: " << p.product_name << endl;
      }
  }

}

void bootStrap() {
  cout << "\n Welcome to Amazon Inventory Query System" << endl;
  cout << " enter :quit to exit. or :help to list supported commands." << endl;
  cout << "\n> ";
}

int main(int argc, char const *argv[]) {
  string line;
  bootStrap();

  ProductsStructure allProducts = parseProductsFile("marketing_dataset.csv");

  while (getline(cin, line) && line != ":quit") {
    if (validCommand(line)) {
      evalCommand(line, allProducts);
    } else {
      cout
          << "Command not supported. Enter :help for list of supported commands"
          << endl;
    }
    cout << "> ";
  }
  return 0;
}
