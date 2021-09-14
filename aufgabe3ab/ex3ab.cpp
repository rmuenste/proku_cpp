#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <ex_assert.hpp>
#include <string>
#include <limits>
#include <aufgabe3ab/ggt.hpp>
#include <aufgabe3ab/kgv.hpp>

inline void exGGT(int a, int b) {

    int exGGT = ex::ggT(a, b);
    std::cout << "Der ggT von " << a << " und " << b << " ist " << exGGT << "." << std::endl;

}

inline void exKGV(int a, int b) {

    int exKGV = ex::kgV(a, b);
    std::cout << "Das kgV von " << a << " und " << b << " ist " << exKGV << "." << std::endl;

}

int main(int argc, char *argv[]) {

    ex_HEADLINE("EX3A");
    ex_EMPTY_LINE(2);

    exGGT(3, 17);
    ex_EMPTY_LINE(2);
    exGGT(12, -18);
    ex_EMPTY_LINE(2);
    exGGT(-70, 42);
    ex_EMPTY_LINE(2);
    exGGT(-24, -96);
    ex_EMPTY_LINE(2);
    exGGT(0, 1);
    ex_EMPTY_LINE(2);
    exGGT(0, 0);
    ex_EMPTY_LINE(2);

    ex_HEADLINE("EX3B");
    ex_EMPTY_LINE(2);
    exKGV(3, 4);
    ex_EMPTY_LINE(2);
    exKGV(6, -13);
    ex_EMPTY_LINE(2);
    exKGV(-8, 24);
    ex_EMPTY_LINE(2);
    exKGV(-7, -17);
    ex_EMPTY_LINE(2);
    exKGV(0, 1);
    ex_EMPTY_LINE(2);
    exKGV(0, 0);
    
    return EXIT_SUCCESS;
}
