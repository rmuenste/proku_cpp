#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <ex_assert.hpp>
#include <string>
#include <limits>


namespace ex {

    int ex2a() {

        int a, b;
        char op;
        std::cout << "Geben Sie einen Ausdruck der Form: a + b<return> ein." << std::endl;

        std::cin >> a >> op >> b;

        if (std::cin.fail()) {

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Error: invalid input." << std::endl;
            std::exit(EXIT_FAILURE);
        }

        switch (op) {
        case '+':
            std::cout << a << " + " << b << " = " << (a + b) << std::endl;
            break;
        case '-':
            std::cout << a << " - " << b << " = " << (a - b) << std::endl;
            break;
        case '*':
            std::cout << a << " * " << b << " = " << (a * b) << std::endl;
            break;
        case '/':
            std::cout << a << " / " << b << " = " << (a / b) << std::endl;
            break;
        case '%':
            std::cout << a << " % " << b << " = " << (a % b) << std::endl;
            break;
        default:
            std::cout << "Error: unknown operator." << std::endl;
            break;
        }

    }

};

using namespace ex;

int main(int argc, char *argv[]) {

    ex_HEADLINE("EX1A");
    ex_EMPTY_LINE(2);
    ex2a();

    return EXIT_SUCCESS;
}
