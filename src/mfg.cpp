/*
Copyright (c) 2015 Máté Vágó
This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.
Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:
1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgement in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#include "mfg.hpp"

namespace mfg {
#ifdef MFG_ASSERTION
void ReportAssert(char* exp, char* file, char* baseFile, int line) {
    std::ofstream fout;
    fout.open("MfgLastAssert.txt", std::ios::out);
    if (!strcmp(file, baseFile)) {
        fout << "Assert(" << exp << ") failed in file " << file << ", line " << line << std::endl;
        printf("Assert(%s) failed in file %s, line %d\n", exp, file, line);
    }
    else {
        fout << "Assert(" << exp << ") failed in file " << file << " (included from " << baseFile << "), line " << line << std::endl;
        printf("Assert(%s) failed in file %s (included from %s), line %d\n", exp, file, baseFile, line);
    }
}
#endif // MFG_ASSERTION
}//mfg
