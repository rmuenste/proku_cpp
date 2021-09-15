#include "dbe.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <assert.h>
#include "aufgabe3ab/ggt.hpp"

namespace ex {

    void dbe(int d, int m, int p, int n) {

        std::cout << "d: " << d << std::endl;
        std::cout << "m: " << m << std::endl;
        std::cout << "p: " << p << std::endl;
        std::cout << "n: " << n << std::endl;

        // Calc 10^m;
        int tenPowerM = 1;
        for (int i(0); i < m; ++i) 
            tenPowerM *= 10;

        // Calc 10^n;
        int tenPowerN = 1;

        if ( n > 0 ) {
            for (int i(0); i < n; ++i) 
                tenPowerN *= 10;
            tenPowerN -= 1;
        }

        int nom = d * tenPowerN + p;
        int denom = tenPowerM * tenPowerN;

        int exGGT = ggT(nom, denom);

        if (exGGT > 1) {
            nom /= exGGT;
            denom /= exGGT;
        }

        std::cout << nom;
        if(denom > 1)
          std::cout << " / " << denom;

        std::cout << " = " << std::setprecision(15) << (double(nom) / double(denom)) << std::endl;



    }

};
