#ifndef _EX_ASSERT_H_
#define _EX_ASSERT_H_

#include <cassert>
#include <iostream>
#include <cstdlib>

namespace ex {

inline bool ASSERT_MESSAGE(const char* /*msg*/) {
    return false;
}

inline std::string COMP(double a, double b) {
    if (a == b)
        return "TRUE";
    else
        return "FALSE";
}

#define ex_EMPTY_LINE(count) \
       for (int i(0); i < count; ++i) \
         std::cout << std::endl; 

#define ex_HEADLINE(msg) \
       std::cout << "================================= " << msg << " =================================" << std::endl; 

#define ex_INTERNAL_ASSERT(expr, msg) assert( (expr) || ASSERT_MESSAGE (msg) )

#define ex_WARNING_UNFINISHED(msg) \
       std::cout << "Warning unfinished function used: " << msg << std::endl; 

#define ex_ERROR_END_UNFINISHED(msg) \
       std::cout << "Termination because of erronous unfinished function call: " << msg << std::endl; \
       std::exit(EXIT_FAILURE);

#if fc_USER_ASSERTION 
#define fc_USER_ASSERT(expr, msg)
#else
#define fc_USER_ASSERT(expr, msg)
#endif
       


}

#endif
