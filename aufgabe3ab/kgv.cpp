#include "kgv.hpp"
#include "ggt.hpp"
#include <cmath>

namespace ex {

int kgV(int a, int b)
{
    if (a == 0 && b == 0)
        return 0;

    return std::abs(a * b) / ggT(a, b);
}

};
