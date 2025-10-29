#ifndef PARSE_CSV_H
#define PARSE_CSV_H

#include <vector>
#include <string>
#include "product.h"


std::vector<std::string> parseCsvLine(std::string line);

Product parseCsvLineToProduct(std::string line);

std::vector<Product> parseProductsFile(std::string filename);


#endif
