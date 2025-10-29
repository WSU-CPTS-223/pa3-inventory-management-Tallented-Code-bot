#ifndef TEST_H
#define TEST_H
#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <exception>
#include <typeinfo>
#include <stdexcept>


// A couple of functions for colored text using ANSI codes
inline std::string red(std::string text){
    return "\x1B[31m" + text + "\033[0m\t\t";
}
inline std::string green(std::string text){
    return "\x1B[32m" + text + "\033[0m\t\t";
}



// A basic test macro to make it easier to write tests.
// It also registers the test to be run automatically in main.
#define TEST(name, ...)\
    inline std::string name(){\
        std::cout << "Running test " << __FILE__ << "::" << __func__ << " ... "; \
        try{\
            __VA_ARGS__ \
        }catch(const std::exception &e){\
            std::cout << red("FAILED") << std::endl;\
            std::stringstream s;\
            s << "ERROR: Exception thrown in " << __FILE__ << ", line " << __LINE__ << std::endl;\
            s << e.what() << std::endl;\
            return s.str();\
        }\
        std::cout << green("ok") << std::endl;\
        return ""; \
    }\
    static bool name##_registered = [](){\
        TestRegistry::getInstance().registerTest(name, #name); \
        return true; \
    }();


// This redefines the `assert` macro from <cassert>, to report the error for later.
#ifdef assert
#undef assert
#endif
#define assert(condition)\
    do{\
        if(!(condition)){\
            std::cout << red("FAILED") << std::endl;\
            std::stringstream s; \
            s << "ERROR: Assertion failed (`" << #condition << "`)" << " in " << __FILE__ << ", line " << __LINE__ << std::endl;\
            return s.str();\
        }\
    }while(0)

// Assert that two value are equal; if not, the test fails.
#define assert_eq(left, right)\
    do{\
        if(left != right){\
            std::cout << red("FAILED") << std::endl;\
            std::stringstream s; \
            s << "ERROR: Assertion failed (`" << #left << " == " << #right << "`) (left is " << left << ", right is " << right << "), in " << __FILE__ << ", line " << __LINE__ << std::endl; \
            return s.str();\
        }\
    }while(0)

// A class to register tests in, which will then be run.
// It also keeps track of test passes and fails.
class TestRegistry{
    public:
    using TestFunction = std::string(*)();

    static TestRegistry& getInstance(){
        static TestRegistry instance;
        return instance;
    }

    void registerTest(TestFunction testFunc, std::string testName){
        tests.push_back(testFunc);
        testNames.push_back(testName);
    }

    void runTests(){
        for (auto& test: tests){
            std::string passed =  test();
            passes.push_back(passed);
        }
    }

    std::vector<std::string> passes;
    std::vector<std::string> testNames;
    private:
    TestRegistry() = default;
    std::vector<TestFunction> tests;
};


// The main test runner function.
inline void test_all(){
    std::cout << "===========================" << std::endl;
    std::cout << "Running all tests..." << std::endl;
    std::cout << "===========================" << std::endl;
    std::cout << std::endl;


    // Actually run all the tests
    TestRegistry::getInstance().runTests();

    std::cout << std::endl;
    std::cout << std::endl;

    // loop over all tests and figure out how many tests passed and failed.
    int passed = 0;
    int failed = 0;

    for(unsigned long i = 0; i < TestRegistry::getInstance().testNames.size(); i++){
        if(TestRegistry::getInstance().passes[i] == ""){ // empty string means test passed
            passed += 1;
        }else{
            failed += 1;
        }
    }

    // print statistics
    std::cout << "Test results: " << passed << " passed, " << failed << " failed, " << passed + failed << " total." << std::endl;

    // show errors for failed tests
    if(failed > 0){
        std::cout << std::endl;
        std::cout << "Failures:" << std::endl;

        for(unsigned long i = 0; i < TestRegistry::getInstance().testNames.size(); i++){
            if(TestRegistry::getInstance().passes[i] != ""){
                std::cout << "In test " <<  TestRegistry::getInstance().testNames[i] << ":" << std::endl;
                std::cout << TestRegistry::getInstance().passes[i] << std::endl;
            }
        }
    }

}

#endif
