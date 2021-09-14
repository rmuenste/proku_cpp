#include "ggt.hpp"
#include <cmath>

namespace ex {

int ggT(int a, int b)
{
    if (a == 0) {
        return b;
    }

    while (b != 0) {
        int aux = a % b;
        a = b;
        b = aux;
    }
    return std::abs(a);
}

};

