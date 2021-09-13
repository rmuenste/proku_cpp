#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <ex_assert.hpp>
#include <cmath>

namespace ex {

    double X() {

        double x = 0.0;

        for (int k = 1; k <= 8; ++k) {
            x += 1.0 / 8.0;
        }

        return x;
    }

    double Y() {

        double y = 0.0;

        for (int k = 1; k <= 10; ++k) {
            y += 1.0 / 10.0;
        }

        return y;
    }

    double BBP_PI() {

        double PI_CURR = 0.0, PI_LAST = PI_CURR;
        int k = 0;
        double factor = 1.0;
        do {
            PI_LAST = PI_CURR;

            double k_fac = static_cast<double>(k);
            double EightK = 8.0 * k_fac;
            double termA = ( 4.0 / (EightK + 1.0) )  - ( 2.0 / (EightK + 4.0) ) - ( 1.0 / (EightK + 5.0) ) - ( 1.0 / (EightK + 6.0) );

            PI_CURR += factor * termA;

            factor *= 1.0 / 16.0;
            
            ++k;
            std::cout << "PI_APPROX(16) = " << std::setprecision(16) << PI_CURR << std::endl;
        } while (PI_CURR != PI_LAST);

        return PI_CURR;
    }

    void primeErathosthenes() {
        constexpr int N = 100;
        bool A[N+1];

        int sqrN = static_cast<int>(std::sqrt(static_cast<double>(N)));

        for (int i(0); i <= N; ++i)
            A[i] = false;

        for (int i(2); i <= sqrN; ++i) {
            if (!A[i]) {
                std::cout << i << " ";

                for (int j(i* i); j <= N; j=j+i) {
                    A[j] = true;
                }
            }

        }

        for (int i(sqrN + 1); i <= N; ++i) {
            if (!A[i]) {
                std::cout << i << " ";
            }
        }

        std::cout << std::endl;

    }

};

using namespace ex;

int main(int argc, char* argv[]) {

    ex_HEADLINE("EX1A");
    ex_EMPTY_LINE(2);
    std::cout << "  SumX = " << X() << "    |  SumY = " << Y() << std::endl;
    std::cout << "  1.0 - SumX = " << 1.0 - X() << "    |  1.0 - SumY = " << 1.0 - Y() << std::endl;
    std::cout << "  SumX == SumY : " << COMP(X(), Y()) << std::endl;

    ex_EMPTY_LINE(2);
    ex_HEADLINE("EX1B");
    ex_EMPTY_LINE(2);

    BBP_PI();

    ex_EMPTY_LINE(2);
    ex_HEADLINE("EX1C");
    ex_EMPTY_LINE(2);
    primeErathosthenes();

    return EXIT_SUCCESS;
}