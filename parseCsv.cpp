#include "parseCsv.h"
#include "product.h"
#include "test.h"
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

vector<string> parseCsvLine(string line){
    vector<string> output;

    string entry;


    bool inQuotes = false; // Whether we are currently in a quoted entry
    bool prevCharWasQuote = false; // Whether the previous character was a quote; used to recognize escaped quotes
    bool endOfEntry = false;

    for(char c : line){
        if(c == '"' && !inQuotes && entry.size() == 0){
            inQuotes = true;
            continue;
        }
        if(c == '"' && inQuotes && !prevCharWasQuote){
            prevCharWasQuote = true;
            continue;
        }
        if(prevCharWasQuote){
            if(c == '"'){
                // double quotes are fine, add a quote character to entry
                prevCharWasQuote = false;
                entry.push_back(c);
                continue;
            }else{
                // prev char was the end of the string
                prevCharWasQuote = false;
                inQuotes = false;
                endOfEntry = true;
            }
        }

        if(!inQuotes && c==','){
            output.push_back(entry);
            entry.clear();
            endOfEntry = false;
            continue;
        }

        if(endOfEntry && c!=','){
            std::stringstream s;
            s <<  "invalid CSV, characters after endquote. (character is `" << c << "`), entry so far is `" << entry << "`.";
            throw runtime_error(s.str());
        }

        entry.push_back(c);
    }

    // as long as the string is not empty, push the remaining characters
    if(line.size() > 0){
        output.push_back(entry);
    }

    return output;
}


TEST(testParseBasicCsvLine, {
    string line = "one,two has some words,three,four,five";

    vector<string> output = parseCsvLine(line);

    assert_eq(output.size(), 5);
    assert_eq(output[0], "one");
    assert_eq(output[1], "two has some words");
    assert_eq(output[2], "three");
    assert_eq(output[3], "four");
    assert_eq(output[4], "five");
})

TEST(testParseEmptyCsvLine, {
    string line = "";
    vector<string> output = parseCsvLine(line);

    assert_eq(output.size(), 0);
})


TEST(testParseQuotedCsvLine, {
    string line = R"(one is not quoted,"two is quoted","three has a "" character","four has a "" and , character",)";
    vector<string> output = parseCsvLine(line);

    assert_eq(output.size(), 5);
    assert_eq(output[0], "one is not quoted");
    assert_eq(output[1], "two is quoted");
    assert_eq(output[2], "three has a \" character");
    assert_eq(output[3], "four has a \" and , character");
    assert_eq(output[4], "");
})


// TODO test faulty CSV strings ...


Product parseCsvLineToProduct(string line){
    vector<string> fields = parseCsvLine(line);

    if(fields.size() != NUM_FIELDS){
        stringstream s;
        s << "Wrong number of fields: expected " << NUM_FIELDS << ", found " << fields.size() << ".";
        throw runtime_error(s.str());
    }

    Product product;


    product.id = fields[0];
    product.product_name = fields[1];
    product.category = fields[2];
    product.upc_ean_code = fields[3];
    product.selling_price = fields[4];
    product.model_number = fields[5];
    product.about_product = fields[6];
    product.product_specification = fields[7];
    product.technical_details = fields[8];
    product.shipping_weight = fields[9];
    product.product_dimensions = fields[10];
    product.image = fields[11];
    product.variants = fields[12];
    product.sku = fields[13];
    product.product_url = fields[14];
    product.is_amazon_seller = fields[15];

    return product;
}

TEST(testParseCsvLineToProduct, {
    string line = R"(18018b6bc416dab347b1b7db79994afa,Guillow Airplane Design Studio with Travel Case Building Kit,Toys & Games | Hobbies | Models & Model Kits | Model Kits | Airplane & Jet Kits,,$28.91,142,Make 8 different Planes at one time. | Experiment with different designs and learn about flight. | All contained in Part trays inside an attractive box with carry handle! | Guillow's - your one source for flying toys since 1926. | Made in the USA.,ProductDimensions:3.5x6.2x13inches|ItemWeight:13.4ounces|ShippingWeight:13.4ounces(Viewshippingratesandpolicies)|DomesticShipping:ItemcanbeshippedwithinU.S.|InternationalShipping:ThisitemcanbeshippedtoselectcountriesoutsideoftheU.S.LearnMore|ASIN:B076Y2SNHM|Itemmodelnumber:142|Manufacturerrecommendedage:8yearsandup,"Go to your orders and start the return Select the ship method Ship it! | Go to your orders and start the return Select the ship method Ship it! | 13.4 ounces (View shipping rates and policies) | show up to 2 reviews by default Kit contains parts to let your imagination soar and build flying planes! comes with over 35 parts (balsa wood wings, tails & bodies, plastic propellers and landing gear, rubber motors, etc) to let you build your own unique flying toy designs. Simple to build, easy to fly and hours of fun!",13.4 ounces,,https://images-na.ssl-images-amazon.com/images/I/516UijZMilL.jpg|https://images-na.ssl-images-amazon.com/images/I/51J6y3oM6VL.jpg|https://images-na.ssl-images-amazon.com/images/G/01/x-locale/common/transparent-pixel.jpg,,,https://www.amazon.com/Guillow-Airplane-Design-Studio-Building/dp/B076Y2SNHM,Y)";

    Product p = parseCsvLineToProduct(line);

    assert_eq(p.id, "18018b6bc416dab347b1b7db79994afa");
    assert_eq(p.category, "Toys & Games | Hobbies | Models & Model Kits | Model Kits | Airplane & Jet Kits");
    // could assert more things, looks like it's working though.
})



ProductsStructure parseProductsFile(string filename){
    ProductsStructure products;

    fstream file(filename);

    if(file.is_open()){
        string line;
        while(getline(file, line)){
            Product p = parseCsvLineToProduct(line);
            products.insert(p);
        }
        file.close();
    }

    return products;
}
