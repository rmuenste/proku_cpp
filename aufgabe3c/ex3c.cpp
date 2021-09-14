#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <ex_assert.hpp>
#include <string>
#include <limits>


namespace ex {


};

using namespace ex;

int main(int argc, char *argv[]) {

    ex_HEADLINE("EX3C");
    ex_EMPTY_LINE(2);
    if (argc > 4) {
        std::cout << argv[0] << " " << argv[1] << " " << argv[2] << " " << argv[3] << " " << argv[4]  << std::endl;
    }
    else {
        std::cout << "Not enough command line arguments provided." << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
