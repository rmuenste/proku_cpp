#include "ggt.hpp"
#include <cmath>

namespace ex {

int ggT(int a, int b)
{

    if (a < 0)
        a = -a;

    if (b < 0)
        b = -b;

    while (b != 0) {
        int aux = a % b;
        a = b;
        b = aux;
    }

    return a;
}

};

