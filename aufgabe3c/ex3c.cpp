#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <ex_assert.hpp>
#include <string>
#include <limits>
#include <cassert>

namespace ex {

    int processInput(const char* inp) {

//   Reminder:
//      const char * str = "Hello World !";
//      int Size = 0;
//      while (str[Size] != '\0') Size++;
//      return Size;

        assert(inp != nullptr);

        bool neg = false;

        int d = 0, m = 0, p = 0, n = 0;

        int i = 0;

        for (; inp[i] != '\0'; ++i) {

            if ((inp[i] >= '0') && (inp[i] <= '9')) {
                char c = inp[i];
                int number = c - 48;
                (d *= 10) += number;
                continue;
            }

            if (inp[i] == '.') {
                ++i;
                break;
            }

            return i + 1;
        }


        for (; inp[i] != '\0'; ++i) {

            if ((inp[i] >= '0') && (inp[i] <= '9')) {
                char c = inp[i];
                int number = c - 48;
                (d *= 10) += number;
                ++m;
                continue;
            }

            if ((inp[i] == 'p') || (inp[i] == 'P')) {
                ++i;
                break;
            }

            return i + 1;
        }



        for (; inp[i] != '\0'; ++i) {

            if ((inp[i] >= '0') && (inp[i] <= '9')) {
                char c = inp[i];
                int number = c - 48;
                (p *= 10) += number;
                ++n;
                continue;
            }
            return i + 1;
        }

        std::cout << "d: " << d << std::endl;
        std::cout << "m: " << m << std::endl;
        std::cout << "p: " << p << std::endl;
        std::cout << "n: " << n << std::endl;

        return 0;

    }

};

using namespace ex;

int main(int argc, char *argv[]) {

    ex_HEADLINE("EX3C");
    ex_EMPTY_LINE(2);

    if (argc < 2) {
        std::cout << "Not enough command line arguments provided." << std::endl;
        return EXIT_FAILURE;
    }

    for (int i(1); i < argc; ++i) {
        processInput(argv[i]);
    }


    return EXIT_SUCCESS;
}
